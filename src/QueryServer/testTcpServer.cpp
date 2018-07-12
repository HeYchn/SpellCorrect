#include "TcpServer.h"
#include "threadPool.h"
#include "result.h"
#include <iostream>

ThreadPool* threadpoolPtr = NULL;
Result* resultPtr = NULL;

using namespace std;

class Query{

public:
	Query(const string& queryWord, const TcpConnectionPtr& conn)
	: _queryWord(queryWord)
	, _conn(conn)
	{

	}
	
	void process(){
		vector<string> wordslist;
		wordslist = resultPtr -> getResult(_queryWord);

		cout << _queryWord << endl;
		cout << "---------" << endl;
		for(auto& word : wordslist){
			cout << word << endl;
		}
		cout << "---------" << endl;
		//_conn -> sendInLoop(_query);
	}

private:
	string _queryWord;
	TcpConnectionPtr _conn;

};

void onConnection(const TcpConnectionPtr& conn){
	cout << conn -> toString() << endl;
	conn -> send("welcome");
}

void onMessage(const TcpConnectionPtr& conn){
	string queryWord(conn -> receive());
	
	Query query(queryWord, conn);
	threadpoolPtr -> addTask(bind(&Query :: process, query));
}

void onClose(const TcpConnectionPtr& conn){
	cout << "close" << endl;
	cout << conn -> toString() << endl;
}

int main(){
	ThreadPool threadpool(10, 20);
	threadpoolPtr = &threadpool;
	threadpool.start();
	
	Result result("/home/hey/code/SpellCorrect/conf/config.txt");
	resultPtr = &result;
	
	TcpServer tcpServer("192.168.184.128", 1994);
	tcpServer.setConnectionCallback(&onConnection);
	tcpServer.setMessageCallback(&onMessage);
	tcpServer.setCloseCallback(&onClose);
	
	tcpServer.start();
}
