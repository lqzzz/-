#include"DB.h"
int db_match_name(DBnode* node, const char* key){
	return strcmp(node->name_, key);
}

void* dbnode_search(void* head,const char* name){
	return list_search(head, name, db_match_name);
}

Table* table_create(){
	Table* t = mem_calloc(1,sizeof(Table)+sizeof(size_t)*INIT_TTABLE_NUM);
	LIST_INIT(t);
	return t;
}

DBnode* database_create(){
	DBnode* dbnode = mem_calloc(1,sizeof(DBnode));
	LIST_INIT(dbnode);
	return dbnode;
}

void col_del(Column* col){
	mem_free(col->name_);
	mem_free(col);
}

Column* col_create(int num){
	Column* col_ = mem_calloc(1,sizeof(Column));
	LIST_INIT(col_);
	col_->data_type = NULL_;
	col_->num_ = num;
	return col_;
}

Record* rec_create(char* schema,int pvarcount, int16_t fieldcount){
	Record* rec_ = mem_alloc(sizeof(Record));
	rec_->data_ = mem_alloc(fieldcount*sizeof(size_t)); 
	rec_->p_variable = mem_alloc(sizeof(size_t)*pvarcount);
	rec_->schema_name = schema;
	return rec_;
}

