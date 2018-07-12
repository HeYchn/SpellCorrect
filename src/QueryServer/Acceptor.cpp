#include "acceptor.h"
#include <sys/socket.h>
#include <unistd.h>

Acceptor :: Acceptor(int listenfd, const InetAddress& addr)
: _listenSocket(listenfd)
, _addr(addr)
{

}

void Acceptor :: ready(){
	setReuseAddr(true);
	setReusePort(true);
	
	bind();
	listen();
}

int Acceptor :: accept(){
	int peerfd = ::accept(_listenSocket.fd(), NULL, NULL);
	
	if(-1 == peerfd){
		perror("ERROR: Accept.");
	}

	return peerfd;
}

int Acceptor :: fd(){
	return _listenSocket.Socket :: fd();
}

void Acceptor :: bind(){
	if(-1 == ::bind(_listenSocket.fd(), (const struct sockaddr*)_addr.getAddrPtr(), sizeof(InetAddress))){
		perror("ERROR: Bind.");
		close(_listenSocket.fd());
		return ;
	}
}

void Acceptor :: listen(){
	if(-1 == ::listen(_listenSocket.fd(), 10)){
		perror("ERROR: Listen.");
		close(_listenSocket.fd());
		return ;
	}
}

void Acceptor :: setReuseAddr(bool flag){
	int on = (flag ? 1 : 0);
	if(-1 == setsockopt(_listenSocket.fd(), SOL_SOCKET, SO_REUSEADDR, &on, static_cast<socklen_t>(sizeof(on)))){
		perror("ERROR: setReuseAddr.");
		close(_listenSocket.fd());
		return ;
	}
}

void Acceptor :: setReusePort(bool flag){
	int on = (flag ? 1 : 0);
	if(-1 == setsockopt(_listenSocket.fd(), SOL_SOCKET, SO_REUSEPORT, &on, static_cast<socklen_t>(sizeof(on)))){
		perror("ERROR: setReusePort.");
		close(_listenSocket.fd());
		return ;
	}
}
