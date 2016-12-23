#include<stdio.h>
#include"str.h"
#include"dict.h"
#include<string.h>
#include"Object.h"
#include"DB.h"
#include"MemPool.h"
#include"Vector.h"
#include"stdlib.h"
#include <stdio.h>
#include "SourceStream.h"
#include<time.h>
#include "Pair.h"
#include "Sqlparse.h"
#include "Listhead.h"
#include "Scanner.h"
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

void TestList() {
	//test_swap(";
	//test_list_creat(";
	//test_list_add_head(";
	//test_list_dup(";
}
//typedef struct A {
//	Listhead	head_;
//	int a;
//}A;
//void delA(A* a) {
//	mem_free(a);
//	printf("É¾³ýA %d\n", a->a);
//}

int main() {
	init_key_word();
	Srcstream stream1;
	stream1.c_num = 1;
	stream1.l_num = 1;
	//char* sqlstr = "create table ti(id text not null,name text,age int not null,score real) insert into ti(id,name) values('shiter','fucker'),('0002','shit')";
	char* sqlstr = "select c1,c2 from t1,t2 where (t1.c3 = t2.c6 or t2.c1 like '%asd') and c3 = t1.c5";
	stream1.str = sqlstr;
	DBnode *db = database_create();
	sql_parse(db, &stream1);
	/*TestList(";
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
		test_pass * 100.0 / test_count);
	return main_ret;*/
	getchar();
	return 0;
}

