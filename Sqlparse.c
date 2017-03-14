#include "Sqlparse.h"
#include "MemPool.h"
extern int parse_create(DBnode* dbnode, Token** curr);
extern Table* parse_create_table(DBnode *dbnode,Token** token);
extern Column* parse_create_column(DBnode *dbnode,Token** token);
extern int parse_datatype(Column*, int datatype, Token**);
extern int parse_insert(DBnode*, Token**);
extern int parse_insert_values(DBnode*, Table*, Token**,int* ,int);

int parse_insert_values(DBnode* dbnode, Table* table, Token** curr,int* fill_field_index,int fill_field_count) {
	int values_index = 0;
	int fill_rec_count = 0;
	size_t data_len = 0;
	int offset_ = 0;
	Column *col_;
	int rec_size_index = TABLE_USED_REC_SIZE(table);
	int *fill_index = fill_field_index;
	if (TOKEN_TYPE != LB) PARSE_ERROR("ȱ�� �� ");
	NEXT_TOKEN;
	for (;;) {
		LIST_FOREACH(col_, table->col_head,
			if (col_->num_ == *fill_index) {
				offset_ = col_->rec_offset;
				fill_index++;
				break;
			}		
			);
		if (!((TOKEN_TYPE == col_->data_type)||
			 TOKEN_TYPE==TEXT && 
			(col_->data_type == CHAR || col_->data_type==VARCHAR)))
			PARSE_ERROR("�������Ͳ�ƥ��");

		switch (TOKEN_TYPE)
		{
		case INT:
			data_len = sizeof(int);
			break;
		case REAL:
			data_len = sizeof(float);
			break;
		case TEXT:
			data_len = strlen((*curr)->value_) + 1;
			break;
		default:
			PARSE_ERROR("ȱ��ID");
			break;
		}
		if (values_index == fill_field_count)
			PARSE_ERROR("insert���������ĿС��values�����ָ��ֵ����Ŀ,VALUES �Ӿ���ֵ����Ŀ������ INSERT �����ָ�����е���Ŀƥ��");
		TABLE_FILL_REC(table, TABLE_USED_REC_SIZE(table), offset_, (*curr)->value_, data_len);
		values_index++;
		switch (MOVE_NEXT_TOKEN_TYPE) {
		case COMMA:
			NEXT_TOKEN;
			break;
		case RB:
			if (values_index != fill_field_count) PARSE_ERROR("insert���������Ŀ����values�����ָ��ֵ����Ŀ,VALUES �Ӿ���ֵ����Ŀ������ INSERT �����ָ�����е���Ŀƥ��");
			table->used_rec_size++;
			rec_size_index++;
			values_index = 0;
			fill_index = fill_field_index;
			fill_rec_count++;
			if (MOVE_NEXT_TOKEN_TYPE == COMMA) {
				if (MOVE_NEXT_TOKEN_TYPE != LB) 
					PARSE_ERROR("ȱ�� ( ");
				NEXT_TOKEN;
			}else {
				printf("%d����Ӱ��\n", fill_rec_count);
				return 0;
			}
			break;
		default:
			PARSE_ERROR("ȱ�� , �� )");
		}
	}
	ERROR:
	return -1;
}

static int parse_insert(DBnode* dbnode, Token** curr) {
	Table* table_;
	Column **ptr_col = NULL;
	if ((table_ = DBNODE_SEARCH(dbnode->table_head, (*curr)->value_)) == NULL) PARSE_ERROR("��Ч����");
	int fill_field_count = 0;
	//TODO
	int fill_field_index[10];
	switch (MOVE_NEXT_TOKEN_TYPE){
	case LB:
		if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("ȱ��ID");
		Column *col_ = NULL;
		for (;;) {
			if ((col_ = DBNODE_SEARCH(table_->col_head, (*curr)->value_)) == NULL) PARSE_ERROR("�޶�Ӧ����");
			fill_field_index[fill_field_count++] = col_->num_;
			switch (MOVE_NEXT_TOKEN_TYPE){
			case COMMA:
				if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("ȱ��ID");
				break;
			case RB:
				if (MOVE_NEXT_TOKEN_TYPE != VALUES) PARSE_ERROR("ȱ��values");
				NEXT_TOKEN;
				if ((parse_insert_values(dbnode, table_, curr,fill_field_index,fill_field_count)) == -1) goto ERROR;
				return 1;			
			default: PARSE_ERROR("�޶�Ӧ����");
			}
		}
	case VALUES:
		//TODO
		if ((parse_insert_values(dbnode, table_, table_, curr, fill_field_count)) == -1) goto ERROR;
		return 0;
	default:
		PARSE_ERROR("ȱ��ID");
	}
ERROR:
	return -1;
}

