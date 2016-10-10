
#ifndef __DICT_H
#define __DICT_H


#define DICT_OK 0
#define DICT_ERR 1
#define HT_SIZE 97
typedef struct DictEntry 
{
	void *key_;
	void *value_;
	struct DictEntry *next_;
}DictEntry;

typedef struct DictHt 
{
	DictEntry **table_;
	unsigned long size_;
	unsigned long size_mask;
	unsigned long used_;
}DictHt;

typedef struct DictType 
{
	unsigned int(*hash_funtion)(const void *key);
	/*void *(*key_dup)(const void* key, void* privdata);
	void *(*value_dup)(const void* key, void* privdata);*/
	void *(*key_dup)(const void* key);
	void *(*value_dup)(const void* key);
	//int(*key_compare)(const void* key1, const void* key2, void* privdata);
	int(*key_compare)(const void* key1, const void* key2);
	/*int(*key_destructor)(void *key, void* privdata);
	int(*value_destructor)(void *value, void *privdata);*/
	int(*key_destructor)(void *key);
	int(*value_destructor)(void *value);

}DictType;

typedef struct Dict 
{

	DictType *type_;

	void *privdata_;

	DictHt *ht_;

	//int rehash;
}Dict;

#define DictHashKey(d,key) (d)->type_->hash_funtion(key)

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
		FreeMem((entry)->key_); \
} while(0)

#define DictFreeValue(d,entry) do { \
	if((d)->type_->value_destructor) \
		(d)->type_->value_destructor((entry)->value_); \
	else \
		FreeMem((entry)->value_); \
}while(0)

#define DictCompareHashKey(d,key_1,key_2)\
	(((d)->type_->key_compare) ? \
		(d)->type_->key_compare(key_1,key_2) : \
		((key_1)==(key2)))

DictEntry* DicEntryCreate();
Dict* DictCreate();
int DictInit(Dict *dict,const DictType *type);
void* DictAdd(const Dict *const, void *const, void *const);
int DictReplace(const Dict *const, const void *key, const void *value);
void* DictFatchValue(const Dict *const dict, const void *const key);
int DictDelete(const Dict *const dict,const void *const key);

#endif /* __DICT_H */