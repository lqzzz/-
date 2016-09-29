#pragma once
#define MAXSIZE 1000
typedef struct sdshdr {
	int len;

	int free;
	
	char *buf;
	//char buf[MAXSIZE];必须指定大小,但整个结构过大

}sds;

int sds_len(const sds*const sdsp);
sds* sds_new(const char *dest);
sds* sds_empty();
void sds_free(sds* block);
int sds_avail(const sds *const sdsp);
sds* sds_dup(const sds* const source);
void sds_clear(sds * const sdsp);
void sds_cat(sds * psds, const char* str);
void sds_cpy(const char* str, sds* psds);
void sds_growzero(sds *sdsp);
void sds_trim(sds* sdsp, const char* str);