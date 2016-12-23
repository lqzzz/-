#include "Object.h"
#include"str.h"
#include"MemPool.h"
void FreeStringObjent(Object *obj){
	/*int obj_type = obj->tyep_;
	switch (obj_type){
		case OBJTYPE_STRING: FreeStringObjent(obj); break;
		default:return;
		}

	if (obj->value_type == VALTYPE_RAW)
		str_free(obj->ptr_);
	FreeMem(obj);*/
}

void DecrRefConut(void *obj){
	Object *obj_ = obj;
	if (--(obj_->refcount_) == 0){
		switch (obj_->tyep_){
		case OBJTYPE_STRING: FreeStringObjent(obj_); break;
		default:return;
		}
	}
}

void ObjectDestructor(void *obj){
	if (!obj) return;
	DecrRefConut(obj);
}

//unsigned int ObjectHashCode(const Object *obj){
//	return strhashcode(obj->ptr_);
//}

//int DictObjentCompare(const void *key1, const void *key2){
//	Object *o1 = key1, *o2 = key2;
//	return str_compare(o1->ptr_, o2->ptr_);
//}

Object* CreateObject(int type, void *ptr){
	Object *obj = mem_alloc(sizeof(Object));
	obj->tyep_ = type;
	obj->ptr_ = ptr;
	obj->refcount_ = 1;
	return obj;
}

Object* CreateStringObject(void *ptr){
	return CreateObject(OBJTYPE_STRING, ptr);
}




