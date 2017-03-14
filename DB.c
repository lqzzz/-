#include"DB.h"

int db_match_name(DBnode* node, const char* key){
	if (node->name_ == NULL || key == NULL)
		return -1;
	return strcmp(node->name_, key);
}

void* dbnode_search(void* head,const char* name){
	return list_search(head, name, db_match_name);
}

Table* table_create(){
	Table* t = mem_calloc(1,sizeof(Table));
	VECTOR_INIT(&t->rec_vec,INIT_RECROD_NUM);
	VectorSetFreeMethod(&t->rec_vec, rec_del);
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

obj* create_obj(void* data) {
	obj* o = mem_alloc(sizeof(obj));
	o->data_ = data;
	o->ref_count = 0;
	return o;
}

void database_del(DBnode * db){
	
}

void rec_del(Record * rec){
	mem_free(rec->time_stamp);
	mem_free(rec->data_);
	mem_free(rec);
}

Column* col_create(int num) {
	Column* col_ = mem_calloc(1,sizeof(Column));
	LIST_INIT(col_);
	col_->data_type = NULL_;
	col_->num_ = num;
	return col_;
}

//不定长数据未考虑

Record* rec_create(char* schemaname,size_t len){
	Record* rec_ = mem_alloc(sizeof(Record));
	rec_->time_stamp = NULL;
	rec_->schema_name = schemaname;
	rec_->data_ = mem_alloc(len);
	return rec_;
}

void* rec_dup_data(Record * rec,size_t datalen){
	void* data_ = mem_alloc(datalen);
	memcpy(data_, rec->data_, datalen);
	return data_;
}

void col_free(Column * col){
	mem_free(col->name_);
	mem_free(col);	
}

void table_del(Table * table){
	list_del_all(table->col_head,col_del);
	//vector_destruct(&table->rec_vec);
	mem_free(table->name_);
	mem_free(table->creator_);
	mem_free(table);
}




