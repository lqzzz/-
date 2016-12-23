#include "str.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"MemPool.h"
//第一版 字符串拼接
//if (pstr->free <= size)
//{
//	size_t newsize = (pstr->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';
//	while (*newstrp++ == *oldstrp++);//去死！！
//	char* constrp = newstrp;
//	while (*constrp++ = *str++);
//	pstr->buf = restrp;
//	free(pstr->buf);
//	pstr->free = pstr->len = (newsize - 1) / 2;
//}
//第二版 字符串拼接
//if (pstr->free <= size)
//{
//	size_t newsize = (pstr->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';//!!
//	while (*restrp++ = *oldstrp++);//
//	puts(newstrp); //
//	char* constrp = restrp;
//	--constrp		//这里需要会退一个指针
//	while (*constrp++ = *str++);
//	puts(newstrp);
//	free(pstr->buf);
//	pstr->buf = newstrp;
//	pstr->free = pstr->len = (newsize - 1) / 2;
//}

//第一版 字符串拼接
//else
//{
//	char *endstrp = pstr->buf + pstr->len;
//	while (*endstrp++ == *str++);//又是这里
//	pstr->free -= size - 1;
//	pstr->len += size - 1;
//}

//第一版 接受一个 str 和一个 C 字符串作为参数，清除在C字符串中出现过的str字符
//外循环采用c字符串，改进后用str
//void str_trim(str * strp, const char * str)
//{
//	int freecount = 0;
//	while (*str)
//	{
//		int i = 0;
//		for (i = 0; i < strp->len; i++)
//		{
//			char *target = strp->buf + i;
//			if (*target == *str)
//			{
//				*target = '\0';
//				strp->free++;
//				freecount++;
//			}
//			else
//			{
//
//			}
//		
//			
//		}
//		str++;
//	}
//	strp->len -= freecount;
//}

//void str_clear(const string strp)
//{
//	char* p = strp->buf;
//	while (*p++) strp->free++;
//	strp->len = 0;
//	*strp->buf = '\0';
//}

//void str_cat(string *pstr, const char * str)
//{
//	int size = (int)strlen(str) + 1;//计算所需分配的空间
//	char *oldstrp = pstr->buf;
//	if (pstr->free <= size)
//	{	
//		size_t newsize = (pstr->len + size)*2-1; //新开辟字符串，并扩容
//		char* newstrp = mem_alloc(newsize);
//		assert(newstrp);
//		char* restrp = newstrp;
//		*newstrp = '\0';
//		while (*restrp++ = *oldstrp++);
//		--restrp;//回退至'\0'
//		while (*restrp++ = *str++);
//		free(pstr->buf);//释放原字符串内存
//		pstr->buf = newstrp;//指向新内存
//		pstr->free = pstr->len = (newsize - 1) / 2;
//	}
//	else
//	{
//		char *endstrp = pstr->buf + pstr->len;//直接偏移至'\0'
//		while (*endstrp++ = *str++);
//		pstr->free -= size - 1;
//		pstr->len += size - 1;
//	}
//}
void str_cpy(const char * str, string * pstr)
{
	
}
void str_growzero(string * strp)
{

}

//int str_compare(string * s1, string * s2)
//{
//	if (s1&&s2)
//	{
//		int len;
//		len = str_len(s1);
//		return memcmp(s1->buf, s2->buf, len);
//	}
//	return -1;
//	//return strcmp(s1->buf, s2->buf);
//}

//void str_trim(str * strp, const char * str)
//{
//	int freecount = 0;
//	char *strstr = strp->buf;
//	int in = strp->len;
//	int saveindex[in] = 0;
//	while (*strstr)
//	{
//		int i = 0;
//		for (i = 0; i < strlen(str); i++)
//		{
//
//		}
//		/*int i = 0;
//		for (i = 0; i < strp->len; i++)
//		{
//			char *target = strp->buf + i;
//			if (*target == *str)
//			{
//				*target = '\0';
//				strp->free++;
//				freecount++;
//			}
//			else
//			{
//
//			}
//		
//			
//		}
//		str++;*/
//	}
//	strp->len -= freecount;
//}

//string str_dup(const string const source)
//{	
//	string strp = str_empty();
//	strp->buf = mem_alloc(source->free+source->len+1);//注意分配内存！
//	strp->free = source->free;
//	strp->len = source->len;
//	char *sp = source->buf;
//	char *dp = strp->buf;
//	int len = str_len(source);
//	memcpy(dp,sp,len);
//	dp[len] = '\0';
//	/*char *sp = source->buf;
//	char *dp = strp->buf;
//	*dp = '\0';
//	while (*dp++ = *sp++);*/
//	return strp;
//}

int str_avail(const string * strp)
{
	struct strh	*strh_ = strp - sizeof(struct strh);
	return strh_->free_size;
}

//int str_len(const string  strp)
//{
//	struct strh* sh;
//	sh = strp - sizeof(struct strh);
//	return sh->free_size;
//}

string str_new_len(const char * src, size_t initlen){
	struct strh* sh;
	if (src)
		sh = mem_alloc(sizeof(struct strh) + initlen + 1);
	else {
		sh = mem_alloc(sizeof(struct strh) + initlen + 1);
		memset(sh->buf_, 0, initlen);
	}
	if (sh == NULL) return NULL;
	sh->free_size = 0;
	sh->used_size = initlen;
	if (src && initlen)
		memcpy(sh->buf_, src, initlen + 1);
	return sh->buf_;
}

string str_new(const char * src){
	size_t initlen = src ? strlen(src) : 0;
	return str_new_len(src, initlen);
}

string str_empty(){
	return str_new_len(NULL, 0);
}

int str_free(string str)
{
	if (!str) return NULL;
	struct strh* sh = str - sizeof(struct strh);
	mem_free(str);
	mem_free(sh);
	return 1;
}
