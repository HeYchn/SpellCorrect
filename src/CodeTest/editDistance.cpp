#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int calEditDistance(const string& queryWord, const string& alterWord){
	int len1 = queryWord.size();
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
			int flag = (queryWord[i - 1] == alterWord[i - 1] ? 0 : 1);
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
		cout << "size of queryWord : " << queryWord.size() << endl;
		cout << "size of alterWord : " << alterWord.size() << endl;

		cout << "The editDistance is " << calEditDistance(queryWord, alterWord) << endl;
	}
	
}
