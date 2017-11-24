#ifndef __HASHMAP_H
#define __HASHMAP_H
#define SIZE 1024       /* Total Size of Hash Map */
#define STATE int
#define TRUE 1          /* Value for True */
#define FALSE 0         /* Value for False */
#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2     /* Hashmap is full */
#define MAP_OMEM -1     /* Out of Memory */
#define MAP_OK 0        /* OK */


/* Struct for the Hash Map */
typedef struct _hashmap {
    int capacity;
    int size;
    struct _elements **data
}hashmap;

/* Struct for the Elements of Hash Map */
typedef struct _elements {
    int key;
    int in_use;
    void *value
}hashmap_el;

typedef void* map_t;

extern map_t hashmap_new();

extern STATE hashmap_add();

extern hashmap_get();
 
extern hashmap_remove();
 
extern hashmap_size();
 
extern hashmap_iterator();


#endif
