#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sds.h"
#include<assert.h>
//malloc后if(p)为真  字符串中'\0'为假
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

