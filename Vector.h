#ifndef _VECTOR_H
#define _VECTOR_H
#define VITER_START_HEAD 0
#define VITER_START_TAIL 1
#include"MemPool.h"
#include"Iterator.h"
#include"sds.h"
#include<string.h>

typedef struct Vector{
	size_t  usedsize;
	size_t  freesize;
	Dupfun dup;
	Freefun free;
	Matchfun match;
	void *vector[];
}Vector;

typedef struct VectorIter{
	short direction;
	short index;
	int end;
	void **value;
}VectorIter;

//#define VectorGetFreeSize(v) ((v)->freesize)
//#define VectorGetUsedSize(v) ((v)->usedsize)
//#define VectorGetDupMethod(v) ((v)->dup)
//#define VectorGetMatchMethod(v) ((v)->match)

Vector* VectorCreateLen(int count);
Vector* VectorCreate();
Vector* VectorGrow(Vector* v);
Vector* Where(Vector* v, int argc, sds argv[]);
void VectorSetDup(Vector* v, Dupfun dupfun);
void VectorSetFree(Vector* v, Freefun freefun);
void VectorSetMatch(Vector* v, Matchfun matchfun);

void VectorRelease(Vector *v);
Vector* PustBack(Vector *v, void* value);
int VectorCopy(Vector* vdest, Vector* vsrc);
VectorIter* VectorGetIter(Vector* v,short direction);
int VectorValueCopy(Vector *vdest, Vector *vsrc);
void VectorReleaseIter(VectorIter *iter);
void* VectorNext(VectorIter *iter);

#endif // !_VECTOR_H

