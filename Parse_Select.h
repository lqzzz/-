#ifndef PARSE_SELECT_H
#define PARSE_SELECT_H
#include "DB.h"
#include "Scanner.h"

typedef struct con {
	enum Tokentype oper_;
	struct {
		char* table_name;
		char* attribute_;
	}right_op,left_op;
	struct con* right_con, *left_con;
	struct que* query_;
}Condition;

typedef struct que{
	char *sel_list[10], *from_list[5];
	int sel_list_count,from_list_count;
	Condition* con_;
}Query;

void interpre_select(DBnode*,Query*);
Query* parse_select(Token**);
Condition* create_con(int oper, Condition* leftcon, Condition* rightcon);
void delete_con(Condition* con);
void delete_que(Query* que);
Condition* get_con_exp(Token** curr);

#endif // !PARSE_SELECT_H
