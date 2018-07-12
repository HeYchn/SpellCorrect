#include "socketIO.h"
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

SocketIO :: SocketIO(int sfd)
: _sfd(sfd)
{
	
}

size_t SocketIO :: readn(char* buf, size_t count){
	size_t nleft = count;
	char* tempBuf = buf;
	while(nleft > 0){
		int nread = read(_sfd, tempBuf, nleft);
		if(-1 == nread){
			if(EINTR == errno){
				continue;
			}
			return -1;
		}
		else if(0 == nread){
			break;
		}

		tempBuf += nread;
		nleft -= nread;
	}

	return (count - nleft);
}

size_t SocketIO :: writen(const char* buf, size_t count){
	size_t nleft = count;
	const char* tempBuf = buf;
	while(nleft > 0){
		int nread = write(_sfd, tempBuf, nleft);
		if(-1 == nread){
			if(EINTR == errno){
				continue;
			}
			return -1;
		}
		else if(0 == nread){
			break;
		}

		tempBuf += nread;
		nleft -= nread;
	}

	return (count - nleft);
}

size_t SocketIO :: recv_peek(char* buf, size_t count){
	int nread;
	do{
		nread = recv(_sfd, buf, count, MSG_PEEK);
	}while(-1 == nread && EINTR == errno);

	return nread;
}

size_t SocketIO :: readline(char* buf, size_t maxlen){
	size_t nleft = maxlen - 1;
	char* tempBuf = buf;
	size_t total = 0;
	while(nleft > 0){
		size_t nread = recv_peek(tempBuf, nleft);
		if(nread <= 0){
			return nread;
		}

		for(size_t i = 0; i != nread; ++i){
			if('\n' == tempBuf[i]){
				size_t nsize = i + 1;
				if(readn(tempBuf, nsize) != nsize){
					return -1;
				}
				tempBuf += nsize;
				total += nsize;
				*tempBuf = 0;
				return total;
			}
		}
		if(readn(tempBuf, nread) != nread){
			return -1;
		}
		tempBuf += nread;
		nleft -= nread;
		total += nread;
	}
	*tempBuf = 0;
	return maxlen - 1;
}
