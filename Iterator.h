#ifndef _ITERATOR_H
#define _ITERATOR_H

#define VECTOR_ITER 0
#define LIST_ITER 1

#define GREATE_THAN 0
#define LESS_THAN 1
#define EQUAL_ 2

typedef void*(*Dupfun)(void*);
typedef void*(*Visit)(void*);
typedef void(*Freefun)(void*);
typedef int(*Matchfun)(void*, void*);
//typedef int(*Compare)(void*,void*);

typedef struct OperFuntion {
	Dupfun dup_fun;
	Visit visit_fun;
	Freefun free_fun;
	Matchfun match_fun;
}OperFuntion;

typedef struct Iterator{
	void *current_;
	OperFuntion *oper_fun;
}Iterator;

void *Filter(void *iter, int type,int c);


#endif // !_ITERATOR_H

