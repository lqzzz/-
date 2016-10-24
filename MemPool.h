#ifndef __MEMPOOL_
#define __MEMPOOL_

typedef struct MemNode
{
	unsigned int size_;
	struct MemNode *next_;
	void* chunk_;
}MemNode;
typedef struct MemList
{
	unsigned int free_;
	unsigned int used_;
	MemNode *used_head;
	MemNode *free_head;
}MemList;

void* Memalloc(unsigned int size);
void FreeMem(void *ptr);
void* Memrealloc(void* address,unsigned int size);

#endif // !__MEMPOOL_
