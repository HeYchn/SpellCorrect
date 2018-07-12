#include "result.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

Result :: Result(const string& configPath)
: _config(configPath)
{
	read();
}

void Result :: read(){
	ifstream ifs(_config.getEngIndexPath());
	string line;

	while(getline(ifs, line)){
		istringstream iss(line);	
		char ch;
		string word;
		int frequent;
		string useless;
		iss >> ch;
		while(iss){
			iss >> word;
			iss >> frequent;
			iss >> useless;

			_indexTable[ch].push_back(make_pair(word, frequent));
		}
	}
}

void Result :: makeWordsList(){
	for(auto& ch : _queryWord){
		for(auto& word : _indexTable[ch]){
			_alterWordsList.push_back(word);
		}
	}
}

void Result :: clear(){
	while(!_resultList.empty()){
		_resultList.pop();
	}

	_alterWordsList.clear();
}

vector<string> Result :: getResult(const string& queryword){
	_queryWord = queryword;
	makeWordsList();
	
	struct alterWord tempWord;
	for(auto& wordInList : _alterWordsList){
		tempWord.word = wordInList.first;
		tempWord.editDistance = calEditDistance(wordInList.first);
		tempWord.frequency = wordInList.second;

		_resultList.push(tempWord);
	}
	
	vector<string> result;
	string lastWord;
	string currWord;
	int sum = 0;

	while(sum < 5){
		currWord = _resultList.top().word;
		_resultList.pop();

		if(currWord != lastWord){
			result.push_back(currWord);
			++sum;
		}
		lastWord = currWord;
	}
	
	clear();
	return result;
}
		
int Result :: calEditDistance(const string& alterWord){
	int len1 = _queryWord.size();
	int len2 = alterWord.size();
	
	int d[len1 + 1][len2 + 1];
	for(int i = 0; i <= len1; ++i){
		d[i][0] = i;
	}
	for(int j = 0; j <= len2; ++j){
		d[0][j] = j;
	}

	for(int i = 1; i <= len1; ++i ){
		for(int j = 1; j <= len2; ++j){
			int flag = (_queryWord[i - 1] == alterWord[i - 1] ? 0 : 1);
			int del = d[i - 1][j] + 1;
			int ins = d[i][j - 1] + 1;
			int mod = d[i - 1][j - 1] + flag;
			d[i][j] = min({del, ins, mod});
		}
	}

	return d[len1][len2];
}

#if 0

int main(){
	Result result("/home/hey/code/SpellCorrect/conf/config.txt");
	vector<string> wordlist;
	string queryword;

	while(cin >> queryword){
		wordlist = result.getResult(queryword);
		
		cout << "----------" << endl;
		for(auto& word : wordlist){
			cout << word << endl;
		}
		cout << "----------" << endl;
	}

	return 0;
}

#endif
