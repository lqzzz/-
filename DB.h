#ifndef _DB_H
#define _DB_H
#include "DB.h"
#include"MemPool.h"
#include"Object.h"
#include "listhead.h"
#include "Vector.h"
#include "Pair.h"
#define INIT_TTABLE_NUM 64
#define DBNODE_SEARCH(head,key) list_search(head,key,db_match_name)
enum Tokentype {
	CREATE = 1, TABLE, INDEX, UPDATE, PROCEDURE, VIEW,
	TEXT, REAL, DATE, DATETIME, TIME, INT, CHAR, BOOL,VARCHAR,
	PRIMARY, KEY, FOREIGN, REFERENCES, NULL_, NOT, DEFAULT, UNIQUE,
	LIKE, AND, BETWEEN, OR, IN, EXISTS,EQUAL,DOT,
	SELECT, WHERE, FROM, GROUP, BY, ORDER, HAVING,
	ALTER, ADD, DROP, INSERT,
	COMMIT, TRANSACTION, ROLLBACK,
	INTO, VALUES, ON, SET,
	ALL, AS, DELETE, UNION,
	AVG, MAX, MIN, COUNT,
	ID, LB, RB, COMMA, SQM, SEM,
};

struct Operfun{
	void*(*dup_)(void*);
	void(*free_)(void*);
	int(*cmp_)(void*, void*);
	void(*visit_)();
};

typedef struct Record {
	char* schema_name;
	char* time_stamp;
	void** p_variable;
	void** data_;
}Record;

typedef struct Column {
	Listhead list_head;
	char *name_;
	int num_;
	size_t data_len;
	size_t rec_offset;
	enum Tokentype data_type;
	void **fk_;
	unsigned not_null : 1;
	unsigned unique_ : 1;
	unsigned pk_ : 1;
}Column;

typedef struct Table {
	Listhead list_head;
	char* name_;
	int num_;
	char* creator_;
	int column_count;
	int record_size;
	Column *col_head;
	Vector rec_vec;
}Table;

typedef struct DBnode {
	Listhead list_head;
	char *name_;
	int num_;
	Table* table_head;
	int table_count;
}DBnode;

Table* table_create();
DBnode* database_create();
Column* col_create(int num);
Record* rec_create(char* schema_name, int pvarcount, int16_t fieldcount);
int db_match_name(DBnode* node, const char* name);
void* dbnode_search(void* head, const char* name);
void col_del(Column* col);

#endif // !_DB_H

