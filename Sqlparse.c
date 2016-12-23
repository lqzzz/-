#include "Sqlparse.h"
#include "MemPool.h"

extern int parse_create(DBnode* dbnode, Token** curr);
extern Table* parse_create_table(DBnode *dbnode,Token** token);
extern Column* parse_create_column(DBnode *dbnode,Token** token);
extern int parse_datatype(Column*, int datatype, Token**);
extern int parse_insert(DBnode*, Token**);
extern int parse_insert_values(DBnode*, Column**,Table*, Token**,int);

int parse_insert_values(DBnode* dbnode, Column** ptr_col,Table* table, Token** curr,int col_guard) {
	int col_index = 0;
	int data_size_index = table->record_size;
	if (TOKEN_TYPE != LB) PARSE_ERROR("缺少 （ ");
	if (MOVE_NEXT_TOKEN_TYPE != INT &&
		TOKEN_TYPE != REAL&&
		TOKEN_TYPE != TEXT) PARSE_ERROR("缺少ID");
	for (;;) {
		if (TOKEN_TYPE != INT &&
			TOKEN_TYPE != REAL &&
			TOKEN_TYPE != TEXT)  PARSE_ERROR("缺少ID");
		if (col_index == col_guard)
			PARSE_ERROR("insert语句中列数目小于values语句中指定值的数目,VALUES 子句中值的数目必须与 INSERT 语句中指定的列的数目匹配");
		//move_value(&(*curr)->value_, &ptr_col[col_index++]->data_[data_size_index]);
		switch (MOVE_NEXT_TOKEN_TYPE) {
		case COMMA:
			NEXT_TOKEN;
			break;
		case RB:
			if (col_index != col_guard) PARSE_ERROR("insert语句中列数目大于values语句中指定值的数目,VALUES 子句中值的数目必须与 INSERT 语句中指定的列的数目匹配");
			NEXT_TOKEN;
			if (TOKEN_TYPE == COMMA) {
				data_size_index++;
				col_index = 0;
				if (MOVE_NEXT_TOKEN_TYPE != LB) PARSE_ERROR("缺少 ( ");
				NEXT_TOKEN;
			}else {
				printf("%d行受影响\n", data_size_index + 1);
				table->record_size += data_size_index + 1;
				return 1;
			}
			break;
		default:
			PARSE_ERROR("缺少 , 或 )");
		}
	}
	ERROR:
	return NULL;
}

static int parse_insert(DBnode* dbnode, Token** curr) {
	Table* table_;
	Column **ptr_col = NULL;
	if ((table_ = DBNODE_SEARCH(dbnode->table_head, (*curr)->value_)) == NULL) PARSE_ERROR("无效表名");
	ptr_col = mem_alloc(table_->column_count * sizeof(size_t));
	int col_guard = 0;
	switch (MOVE_NEXT_TOKEN_TYPE)
	{
	case LB:
		if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("缺少ID");
		Column *col_ = table_->col_head;
		for (;;) {
			if ((col_ = DBNODE_SEARCH(col_, (*curr)->value_)) == NULL) PARSE_ERROR("无对应列名");
			ptr_col[col_guard++] = col_;
			switch (MOVE_NEXT_TOKEN_TYPE)
			{
			case COMMA:
				if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("缺少ID");
				break;
			case RB:
				if (MOVE_NEXT_TOKEN_TYPE != VALUES) PARSE_ERROR("缺少values");
				NEXT_TOKEN;
				if ((parse_insert_values(dbnode, ptr_col, table_, curr, col_guard)) == NULL) goto ERROR;
				return 1;			
			default: PARSE_ERROR("无对应列名");
			}
		}
	case VALUES:
		if ((parse_insert_values(dbnode, ptr_col, table_, curr, col_guard)) == NULL) goto ERROR;
		return 1;
	default:
		PARSE_ERROR("缺少ID");
	}
ERROR:
	mem_free(ptr_col);
	return NULL;
}

Table* parse_create_table(DBnode *dbnode, Token** curr) {
	Table* table_ = NULL;
	table_ = table_create();
	if (TOKEN_TYPE != ID) PARSE_ERROR("缺少表名");
	move_value(&(*curr)->value_, &table_->name_);
	if (MOVE_NEXT_TOKEN_TYPE != LB) PARSE_ERROR("缺少左括号");
	if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("缺少列名");
	if ((table_->col_head = parse_create_column(dbnode, curr)) == NULL) goto ERROR;
	Column* col_ = table_->col_head;
	table_->column_count = ((Column*)(LIST_GET_PRVE(col_)))->num_ + 1;
	table_->record_size = INIT_TTABLE_NUM;
	int p_var_count = 0;
	int rec_size = 0;
	LIST_LOOP(col_,
		

		);
	return table_;
ERROR:
	mem_free(table_);
	return NULL;
}

