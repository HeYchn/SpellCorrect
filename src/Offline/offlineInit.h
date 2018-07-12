#ifndef __OFFLINEINIT_H__
#define __OFFLINEINIT_H__

#include "dictionary.h"
#include "index.h"
#include "config.h"

class OfflineInit{

public:
	OfflineInit(const string&);
	
	void init();

private:
	Dictionary _dictionary;
	Index _index;
	Config _config;
};

#endif
