#include "tcpConnection.h"
#include "epollPoller.h"
#include <string.h>

TcpConnection :: TcpConnection(int sfd, EpollPoller* loop)
: _sfd(sfd)
, _socketIO(sfd)
, _localAddr(Socket :: getLocalAddr(sfd))
, _peerAddr(Socket :: getPeerAddr(sfd))
, _isShutdownWrite(false)
, _loop(loop)
{
	_sfd.setNonblock();
}

TcpConnection :: ~TcpConnection()
{
	if(!_isShutdownWrite){
		_isShutdownWrite = true;
		shutdown();
	}
}

string TcpConnection :: receive(){
	char buf[65536];
	bzero(buf, sizeof(buf));
	size_t ret = _socketIO.readline(buf, sizeof(buf));

	if(0 == ret){
		return string();
	}
	else{
		return string(buf);
	}
}

void TcpConnection :: send(const string& msg){
	_socketIO.writen(msg.c_str(), msg.size());
}

void TcpConnection :: sendInLoop(const string& msg){
	_loop -> runInLoop(bind(&TcpConnection :: send, this, msg));
}

void TcpConnection :: shutdown(){
	if(!_isShutdownWrite){
		_sfd.shutdownWrite();
	}

	_isShutdownWrite = true;
}

string TcpConnection :: toString(){
	char str[100];
	snprintf(str, sizeof(str), "%s:%d -> %s:%d",
			 _localAddr.ip().c_str(),
			 _localAddr.port(),
			 _peerAddr.ip().c_str(),
			ntohs( _peerAddr.port()));

	return string(str);
}

void TcpConnection :: setConnectionCallback(TcpConnectionCallback cb){
	_onConnectionCb = cb;
}

void TcpConnection :: setMessageCallback(TcpConnectionCallback cb){
	_onMessageCb = cb;
}

void TcpConnection :: setCloseCallback(TcpConnectionCallback cb){
	_onCloseCb = cb;
}

void TcpConnection :: handleConnectionCallback(){
	if(_onConnectionCb){
		_onConnectionCb(shared_from_this());
	}
}

void TcpConnection :: handleMessageCallback(){
	if(_onMessageCb){
		_onMessageCb(shared_from_this());
	}
}

void TcpConnection :: handleCloseCallback(){
	if(_onCloseCb){
		_onCloseCb(shared_from_this());
	}
}

