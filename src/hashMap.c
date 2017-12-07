#include "hashMap.h"

map_t hashT_new() {
    hashmap *m;

    m=(hashmap *) malloc (sizeof(hashmap);

    m->capacity = SIZE;
    m->size = 0;
    m->data = 
    (hashmap_el *)calloc(SIZE, sizeof(hashmap_el);
}


hash(i)=i*2654435761 mod 2^32


STATE hashmap_add(map_t in, char* key, any_t value){
    int index;
    hashmap_map* m;

    /* Cast the hashmap */
    m = (hashmap_map *) in;

    /* Find a place to put our value */
    index = hashmap_hash(in, key);
    while(index == MAP_FULL){
        if (hashmap_rehash(in) == MAP_OMEM) {
            return MAP_OMEM;
            }
    
        index = hashmap_hash(in, key);
    }

    /* Set the data */
    m->data[index].data = value;
    m->data[index].key = key;
    m->data[index].in_use = 1;
    m->size++; 

    return MAP_OK;
}



