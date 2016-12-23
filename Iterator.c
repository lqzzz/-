#include "Iterator.h"
#include<memory.h>
#include<stdlib.h>
//static void swap(int * a, int *b) {
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//static void quicksort(int *x, int l, int u) {
//	int i, m;
//	if (l >= u) return;
//	m = l;
//	for (i = l + 1; i <= u; i++)
//		if (x[i] < x[l]) // buggy!
//			swap(&x[++m], &x[i]);
//	swap(&x[l], &x[m]);
//	for (int i = 0; i < 10; i++)
//		printf("%d,", x[i]);
//	printf(" Ëã·¨2\n");
//	quicksort(x, l, m - 1);
//	quicksort(x, m + 1, u);
//}

static void swap(void* first, void* second) {
	void* temp = first;
	first = second;
	second = temp;
}

static void* binary_search(Iterator* begin, Iterator* end, void* val, Comparefun comp) {

}

static void insert_sort(Iterator* begin, Iterator* end) {

}

static void quick_sort(Iterator* begin, Iterator* end) {

}

void * filter(void * iter, int type, int c)
{

}

void sort(Iterator* begin, Iterator* end, int comp(void*, void*)) {

}
