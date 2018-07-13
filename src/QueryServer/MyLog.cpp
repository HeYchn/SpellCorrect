#include "mylog.h"
#include <log4cpp/Appender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>

using namespace log4cpp;
using std :: cout;

MyLog* MyLog :: _pLog = NULL;

//单例模式下显式调用构造函数//
MyLog* MyLog :: logInit(){
	if(NULL == _pLog){
		_pLog = new MyLog ();
	}

	return _pLog;
}

//单例模式下显示调用析构函数//
void MyLog :: logShutDown(){
	if(_pLog){
		delete _pLog;
	}
}

//显式构造函数,日志信息输出到终端和回卷文件//
MyLog :: MyLog()
:_root(Category :: getRoot().getInstance("root"))
{
	//设置输出格式//
	PatternLayout *layoutForOs = new PatternLayout ();
	layoutForOs -> setConversionPattern("%d [%-5p] %m %n");
	PatternLayout *layoutForRollingFile = new PatternLayout ();
	layoutForRollingFile -> setConversionPattern("%d [%-5p] %m %n");

	OstreamAppender *osAppender = new OstreamAppender ("osStreamAppender", &cout);
	osAppender -> setLayout(layoutForOs);

	RollingFileAppender *rollingFileAppender = new RollingFileAppender (
		"rollingFileAppender", "/home/hey/code/SpellCorrect/log/Info.log", 20 * 1024 * 1024, 1); 
	rollingFileAppender -> setLayout(layoutForRollingFile);

	_root.addAppender(osAppender);
	_root.addAppender(rollingFileAppender);
	
	//设置优先级//
	_root.setPriority(Priority :: DEBUG);

}

//显式析构函数//
MyLog :: ~MyLog(){
	Category :: shutdown();
}

