#include "Object.h"
#include"sds.h"
#include"MemPool.h"
Object* CreateObject(int type, void *ptr)
{
	Object *obj = Memalloc(sizeof(Object));
	obj->enconding_ = ENCONDING_RAW;
	obj->tyep_ = type;
	obj->ptr_ = ptr;
	obj->refcount_ = 1;
	return obj;
}

Object* CreateRawStringObject(void *ptr)
{
	return CreateObject(OBJTYPE_STRING, ptr);
}



