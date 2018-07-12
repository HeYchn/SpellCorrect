#include "offlineInit.h"

OfflineInit :: OfflineInit(const string& filePath)
: _config(filePath)
{

}

void OfflineInit :: init(){
	_dictionary.read(_config.getEngSourcePath());
	_dictionary.store(_config.getEngDictionaryPath());

	_index.read(_config.getEngDictionaryPath());
	_index.store(_config.getEngIndexPath());
};
