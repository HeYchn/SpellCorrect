#include "cache.h"
#include <iostream>

using namespace std;

Cache :: Cache(const string& ip, int port, Result& result)
: _result(result)
{
	_pContext = redisConnect(ip.c_str(), port);
	if(NULL == _pContext || _pContext -> err){
		if(_pContext){
			cout << "Error: " << _pContext -> errstr << endl;
		}
		else{
			cout << "Can not allocate redis context." << endl;
		}
	}
	else{
		cout << "Connected to Redis." << endl;
	}
}

vector<string> Cache :: searchFromCache(const string& queryWord){
	vector<string> wordsList;
	
	redisReply *reply;	
	reply = static_cast<redisReply*>(redisCommand(_pContext, "SMEMBERS %s", queryWord.c_str()));
	
	if(reply -> elements != 0){
		for(size_t i = 0; i < reply -> elements; ++i){
			wordsList.push_back(reply -> element[i] -> str);
		}
	}
	else{
		wordsList = insertIntoCache(queryWord);
	}

	return wordsList;
	
}

vector<string> Cache :: insertIntoCache(const string& queryWord){
	vector<string> wordsList = _result.getResult(queryWord);	
	redisReply *reply;
	for(auto word : wordsList){
		reply = static_cast<redisReply*>(redisCommand(_pContext, "SADD %s %s", queryWord.c_str(), word.c_str()));
	}
	
	return wordsList;
}
