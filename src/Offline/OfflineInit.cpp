#include "offlineInit.h"

const string& dic_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/jieba.dict.utf8");
const string& model_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/hmm_model.utf8");
const string& user_dict_path("/home/hey/code/cppJIEBA/cppjieba-master/dict/user.dict.utf8");
const string& idfPath("/home/hey/code/cppJIEBA/cppjieba-master/dict/idf.utf8");
const string& stopWordPath("/home/hey/code/cppJIEBA/cppjieba-master/dict/stop_words.utf8");



OfflineInit :: OfflineInit(const string& filePath)
: _dictionary(dic_path, model_path, user_dict_path, idfPath, stopWordPath)
, _config(filePath)
{

}

void OfflineInit :: init(){
	_dictionary.read(_config.getEngSourcePath());
	_dictionary.store(_config.getEngDictionaryPath());

	_dictionary.restart();
	_dictionary.readZH(_config.getZhSourcePath());
	_dictionary.store(_config.getZhDictionaryPath());
	
//	_index.read(_config.getEngDictionaryPath());
//	_index.store(_config.getEngIndexPath());
};
