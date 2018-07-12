#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class MutexLock{

public:
	MutexLock(){
		pthread_mutex_init(&_mutex, NULL);
	}

	~MutexLock(){
		pthread_mutex_destroy(&_mutex);
	}

	void lock(){
		pthread_mutex_lock(&_mutex);
	}

	void unlock(){
		pthread_mutex_unlock(&_mutex);
	}

	pthread_mutex_t* getMutexPtr(){
		return &_mutex;
	}
	
private:
	pthread_mutex_t _mutex;

};

class MutexLockGuard{

public:
	MutexLockGuard(MutexLock& mutexlock)
	: _mutexlock(mutexlock)
	{
		_mutexlock.lock();		
	}

	~MutexLockGuard(){
		_mutexlock.unlock();
	}
	
private:
	MutexLock _mutexlock;
};


#endif
