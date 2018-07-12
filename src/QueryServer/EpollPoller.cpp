#include "epollPoller.h"
#include "socketIO.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <assert.h>
#include <sys/eventfd.h>
#include <iostream>

using namespace std;

EpollPoller :: EpollPoller(Acceptor& acceptor)
: _acceptor(acceptor)
, _epollfd(createEpollFd())
, _eventfd(createEventFd())
, _listenfd(acceptor.fd())
, _isLooping(false)
, _eventList(1024)
{
	addEpollFdRead(_epollfd, _listenfd);
	addEpollFdRead(_epollfd, _eventfd);
}

EpollPoller :: ~EpollPoller(){
	close(_epollfd);
}

void EpollPoller :: loop(){
	_isLooping = true;
	while(_isLooping){
		waitEpollfd();
	}
}

void EpollPoller :: unloop(){
	if(_isLooping){
		_isLooping = false;
	}
}

void EpollPoller :: setConnectionCallback(EpollCallback cb){
	_onConnectionCb = cb;
}

void EpollPoller :: setMessageCallback(EpollCallback cb){
	_onMessageCb = cb;
}

void EpollPoller :: setCloseCallback(EpollCallback cb){
	_onCloseCb = cb;
}

int EpollPoller :: createEpollFd(){
	int epollfd = epoll_create1(0);
	if(-1 == epollfd){
		perror("ERROR: epoll_create1");
		return -1;
	}

	return epollfd;
}

int EpollPoller :: createEventFd(){
	int eventfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if(-1 == eventfd){
		perror("ERROR: eventfd.");
		return -1;
	}

	return eventfd;
}

void EpollPoller :: addEpollFdRead(int epollfd, int fd){
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	if(-1 == ret){
		perror("ERROR: epoll_ctl add.");
		return ;
	}
}

void EpollPoller :: delEpollFdRead(int epollfd, int fd){
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
	if(-1 == ret){
		perror("ERROR: epoll_ctl del.");
		return ;
	}

}

//预览数据//
size_t EpollPoller :: recvPeek(int socketfd, void* buf, size_t len){
	int nread;
	do{
		nread = recv(socketfd, buf, len, MSG_PEEK);
	}
	while(-1 == nread && EINTR == errno);

	return nread;
}

//通过预览数据判断conn是否关闭//
bool EpollPoller :: isConnectionClosed(int socketfd){
	char buf[1024];
	int nread = recvPeek(socketfd, buf, sizeof(buf));
	if(-1 == nread){
		perror("ERROR: recvPeek.");
		return true;
	}

	return( 0 == nread);
}

void EpollPoller :: waitEpollfd(){
	int nready;
	do{
		nready = epoll_wait(_epollfd, &(*_eventList.begin()), _eventList.size(), -1);
	}
	while(-1 == nready && EINTR == errno);

	if(-1 == nready){
		perror("ERROR: epoll_wait.");
		return ;
	}
	else{
		//扩容//
		if(nready == static_cast<int>(_eventList.size())){
			_eventList.resize(_eventList.size() * 2);
		}

		for(int i = 0; i != nready; ++i){
			if(_listenfd == _eventList[i].data.fd){
				if(_eventList[i].events & EPOLLIN){
					handleConnection();
				}
			}
			else if(_eventfd == _eventList[i].data.fd){
				handleRead();
				doPendingFunctors();
				

				cout << "im done" << endl;
			}
			else{
				if(_eventList[i].events & EPOLLIN){
					handleMessage(_eventList[i].data.fd);
				}
			}
		}
	}
}

void EpollPoller :: handleConnection(){
	int peerfd = _acceptor.accept();
	addEpollFdRead(_epollfd, peerfd);

	TcpConnectionPtr conn(new TcpConnection(peerfd, this));
	conn -> setConnectionCallback(_onConnectionCb);
	conn -> setMessageCallback(_onMessageCb);
	conn -> setCloseCallback(_onCloseCb);

	pair<ConnectionMap :: iterator, bool> ret;
	ret = _connMap.insert(make_pair(peerfd, conn));
	assert(true == ret.second);
	(void)ret;

	conn -> handleConnectionCallback();		
}

void EpollPoller :: handleMessage(int peerfd){
	bool isClosed = isConnectionClosed(peerfd);
	ConnectionMap :: iterator it = _connMap.find(peerfd);
	assert(it != _connMap.end());

	if(isClosed){
		it -> second -> handleCloseCallback();
		delEpollFdRead(_epollfd, peerfd);
		_connMap.erase(it);
	}
	else{
		it -> second -> handleMessageCallback();
	}
}

void EpollPoller :: runInLoop(const Functor&& cb){
	{
		MutexLockGuard autoLock(_mutex);
		_pendingFunctors.push_back(move(cb));
	}

	wakeup();
}

void EpollPoller :: doPendingFunctors(){
	vector<Functor> temp;

	{
		MutexLockGuard autoLock(_mutex);
		temp.swap(_pendingFunctors);
	}
	for(auto& functor : temp){
		functor();
	}

	cout << "doPendingFunctors" << endl;
}

void EpollPoller :: handleRead(){
	uint64_t flag;
	
	int ret = read(_eventfd, &flag, sizeof(flag));
	if(ret != sizeof(flag)){
		perror("ERROR: read.");
	}
}

void EpollPoller :: wakeup(){
	uint64_t flag = 1;

	int ret = write(_eventfd, &flag, sizeof(flag));
	if(ret != sizeof(flag)){
		perror("ERROR: wakeup.");
	}	
}
