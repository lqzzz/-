#include "dict.h"
#include<stdio.h>
static int16_t dict_search_index(Dict* dict, void* key) {
	int16_t index_ = get_hash_code(key) % dict->ht_->size_;
	DictEntry *entry_ = dict->ht_->table_[index_];
	while (entry_) {
		if (DictMatchHashKey(dict, entry_->key_, key) == 0)
			return -1;
		entry_ = entry_->next_;
	}
	return index_;
}

int16_t get_hash_code(const char *str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
		hash = hash * seed + (*str++);
	return (hash & 0x7FFFFFFF);
}

DictEntry* dict_get_entry(const Dict *dict, const void *key){
	int index_ = get_hash_code(key) % dict->ht_->size_;
	DictEntry *entry_ = dict->ht_->table_[index_];
	while (entry_) {
		if (DictMatchHashKey(dict, entry_->key_, key) == 0) {
			return entry_;
		}
		entry_ = entry_->next_;
	}
	return NULL;
}

Dict* dict_create(DictType *Type){
	Dict *dic_ = mem_alloc(sizeof(Dict));
	dic_->type_ = Type;
	dic_->ht_ = mem_alloc(sizeof(DictHt) + HT_SIZE * sizeof(size_t));
	dic_->ht_->size_ = HT_SIZE;
	dic_->ht_->mask_ = HT_SIZE - 1;
	dic_->ht_->used_ = 0;
	DictHt *t = dic_->ht_;
	for (int i = 0; i < HT_SIZE; ++i)
		t->table_[i] = NULL;
	dic_->privdata_ = NULL;
	return dic_;
}

int16_t dict_add_entry(const Dict* dict,const void* key,const void* value){
	DictEntry *entry_ = dict_add_key(dict,key);
	if (entry_ == NULL)
		return DICT_ERR;
	DictSetHashValue(dict, entry_,value);
	return DICT_OK;
}

DictEntry* dict_add_key(const Dict *dict, const void* key){
	int index_ = dict_search_index(dict, key);
	if (index_ == -1)
		return NULL;
	DictEntry **ht_head = dict->ht_->table_ + index_;
	DictEntry *entry_ = mem_alloc(sizeof(DictEntry));
	DictSetHashKey(dict, entry_, key);
	entry_->next_ = *ht_head;
	*ht_head = entry_;
	return *ht_head;
}

//int dict_replace(const Dict *dict, void *key, void *value){
//	void *target = dict_add(dict, key, value);
//	if (*(int*)target == DICT_OK)
//		return DICT_OK;
//	DictEntry *target_entry = (DictEntry*)target;
//	DictFreeKey(dict, target_entry);
//	DictFreeValue(dict, target_entry);
//	DictSetHashKey(dict, target_entry,key);
//	DictSetHashValue(dict, target_entry,value);
//	return DICT_OK;
//}

void* dict_get_value(const Dict *dict, const void * key){
	DictEntry *target_ = dict_get_entry(dict, key);
	return target_ ? target_->value_ : NULL;
}

int dict_delete(const Dict* dict, const void* key){
	DictEntry *target_entry;
	if (target_entry = dict_get_entry(dict,key)){
		DictFreeKey(dict, target_entry);
		DictFreeValue(dict, target_entry);
		return DICT_OK;
	}
	return DICT_ERR;
}
