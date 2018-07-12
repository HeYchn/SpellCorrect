#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <map>

using namespace std;

class Config{

public:	
	Config(const string&);
	
	string getEngSourcePath();
	string getZhSourcePath();
	string getEngDictionaryPath();
	string getZhDictionaryPath();
	string getEngIndexPath();
	string getZhIndexPath();

private:
	void read();
	
private:
	string _filePath;
	map<string, string> _config;	
};

#endif
