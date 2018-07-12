#include "TcpServer.h"
#include "socket.h"

TcpServer :: TcpServer(const string& ip, short port)
: _acceptor(createSocketFd(), InetAddress(ip.c_str(), port))
, _poller(_acceptor)
{

}

TcpServer :: TcpServer(short port)
: _acceptor(createSocketFd(), InetAddress(port))
, _poller(_acceptor)
{

}

void TcpServer :: start(){
	_acceptor.ready();
	_poller.setConnectionCallback(_connectionCallback);
	_poller.setMessageCallback(_messageCallback);
	_poller.setCloseCallback(_closeCallback);
	_poller.loop();
}

void TcpServer :: stop(){
	_poller.unloop();
}

void TcpServer :: setConnectionCallback(TcpServerCallback cb){
	_connectionCallback = cb;
}

void TcpServer :: setMessageCallback(TcpServerCallback cb){
	_messageCallback = cb;
}

void TcpServer :: setCloseCallback(TcpServerCallback cb){
	_closeCallback = cb;
}

int TcpServer :: createSocketFd(){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == fd){
		perror("ERROR: Createfd.");
	}

	return fd;
}
