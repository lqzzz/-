#include "Scanner.h"

extern uint16_t char_type(char);
extern Token* scanner(Srcstream*);
extern Token* token_new(const char*, uint16_t, uint16_t, int);

static uint16_t char_type(char ch) {
	if (ch >= 'a'&&ch <= 'z' ||
		ch >= 'A'&&ch <= 'Z' ||
		ch == '_')
		return ID;
	else if (ch >= '0'&&ch <= '9')
		return INT;
	else if (ch == '\'')
		return TEXT;
}

static Token* token_new(const char* value, uint16_t cnum, uint16_t lnum, int tokentype) {
	Token* token_;
	token_ = mem_alloc(sizeof(Token));
	token_->c_num = cnum;
	token_->l_num = lnum;
	token_->token_type = tokentype;
	LIST_INIT(token_);
	token_->value_ = NULL;
	if (value) {
		token_->value_ = mem_alloc(strlen(value) + 1);
		char* str = token_->value_;
		while (*str++ = *value++);
	}
	return token_;
}

static Token* scanner(Srcstream* stream) {
	const char** src_ = &stream->str;
	int *c_num = &stream->c_num;
	int *l_num = &stream->l_num;
	char *p = *src_;
	char ch = *p;
	size_t len_ = 0;
	uint16_t type;
	switch (type = char_type(ch))
	{
	case ID:
		while (ch >= 'a' && ch <= 'z' ||
			ch >= 'A' && ch <= 'Z' ||
			ch >= '0' && ch <= '9' ||
			ch == '_') {
			(*c_num)++;
			len_++;
			ch = *++*src_;
		}
		break;
	case INT: {
		Token* token_ = token_new(NULL, *c_num, *l_num, INT);
		token_->value_ = mem_alloc(sizeof(int));
		int *p_int = token_->value_;
		int num_ = 0;
		while (ch >= '0'&&ch <= '9') {
			num_ += (ch - '0') * 10;
			(*c_num)++;
			len_++;
			ch = *++*src_;
		}
		*p_int = num_;
		return token_;
	}
	case TEXT:
		p = ++*src_;
		(*c_num)++;
		ch = *p;
		while (ch != '\'') {
			(*c_num)++;
			len_++;
			ch = *++*src_;
		}
		++*src_;
		break;
	default:
		++*src_;
		switch (ch) {
		case '(': return token_new(NULL, *c_num, *l_num, LB);
		case ')': return token_new(NULL, *c_num, *l_num, RB);
		case ',': return token_new(NULL, *c_num, *l_num, COMMA);
		case ';': return token_new(NULL, *c_num, *l_num, SEM);
		case '=': return token_new(NULL, *c_num, *l_num, EQUAL);
		case '.': return token_new(NULL, *c_num, *l_num, DOT);
		default : break;
		}
		break;
	}
	char *token_str = mem_alloc(len_ + 1);
	for (int i = 0; i < len_ ; ++i)
		*token_str++ = *p++;
	*token_str = '\0';
	token_str -= len_;
	int token_type;
	Token *token_ = NULL;
	if (token_type = dict_get_value(dict, token_str)) {
		token_ = token_new(NULL, *c_num, *l_num, token_type);
		mem_free(token_str);
	}
	else
		token_ = token_new(token_str, *c_num, *l_num, type);
	return token_;
}

void token_del(Token* token){
	void *value_ = token->value_;
	char *name = value_;
	if (value_)
		mem_free(value_);
	mem_free(token);
}

Token* get_next_token(Srcstream* stream) {
	const char** src_ = &stream->str;
	int *c_num = &stream->c_num;
	int *l_num = &stream->l_num;
	char ch;
	while (ch = **src_)
		if (ch == ' ' || ch == ';') {
			(*src_)++;
			(*c_num)++;
		}
		else if (ch == '\n') {
			(*l_num)++;
			(*src_)++;
		}
		else return scanner(stream);
		return NULL;
}

void move_value(void** src, void** dest){
	*dest = *src;
	*src = NULL;
}

void init_key_word() { 
	DictType* dict_type = mem_alloc(sizeof(DictType));
	dict_type->key_match = strcmp;
	dict_type->key_dup = NULL;
	dict_type->value_dup = NULL;
	dict = dict_create(dict_type);
	dict_add_entry(dict, "create", CREATE);
	dict_add_entry(dict, "view", VIEW);
	dict_add_entry(dict, "table", TABLE);
	dict_add_entry(dict, "index", INDEX);

	dict_add_entry(dict, "text", TEXT);
	dict_add_entry(dict, "real", REAL);
	dict_add_entry(dict, "date", DATE);
	dict_add_entry(dict, "datetime", DATETIME);
	dict_add_entry(dict, "char", CHAR);
	dict_add_entry(dict, "varchar", VARCHAR);
	dict_add_entry(dict, "time", TIME);
	dict_add_entry(dict, "int", INT);
	dict_add_entry(dict, "bool", BOOL);

	dict_add_entry(dict, "primary", PRIMARY);
	dict_add_entry(dict, "key", KEY);
	dict_add_entry(dict, "update", UPDATE);
	dict_add_entry(dict, "foreign", FOREIGN);
	dict_add_entry(dict, "references", REFERENCES);
	dict_add_entry(dict, "null", NULL_);
	dict_add_entry(dict, "not", NOT);

	dict_add_entry(dict, "select", SELECT);
	dict_add_entry(dict, "where", WHERE);
	dict_add_entry(dict, "=", EQUAL);
	dict_add_entry(dict, "or", OR);
	dict_add_entry(dict, "and", AND);
	dict_add_entry(dict, "like", LIKE);
	dict_add_entry(dict, "from", FROM);
	dict_add_entry(dict, "group", GROUP);
	dict_add_entry(dict, "by", BY);
	dict_add_entry(dict, "order", ORDER);
	dict_add_entry(dict, "having", HAVING);

	dict_add_entry(dict, "procedure", PROCEDURE);
	dict_add_entry(dict, "alter", ALTER);
	dict_add_entry(dict, "add", ADD);
	dict_add_entry(dict, "drop", DROP);
	dict_add_entry(dict, "commit", COMMIT);
	dict_add_entry(dict, "transaction", TRANSACTION);
	dict_add_entry(dict, "unique", UNIQUE);

	dict_add_entry(dict, "insert", INSERT);
	dict_add_entry(dict, "into", INTO);
	dict_add_entry(dict, "values", VALUES);
	dict_add_entry(dict, "on", ON);
	dict_add_entry(dict, "set", SET);
	dict_add_entry(dict, "as", AS);
	dict_add_entry(dict, "delete", DELETE);
	dict_add_entry(dict, "union", UNION);
	dict_add_entry(dict, "rollback", ROLLBACK);

	dict_add_entry(dict, "avg", AVG);
	dict_add_entry(dict, "max", MAX);
	dict_add_entry(dict, "min", MIN);

	dict_add_entry(dict, "'", SQM);
	dict_add_entry(dict, ";", SEM);
	dict_add_entry(dict, "(", LB);
	dict_add_entry(dict, ")", RB);
	dict_add_entry(dict, ",", COMMA);
	dict_add_entry(dict, ".", DOT);
}