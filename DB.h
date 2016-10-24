#ifndef _DB_H
#define _DB_H
#include "DB.h"
#include"MemPool.h"
#include"Object.h"
#include<string.h>
#include "list.h"
#include "Vector.h"
#include "Pair.h"
typedef struct DB{
	Object *node;
}DB;

DB* Createdb();
//int Insert(DB* db, Object *obj, int level);
#endif // !_DB_H

