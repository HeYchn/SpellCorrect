#include "threadPool.h"
#include <unistd.h>
#include <iostream>
#include <functional>

using namespace std;

ThreadPool :: ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQueue(queSize)
, _isExit(false)
{
	_threads.reserve(threadNum);
}

ThreadPool :: ~ThreadPool(){
	if(!_isExit){
		stop();		
	}
}

void ThreadPool :: start(){
	for(size_t i = 0; i < _threadNum; ++i){
		shared_ptr<Thread> pThread(new Thread(bind(&ThreadPool :: threadFunc, this)));
		_threads.push_back(move(pThread));
	}

	for(auto& thread : _threads){
		thread -> start();
	}
}

void ThreadPool :: stop(){
	if(!_isExit){
		while(_taskQueue.empty()){
			sleep(1);
		}
		_isExit = true;
		_taskQueue.wakeup();

		for(auto& thread : _threads){
			thread -> join();
		}

	}
}

void ThreadPool :: addTask(Task&& task){		
	_taskQueue.push(move(task));
}

Task ThreadPool :: getTask(){
	Task task = _taskQueue.pop();
	return task;
}

void ThreadPool :: threadFunc(){
	if(!_isExit){
		Task task = getTask();
		if(task){
			task();
		}
	}
}

