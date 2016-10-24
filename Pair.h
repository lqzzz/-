#ifndef  _PAIR_H
#define  _PAIR_H
#include"Iterator.h"
typedef struct PairType{
	Dupfun first_dup;
	Dupfun second_dup;
	Freefun first_freefun;
	Freefun second_freefun;
	Matchfun first_match;
}PairType;
typedef struct Pair {
	void* *first_;
	void *second_;
	PairType *piartype_;
}Pair;

Pair* PairCreate(void* first, void* second, PairType *type);
void* PairGetFirst(Pair *pair);
void* PairGetSecond(Pair *pair);


#endif // ! _PAIR_H

