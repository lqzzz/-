#include "Vector.h"
#define INIT_LEN 1
#define SWAP(v1,v2) do {\
	void* temp = v1; \
	v1 = v2;\
	v2 = temp;\
}while(0)

uint16_t vector_insert(size_t index, Vector *v){
	
}

Vector * vector_create_len(int count){
	Vector *v = mem_alloc(sizeof(Vector) + sizeof(size_t)*count); v->dup_ = NULL; v->free_ = NULL; v->comp_ = NULL; v->usedsize_ = 0;
	v->freesize_ = count;
	return v;
}

Vector * vector_create(){
	return vector_create_len(INIT_LEN);
}

void vector_init(Vector* v,size_t size){
	
}

Vector * vector_filter(Vector * v)
{
	return NULL;
}

Vector * vector_distinct(Vector * v){
	if (!VectorGetUsedSize(v))
		return NULL;
	Vector *v_ = vector_create();
	v_->dup_ = v->dup_;
	v_->free_ = v->free_;
	v_->comp_ = v->comp_;
	VectorIter *iter_ = vector_get_begin(v);
	v_ = push_back(v_, vector_next(iter_));
	void* key_ = vector_next(iter_);
	while (key_) {
		
	}
	return NULL;
}

uint16_t vector_copy(Vector * v,Vector* vsrc){
	return 0;
}

void vector_destruct(Vector * v){
	size_t len = v->usedsize_;
	int i = 0;
	if (v->free_)
		for (; i < len; ++i)
			v->free_(v->vector_[i]);
	else
		for (; i < len; ++i)
			mem_free(v->vector_[i]);
	vector_release(v);
}

void vector_release(Vector *v){
	mem_free(v);
}

Vector * push_back(Vector *v, void* value){
	size_t freesize_ = v->freesize_;
	size_t usedsize_ = v->usedsize_;
	if (freesize_)
		v->vector_[usedsize_] = value;
	else{
		v = mem_realloc(v, v->usedsize_ << 1);
		v->vector_[usedsize_] = value;
	}
	v->usedsize_++;
	v->freesize_--;
	return v;
}

VectorIter* vector_get_begin(Vector* v){
	VectorIter *iter_;
	if (!(iter_ = mem_alloc(sizeof(VectorIter))))
		return NULL;
	iter_->value_ = &v->vector_[0];
	iter_->index_ = 0;
	return iter_;
}

VectorIter* vector_get_end(Vector* v) {
	VectorIter *iter_;
	if (!(iter_ = mem_alloc(sizeof(VectorIter))))
		return NULL;
	iter_->index_ = v->usedsize_;
	return iter_;
}
	
uint16_t vector_value_copy(Vector * vdest, Vector * vsrc){
	return 0;
}

inline void swap(void* p1, void* p2) {
	void** temp = p1;
	p1 = p2;
	p2 = temp;
}

void insert_sort(Vector *v) {

}

void quicksort(Vector* vsrc, int l, int u) {
	int i, m;
	void** v = vsrc->vector_;
	if (l >= u) return;
	m = l;
	for (i = l + 1; i <= u; i++)
		if (vsrc->comp_(v[u], v[l]) < 0)
			SWAP(v[i], v[l]);
	SWAP(v[l], v[m]);
	quicksort(vsrc, l, m - 1);
	quicksort(vsrc, m + 1, u);
}

void vector_sort(Vector * v){
	quicksort(v, 0, v->usedsize_ - 1);
}

int vector_search(Vector * v,void* key){
	void **v_ = v->vector_;
	int16_t(*comp_)(void*, void*) = v->comp_;
	int16_t lo = 0, hi = v->usedsize_;
	while (hi > lo) {
		int mi = (lo + hi) >> 1;
		if ((comp_(key, v_[mi]) == -1))
			hi = mi;
		else 
			lo = mi + 1;
	}
	return --lo;
}

void vector_release_iter(VectorIter * iter){
	mem_free(iter);
}

int16_t vector_eq_iter(VectorIter *begin, VectorIter *end){
	return begin->index_ == end->index_ ? 1 : 0;
}

void* vector_next(VectorIter * iter){
	iter->index_++;
	return *iter->value_++;
}

/*Vector *v = VectorCreate();
str *str1 = str_new("str1");
str *str2 = str_new("str2");
str *str3 = str_new("str3");
str *str4 = str_new("str4");
v->dup = str_dup;
v->free = str_free;
v->match = str_compare;
v = PustBack(v, str1);
v = PustBack(v, str2);
v = PustBack(v, str3);
v = PustBack(v, str4);
str* v1 = v->vector[0];
str* v2 = v->vector[1];
str* v3 = v->vector[2];
str* v4 = v->vector[3];
VectorIter *iter = VectorGetIter(v, 0);
str* vv1 = VectorNext(iter);
str* vv2 = VectorNext(iter);
str* vv3 = VectorNext(iter);
str* vv4 = VectorNext(iter);*/







