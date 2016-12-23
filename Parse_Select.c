#include "Parse_Select.h"
extern Condition* get_term(Token** curr);
extern Condition* get_factor(Token** curr);
static Condition* get_factor(Token** curr) {
	Condition* con_ = NULL;
	if(TOKEN_TYPE == ID || TOKEN_TYPE == TEXT){
		con_ = mem_calloc(1,sizeof(Condition));
		if (NEXT_TOKEN_TYPE == DOT) {
			move_value(&(*curr)->value_, &con_->left_op.table_name);
			NEXT_TOKEN;
			if(MOVE_NEXT_TOKEN_TYPE != ID && TOKEN_TYPE != TEXT) PARSE_ERROR("缺少ID");
			move_value(&(*curr)->value_, &con_->left_op.attribute_);
		}else move_value(&(*curr)->value_, &con_->left_op.attribute_);
		if (MOVE_NEXT_TOKEN_TYPE != IN    && 
			TOKEN_TYPE != LIKE  &&
			TOKEN_TYPE != EQUAL &&
			TOKEN_TYPE != EXISTS)
			PARSE_ERROR("缺少运算符");
		con_->oper_ = TOKEN_TYPE;

		if (MOVE_NEXT_TOKEN_TYPE != ID && TOKEN_TYPE != TEXT) PARSE_ERROR("缺少ID");
		if (NEXT_TOKEN_TYPE == DOT) {
			move_value(&(*curr)->value_, &con_->right_op.table_name);
			NEXT_TOKEN;
			if(MOVE_NEXT_TOKEN_TYPE != ID && TOKEN_TYPE != TEXT) PARSE_ERROR("缺少ID");
			move_value(&(*curr)->value_, &con_->right_op.attribute_);
		}else move_value(&(*curr)->value_, &con_->right_op.attribute_);
		NEXT_TOKEN;
		return con_;
	}else if(TOKEN_TYPE == LB){
		con_ = get_con_exp(NEXT_TOKEN);
		if (TOKEN_TYPE != RB) PARSE_ERROR("缺少 )");
		NEXT_TOKEN;
		return con_;
	}else PARSE_ERROR("缺少 ( 或 ID");
ERROR:
	mem_free(con_);
	return NULL;		
}

static Condition* get_term(Token** curr) {
	Condition* con_ = NULL;
	if ((con_ = get_factor(curr)) == NULL)
		goto ERROR;
	for (;;) 
		if (TOKEN_TYPE == AND) {
			Condition* right_con;
			if ((right_con = get_factor(NEXT_TOKEN)) == NULL)
				goto ERROR;
			con_ = create_con(AND, con_, right_con);
		}else break;	
	return con_;
ERROR:
	mem_free(con_);
	return NULL;
}

Condition* get_con_exp(Token** curr) {
	Condition* con_ = NULL;
	if ((con_ = get_term(curr)) == NULL)
		goto ERROR;
	for(;;)
		if (TOKEN_TYPE == OR) {
			Condition* right_con = NULL;
			if ((right_con = get_term(NEXT_TOKEN)) == NULL) goto ERROR;
			con_ = create_con(OR, con_, right_con);
		}else break;
	return con_;
ERROR:
	mem_free(con_);
	return NULL;
}

void interpre_select(DBnode* database,Query* query){
			

}

Query* parse_select(Token** curr) {
	Query* query_ = mem_calloc(1,sizeof(Query));
	int col_count = 0;
	for (;;)
		if (TOKEN_TYPE == ID) {
			move_value(&(*curr)->value_, query_->sel_list + col_count++);
			if (MOVE_NEXT_TOKEN_TYPE != COMMA)
				break;
			if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("缺少ID");
		}
	query_->sel_list_count = col_count;
	if (TOKEN_TYPE != FROM)
		PARSE_ERROR("缺少FROM");
	if (MOVE_NEXT_TOKEN_TYPE != ID)
		PARSE_ERROR("缺少ID");
	int from_list_cunt = 0;
	for (;;)
		if (TOKEN_TYPE == ID) {
			move_value(&(*curr)->value_, query_->from_list + from_list_cunt++);
			if (MOVE_NEXT_TOKEN_TYPE != COMMA)
				break;
			if (MOVE_NEXT_TOKEN_TYPE != ID) PARSE_ERROR("缺少ID");
		}
	if (TOKEN_TYPE != WHERE)
		PARSE_ERROR("缺少where");
	query_->from_list_count = from_list_cunt;
	query_->con_ = get_con_exp(NEXT_TOKEN);
ERROR:
	free(query_);
}

Condition* create_con(int oper, Condition* leftcon, Condition* rightcon){
	Condition* con_ = mem_calloc(1,sizeof(Condition));
	con_->oper_ = oper;
	con_->left_con = leftcon;
	con_->right_con = rightcon;
	return con_;
}

void delete_con(Condition* con){
	if (con->oper_ == OR || con->oper_ == AND) {
		delete_con(con->left_con);
		delete_con(con->right_con);
	}
	mem_free(con->left_op.attribute_);
	mem_free(con->left_op.table_name);
	mem_free(con->right_op.table_name);
	mem_free(con->right_op.table_name);
	mem_free(con->query_);
	mem_free(con);
}

void delete_que(Query* que){
	
}
