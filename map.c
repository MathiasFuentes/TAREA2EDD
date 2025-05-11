#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 1000000
#define LOAD_FACTOR 0.75

/*
    Función createMap:
    Inicializa y reserva memoria para un nuevo mapa hash, configurando su capacidad inicial,
    asignando su arreglo de buckets y asociando las funciones hash y de comparación entregadas
    como parámetros. Este mapa permite almacenar pares clave-valor de forma eficiente.
*/

Map* createMap(size_t (*hashFunction)(void*), int (*keyComparator)(void*, void*)) {
    Map* map = malloc(sizeof(Map));
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->buckets = calloc(map->capacity, sizeof(Pair*));
    map->hashFunction = hashFunction;
    map->keyComparator = keyComparator;
    return map;
}

/*
    Función resizeMap:
    Duplica la capacidad del mapa cuando se supera el factor de carga.
    Reasigna y reubica todos los pares clave-valor en el nuevo arreglo de buckets,
    utilizando la función de hash para determinar su nueva posición.
    También libera la memoria de los pares antiguos.
*/

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

/*
    Función insertMap:
    Inserta un nuevo par clave-valor en el mapa. Si la clave ya existe, reemplaza su valor.
    Antes de insertar, verifica si se debe redimensionar el mapa según el factor de carga.
    Usa la función de hash para ubicar el bucket correspondiente y gestiona colisiones con encadenamiento.
*/

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


/*
    Función removeMap:
    Elimina del mapa un par clave-valor dado su clave. Si se encuentra, se ajustan los punteros
    del bucket correspondiente para excluir el par y se libera su memoria.
    Disminuye el tamaño del mapa al remover correctamente.
*/

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

/*
    Función searchMap:
    Busca en el mapa un valor asociado a una clave determinada.
    Devuelve el valor si se encuentra la clave; de lo contrario, retorna NULL.
*/
 
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

/*
    Función destroyMap:
    Libera toda la memoria asociada al mapa, incluyendo cada uno de los pares en los buckets,
    el arreglo de buckets y la estructura del mapa en sí.
*/

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

static size_t iter_index = 0;
static Pair* iter_pair = NULL;

/*
    Función firstMap:
    Inicializa la iteración sobre el mapa y retorna el primer par clave-valor encontrado.
    Utiliza variables estáticas para mantener el estado de la iteración.
    Si el mapa está vacío, retorna NULL.
*/

Pair* firstMap(Map* map) {
    iter_index = 0;
    iter_pair = NULL;

    while (iter_index < map->capacity) {
        if (map->buckets[iter_index]) {
            iter_pair = map->buckets[iter_index];
            return iter_pair;
        }
        iter_index++;
    }
    return NULL;
}

/*
    Función nextMap:
    Retorna el siguiente par clave-valor del mapa tras una llamada a firstMap.
    Avanza dentro del bucket actual o continúa con los siguientes buckets si es necesario.
    Retorna NULL si no hay más elementos.
*/

Pair* nextMap(Map* map) {
    if (iter_pair && iter_pair->next) {
        iter_pair = iter_pair->next;
        return iter_pair;
    }

    iter_index++;
    while (iter_index < map->capacity) {
        if (map->buckets[iter_index]) {
            iter_pair = map->buckets[iter_index];
            return iter_pair;
        }
        iter_index++;
    }
    return NULL;
}


