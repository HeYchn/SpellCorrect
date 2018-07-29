#ifndef __CACHE_H__
#define __CACHE_H__

#include "result.h"
#include "MutexLock.h"
#include <hiredis/hiredis.h>
#include <deque>

using namespace std;

class Cache{

public:
	Cache(const string&, int, Result&);
	vector<string> searchFromCache(const string&);

private:
	vector<string> insertIntoCache(const string&);
private:
	redisContext* _pContext;
	Result& _result;
};

#endif
