#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using namespace std;

typedef function<void()> Task;

class TaskQueue{

public:
	TaskQueue(size_t queSize);
	
	void push(Task);
	Task pop();
	void wakeup();
	bool empty();
	bool full();

private:
	size_t _queSize;
	queue<Task> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;

};

#endif
