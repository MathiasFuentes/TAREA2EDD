#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 1000000
#define LOAD_FACTOR 0.75

// Crear un nuevo mapa
Map* createMap(size_t (*hashFunction)(void*), int (*keyComparator)(void*, void*)) {
    Map* map = malloc(sizeof(Map));
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->buckets = calloc(map->capacity, sizeof(Pair*));
    map->hashFunction = hashFunction;
    map->keyComparator = keyComparator;
    return map;
}

// Redimensionar el mapa cuando se excede el factor de carga
void resizeMap(Map* map) {
    size_t oldCapacity = map->capacity;
    Pair** oldBuckets = map->buckets;

    map->capacity *= 2;
    map->buckets = calloc(map->capacity, sizeof(Pair*));
    map->size = 0;

    for (size_t i = 0; i < oldCapacity; ++i) {
        Pair* current = oldBuckets[i];
        while (current) {
            insertMap(map, current->key, current->value);
            Pair* toFree = current;
            current = current->next;
            free(toFree);
        }
    }
    free(oldBuckets);
}

// Insertar un par clave-valor en el mapa
void insertMap(Map* map, void* key, void* value) {
    
    if ((double)map->size / map->capacity >= LOAD_FACTOR) {
        resizeMap(map);
    }
    
    size_t index = map->hashFunction(key) % map->capacity;
    Pair* current = map->buckets[index];

    while (current) {
        if (map->keyComparator(current->key, key)) {
            free(current->value);
            current->value = value;
            return;
        }
        current = current->next;
    }

    Pair* newPair = malloc(sizeof(Pair));
    newPair->key = key;
    newPair->value = value;
    newPair->next = map->buckets[index];
    
    map->buckets[index] = newPair;
    map->size += 1;
}


// Remover un elemento del mapa.
void removeMap(Map* map, void* key) {
    size_t index = map->hashFunction(key) % map->capacity;
    Pair* current = map->buckets[index];
    Pair* prev = NULL;
    
    while (current) {
        if (map->keyComparator(current->key, key)) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Buscar un valor dado su clave
void* searchMap(Map* map, void* key) {
    size_t index = map->hashFunction(key) % map->capacity;
    Pair* current = map->buckets[index];
    while (current) {
        if (map->keyComparator(current->key, key)) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// Liberar la memoria del mapa
void destroyMap(Map* map) {
    for (size_t i = 0; i < map->capacity; ++i) {
        Pair* current = map->buckets[i];
        while (current) {
            Pair* toFree = current;
            current = current->next;
            free(toFree);
        }
    }
    free(map->buckets);
    free(map);
}
