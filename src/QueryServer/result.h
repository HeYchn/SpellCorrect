#ifndef __RESULT_H__
#define __RESULT_H__

#include "config.h"
#include <queue>
#include <vector>

using namespace std;

struct alterWord{
	string word;
	int editDistance;
	int frequency;
};

struct cmp{
	bool operator()(struct alterWord word1, struct alterWord word2){
		if(word1.editDistance != word2.editDistance){
			return (word1.editDistance > word2.editDistance);
		}
		else{
			if(word1.frequency != word2.frequency){
				return (word1.frequency > word2.frequency);
			}
			else{
				return word1.word > word2.word;
			}
		}
	}
};

class Result{

public:
	Result(const string&);

	vector<string> getResult(const string&);

private:
	void read();
	void makeWordsList();
	void clear();
	int calEditDistance(const string&);

private:
	string _queryWord;
	priority_queue<struct alterWord, vector<struct alterWord>, cmp> _resultList;
	vector<pair<string, int>> _alterWordsList;
	map<char, vector<pair<string, int>>> _indexTable;
	Config _config;
};

#endif
