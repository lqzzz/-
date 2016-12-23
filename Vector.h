#ifndef _VECTOR_H
#define _VECTOR_H
#define VITER_START_HEAD 0
#define VITER_START_TAIL 1
#include"MemPool.h"
typedef struct Vector{
	size_t  usedsize_;
	size_t  freesize_;
	void*(*dup_)(void*);
	void(*free_)(void*);
	int16_t(*comp_)(void*, void*);
	void *vector_[];
}Vector;

typedef struct VectorIter{
	size_t index_;
	void **value_;
}VectorIter;

#define VectorGetFreeSize(v) ((v)->freesize_)
#define VectorGetUsedSize(v) ((v)->usedsize_)
#define VectorGetDupMethod(v) ((v)->dup_)
#define VectorGetMatchMethod(v) ((v)->comp_)
#define VectorGetFreeMethod(v) ((v)->free_)

#define VectorSetDupMethod(v,dup) ((v)->dup_ = dup)
#define VectorSetMatchMethod(v,comp) ((v)->comp_ = comp)
#define VectorSetFreeMethod(v,free) ((v)->free_ = free)

Vector* vector_create_len(int count);
Vector* vector_create();
void vector_init(Vector* v,size_t size);
uint16_t vector_insert(size_t index, Vector *v);
Vector* push_back(Vector *v, void* value);
uint16_t vector_copy(Vector* vdest, Vector* vsrc);
uint16_t vector_value_copy(Vector *vdest, Vector *vsrc);
void vector_destruct(Vector *v);
void vector_release(Vector *v);

VectorIter* vector_get_begin(Vector* v);
VectorIter* vector_get_end(Vector* v);
void vector_release_iter(VectorIter *iter);
void* vector_next(VectorIter *iter);
int16_t vector_eq_iter(VectorIter *begin, VectorIter *end);

Vector* vector_filter(Vector* v);
Vector* vector_distinct(Vector* v);
void vector_sort(Vector* v);
int vector_search(Vector* v,void* key);
#endif // !_VECTOR_H

