#ifndef __SPLITTOOL_H__
#define __SPLITTOOL_H__

#include "/home/hey/code/cppJIEBA/cppjieba-master/include/cppjieba/Jieba.hpp"

using namespace cppjieba;

class SplitTool{

public:
	SplitTool(const string& dict_path,
			  const string& model_path,
			  const string& user_dict_path,
			  const string& ifdPath,
			  const string& stopWordPath)
	: _jieba(dict_path, model_path, user_dict_path, ifdPath, stopWordPath)
	{

	}

	~SplitTool()
	{

	}

	void Cut(const string& sentence){
		_jieba.Cut(sentence, _result);
	}

	vector<string> getResult(){
		return _result;
	}

private:
	Jieba _jieba;
	vector<string> _result;

};

#endif

