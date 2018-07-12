#ifndef __INDEX_H__
#define __INDEX_H__

#include <vector>
#include <string>
#include <map>

using namespace std;

class Index{

public:
	void read(const string&);
	void store(const string&);

private:
	map<char, vector<pair<string, int>>> _index;

};

#endif
