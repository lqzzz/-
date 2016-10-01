#include "dict.h"

Dict* DictCreate()
{
	Dict* dic_ = (Dict*)malloc(sizeof(Dict));

	assert(malloc);

	return dic_;
}

void DictAdd(DictEntry * dict_entry)
{
	
}

void DictReplace(DictEntry * dict_entry)
{
}

DictEntry * DictFatchValue(void * key)
{
	return nullptr;
}

void DictDelete(void * key)
{
}
