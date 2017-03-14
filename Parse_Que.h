#ifndef PARSE_QUE_H
#define PARSE_QUE_H
#include "DB.h"
#include "Scanner.h"
#include "Relation.h"

struct select {
	Vector v_col;//pair*
	Vector v_from;//table*
	struct con* con_;
};

//oper: and or not in eq exists loop_join hash_join index_join select 
struct que {
	enum Tokentype operator_; // and or not  eq ex...
	Pair *left_opand, *right_opand;
};

struct con {
	enum Tokentype con_type; // WHERE SELECT JOIN
	struct con *right_con, *left_con;
	enum Tokentype operator_; // and or not  eq ex...
	Pair *left_opand, *right_opand;
	struct con* next_;
	Relation* res_;
};

struct update {
	struct setlist {
		Pair col_value;
		Listhead head_;
	}*set_list;
	Table* table_;
	struct con* con_;
};



int parse_select(DBnode* db,Token**);

#endif // !PARSE_QUE_H
