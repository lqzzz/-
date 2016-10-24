#ifndef _LIST_H
#define _LIST_H
#define LITER_START_HEAD 0
#define LITER_START_TAIL 1
#include"Iterator.h"
#include"sds.h"
typedef struct listnode{
 	struct listnode *prev;
	struct listnode *next;
	void* value;
}listnode;

typedef struct list{
	int size;
	Dupfun dup;
	Freefun free;
	Matchfun match;
	struct listnode *head;
	struct listnode *tail;
}list;

typedef struct ListIter {
	short direction;
	listnode *next;
}ListIter;

list* list_creat();
list* select(list* list,int argc, sds argv[]);
listnode* list_get_head(list* target);
listnode* list_get_tail(list* target);
listnode* list_get_next(ListIter* iter);
listnode* list_search(list* list,void *target);
Iterator* list_get_iter(list *list);
void list_set_dup(list* target,Dupfun dupfun);
void list_set_free(list* target, Freefun freefun);
void list_add_head(list* target, void* value);
void list_add_tail(list* target, void* value);

#endif // !_LIST_H




