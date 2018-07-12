#ifndef _SOCKETIO_H__
#define _SOCKETIO_H__

#include <stdio.h>

class SocketIO{

public:
	SocketIO(int sfd);

	size_t readn(char* buf, size_t count);
	size_t writen(const char* buf, size_t count);
	size_t readline(char* buf, size_t max_len);

private:
	size_t recv_peek(char* buf, size_t count);

private:
	int _sfd;
};

#endif
