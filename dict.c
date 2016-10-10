#pragma once
#include "dict.h"
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include"MemPool.h"

static DictEntry* DictSearchEntry(const Dict *const dict, const void *const key)
{
	int index_ = DictHashKey(dict, key) & dict->ht_->size_mask;
	DictEntry *target_ = dict->ht_->table_[index_];
	while (target_->next_)
	{
		if (target_->key_ == key)
			return target_;
		target_ = target_->next_;
	}
	return target_;
}
DictEntry* DicEntryCreate()
{
	DictEntry *entry_ = calloc(HT_SIZE, sizeof(DictEntry));
	//DictEntry *entry_ = Memalloc(sizeof(DictEntry) * HT_SIZE);
	assert(entry_);
	//size_t size_ = 0;
	//for (; size_ < 97; size_++)
	//{
	//	entry_[size_].key_ = NULL;
	//	entry_[size_].value_ = NULL;
	//	entry_[size_].next_ = NULL;
	//}
	return entry_;
}

int DictInit(Dict *dict, const DictType *type)
{
	dict->type_ = type;
	return DICT_OK;
}
Dict* DictCreate()
{
	Dict *dic_ = Memalloc(sizeof(Dict));
	assert(dic_);
	dic_->ht_ = Memalloc(sizeof(DictHt));
	assert(dic_->ht_);
	dic_->ht_->size_mask = HT_SIZE - 1;
	dic_->ht_->size_ = 0;
	dic_->ht_->used_ = 0;
	dic_->privdata_ = NULL;
	dic_->ht_->table_ = Memalloc(sizeof(size_t));
	
	DictEntry *entry_ = DicEntryCreate();
	*dic_->ht_->table_ = entry_;
	DictEntry *e1 = *dic_->ht_->table_;
	DictEntry *e2 = *dic_->ht_->table_ + 1;
	DictEntry *e3 = *dic_->ht_->table_ + 2;
	DictEntry *e4 = *dic_->ht_->table_ + 3;
	DictEntry *e5 = *dic_->ht_->table_ + 96;

	/*DictEntry **head = dic_->ht_->table_;
	while (entry_->key_ == NULL)
		*head++ = entry_++;
	*dic_->ht_->table_ = *head;*/
	return dic_;
}

void* DictAdd(const Dict *const dict, void *const key, void *const value)
{
	DictEntry *key_entry;
	if ((key_entry = DictSearchEntry(dict, key)) == key)
		return key_entry;
	DictHt *ht = dict->ht_;
	DictEntry *new_entry = Memalloc(sizeof(DictEntry));
	key_entry->next_ = new_entry;
	ht->used_++;
	new_entry->key_ = key;
	new_entry->value_ = value;
	/*DictSetHashKey(dict, new_entry, key);
	DictSetHashValue(dict, new_entry, value);*/
	return DICT_OK;
}

int DictReplace(const Dict *const dict, void *key, void *value)
{
	void *target = DictAdd(dict, key, value);
	if (*(int*)target == DICT_OK)
		return DICT_OK;
	DictEntry *target_entry = (DictEntry*)target;
	DictFreeKey(dict, target_entry);
	DictFreeValue(dict, target_entry);
	DictSetHashKey(dict, target_entry,key);
	DictSetHashValue(dict, target_entry,value);
	return DICT_OK;
}

void* DictFatchValue(const Dict *const dict, const void *const key)
{
	DictEntry *target_ = DictSearchEntry(dict, key);
	if (target_)
		return target_->value_;
	else
		return NULL;
}

int DictDelete(const Dict *const dict, const void *const key)
{
	DictEntry *target_entry_ = DictSearchEntry(dict, key);
	if (target_entry_ != NULL)
	{
		dict->type_->key_destructor(target_entry_->key_);
		dict->type_->value_destructor(target_entry_->value_);
		return DICT_OK;
	}
	return DICT_ERR;
}
