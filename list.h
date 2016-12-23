#ifndef _LIST_H
#define _LIST_H

#include"Iterator.h"

#define LITER_START_HEAD 0
#define LITER_START_TAIL 1

#define ListLength(l) ((l)->size_)
#define ListHead(l) ((l)->head_)
#define ListTail(l) ((l)->tail_)
#define ListPrevNode(n) ((n)->prev_)
#define ListNextNode(n) ((n)->next_)
#define ListNodeValue(n) ((n)->value_)

#define ListSetDupMethod(l,m) ((l)->dup_ = (m))
#define ListSetFreeMethod(l,m) ((l)->free_ = (m))
#define ListSetMatchMethod(l,m) ((l)->comp_ = (m))

#define ListGetDupMethod(l) ((l)->dup_)
#define ListGetFree(l) ((l)->free_)
#define ListGetMatchMethod(l) ((l)->comp_)

typedef struct ListNode {
	struct ListNode *prev_;
	struct ListNode *next_;
	void* value_;
}ListNode;

typedef struct list {
	int size_;
	Dupfun dup_;
	Freefun free_;
	Comparefun comp_;
	ListNode *head_;
	ListNode *tail_;
}List;

typedef struct ListIter {
	short direction_;
	ListNode *next_;
}ListIter;

List* list_creat();
List* list_dup(List* lsrc);
List* list_add_head(List* target, void* value);
//List* list_add_tail(List* target, void* value);
void list_free_node(List* list);
void list_free_value(List* list);
inline void list_free(List* list);

inline void* list_next(Iterator* iter);
inline int list_has_next(Iterator* iter);
Iterator* list_get_begin_iter(List *list);
Iterator* list_get_end_iter(List *list);
#endif // !_LIST_H




