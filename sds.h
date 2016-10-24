#ifndef _SDS_H
#define _SDS_H
#define MAXSIZE 1000
typedef struct sdshdr 
{
	int len;
	int free;
	char *buf;
}sds;

unsigned int sdshashcode(const sds *const target);
int sds_len(const sds*const sdsp);
sds* sds_new(const char *src);
sds* sds_empty();
int sds_free(sds* block);
int sds_avail(const sds *const sdsp);
sds* sds_dup(const sds* const source);
void sds_clear(sds * const sdsp);
void sds_cat(sds * psds, const char* str);
void sds_cpy(const char* str, sds* psds);
void sds_growzero(sds *sdsp);
int sds_compare(sds *s1, sds *s2);
#endif _SDS_H
//void sds_trim(sds* sdsp, const char* str);

//char bu[] ÓÃ·¨£»
//char p[] = "abcdasdsdf";
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