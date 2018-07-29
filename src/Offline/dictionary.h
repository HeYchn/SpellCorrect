#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "SplitTool.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Dictionary
{

public:
	Dictionary(const string& dict_path,
			   const string& model_path,
			   const string& user_dict_path,
			   const string& ifdPath,
			   const string& stopWordPath);
	
	void read(const string& filename);	
	void readZH(const string& filename);

	void store(const string& filename);

	void restart(){
		map<string, int> temp;
		swap(temp, _dictionary);
	}

private:
	void processWord(string& word);
	void processCiyu(string& word);

private:
	map<string, int> _dictionary;
	SplitTool _split;
};


#endif
