#include "list.h"
#include"MemPool.h" 

//static ListNode * node_creat() {
//	ListNode* pnode;
//	if ((pnode = memalloc(sizeof(ListNode))) == NULL)
//		return NULL;
//	pnode->next_ = NULL;
//	pnode->prev_ = NULL;
//	return pnode;
//}

List* list_creat() {
	List* list_ = mem_alloc(sizeof(List));
	list_->head_ = list_->tail_ = NULL;
	list_->dup_ = NULL;
	list_->free_ = NULL;
	list_->comp_ = NULL;
	return list_;
}

List * list_dup(List * lsrc)
{
	List* copy_;
	ListNode *current_node;
	if ((copy_ = list_creat()) == NULL)
		return NULL;
	copy_->dup_ = lsrc->dup_;
	copy_->comp_ = lsrc->comp_;
	copy_->free_ = lsrc->free_;
	for (current_node = lsrc->head_;
		 current_node; current_node = current_node->next_) {
		void* value;
		if (copy_->dup_) {
			value = copy_->dup_(current_node->value_);
			if (!value) {
				list_free(copy_);
				return NULL;
			}
		}else
			value = current_node->value_;
		if (!list_add_tail(copy_, value)) {
			list_free(copy_);
			return NULL;
		}
	}
	return copy_;
}

//list * select(list * target_list, int argc, str *argv[])
//{
//	if (!argc) return target_list;
//	list *list_ = list_creat();
//	list_->free_ = target_list->free_;
//	list_->match_ = target_list->match_;
//	list_->dup_ = target_list->dup_;
//	int i = 0;
//	ListNode *node = target_list->head_;
//	for (; i < argc; i++) {
//		ListNode *add_node;
//		if (add_node = list_search(target_list, argv[i]))
//			list_add_tail(list_, add_node);
//	}
//	return list_;
//}

//ListNode * list_search(list * list, void *target)
//{
//	ListNode *node = list->head_;
//	for (; node; node = node->next_)
//		if (list->match_) 
//			return list->match_(node->value_, target) ? node : NULL;		
//		else
//			return (int)target == (int)node->value_ ? node : NULL;				
//}

static Iterator * list_get_iter(List * list) {
	Iterator *iter;
	if (iter = mem_alloc(sizeof(Iterator)) == NULL) return NULL;
	iter->get_next = list_next;
	iter->has_next = list_has_next;
	return iter;
}

void list_free(List * list) {
	list_free_value(list);
	list_free_node(list);
}

void list_free_value(List * list) {
	for (ListNode* curr_ = list->head_; curr_; curr_ = curr_->next_)
		list->free_ ? list->free_(curr_->value_) : mem_free(curr_->value_);
}

void list_free_node(List * list){
	for (ListNode* curr_ = list->head_; curr_;
		curr_ = curr_->next_, list->size_--)
		mem_free(curr_);
}

Iterator * list_get_begin_iter(List * list) {
	Iterator *iter = list_get_iter(list);
	iter->node_ = ListHead(list);
	return iter;
}

Iterator * list_get_end_iter(List * list) {
	Iterator *iter = list_get_iter(list);
	iter->node_ = ListTail(list);
	return iter;
}

List* list_add_head(List * target, void* value) {
	ListNode* node_;
	if ((node_ = malloc(sizeof(ListNode))) == NULL)
		return NULL;
	node_->value_ = value;
	node_->next_ = NULL;
	node_->prev_ = NULL;
	if (!target->head_) {
		target->head_ = node_;
		target->tail_ = node_;
	}else {
		target->head_->prev_ = node_;
		node_->next_ = target->head_;
		target->head_ = node_;
	}
	target->size_++;
	return target;
}

//List * list_add_tail(List * target, void * value) {
//	ListNode* node_;
//	if ((node_ = mem_alloc(sizeof(ListNode))) == NULL)
//		return NULL;
//	node_->value_ = value;
//	node_->next_ = NULL;
//	node_->prev_ = NULL;
//	if (!target->head_) {
//		target->head_ = node_;
//		target->tail_ = node_;
//	}else {
//		target->tail_->next_ = node_;
//		target->tail_ = node_;
//	}
//	target->size_++;
//	return target;
//}

//static ListNode * list_get_next(ListIter * iter) {
//	ListNode *current = iter->next_;
//	if (!current)
//		return NULL;
//	short direction = iter->direction_;
//	if (direction == LITER_START_HEAD)
//		iter->next_ = current->next_;
//	else
//		iter->next_ = current->prev_;
//	return current;
//}

void* list_next(Iterator* iter) {
	if (list_has_next(iter)) {
		ListNode *current_ = iter->node_;
		iter->node_ = current_->next_;
		return current_->value_;
	}
	return NULL;
}

int list_has_next(Iterator* iter) {
	return ((ListNode*)iter->node_)->next_ ? 1 : 0;
}


