#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

typedef struct Pair {
    void* key;
    void* value;
    struct Pair* next;
} Pair;

typedef struct Map {
    Pair** buckets;
    size_t capacity;
    size_t size;
    size_t (*hashFunction)(void* key);
    int (*keyComparator)(void* key1, void* key2);
} Map;

Map* createMap(size_t (*hashFunction)(void*), int (*keyComparator)(void*, void*));

void insertMap(Map* map, void* key, void* value);

void removeMap(Map* map, void* key);

void* searchMap(Map* map, void* key);

void destroyMap(Map* map);

void* firstMap(Map* map);

void* nextMap(Map* map);

#endif // MAP_H
