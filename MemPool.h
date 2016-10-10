#ifndef __MEMPOOL_
#define __MEMPOOL_

typedef struct MemNode
{
	struct MemNode *next_;
	unsigned int size_;
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

#endif // !__MEMPOOL_
