#include "dictionary.h"
#include <string.h>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Dictionary :: Dictionary(const string& dict_path,
						 const string& model_path,
						 const string& user_dict_path,
						 const string& ifdPath,
						 const string& stopWordPath)
: _split(dict_path, model_path, user_dict_path, ifdPath, stopWordPath)
{

}

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

void Dictionary :: readZH(const string& filename)
{
	ifstream ifs(filename);
	if(!ifs){
		cout << "ifstream open error!" << endl;
		return;
	}

	string line;
	while(getline(ifs, line)){
		vector<string> temp;
		_split.Cut(line);
		temp = _split.getResult();

		for(auto& ciyu : temp){
			processCiyu(ciyu);
		}
	}
	ifs.close();
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

void Dictionary :: processCiyu(string& ciyu)
{
	if(ciyu[0] > 0 || ciyu.size() == 3 || ciyu.size() == 4){
		return;
	}

	auto it = _dictionary.find(ciyu);
	if(it != _dictionary.end()){
		++(it -> second);
	}
	else{
		_dictionary.insert(std :: make_pair(ciyu, 1));
	}
}
