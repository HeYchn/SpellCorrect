#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "MutexLock.h"
#include "acceptor.h"
#include "tcpConnection.h"
#include <vector>
#include <map>

class EpollPoller{
	
public:
	typedef TcpConnection :: TcpConnectionCallback EpollCallback;
	typedef function<void()> Functor;

	EpollPoller(Acceptor& acceptor);
	~EpollPoller();

	void loop();
	void unloop();
	void runInLoop(const Functor&& cb);
	void doPendingFunctors();
	void wakeup();

	void setConnectionCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);

private:
	int createEpollFd();
	int createEventFd();
	void addEpollFdRead(int epollfd, int fd);
	void delEpollFdRead(int epollfd, int fd);

	size_t recvPeek(int socketfd, void* buf, size_t len);
	bool isConnectionClosed(int socketfd);
	
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int peerfd);
	void handleRead();
private:
	Acceptor& _acceptor;
	int _epollfd;
	int _eventfd;
	int _listenfd;
	bool _isLooping;

	MutexLock _mutex;
	
	vector<Functor> _pendingFunctors;

	typedef vector<struct epoll_event> EventList;
	EventList _eventList;

	typedef map<int, TcpConnectionPtr> ConnectionMap;
	ConnectionMap _connMap;

	EpollCallback _onConnectionCb;
	EpollCallback _onMessageCb;
	EpollCallback _onCloseCb;
};

#endif
