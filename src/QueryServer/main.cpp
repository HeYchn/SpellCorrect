#include "tcpServer.h"
#include "threadPool.h"
#include "cache.h"
#include "mylog.h"
#include <iostream>

ThreadPool* threadpoolPtr = NULL;
Cache* cachePtr = NULL;

using namespace std;

class Query{

public:
	Query(const string& queryWord, const TcpConnectionPtr& conn)
	: _queryWord(queryWord)
	, _conn(conn)
	{

	}
	
	void process(){
		for(auto& ch : _queryWord){
			if(!isalpha(ch) && !isspace(ch)){
				_conn -> send("ERROR: Invalid Input");
				return ;
			}

			ch = tolower(ch);
		}

		vector<string> wordslist;
		wordslist = cachePtr -> searchFromCache(_queryWord);		
		
		string buf;

		cout << _queryWord << endl;
		cout << "---------" << endl;
		for(auto& word : wordslist){
			buf.append(word);
			buf.append(" ");
			cout << word << endl;
		}
		cout << "---------" << endl;
		_conn -> sendInLoop(buf);
	}

private:
	string _queryWord;
	TcpConnectionPtr _conn;

};

void onConnection(const TcpConnectionPtr& conn){
	LogInfo("CONNECTION: %s", conn -> toString().c_str());
}

void onMessage(const TcpConnectionPtr& conn){
	string queryWord(conn -> receive());
	
	Query query(queryWord, conn);
	threadpoolPtr -> addTask(bind(&Query :: process, query));
}

void onClose(const TcpConnectionPtr& conn){
	LogInfo("DISCONNECTION: %s", conn -> toString().c_str());
}

int main(){
	ThreadPool threadpool(10, 20);
	threadpoolPtr = &threadpool;
	threadpool.start();
	
	Cache cache(10000, "/home/hey/code/SpellCorrect/conf/config.txt");
	cachePtr = &cache;
	
	TcpServer tcpServer("192.168.184.128", 1994);
	tcpServer.setConnectionCallback(&onConnection);
	tcpServer.setMessageCallback(&onMessage);
	tcpServer.setCloseCallback(&onClose);
	
	LogInfo("Syetem Online");
	tcpServer.start();
}
