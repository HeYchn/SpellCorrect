#include "thread.h"

Thread :: Thread(ThreadCallBack cb)
: _pthid(0)
, _cb(cb)
, _isRunning(false)
{
}

void Thread :: start(){
	if(_isRunning == false){
		pthread_create(&_pthid, NULL, pthFun, this);
	}

	_isRunning = true;
}

void Thread :: join(){
	if(_isRunning == true){
		pthread_join(_pthid, NULL);
	}

	_isRunning = false;
}

Thread :: ~Thread(){
	if(_isRunning == true){
		pthread_detach(_pthid);
	}

	_isRunning = false;
}

void* Thread :: pthFun(void* arg){
	Thread* pth = static_cast<Thread*> (arg);
	if(pth -> _cb){
		pth -> _cb();
	}

	return NULL;
}
