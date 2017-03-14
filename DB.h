#ifndef _DB_H
#define _DB_H
#include "DB.h"
#include "MemPool.h"
#include "listhead.h"
#include "Vector.h"
#include "Pair.h"
#include <stdio.h>

#define INIT_RECROD_NUM 16 

#define DBNODE_SEARCH(head,key) list_search(head,key,db_match_name)
#define DB_ADD_TABLE(db,table) LIST_ADD_TAIL(&db->table_head->list_head, &table->list_head);
//#define GET_DBNODE(head,name,dest) dest

#define REC_GET_DATA(rec) (rec)->data_	
#define REC_FILL(rec,offset,data,datalen) memcpy((char*)((Record*)(rec))->data_ + offset,data,datalen)

#define TABLE_ADD_REC(table,rec) VECTOR_PUSHBACK(&(table)->rec_vec, rec)
#define TABLE_GET_REC_SIZE(table) VECTOR_GET_SIZE(&(table)->rec_vec) 
#define TABLE_USED_REC_SIZE(table) (table)->used_rec_size
#define TABLE_GET_REC_VEC(table) &(table)->rec_vec
#define TABLE_GET_REC(table,index) VECTOR_GET_VALUE(TABLE_GET_REC_VEC(table),index)
#define TABLE_GET_COL_SIZE(table) table->column_count
#define TABLE_GET_COL_HEAD(table) table->col_head
#define TABLE_FILL_REC(table,rec_index,offset,data,datalen) REC_FILL(TABLE_GET_REC(table,rec_index),offset,data,datalen)

enum Tokentype {
	CREATE = 1, TABLE, INDEX, UPDATE, PROCEDURE, VIEW,
	NUMBER, TEXT, REAL, DATE, DATETIME, TIME, INT, CHAR, BOOL, VARCHAR,
	PRIMARY, KEY, FOREIGN, REFERENCES, NULL_, DEFAULT, UNIQUE,
	LIKE, AND, BETWEEN, OR, IN, EXISTS, DOT,
	NOT,NOT_IN,NOT_EXISTS,
	SELECT, DISTINCT, WHERE, FROM, GROUP, BY, ORDER, HAVING,
	ALTER, ADD, DROP, INSERT,
	COMMIT, TRANSACTION, ROLLBACK,
	INTO, VALUES, ON, SET,
	ALL, AS, DELETE, UNION,
	AVG, MAX, MIN, COUNT,
	ID, SYMBOL,LB, RB, COMMA, SQM, SEM, STAR,
	LESSTHAN, GREATERTHAN, GREATER_OR_EQ, LESS_OR_EQ, EQUAL,NOT_EQUAL,
	JOIN
};

struct Operfun{
	void*(*dup_)(void*);
	void(*free_)(void*);
	int(*cmp_)(void*, void*);
	void(*visit_)();
};

typedef struct Column {
	Listhead list_head; 
	char* name_;
	int num_;
	size_t data_len;
	size_t rec_offset;
	void** p_data;
	enum Tokentype data_type;
	void** fk_;
	unsigned not_null : 1;
	unsigned unique_ : 1;
	unsigned pk_ : 1;
}Column;

typedef struct Record {
	char* schema_name;
	char* time_stamp;
	//size_t len_;
	//void** p_variable;
	void* data_;
}Record;

typedef struct Table {
	Listhead list_head;
	char* name_;
	int num_;
	char* creator_;
	int column_count;
	Column *col_head; //collist
	size_t rec_len;
	int used_rec_size;
	Vector rec_vec;	//vector<record*>
}Table;

typedef struct DBnode {
	Listhead list_head;
	char *name_;
	int num_;
	Table* table_head;//tablelist
	int table_count;
}DBnode;

typedef struct {
	int ref_count;
	void* data_;
	//void(*del_fun)(void*);
}obj;

#define free_obj(o)do{\
	mem_free((o)->data_); \
	mem_free(o);\
}while(0)

#define inc_ref(o) (o)->ref_count++

#define dec_ref(o) do{\
	if ((--(o)->ref_count) == 0) {\
		free_obj(o);\
	}\
}while(0)


void database_del(DBnode* db);
DBnode* database_create();

int db_match_name(DBnode* node, const char* name);
void* dbnode_search(void* head, const char* name);

Table* table_create();
void table_del(Table* table);

Column* col_create(int num);
void col_del(Column* col);

Record* rec_create(char* schemaname, size_t len);
void* rec_dup_data(Record* rec,size_t datalen);
void rec_del(Record* rec);

//void data_print(int tokentype,void* data,int maxlen);
#endif // !_DB_H

