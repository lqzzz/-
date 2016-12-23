#ifndef __MEMPOOL_
#define __MEMPOOL_
#include<stdint.h>
#include<stddef.h>
#include<string.h>

void* mem_alloc(size_t size);
void mem_free(void *ptr);
void* mem_calloc(int num,size_t size);
void* mem_realloc(void*,size_t);
#endif // !__MEMPOOL_
