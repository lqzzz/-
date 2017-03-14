#ifndef _STR_H
#define _STR_H
#define MAXSIZE 1000
#include"MemPool.h"
typedef char* string;

struct strh 
{
	int used_size;
	int free_size;
	char buf_[];
};

//int str_len(const string const strp);
string str_new_len(const char* src,size_t initlen);
string str_new(const char *src);
inline int str_avail(const string *const strp);
string str_dup(const string source);
//void str_clear(string * const strp);
//void str_cat(string * pstr, const char* str);
//void str_cpy(const char* str, string pstr);
void str_growzero(string *strp);
//int str_compare(string *s1, string *s2);
#endif _STR_H
