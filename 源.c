#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sds.h"
#include<assert.h>
#include"list.h"
//malloc后if(p)为真  字符串中'\0'为假
void strcp(const char* str, char* p)
{
	while (*p++ = *str++);
}

void* sum(void* p) {
	return p;
}

typedef char*(*fun)(char*);

int main() 
{
	fun f = sum;
	//puts(f("qwert"));
	puts(sum("asdfg"));
	/*sds* psds = sds_new("what the fuck");
	list *Linklist = list_creat();
	list_set_dup(Linklist, sds_dup);
	list_set_free(Linklist, sds_free);
	list_add_head(Linklist, psds);
	sds *p = (sds*)Linklist->head->value;
	puts(p->buf);*/
	return 0;
	
}

