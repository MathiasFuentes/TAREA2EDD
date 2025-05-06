#ifndef MAP.H
#define MAP.H

// Comenzamos definiendo lo que es el pair del mapa.
// Y la estructura Map, que es variable dependiendo de su aplicación.

typedef struct {
    void *key;
    void *value;
} MapPair;

typedef struct Map Map;
  
/*
Funciones:
    map_create: crea e inicializa un mapa no ordenado, solo definiendo la función is_equal, retornando un puntero al mapa.
    sorted_map_create: también crea un mapa, pero este se crea para que sea ordenado con la función lower_thanl, retorna un puntero al mapa.
    
    map_insert: se inserta un objeto en el mapa y se retorna un puntero al pair insertado.
    map_remove: se elimina un objeto del mapa y retorna un puntero al pair eliminado.
    map_search: se busca un objeto en el mapa y retorna el puntero al pair buscado.

    map_first: devuelve un puntero a la primera pair que contenga la menor clave del mapa.
    map_next: devuelve un puntero al siguiente pair del mapa.

    map_clean: libera la memoria del mapa.
*/

Map *map_create(int (*is_equal)(void *key1, void *key2));
  
Map *sorted_map_create(int (*lower_than)(void *key1, void *key2));
  
void map_insert(Map *map, void *key, void *value);
  
MapPair *map_remove(Map *map, void *key);
  
MapPair *map_search(Map *map, void *key);
  
MapPair *map_first(Map *map);
  
MapPair *map_next(Map *map);

void map_clean(Map *map);

#endif