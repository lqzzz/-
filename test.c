#include<stdio.h>
#include"str.h"
#include"dict.h"
#include<string.h>
#include"Object.h"
#include"DB.h"
#include"MemPool.h"
#include"stdlib.h"
#include <stdio.h>
#include "SourceStream.h"
//#include<time.h>
#include "Pair.h"
#include "Sqlparse.h"
#include "Scanner.h"
#include "Relation.h"
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

int main() {
	mem_alloc_enable_thread_safeness();
	init_key_word();
	Srcstream stream;
	stream.c_num = 1;
	stream.l_num = 1;
	char *sqlstr[] = {
		"create table SCInfo(Sno char(10),Cno char(10),Score int)",
		"create table StuInfo(Sno char(8),Sname char(8))",
		"create table CourseInfo(Cno char(10),Cname char(10))",
	    "insert into CourseInfo(Cno,Cname) values('0001','数学'),('0002','英语'),('0003','物理'),('0004','计算机')",
		"insert into SCInfo(Sno,Cno,Score) values('0001','0001',90),('0002','0002',100),('0003','0001',50),('0004','0004',90),('0001','0002',40)",
		"insert into StuInfo(Sno,Sname) values('0001','我的'),('0002','天啊'),('0003','操你'),('0004','妈的')",
		//"select* from SCInfo where Score = 40 Score = 50",
		//"select* from SCInfo where Score = 40 Score = 50",
		//"select* from StuInfo,CourseInfo,SCInfo where Score = 40 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno Score = 50" ,
		//"select* from StuInfo,CourseInfo,SCInfo where Score = 40 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno Score = 50" ,
		"select* from StuInfo,CourseInfo,SCInfo where Score = 40 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and (Score = 50 or Score = 100)" ,
		"select* from StuInfo,CourseInfo,SCInfo where Score = 40 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and (Score = 50 or Score = 100)" ,
		"select* from StuInfo,CourseInfo,SCInfo where Score = 90 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and (Score = 50 or Score = 100)" ,
		"select* from StuInfo,CourseInfo,SCInfo where Score = 90 or StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and (Score = 50 or Score = 100)" ,
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno or Score = 50 or Score = 100",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno or Score = 50 or Score = 100",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score = 50 ",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score = 50 ",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and (Score = 50 or Score = 100)" ,
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score = 50",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score = 50",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score != 50",
		"select* from StuInfo,CourseInfo,SCInfo where StuInfo.Sno = SCInfo.Sno and SCInfo.Cno = CourseInfo.Cno and Score != 50",
					   };
	DBnode *db = database_create();
	int pr = 0;
	for (int i = 0; i < 12; i++) {
		char* str = sqlstr[i];
		stream.str = str;
		if (sql_parse(db, &stream) == 0);
		printf("命令成功完成  ");
		int memus = malloc_used_memory();
		printf("内存使用： %d  内存差: %d\n", memus, memus - pr);
		pr = memus;
	}
	
	//TestList(";
	//printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
	//	test_pass * 100.0 / test_count);
	//return main_ret;
	getchar();
	return 0;
}