static int parse_create(DBnode* dbnode, Token** curr) {
	Table* table_ = NULL;
	switch (TOKEN_TYPE)
	{
	case TABLE:
		if ((table_ = parse_create_table(dbnode, NEXT_TOKEN)) == NULL)
			goto ERROR;
		dbnode->table_head = table_;
		return 1;
		break;
	default:
		PARSE_ERROR("创建节点无效");
		break;
	}
ERROR:
	return NULL;
}

int sql_parse(DBnode *dbnode, Srcstream* stream) {
	Token* token_head;
	if ((token_head = get_next_token(stream)) == NULL) 
		return NULL;
	for (Token *token_next = get_next_token(stream), *head = &token_head->list_head;
		token_next; token_next = get_next_token(stream)) 
		list_add_tail(head, token_next);	
	Token *t_curr = token_head;
	Token **curr = &t_curr;
	do {
		switch (TOKEN_TYPE)
		{
		case CREATE:
			if (parse_create(dbnode, NEXT_TOKEN) == NULL)
				goto ERROR;
			break;
		case SELECT:
			if (MOVE_NEXT_TOKEN_TYPE!= ID)
				goto ERROR;
			parse_select(curr);
			break;
		case INSERT:
			if (MOVE_NEXT_TOKEN_TYPE != INTO) goto ERROR;
			if (MOVE_NEXT_TOKEN_TYPE != ID) goto ERROR;
			parse_insert(dbnode, curr);
			break;
		default:
			break;
		}
	} while (t_curr != token_head);
ERROR:
	list_del_all(token_head, token_del);	
}

int parse_datatype(Column *col, int datatype, Token** curr) {
	col->data_type = datatype;
	switch (datatype) {
	case INT:
		break;
	case CHAR:
		if (MOVE_NEXT_TOKEN_TYPE != LB) {
			col->data_len = 1;
			break;
		}else if(MOVE_NEXT_TOKEN_TYPE != INT) {
			PARSE_ERROR("缺少数据长度");
		}else 
			col->data_len = *(size_t*)(*curr)->value_;
		if (MOVE_NEXT_TOKEN_TYPE != RB)
			PARSE_ERROR("缺少 ) ");
		break;
	case REAL:
		break;
	case TEXT:
		break;
	case TIME:
		break;
	case DATE:
		break;
	case DATETIME:
		break;
	default:
		return 0;
		break;
	}
	switch (MOVE_NEXT_TOKEN_TYPE) {
	case COMMA:
		NEXT_TOKEN;
		break;
	case RB:
		NEXT_TOKEN;
		return 1;
	case NOT:
		break;
	case PRIMARY:
		break;
	case FOREIGN:
		break;
	case DEFAULT:
		break;
	default:
		goto ERROR;
		break;
	}
	return 2;
ERROR:
	return NULL;
}

int parse_not(Column *col, Token** curr) {
	if (TOKEN_TYPE != NULL_) PARSE_ERROR("缺少NULL");
	col->not_null = 1;
	switch (MOVE_NEXT_TOKEN_TYPE) {
	case COMMA:
		NEXT_TOKEN;
		break;
	case RB:
		NEXT_TOKEN;
		return 1;
	case NOT:
		break;
	case PRIMARY:
		break;
	case FOREIGN:
		break;
	case DEFAULT:
		break;
	default:
		return 0;
		break;
	}
	return 2;
ERROR:
	return 0;
}

Column* parse_create_column(DBnode *dbnode, Token** curr) {
	int num_ = 0;
	Column *col_head = col_create(0);
	Column *col_curr = NULL;
	for(;;)
		switch (TOKEN_TYPE){
		case ID:
			if (col_curr == NULL) col_curr = col_head;
			else {
				col_curr = col_create(num_++);
				list_add_tail(col_head, col_curr);
			}
			move_value(&(*curr)->value_, &col_curr->name_);
			switch (parse_datatype(col_curr, MOVE_NEXT_TOKEN_TYPE, curr)) {
			case 1:
				return col_head;
			case 0:
				goto ERROR;
			default:
				continue;
			}
			PARSE_ERROR("缺少数据类型");
			goto ERROR;
			break;
		case NOT:
			switch (parse_not(col_curr, NEXT_TOKEN)) {
			case 1:
				return col_head;
			case 0:
				goto ERROR;
			default:
				break;
			}
			break;
		default:
			goto ERROR;
			break;
		}
ERROR:
	list_del_all(col_head, col_del);
	return NULL;
}

