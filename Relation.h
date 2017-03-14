#ifndef RELATION_H
#define RELATION_H
#include"DB.h"
#define rela_clear_head(rela)do{\
	struct rehead* node_ = NULL;\
	LIST_DEL_ALL(node_,&rela->rehead_list->head_,mem_free(node_););\
}while(0)
#define rela_clear_v(rela) VECTOR_CLEAR_NODE(&rela->data_set)
#define rela_del_v(rela) VECTOR_CLEAR_VAL(&rela->data_set) 
#define RELA_DEL(rela)do{\
	rela_clear_head(rela)\
	rela_clear_v(rela);\
	mem_free(rela);\
}while(0)
#define RELA_FREE(rela) do{\
	if(rela->is_join){\
		VECTOR_CLEAR_VAL(&rela->data_set);\
		RELA_DEL(rela);\
	}else RELA_DEL(rela);\
}while(0)

typedef struct {
	struct rehead{
		Listhead head_;
		Pair schema_name;
		size_t data_len;
		size_t rec_offset;
		size_t max_len;
		enum Tokentype data_type;
	}*rehead_list;
	int is_join;
	size_t data_len;
	Vector data_set;
}Relation;

Relation* rela_create(size_t datalen, int isjoin,struct rehead*,int v_size);
Relation* rela_loop_join(Relation* left,Relation* right);
struct rehead* rela_search_col(Relation* rela, Pair* schema);
Relation* get_relation(Table* table_name);
size_t rela_get_max_len(Relation* rela,int colindex);
void rela_print(Relation* rela);
Relation* rela_or(Relation* left, Relation* right);
Relation* rela_filter(Relation* rela,DBnode* db, Pair* first, Pair* second, int opertype);
#endif // !RELATION_H
