#include"DB.h"
#define LEVEL_DATABASE 0
#define LEVEL_TABLE 1
#define LEVEL_PROPERTY 2
#define LEVEL_DATA 3
DB * Createdb() {
	DB* db = Memalloc(sizeof(DB));
	return db;
}