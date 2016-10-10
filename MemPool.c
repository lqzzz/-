#include "MemPool.h"
#include<stdlib.h>
#include<string.h>
#include<assert.h>
static MemList list = { 0,0,NULL,NULL };
#define PREFIX_SIZE sizeof(size_t)
#define SIZE_ALINE(__n) do{ \
	if((*__n)&(sizeof(size_t)-1)) *__n += sizeof(size_t)-((*__n)&sizeof(size_t)-1);\
} while(0)

static void* CreateNode(size_t size)
{
	MemNode* node = malloc(sizeof(MemNode));
	assert(node);
	node->size_ = size;
	node->chunk_ = malloc(size);
	node->next_ = list.used_head;
	list.used_head = node;
	list.used_ += size;
	return node->chunk_;
}

void* Memalloc(unsigned int size)
{
	SIZE_ALINE(&size);
	if (list.free_ >= size)
	{
		for (MemNode **curr = &list.free_head; *curr;)
		{
			MemNode *node = *curr;
			if (node->size_ == size)
			{
				list.free_ -= size;
				*curr = node->next_;
				node->next_ = list.used_head;
				list.used_head = node;
				return node->chunk_;
			}
		}
		//return CreateNode(size);
	}
	return CreateNode(size);
}

void FreeMem(void *chunk)
{
	for (MemNode **curr = &list.used_head; *curr;)
	{
		MemNode* node = *curr;
		if (node->chunk_ == chunk)
		{
			*curr = node->next_;
			node->next_ = list.free_head;
			list.free_head = node;
			list.free_ += node->size_;
			list.used_ -= node->size_;
			memset(node->chunk_, 0, node->size_);
			return;
		}
		curr = &node->next_;
	}	
}
