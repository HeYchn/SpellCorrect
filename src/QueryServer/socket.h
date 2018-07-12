#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "inetAddress.h"

class Socket{

public:
	Socket();
	Socket(int);
	~Socket();

	void shutdownWrite();
	void setNonblock();
	int fd();
	
	static InetAddress getLocalAddr(int sfd);
	static InetAddress getPeerAddr(int sfd);

private:
	int createSocketFd();

private:
	int _sfd;

};

#endif
