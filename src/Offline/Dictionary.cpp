#include "dictionary.h"
#include <string.h>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void Dictionary::read(const string& filename)
{
	ifstream ifs(filename);
	if(!ifs) {
		cout << "ifstream open error!" << endl;
		return;
	}

	string line;
	while(getline(ifs, line))
	{
		istringstream iss(line);
		string word;
		while(iss >> word)
		{
			processWord(word);
		}
	}
	ifs.close();
}


void Dictionary::store(const string& filename)
{
	ofstream ofs(filename);
	if(!ofs){
		cout << "ofstream open error!" << endl;
		return;
	}

	for(auto& record : _dictionary)
	{
		ofs << record.first << " " << record.second << endl;
	}
	ofs.close();
}

void Dictionary::processWord(string& word)
{
	for(auto& ch : word)
	{
		if(!isalpha(ch)){
			return;
		}
		
		ch = tolower(ch);
	}
	
	auto it = _dictionary.find(word);
	if(it != _dictionary.end()){
		++(it -> second);
	}
	else{
		_dictionary.insert(std::make_pair(word, 1));
	}
}

