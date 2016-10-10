#include<stdio.h>
#include"sds.h"
#include"dict.h"
#include<string.h>
#include"MemPool.h"
//void remove_if(node ** head, remove_fn rm)
//{
//	for (node** curr = head; *curr; )
//	{
//		node * entry = *curr;
//		if (rm(entry))
//		{
//			*curr = entry ->next;
//			free(entry);
//		}
//		else
//			curr = &entry ->next;
//	}
//}
#include<stdlib.h>

#define PREFIX_SIZE sizeof(size_t)
#define Increment_User_Mem(__n) do{ \
	if((*__n)&(sizeof(size_t)-1)) *__n += sizeof(size_t)-((*__n)&sizeof(size_t)-1);\
} while(0)
typedef struct c {
	int free;
	int d;
	char *buf;
}c;

int main()
{
	
	Dict *dict = DictCreate();
	sds *key1 = sds_new("key1");
	sds *value1 = sds_new("value1");
	sds *key2 = sds_new("key2");
	sds *value2 = sds_new("value2");
	DictType *type = Memalloc(sizeof(DictType));
	type->hash_funtion = sdshashcode;
	return 0;
}



