#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "epollPoller.h"

class TcpServer{

public:
	typedef EpollPoller :: EpollCallback TcpServerCallback; 

	TcpServer(const string& ip, short port);
	TcpServer(short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	int createSocketFd();

private:
	Acceptor _acceptor;
	EpollPoller _poller;

	TcpServerCallback _connectionCallback;
	TcpServerCallback _messageCallback;
	TcpServerCallback _closeCallback;
};

#endif
