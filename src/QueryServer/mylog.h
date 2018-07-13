#ifndef __MYLOG_H__
#define __MYLOG_H__

#include <log4cpp/Category.hh>
#include <string>

using std :: string;

class MyLog{

public:
	static MyLog* logInit();
	void logShutDown();

	template <typename... Args>
	void warn(const char* msg, Args... args){
		_root.warn(msg, args...);
	}

	template <typename... Args>
	void error(const char* msg, Args... args){
		_root.error(msg, args...);
	}

	template <typename... Args>
	void debug(const char* msg, Args... args){
		_root.debug(msg, args...);
	}

	template <typename... Args>
	void info(const char* msg, Args... args){
		_root.info(msg, args...);
	}

private:
	MyLog();
	~MyLog();

private:
	static MyLog *_pLog;
	log4cpp :: Category& _root;
	
};


//调用编译器提供的宏处理日志消息，使其提供文件名/函数名/行号信息//
//此处应用宏命令替换函数以保证函数名和行号的输出达到预期结果//
//注意行号转换成string类型，结果转为C型字符串//
#define MsgHandler(msg) string("[").append(__FILE__).append(" -> ").append(__FUNCTION__)\
	.append(" -> ").append("line ").append(std :: to_string(__LINE__)).append("] ").append(msg).c_str()

//借助宏命令简化调用过程//
#define LogWarn(msg, ...) MyLog :: logInit() -> warn(MsgHandler(msg), ##__VA_ARGS__)
#define LogError(msg, ...) MyLog :: logInit() -> error(MsgHandler(msg), ##__VA_ARGS__)
#define LogDebug(msg, ...) MyLog :: logInit() -> debug(MsgHandler(msg), ##__VA_ARGS__)
#define LogInfo(msg, ...) MyLog :: logInit() -> info(MsgHandler(msg), ##__VA_ARGS__)

#endif

