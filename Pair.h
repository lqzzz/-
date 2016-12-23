#ifndef  _PAIR_H
#define  _PAIR_H
#include"MemPool.h"
typedef struct PairType{
	void(*first_free)(void*);
	void(*second_free)(void*);
	void*(*first_dup)(void*);
	void*(*second_dup)(void*);
	int16_t(*first_cmp)(void*, void*);
}PairType;
typedef struct Pair {
	void* first_;
	void* second_;
	PairType *piartype_;
}Pair;

#define PairGetFirst(pair_) ((pair_)->first_)
#define PairGetSecond(pair_) ((pair_)->second_)
#define PairMatch(pair_,key) ((pair_)->piartype_->first_cmp(key,pair_->first_))
#define PairSetFirst(pair_,first_)((pair_)->first_ = first_)
#define PairSetSecond(pair_,second_)((pair_)->second_ = second_)

Pair* pair_create(void* first, void* second, PairType* type);
PairType* pair_type_create(void(*first_free)(void*),
						   void(*second_free)(void*),
						   void*(*first_dup)(void*),
						   void*(*second_dup)(void*),
						   int16_t(*first_cmp)(void*, void*));
int16_t pair_cmp(Pair* p1,Pair* p2);
void pair_free(Pair* p);

#endif // ! _PAIR_H

