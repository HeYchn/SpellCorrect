#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "MutexLock.h"

class Condition{

public:
	Condition(MutexLock& mutex)
	: _mutex(mutex)
	{
		pthread_cond_init(&_cond, NULL);
	}

	~Condition(){
		pthread_cond_destroy(&_cond);
	}

	void wait(){
		pthread_cond_wait(&_cond, _mutex.getMutexPtr());
	}

	void notify(){
		pthread_cond_signal(&_cond);
	}

	void notifyAll(){
		pthread_cond_broadcast(&_cond);
	}

private:
	MutexLock _mutex;
	pthread_cond_t _cond;

};

#endif
