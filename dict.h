#ifndef __DICT_H
#define __DICT_H

#include "dict.h"
#include<string.h>
#include<assert.h>
#include"MemPool.h"
#include"str.h"

#define DICT_OK 0
#define DICT_ERR 1
#define HT_SIZE 97
typedef struct DictEntry {
	void *key_;
	void *value_;
	struct DictEntry *next_;
}DictEntry;

typedef struct DictHt {
	unsigned int size_;
	unsigned int mask_;
	unsigned int used_;
	DictEntry *table_[];
}DictHt;

typedef struct DictType {
	void *(*key_dup)(const void* key);
	void *(*value_dup)(const void* value);
	int(*key_match)(const void* key1, const void* key2);
	int(*value_destructor)(void *value);
	int(*key_destructor)(void *key);
}DictType;

typedef struct Dict {
	DictType *type_;
	void *privdata_;
	DictHt *ht_;
	//int rehash;
}Dict;

#define DictHashKey(key) get_hash_code(key)

#define DictSetHashValue(d, entry, _value_) do { \
    if ((d)->type_->value_dup) \
        entry->value_ = (d)->type_->value_dup(_value_); \
    else \
        entry->value_ = (_value_); \
} while(0)

#define DictSetHashKey(d, entry,_key_) do { \
    if ((d)->type_->key_dup) \
        entry->key_ = (d)->type_->key_dup(_key_); \
    else \
        entry->key_ = (_key_); \
} while(0)

#define DictFreeKey(d,entry) do { \
	if((d)->type_->key_destructor) \
		(d)->type_->key_destructor((entry)->key_); \
	else \
		mem_free((entry)->key_); \
} while(0)

#define DictFreeValue(d,entry) do { \
	if((d)->type_->value_destructor) \
		(d)->type_->value_destructor((entry)->value_); \
	else \
		mem_free((entry)->value_); \
}while(0)

#define DictMatchHashKey(d,key_1,key_2)\
	(((d)->type_->key_match) ? \
		(d)->type_->key_match(key_1,key_2) : \
		((key_1)==(key_2)))

Dict* dict_create(DictType *Type);
DictEntry* dict_add_key(const Dict *, const void *);
uint16_t dict_add_entry(const Dict *dict, const void* key, const void *value);
//int dict_replace(const Dict *, const void *key, const void *value);
void* dict_get_value(const Dict * dict, const void * key);
DictEntry* dict_get_entry(const Dict * dict, const void * key);
int dict_delete(const Dict * dict, const void * key);
int16_t get_hash_code(const char *str);

#endif /* __DICT_H */
//
//DictType* dict_type = mem_alloc(sizeof(DictType));
//dict_type->key_match = strcmp;
//dict_type->key_dup = NULL;
//dict_type->value_dup = NULL;
//Dict *dict = dict_create(dict_type);
//string key1 = str_new("key1");
//string value1 = str_new("value1");
//string key2 = str_new("key2");
//string value2 = str_new("value2");
//string key3 = str_new("key3");
//string value3 = str_new("value3");
//string key4 = str_new("key4");
//string value4 = str_new("value4");
//dict_add_entry(dict, key1, value1);
//dict_add_entry(dict, key2, value2);
//dict_add_entry(dict, key3, value3);
//string v1 = dict_get_value(dict, key1);
//string v2 = dict_get_value(dict, key2);
//string v3 = dict_get_value(dict, key3);
//string v4 = dict_get_value(dict, key4);
