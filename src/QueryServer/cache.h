#ifndef __CACHE_H__
#define __CACHE_H__

#include "result.h"
#include "MutexLock.h"
#include <deque>

using namespace std;

class Cache{

public:
	Cache(size_t, const string&);

	vector<string> searchFromCache(const string&);
	size_t size();

private:
	void insertToCache(string, vector<string>);
	void removeFromCache();
	
private:
	deque<pair<string, vector<string>>> _cache;
	size_t _capacity;
	Result _result;
	MutexLock _mutex;
};

#endif
