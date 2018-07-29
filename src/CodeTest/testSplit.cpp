#include "SplitTool.h"


int main(){
	const string& dic_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/jieba.dict.utf8");
	const string& model_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/hmm_model.utf8");
	const string& user_dict_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/user.dict.utf8");
	const string& idfPath("/home/hey/code/cppJIEBA/cppjieba-master/dict/idf.utf8");
	const string& stopWordPath("/home/hey/code/cppJIEBA/cppjieba-master/dict/stop_words.utf8");

	SplitTool split(dic_path, model_path, user_dict_path, idfPath, stopWordPath);
	
	string line;

	while(cin >> line){
		split.Cut(line);
		vector<string> temp = split.getResult();
		for(auto& word : temp){
			cout << word << endl;
		}
	}

	return 0;
}
