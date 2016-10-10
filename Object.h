#define OBJTYPE_STRING 0
#define OBJTYPE_LIST 1
#define OBJTYPE_HASH 2
#define ENCONDING_RAW 0
#define ENCONDING_HT 1
typedef struct Object
{
	unsigned char tyep_;
	unsigned char enconding_;
	int refcount_;
	void *ptr_;
}Object;

Object* CreateObject(int type, void *ptr);

Object* CreateRawStringObject(void* ptr);

//int CompareStringObject();