#pragma once
typedef struct listnode{

 	struct listnode *prev;

	struct listnode *next;

	void* value;

}listnode;

listnode* node_creat();

typedef void*(*Dupfun)(void*);
typedef void(*Freefun)(void*);
typedef int(*Matchfun)(void*, void*);

typedef struct list{

	struct listnode *head;

	struct listnode *tail;

	int size;

	Dupfun dup;

	Freefun free;

	Matchfun match;

}list;

list* list_creat();
void list_set_dup(list* target,void* (*setmethod)(void *ptr));
Dupfun list_get_dup(list* target);
void list_set_free(list* target, void (*getmethod)(void *ptr));
Freefun list_get_free(list* target);
void list_add_head(list* target,void* value);
listnode* list_get_head(list* target);


