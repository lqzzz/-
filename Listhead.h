#ifndef _LISTHEAD_H
#define _LISTHEAD_H
#define LIST_INIT(head) ((Listhead*)head)->next_ = head; ((Listhead*)head)->prve_ = head
#define LIST_GET_NEXT(head) ((Listhead*)head)->next_
#define LIST_GET_PRVE(head) ((Listhead*)head)->prve_
#define LIST_LOOP(listhead,action) do{\
	Listhead *head_ = listhead;\
	do{\
		action\
	}while(*list_move_next(&listhead) != head_);\
}while(0)

typedef struct Listhead {
	struct Listhead *next_, *prve_;
}Listhead;

void list_del_all(Listhead* node, void del(void *));
void* list_search(Listhead *listhead, void* key, int cmp(void*, void*));
void list_add_tail(Listhead* head, Listhead* newnode);
Listhead** list_move_next(Listhead** head);

#endif // !_LISTHEAD_H
