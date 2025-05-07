#include "list.h"
#include "map.h"
#include "extra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTIST 256
#define MAX_ID 512
#define MAX_ALBUM 256
#define MAX_TRACK 512
#define MAX_GENRE 256

//  Definición del struct tipoCanción

typedef struct {
    char id[MAX_ID];
    char artist[MAX_ARTIST];
    char album_name[MAX_ALBUM];
    char track_name[MAX_TRACK];
    char track_genre[MAX_GENRE];
    float tempo;
} tipoCancion;

typedef struct {
    char artist[MAX_ARTIST];
    List* canciones;
} tipoArtista;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("      Base de Datos de Spotifind");
    puts("========================================");
    puts("1) Cargar Canciones.");
    puts("2) Buscar por Género.");
    puts("3) Buscar por Artista.");
    puts("4) Buscar por Tempo.");
    puts("5) Crear Lista de Reproducción.");
    puts("6) Agregar Canción a lista de Reproducción.");
    puts("7) Mostrar canciones de una lista de Reproducción.");
    puts("8) Salir.");
}

void cargar_canciones() {
    FILE *archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ','); // leer encabezado

    int contador = 0;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        tipoCancion* cancion = (tipoCancion*) malloc(sizeof(tipoCancion));
        if (cancion == NULL) continue;

        strncpy(cancion->id, campos[0], MAX_ID);
        strncpy(cancion->artist, campos[2], MAX_ARTIST);
        strncpy(cancion->album_name, campos[3], MAX_ALBUM);
        strncpy(cancion->track_name, campos[4], MAX_TRACK);
        strncpy(cancion->track_genre, campos[20], MAX_GENRE);
        cancion->tempo = atof(campos[18]);

        // Guardar por ID
        map_insert(mapaCancionesPorID, strdup(cancion->id), cancion);

        // Guardar por artista
        List* artistas = split_string(cancion->artist, ";");
        for (char* artista = list_first(artistas); artista != NULL; artista = list_next(artistas)) {
            MapPair* par = map_search(mapaArtistas, artista);
            tipoArtista* tArtista;

            if (par == NULL) {
                tArtista = (tipoArtista*) malloc(sizeof(tipoArtista));
                strncpy(tArtista->artist, artista, MAX_ARTIST);
                tArtista->canciones = list_create();
                map_insert(mapaArtistas, strdup(artista), tArtista);
            } else {
                tArtista = par->value;
            }
            list_pushBack(tArtista->canciones, cancion);
        }

        // Guardar por tempo
        if (cancion->tempo < 80)
            list_pushBack(cancionesLentas, cancion);
        else if (cancion->tempo <= 120)
            list_pushBack(cancionesModeradas, cancion);
        else
            list_pushBack(cancionesRapidas, cancion);

        // Guardar por género
        MapPair* generoPar = map_search(mapaGeneros, cancion->track_genre);
        List* listaGenero;
        if (generoPar == NULL) {
            listaGenero = list_create();
            map_insert(mapaGeneros, strdup(cancion->track_genre), listaGenero);
        } else {
            listaGenero = generoPar->value;
        }
        list_pushBack(listaGenero, cancion);

        contador++;
    }

    fclose(archivo);
    printf("Se cargaron %d canciones correctamente.\n", contador);
}

int is_equal_string(void* key1, void* key2) {
    return strcmp((char*)key1, (char*)key2) == 0;
}

Map* mapaCancionesPorID;
Map* mapaArtistas;
Map* mapaGeneros;

List* cancionesLentas;
List* cancionesModeradas;
List* cancionesRapidas;

int main() {
    mapaCancionesPorID = map_create(is_equal_string);
    mapaArtistas = map_create(is_equal_string);
    mapaGeneros = map_create(is_equal_string);

    cancionesLentas = list_create();
    cancionesModeradas = list_create();
    cancionesRapidas = list_create();
    char opcion;
    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
        case '1':
            cargar_canciones();
            break;
        case '2':
            // buscar_por_genero();
            break;
        case '3':
            // buscar_por_artista();
            break;
        case '4':
            // buscar_por_tempo();
            break;
        case '5':
            // crear_lista();
            break;
        case '6':
            // agregar_a_lista();
            break;
        case '7':
            // mostrar_lista();
            break;
        }

        presioneTeclaParaContinuar();

    } while (opcion != '8');

    return 0;
}
