#include "list.h"
#include<stdlib.h>
#include"sds.h"
listnode * node_creat()
{
	listnode* pnode = (listnode*)malloc(sizeof(listnode));
	pnode->value = NULL;
	pnode->next = NULL;
	pnode->prev = NULL;
	return pnode;
}

list* list_creat()
{
	list* listhead=(list*)malloc(sizeof(list));
	listhead->head = NULL;
	return listhead;
}

void list_set_dup(list* target,void* (*setmethod)(void *ptr))
{
	target->dup = setmethod;
}

void list_set_free(list * target, void (*setmethod)(void *ptr))
{
	target->free = setmethod;
}

listnode * list_get_head(list * target)
{
	return target->head;
}

//typedef sds*(*dup)(const sds* const);

void list_add_head(list * target,void* value)
{
	listnode* Lnode = node_creat();
	Lnode->value = target->dup(value);//(dup)list_get_dup(value);
	if (!target->head)
	{
		target->head = Lnode;
		target->tail = Lnode;
	}
	else
	{
		target->head->prev = Lnode;
		Lnode->next = target->head;
		target->head = Lnode;
		target->tail = Lnode;
	}
}


