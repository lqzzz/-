#include "Pair.h"
#include"MemPool.h"

Pair * PairCreate(void * first, void * second,PairType *type){
	Pair *pair_ = Memalloc(sizeof(Pair));
	pair_->piartype_ = type;
	pair_->first_ = first;
	pair_->second_ = second;
	return pair_;
}

int PairCompare(void * key, Pair *pair)
{

	return 0;
}

void * PairGetFirst(Pair * pair){
	return pair->first_;
}

void * PairGetSecond(Pair *pair){
	return pair->second_;
}
