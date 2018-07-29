#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int calEditDistance(const string& queryWord, const string& alterWord){
	vector<string> hanzi1;
	vector<string> hanzi2;
	string temp;

	int len1 = queryWord.size();
	int len2 = alterWord.size();

	if(queryWord[0] < 0){
		len1 = queryWord.size() / 3;
		for(auto it = queryWord.begin(); it != queryWord.end(); ++it){
			for(int i = 0; i < 3; i++){
				temp.push_back(*it);
				cout << temp << endl;
			}
			hanzi1.push_back(temp);
		}
	}
	
	if(alterWord[0] < 0){
		len2 = alterWord.size() / 3;
		for(auto it = alterWord.begin(); it != alterWord.end(); ++it){
			for(int i = 0; i < 3; i++){
				temp.push_back(*it);
			}
			hanzi2.push_back(temp);
		}
	}
	
	int d[len1 + 1][len2 + 1];
	for(int i = 0; i <= len1; ++i){
		d[i][0] = i;
	}
	for(int j = 0; j <= len2; ++j){
		d[0][j] = j;
	}

	for(int i = 1; i <= len1; ++i ){
		for(int j = 1; j <= len2; ++j){
			int flag = (hanzi1[i - 1] == hanzi2[i - 1] ? 0 : 1);
			int del = d[i - 1][j] + 1;
			int ins = d[i][j - 1] + 1;
			int mod = d[i - 1][j - 1] + flag;
			d[i][j] = min({del, ins, mod});
		}
	}

	return d[len1][len2];
}

int main(){
	string queryWord;
	string alterWord;
	
	
	while(cin >> queryWord >> alterWord){
		cout << "The editDistance is " << calEditDistance(queryWord, alterWord) << endl;
	}	
}
