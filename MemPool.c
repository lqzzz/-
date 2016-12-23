#include "MemPool.h"
#include<stdlib.h>
#include<assert.h>
#define PREFIX_SIZE sizeof(size_t)
#define SIZE_ALINE(__n) do{ \
	if((*__n)&(sizeof(size_t)-1)) *__n += sizeof(size_t)-((*__n)&sizeof(size_t)-1);\
} while(0)

void* mem_calloc(int num, size_t size) {
	return calloc(num, size);
}

void* mem_realloc(void* block,size_t size){
	realloc(block, size);
}

void* mem_alloc(size_t size){
	return malloc(size);
}

void mem_free(void* chunk) {
	free(chunk);
}
