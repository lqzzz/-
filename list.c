#include "list.h"
#include<stdlib.h>
#include"MemPool.h" 
static listnode * node_creat(){
	listnode* pnode = Memalloc(sizeof(listnode));
	pnode->value = NULL;
	pnode->next = NULL;
	pnode->prev = NULL;
	return pnode;
}

list* list_creat(){
	list* list=Memalloc(sizeof(list));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

list * select(list * target_list, int argc, sds argv[])
{
	if (!argc) return target_list;
	list *list_ = list_creat();
	list_->free = target_list->free;
	list_->match = target_list->match;
	list_->dup = target_list->dup;
	int i = 0;
	listnode *node = target_list->head;
	for (; i < argc; i++) {
		listnode *add_node;
		if (add_node = list_search(target_list, &argv[i]))
			list_add_tail(list_, add_node);
	}
	return list_;
}

void list_set_dup(list* target, Dupfun dupfun){
	target->dup = dupfun;
}

void list_set_free(list * target, Freefun freefun){
	target->free = freefun;
}

listnode * list_get_head(list * target){
	return target->head;
}

listnode * list_get_tail(list * target){
	return target->tail;
}

listnode * list_search(list * list, void *target)
{
	listnode *node = list->head;
	while (node)
		if (list->match && list->match(node->value, target)
			|| (int)target == (int)node->value)
			return node;		
	return NULL;
}

Iterator * list_get_iter(list * list){
	Iterator *iter = Memalloc(sizeof(Iterator));
	iter->current_ = list->head;
	return iter;
}

listnode * list_get_next(ListIter * iter){
	listnode *current = iter->next;
	if (!current)
		return NULL;
	short direction = iter->direction;
	if(direction == LITER_START_HEAD) 
		iter->next = current->next;
	else
		iter->next = current->prev;
	return current;
}


void list_add_head(list * target,void* value){
	listnode* Lnode = node_creat();
	Lnode->value = target->dup(value);
	if (!target->head){
		target->head = Lnode;
		target->tail = Lnode;
	}else{
		target->head->prev = Lnode;
		Lnode->next = target->head;
		target->head = Lnode;
		target->tail = Lnode;
	}
}

void list_add_tail(list * target, void * value){
	listnode* Lnode = node_creat();
	Lnode->value = target->dup(value);
	if (!target->head) {
		target->head = Lnode;
		target->tail = Lnode;
	}else{
		target->tail->next = Lnode;
		target->tail = Lnode;
	}
}


