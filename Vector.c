#include "Vector.h"
#define Init_LEN 1
Vector * VectorCreateLen(int count){
	Vector *v = Memalloc(sizeof(Vector) + sizeof(size_t)*count);
	v->dup = NULL;
	v->free = NULL;
	v->match = NULL;
	v->usedsize = 0;
	v->freesize = count;
	return v;
}

Vector * VectorCreate(){
	return VectorCreateLen(Init_LEN);
}

Vector * VectorGrow(Vector * v){
	Vector *newv = VectorCreateLen(v->usedsize << 1);
	newv->dup = v->dup;
	newv->free = v->free;
	newv->match = v->match;
	int i = 0;
	for (; i < v->usedsize; ++i)
		PustBack(newv, v->vector[i]);
	VectorRelease(v);
	return newv;
}

Vector * Where(Vector * v, int argc, sds argv[])
{
	return NULL;
}

void VectorSetDup(Vector* v, Dupfun dupfun)
{
	v->dup = dupfun;
}

void VectorSetFree(Vector* v, Freefun freefun)
{
	v->free = freefun;
}

void VectorSetMatch(Vector* v, Matchfun matchfun)
{
	v->match = matchfun;
}


int VectorCopy(Vector * v,Vector* vsrc){
	return 0;
}

void VectorRelease(Vector * v){
	size_t len = v->usedsize;
	int i = 0;
	if (v->free)
		for (; i < len; ++i)
			v->free(v->vector[i]);
	else
		for (; i < len; ++i)
			FreeMem(v->vector[i]);
	FreeMem(v);
}

Vector * PustBack(Vector *v, void* value){
	size_t freesize = v->freesize;
	size_t usedsize = v->usedsize;
	if (freesize)
		v->vector[usedsize] = value;
	else{
		v = VectorGrow(v);
		v->vector[usedsize] = value;
	}
	v->usedsize++;
	v->freesize--;
	return v;
}

VectorIter * VectorGetIter(Vector * v, short direction){
	VectorIter *iter;
	if (!(iter = Memalloc(sizeof(VectorIter))))
		return NULL;
	if (direction == VITER_START_HEAD){
		iter->value = &v->vector[0];
		iter->index = 0;
		iter->end = v->usedsize;
	}else{
		iter->value = &v->vector[v->usedsize - 1];
		iter->index = v->usedsize - 1;
		iter->end = -1;
	}
	iter->direction = direction;
	return iter;
}

int VectorValueCopy(Vector * vdest, Vector * vsrc){
	return 0;
}

void VectorReleaseIter(VectorIter * iter){
	FreeMem(iter);
}

void* VectorNext(VectorIter * iter){
	if(iter->index == iter->end)
		return iter->value = NULL;
	else if (iter->direction == 0){
		iter->index++;
		return *iter->value++;
	}else{
		iter->index--;
		return *iter->value--;
	}
}

/*Vector *v = VectorCreate();
sds *str1 = sds_new("str1");
sds *str2 = sds_new("str2");
sds *str3 = sds_new("str3");
sds *str4 = sds_new("str4");
v->dup = sds_dup;
v->free = sds_free;
v->match = sds_compare;
v = PustBack(v, str1);
v = PustBack(v, str2);
v = PustBack(v, str3);
v = PustBack(v, str4);
sds* v1 = v->vector[0];
sds* v2 = v->vector[1];
sds* v3 = v->vector[2];
sds* v4 = v->vector[3];
VectorIter *iter = VectorGetIter(v, 0);
sds* vv1 = VectorNext(iter);
sds* vv2 = VectorNext(iter);
sds* vv3 = VectorNext(iter);
sds* vv4 = VectorNext(iter);*/







