#pragma once
#include<assert.h>
#include<stdlib.h>
typedef struct DictEntry {
	void *key_;
	void *value_;
	struct DictEntry *next_;
}DictEntry;

typedef struct DictHt {
	DictEntry **table_;
	unsigned long size_;
	unsigned long size_mask;
	unsigned long used_;
}DictHt;

typedef struct DictType {

	unsigned int(*hash_funtion)(const void *key);
	void *(*key_dup)(const void* key, void* privdata);
	void *(*value_dup)(const void* key, void* privdata);
	int(*key_compare)(const void* key1, const void* key2, void* privdata);
	int(*key_destructor)(void *key, void* privdata);
	int(*value_destructor)(void *value, void *privdata);

}DictType;

typedef struct Dict {

	DictType &type_;

	void *privdata_;

	DictHt ht_;

	//int rehash;
}Dict;


Dict* DictCreate();
void DictAdd(DictEntry* dict_entry);
void DictReplace(DictEntry* dict_entry);
DictEntry* DictFatchValue(void* key);
void DictDelete(void* key);
