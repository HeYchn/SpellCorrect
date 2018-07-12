#include "config.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

Config :: Config(const string& filePath)
: _filePath(filePath)
{

}

void Config :: read(){
	ifstream ifs(_filePath);
	string line;

	while(getline(ifs, line)){
		istringstream iss(line);
		string index;
		string content;

		iss >> index;
		iss >> content;

		_config.insert(make_pair(index, content));

	}
}

string Config :: getEngSourcePath(){
	read();

	return _config["ENG_SOURCE"];	
}

string Config :: getZhSourcePath(){
	read();

	return _config["ZH_SOURCE"];	
}

string Config :: getEngDictionaryPath(){
	read();

	return _config["ENG_DICTIONARY"];	
}

string Config :: getZhDictionaryPath(){
	read();

	return _config["ZH_DICTIONARY"];	
}

string Config :: getEngIndexPath(){
	read();

	return _config["ENG_INDEX"];	
}

string Config :: getZhIndexPath(){
	read();

	return _config["ZH_INDEX"];	
}

