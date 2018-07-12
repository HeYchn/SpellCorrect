#include "index.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void Index :: read(const string& filename){
	ifstream ifs(filename);
	string line;
	string word;
	int frequency;

	while(getline(ifs, line)){
		istringstream iss(line);
		iss >> word;
		iss >> frequency;

		for(auto& ch : word){
			auto it = find(_index[ch].begin(), _index[ch].end(), make_pair(word, frequency));
			if(it != _index[ch].end()){
				continue;
			}

			_index[ch].push_back(make_pair(word, frequency));
		}
	}
}

void Index :: store(const string& filename){
	ofstream ofs(filename);
	for(auto it = _index.begin(); it != _index.end(); ++it){
		ofs << (*it).first << " ";
		for(auto& word : (*it).second){
			ofs << word.first << " " << word.second << " / ";
		}
		ofs << endl;
	}
}

