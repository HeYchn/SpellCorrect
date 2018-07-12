#ifndef _INETADDRESS_H__
#define _INETADDRESS_H__

#include <netinet/in.h>
#include <string>

using namespace std;

class InetAddress{

public:
	InetAddress(short port);
	InetAddress(const char* ip, short port);
	InetAddress(const struct sockaddr_in& addr);

	const struct sockaddr_in* getAddrPtr() const;
	string ip() const;
	short port() const;

private:
	struct sockaddr_in _addr;
};

#endif
