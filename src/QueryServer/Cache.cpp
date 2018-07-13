#include "cache.h"

Cache :: Cache(size_t capacity, const string& configPath)
: _capacity(capacity)
, _result(configPath)
{

}

vector<string> Cache :: searchFromCache(const string& queryWord){
	vector<string> wordsList;

	for(auto it = _cache.begin(); it != _cache.end(); ++it){
		if((*it).first == queryWord){
			swap(wordsList, (*it).second);
			_cache.erase(it);
			insertToCache(queryWord, wordsList);

			return wordsList;
		}
	}
	
	if(_cache.size() == _capacity){
		removeFromCache();
	}
	
	wordsList = _result.getResult(queryWord);
	insertToCache(queryWord, wordsList);

	return wordsList;
	
}

size_t Cache :: size(){
	return _cache.size();
}

void Cache :: insertToCache(string queryWord, vector<string> wordList){
	MutexLockGuard autoLock(_mutex);
	_cache.push_front(make_pair(queryWord, wordList));
}

void Cache :: removeFromCache(){
	MutexLockGuard autoLock(_mutex);
	_cache.pop_back();
}
