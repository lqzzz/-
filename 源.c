#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sds.h"
#include<assert.h>
//malloc��if(p)Ϊ��  �ַ�����'\0'Ϊ��
void strcp(const char* str, char* p)
{
	while (*p++ = *str++);
}

int main()
{
	sds* sdsp = sds_empty();
	sds_free(sdsp);
	return 0;
}