Table* parse_create_table(DBnode *dbnode, Token** curr) {
	Table* table_ = NULL;
	if (TOKEN_TYPE != ID) PARSE_ERROR("ȱ�ٱ���");
	if (dbnode->table_head != NULL) {
		if (DBNODE_SEARCH(dbnode->table_head, (*curr)->value_) != NULL)
			PARSE_ERROR("�ñ��Ѵ���");
	}
	table_ = table_create();
	move_value(&(*curr)->value_, &table_->name_);
	if (MOVE_NEXT_TOKEN_TYPE != LB) PARSE_ERROR("ȱ��������");
	if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("ȱ������");
	if ((table_->col_head = parse_create_column(dbnode, curr)) == NULL) goto ERROR;
	table_->column_count = ((Column*)(LIST_GET_PRVE(table_->col_head)))->num_ + 1;
	Column* col_ = NULL;
	int offset_ = 0;
	LIST_FOREACH(col_,table_->col_head,
	col_->rec_offset = offset_;
	offset_ += col_->data_len;
	);
	table_->rec_len = offset_;
	char* name_ = table_->name_;
	for (int i = 0; i < INIT_RECROD_NUM; i++) {
		TABLE_ADD_REC(table_, rec_create(name_, offset_));
	}
	return table_;
ERROR:
	if (table_ != NULL)
		table_del(table_);
	return NULL;
}

static int parse_create(DBnode* dbnode, Token** curr) {
	Table* table_ = NULL;
	switch (TOKEN_TYPE)
	{
	case TABLE:
		NEXT_TOKEN;
		if ((table_ = parse_create_table(dbnode, curr)) == NULL)
			goto ERROR;
		if (dbnode->table_head == NULL)
			dbnode->table_head = table_;
		else
			DB_ADD_TABLE(dbnode, table_);
		return 1;
		break;
	default:
		PARSE_ERROR("�����ڵ���Ч");
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
		token_next; token_next = get_next_token(stream)) {
		LIST_ADD_TAIL(&head->list_head, &token_next->list_head);
	}
	Token *t_curr = token_head;
	Token **curr = &t_curr;
	do {
		switch (TOKEN_TYPE)
		{
		case CREATE:
			NEXT_TOKEN;
			if (parse_create(dbnode, curr) == NULL)
				goto ERROR;
			break;
		case SELECT:
			NEXT_TOKEN;
			if (parse_select(dbnode, curr) == -1)
				goto ERROR;
			break;
		case INSERT:
			if (MOVE_NEXT_TOKEN_TYPE != INTO) PARSE_ERROR("ȱ��INTO");
			if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("ȱ��ID");
			if (parse_insert(dbnode, curr) == -1) goto ERROR;
			break;
		default:
			break;
		}
	} while (t_curr != token_head);
	Token* token_ = token_head;
	int i = 0;
	LIST_DEL_ALL(token_, &token_head->list_head, token_del(token_););
	return 0;
ERROR: {
	int i = 1;
	Token* token_ = token_head;
	LIST_DEL_ALL(token_, &token_head->list_head,token_del(token_););
	}
	return -1;
}

int parse_datatype(Column *col, int datatype, Token** curr) {
	col->data_type = datatype;
	switch (datatype) {
	case INT:
		col->data_len = sizeof(int);
		break;
	case CHAR:
		if (MOVE_NEXT_TOKEN_TYPE != LB) {
			col->data_len = 1;
			break;
		}else if(MOVE_NEXT_TOKEN_TYPE != INT) {
			PARSE_ERROR("ȱ�����ݳ���");
		}else 
			col->data_len = *(int*)(*curr)->value_;
		if (MOVE_NEXT_TOKEN_TYPE != RB)
			PARSE_ERROR("ȱ�� ) ");
		break;
	case REAL:
		col->data_len = sizeof(float);
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
	if (TOKEN_TYPE != NULL_) PARSE_ERROR("ȱ��NULL");
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
	Column *col_head = col_create(num_++);
	Column *col_curr = NULL;
	for(;;)
		switch (TOKEN_TYPE){
		case ID:
			if (col_curr == NULL) col_curr = col_head;
			else {
				col_curr = col_create(num_++);
				LIST_ADD_TAIL(&col_head->list_head, &col_curr->list_head);
				if (DBNODE_SEARCH(col_head, (*curr)->value_) != 0)
					PARSE_ERROR("�����Ѵ���");
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
			PARSE_ERROR("ȱ����������");
			goto ERROR;
			break;
		case NOT:
			NEXT_TOKEN;
			switch (parse_not(col_curr, curr)) {
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

