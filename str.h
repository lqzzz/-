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
//void str_trim(str* strp, const char* str);

//char bu[] ÓÃ·¨£»
//char p[] = "abcdastrdf";
//int len = strlen(p);
//a *c = malloc(sizeof(a) + len);
//memcpy(c->bu, p, len);
//puts(p);
//puts(c->bu);
//c->bu[len] = '\0';
//if (c->bu[len] == '\0')
//printf("yes\n");
//char *d = "123";
//memcpy(c->bu, d, 3);
//c->bu[3] = '\0';
//puts(c->bu);
//return 0;