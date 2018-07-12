#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "socket.h"
#include "inetAddress.h"
class Acceptor{

public:
	Acceptor(int listenfd, const InetAddress& addr);

	void ready();
	int accept();

	int fd();

private:
	void bind();
	void listen();

	void setReuseAddr(bool on);
	void setReusePort(bool on);

private:
	Socket _listenSocket;
	InetAddress _addr;
};

#endif
