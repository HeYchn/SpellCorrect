#include "socket.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

Socket :: Socket()
: _sfd(createSocketFd())
{

}

Socket :: Socket(int sfd)
: _sfd(sfd)
{

}

Socket :: ~Socket(){
	close(_sfd);
}

void Socket :: setNonblock(){
	int flag = fcntl(_sfd, F_GETFL, 0);
	flag |= O_NONBLOCK;
	fcntl(_sfd, F_SETFL, flag);
}

void Socket :: shutdownWrite(){
	if(-1 == shutdown(_sfd, SHUT_WR)){
		perror("ERROR: Shutdown Write.");
	}
}

InetAddress Socket :: getLocalAddr(int sfd){
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(sockaddr_in);
	if(-1 == getsockname(sfd, (struct sockaddr*)&addr, &addrlen)){
		perror("ERROR: Getsockname.");
	}

	return InetAddress(addr);
}

InetAddress Socket :: getPeerAddr(int sfd){
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(sockaddr_in);
	if(-1 == getpeername(sfd, (struct sockaddr*)&addr, &addrlen)){
		perror("ERROR: Getpeername.");
	}

	return InetAddress(addr);
}

int Socket :: createSocketFd(){
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == fd){
		perror("ERROR: Createfd.");
	}

	return fd;
}

int Socket :: fd(){
	return _sfd;
}
