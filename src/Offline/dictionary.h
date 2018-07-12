#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Dictionary
{

public:	
	void read(const string& filename);
	void store(const string& filename);

private:
	void processWord(string& word);

private:
	map<string, int> _dictionary;
};


#endif
