#ifndef __MEMPOOL_
#define __MEMPOOL_
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<stdint.h>
#include<pthread.h>
void* mem_alloc(size_t size);
void mem_free(void *ptr);
void* mem_calloc(int num,size_t size);
void* mem_realloc(void*,size_t);
size_t malloc_used_memory(void);
void mem_alloc_enable_thread_safeness(void);
#endif // !__MEMPOOL_
