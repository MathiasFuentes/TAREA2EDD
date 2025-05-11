#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

/*
  Estructura Pair:
  Representa un par clave-valor dentro del mapa.
*/
typedef struct Pair {
    void* key;
    void* value;
    struct Pair* next;
} Pair;

/*
  Estructura Map:
  Representa un mapa hash con manejo de colisiones mediante listas enlazadas.
*/
typedef struct Map {
    Pair** buckets;                              // Arreglo de punteros a pares (buckets)
    size_t capacity;                             // Capacidad total del mapa
    size_t size;                                 // Cantidad de elementos actuales
    size_t currentIndex;                         // Índice actual para iteración
    Pair* currentPair;                           // Par actual para iteración
    size_t (*hashFunction)(void* key);           // Función hash
    int (*keyComparator)(void* key1, void* key2); // Función de comparación de claves
} Map;

// Crea un mapa vacío con funciones de hash y comparación personalizadas.
Map* createMap(size_t (*hashFunction)(void*), int (*keyComparator)(void*, void*));

// Inserta una clave y su valor en el mapa (reemplaza si ya existe).
void insertMap(Map* map, void* key, void* value);

// Elimina un par clave-valor del mapa.
void removeMap(Map* map, void* key);

// Busca y devuelve el valor asociado a una clave, o NULL si no existe.
void* searchMap(Map* map, void* key);

// Libera toda la memoria utilizada por el mapa.
void destroyMap(Map* map);

// Retorna el primer par del mapa (para iterar).
Pair* firstMap(Map* map);

// Retorna el siguiente par del mapa (para iterar).
Pair* nextMap(Map* map);

#endif // MAP_H

