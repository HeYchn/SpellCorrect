#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using namespace std;

class Thread{
	
public:	
	using ThreadCallBack = function<void()>;
	
	Thread(ThreadCallBack cb);
	virtual ~Thread();

	void start();
	void join();

private:
	static void* pthFun(void* arg);
	
private:
	pthread_t _pthid;
	ThreadCallBack _cb;
	bool _isRunning;
};


#endif
