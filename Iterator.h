#ifndef _ITERATOR_H
#define _ITERATOR_H
#include<stddef.h>
#include<stdint.h>
#define VECTOR_ITER 0
#define LIST_ITER 1

#define ITER_ERROR 0
#define ITER_OK 1

typedef void*(*Dupfun)(void*);
typedef void*(*Visit)(void*);
typedef void(*Freefun)(void*);
typedef int(*Comparefun)(void*, void*);

typedef struct Iterator {
	uint16_t iter_type;
	size_t index_;
	void* node_;
	void *(*get_next)(void*);
	int(*has_next)(void*);
	void*(*dup_)(void*);
	void(*free_)(void*);
	int16_t(*comp_)(void*, void*);
}Iterator;

void *filter(void *iter, int type, int c);
void sort(Iterator* begin, Iterator* end, int comp(void*, void*));
void search(Iterator* begin, Iterator* end, void* val);

#endif // !_ITERATOR_H

