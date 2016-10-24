#include "sds.h"
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"MemPool.h"
//��һ�� �ַ���ƴ��
//if (psds->free <= size)
//{
//	size_t newsize = (psds->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';
//	while (*newstrp++ == *oldstrp++);//ȥ������
//	char* constrp = newstrp;
//	while (*constrp++ = *str++);
//	psds->buf = restrp;
//	free(psds->buf);
//	psds->free = psds->len = (newsize - 1) / 2;
//}
//�ڶ��� �ַ���ƴ��
//if (psds->free <= size)
//{
//	size_t newsize = (psds->len + size) * 2 - 1;
//	char* newstrp = malloc(newsize);
//	char* restrp = newstrp;
//	*newstrp = '\0';//!!
//	while (*restrp++ = *oldstrp++);//
//	puts(newstrp); //
//	char* constrp = restrp;
//	--constrp		//������Ҫ����һ��ָ��
//	while (*constrp++ = *str++);
//	puts(newstrp);
//	free(psds->buf);
//	psds->buf = newstrp;
//	psds->free = psds->len = (newsize - 1) / 2;
//}

//��һ�� �ַ���ƴ��
//else
//{
//	char *endstrp = psds->buf + psds->len;
//	while (*endstrp++ == *str++);//��������
//	psds->free -= size - 1;
//	psds->len += size - 1;
//}

//��һ�� ����һ�� SDS ��һ�� C �ַ�����Ϊ�����������C�ַ����г��ֹ���sds�ַ�
//��ѭ������c�ַ������Ľ�����sds
//void sds_trim(sds * sdsp, const char * str)
//{
//	int freecount = 0;
//	while (*str)
//	{
//		int i = 0;
//		for (i = 0; i < sdsp->len; i++)
//		{
//			char *target = sdsp->buf + i;
//			if (*target == *str)
//			{
//				*target = '\0';
//				sdsp->free++;
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
//	sdsp->len -= freecount;
//}
void sds_clear(sds * const sdsp)
{
	char* p = sdsp->buf;
	while (*p++) sdsp->free++;
	sdsp->len = 0;
	*sdsp->buf = '\0';
}
void sds_cat(sds *psds, const char * str)
{
	int size = (int)strlen(str) + 1;//�����������Ŀռ�
	char *oldstrp = psds->buf;
	if (psds->free <= size)
	{	
		size_t newsize = (psds->len + size)*2-1; //�¿����ַ�����������
		char* newstrp = Memalloc(newsize);
		assert(newstrp);
		char* restrp = newstrp;
		*newstrp = '\0';
		while (*restrp++ = *oldstrp++);
		--restrp;//������'\0'
		while (*restrp++ = *str++);
		free(psds->buf);//�ͷ�ԭ�ַ����ڴ�
		psds->buf = newstrp;//ָ�����ڴ�
		psds->free = psds->len = (newsize - 1) / 2;
	}
	else
	{
		char *endstrp = psds->buf + psds->len;//ֱ��ƫ����'\0'
		while (*endstrp++ = *str++);
		psds->free -= size - 1;
		psds->len += size - 1;
	}
}
void sds_cpy(const char * str, sds * psds)
{
	
}
void sds_growzero(sds * sdsp)
{

}
int sds_compare(sds * s1, sds * s2)
{
	if (s1&&s2)
	{
		int len;
		len = sds_len(s1);
		return memcmp(s1->buf, s2->buf, len);
	}
	return -1;
	//return strcmp(s1->buf, s2->buf);
}
//void sds_trim(sds * sdsp, const char * str)
//{
//	int freecount = 0;
//	char *sdsstr = sdsp->buf;
//	int in = sdsp->len;
//	int saveindex[in] = 0;
//	while (*sdsstr)
//	{
//		int i = 0;
//		for (i = 0; i < strlen(str); i++)
//		{
//
//		}
//		/*int i = 0;
//		for (i = 0; i < sdsp->len; i++)
//		{
//			char *target = sdsp->buf + i;
//			if (*target == *str)
//			{
//				*target = '\0';
//				sdsp->free++;
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
//	sdsp->len -= freecount;
//}
sds* sds_dup(const sds* const source)
{	
	sds* sdsp = sds_empty();
	sdsp->buf = Memalloc(source->free+source->len+1);//ע������ڴ棡
	sdsp->free = source->free;
	sdsp->len = source->len;
	char *sp = source->buf;
	char *dp = sdsp->buf;
	int len = sds_len(source);
	memcpy(dp,sp,len);
	dp[len] = '\0';
	/*char *sp = source->buf;
	char *dp = sdsp->buf;
	*dp = '\0';
	while (*dp++ = *sp++);*/
	return sdsp;
}

int sds_avail(const sds *const sdsp)
{
	return sdsp->free;
}

unsigned int sdshashcode(const sds *const target)
{
	unsigned int num = 0;
	char *str = target->buf;
	while (*str++)
	{
		int inte = *str;
		num = (num * 10) + inte;
	}
	return num % 97;
}

int sds_len(const sds*const sdsp)
{
	sds * p = sdsp;
	return sdsp->len;
}

sds * sds_new(const char * src)
{
	sds* sdsp = sds_empty();
	//char* p = sdsp->buf = (char*)malloc(sizeof(strlen(src)+1));//sizeofʲô��
	char* p = sdsp->buf = Memalloc(strlen(src) + 1);//'\0'�ַ�
	*p = '\0';
	while (*p++=*src++) sdsp->len++; //��ֵͬʱƫ������һλ
	return sdsp;
}

sds * sds_empty()
{
	sds *p = Memalloc(sizeof(sds));
	assert(p);
	p->buf = NULL;
	p->free = 0;
	p->len = 0;
	return p;
}

int sds_free(sds* block)
{
	assert(block);
	if(block->buf) FreeMem(block->buf);
	FreeMem(block);
	return 1;
}
