#include "Listhead.h"
#include <stdio.h>
void list_del_all(Listhead* head,void del(void* )){
	Listhead *next_ = head->next_;
	while (next_ != head) {
		void* target = next_;
		next_ = next_->next_;
		del(target);
	}
	del(next_);
}

void* list_search(Listhead *listhead,void* key,int cmp(void*,void*)){
	void *curr_ = NULL;
	LIST_LOOP(listhead, if (cmp(listhead, key) == 0) {curr_ = listhead; break;});
	return curr_;
}

void list_add_tail(Listhead * head, Listhead * newnode){
	newnode->prve_ = head->prve_;
	newnode->next_ = head;
	head->prve_->next_ = newnode;
	head->prve_ = newnode;
}

Listhead** list_move_next(Listhead** head){
	*head = (*head)->next_;
	return head;
}

void* list_prve(Listhead* head){
	return head->prve_;
}
