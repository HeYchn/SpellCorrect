#include "inetAddress.h"
#include <string.h>
#include <arpa/inet.h>

InetAddress :: InetAddress(short port){
	bzero(&_addr, sizeof(_addr));

	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = port;
}

InetAddress :: InetAddress(const char* ip, short port){
	bzero(&_addr, sizeof(_addr));

	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr(ip);
	_addr.sin_port = htons(port);
}

InetAddress :: InetAddress(const struct sockaddr_in& addr)
: _addr(addr)
{

}

string InetAddress :: ip() const{
	return string(inet_ntoa(_addr.sin_addr));
}

short InetAddress :: port() const{
	return ntohs(_addr.sin_port);
}

const struct sockaddr_in* InetAddress :: getAddrPtr() const{
	return &_addr;
}
