
#ifndef __SKIPLIST_H
#define __SKIPLIST_H
typedef struct SkipNode
{
	struct SkipNode *back_ward;

	double score;

	typedef struct SkipListlevel
	{
		struct SkipNode *for_word;

		unsigned int span;
	}level[];

	void *data;

}SkipNode;
typedef struct Skiplist
{
	SkipNode* head_, tail_;
	int level;
	unsigned long length;
}SkipList;
#endif // __SKIPLIST_H