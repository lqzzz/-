#include"MemPool.h"
#include<string.h>
static size_t used_memory = 0;
static int mem_alloc_thread_safe = 0;
pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

#define PREFIX_SIZE sizeof(size_t)
#define SIZE_ALINE(__n) do{ \
	if(__n&(sizeof(size_t)-1)) __n += sizeof(size_t)-(__n&sizeof(size_t)-1);\
} while(0)

#define increment_used_memory(__n) do { \
    size_t _n = (__n); \
    if (_n&(PREFIX_SIZE-1)) _n += PREFIX_SIZE-(_n&(PREFIX_SIZE-1));\
    if (mem_alloc_thread_safe) { \
        pthread_mutex_lock(&used_memory_mutex);  \
        used_memory += _n; \
        pthread_mutex_unlock(&used_memory_mutex); \
    } else { \
        used_memory += _n; \
    } \
} while(0)

#define decrement_used_memory(__n) do { \
    size_t _n = (__n); \
    if (_n & (PREFIX_SIZE-1)) _n += PREFIX_SIZE-(_n & (PREFIX_SIZE-1)); \
    if (mem_alloc_thread_safe) { \
        pthread_mutex_lock(&used_memory_mutex);  \
        used_memory -= _n; \
        pthread_mutex_unlock(&used_memory_mutex); \
    } else { \
        used_memory -= _n; \
    } \
} while(0)

static void malloc_oom(size_t size) {
	fprintf(stderr, "malloc: Out of memory trying to allocate %zu bytes\n",
		size);
	fflush(stderr);
	abort();
}

void* mem_calloc(int num, size_t size) {
	size_t sum_len = num*size;
	void *ptr = malloc(sum_len + PREFIX_SIZE);
	if (!ptr) malloc_oom(sum_len);
	memset((char*)ptr+PREFIX_SIZE, 0, sum_len);
	*((size_t*)ptr) = sum_len;
	increment_used_memory(sum_len+PREFIX_SIZE);
	return (char*)ptr+PREFIX_SIZE;
}

void* mem_realloc(void* ptr,size_t size){
	void *realptr;
	size_t oldsize;
	void *newptr;
	if (ptr == NULL) return mem_alloc(size);
	realptr = (char*)ptr-PREFIX_SIZE;
	oldsize = *((size_t*)realptr);
	newptr = realloc(realptr, size + PREFIX_SIZE);
	if (!newptr) malloc_oom(size);
	*((size_t*)newptr) = size;
	decrement_used_memory(oldsize);
	increment_used_memory(size);
	return (char*)newptr+PREFIX_SIZE;
}

void* mem_alloc(size_t size){
	void *ptr = malloc(size+PREFIX_SIZE);
	if (!ptr) malloc_oom(size);
	*((size_t*)ptr) = size;
	increment_used_memory(size+PREFIX_SIZE);
	return (char*)ptr+PREFIX_SIZE;
}

void mem_free(void* ptr) {
	if (ptr == NULL) return;
	void* realptr = (char*)ptr - PREFIX_SIZE;
	size_t oldsize = *((size_t*)realptr);
	decrement_used_memory(oldsize + PREFIX_SIZE);
	free(realptr);
}

size_t malloc_used_memory(void) {
	size_t um;
	if (mem_alloc_thread_safe) pthread_mutex_lock(&used_memory_mutex);
	um = used_memory;
	if (mem_alloc_thread_safe) pthread_mutex_unlock(&used_memory_mutex);
	return um;
}

void mem_alloc_enable_thread_safeness(void) {
	mem_alloc_thread_safe = 1;
}
