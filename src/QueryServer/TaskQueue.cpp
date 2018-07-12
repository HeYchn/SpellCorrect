#include "taskQueue.h"

TaskQueue :: TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _flag(true)
{
}

void TaskQueue :: push(Task task){
	MutexLockGuard autoLock(_mutex);

	while(full()){
		_notFull.wait();
	}

	_que.push(task);
	_notEmpty.notify();
}

Task TaskQueue :: pop(){
	MutexLockGuard autoLock(_mutex);

	while(_flag && empty()){
		_notEmpty.wait();
	}
	
	if(_flag){
		Task task = _que.front();
		_que.pop();
		_notFull.notify();
		return task;
	}
	else{
		return NULL;
	}
}

void TaskQueue :: wakeup(){
	_flag = false;
	_notEmpty.notifyAll();
}

bool TaskQueue :: empty(){
	return _que.size() == 0;
}

bool TaskQueue :: full(){
	return _que.size() == _queSize;
}


