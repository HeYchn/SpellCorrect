#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "socket.h"
#include "socketIO.h"
#include <memory>

using namespace std;

class EpollPoller;
class TcpConnection;

typedef shared_ptr<TcpConnection> TcpConnectionPtr; 

class TcpConnection
: public enable_shared_from_this<TcpConnection>
{

public:
	typedef function<void(const TcpConnectionPtr&)> TcpConnectionCallback;

	TcpConnection(int sfd, EpollPoller* loop);
	~TcpConnection();

	string receive();
	void send(const string& msg);
	void sendInLoop(const string& msg);
	void shutdown();

	string toString();
	
	void setConnectionCallback(TcpConnectionCallback cb);	
	void setMessageCallback(TcpConnectionCallback cb);	
	void setCloseCallback(TcpConnectionCallback cb);	

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();
	
private:
	Socket _sfd;
	SocketIO _socketIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;
	EpollPoller* _loop;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};

#endif
