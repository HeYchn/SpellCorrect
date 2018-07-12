#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "thread.h"
#include "taskQueue.h"
#include <stdlib.h>
#include <memory>
#include <vector>

using namespace std;

class ThreadPool{
	
public:	
	ThreadPool(size_t, size_t);
	~ThreadPool();

	void start();
	void stop();
	void addTask(Task&&);

private:
	void threadFunc();
	Task getTask();
	
private:
	size_t _threadNum;
	vector<shared_ptr<Thread>> _threads;
	size_t _queSize;
	TaskQueue _taskQueue;
	bool _isExit;
};

#endif
