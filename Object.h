#ifndef _OBJECT_H
#define _OBJECT_H
#include "dict.h"
#define OBJTYPE_STRING 0
#define OBJTYPE_INTEGER 1
#define OBJTYPE_PAIR 2
#define OBJTYPE_LIST 3
#define OBJTYPE_VECTOR 4

typedef struct Object {
	short tyep_;
	short refcount_;
	void *ptr_;
}Object;

Object* CreateObject(int type, void *ptr);
Object* CreateStringObject(void* ptr);
void DecrRefConut(void *obj);
void ObjectDestructor(void *obj);
int DictObjentCompare(const void *key1, const void *key2);
unsigned int ObjectHashCode(const Object *obj);
void FreeStringObjent(Object *obj);

#endif /*_OBJECT_H*/