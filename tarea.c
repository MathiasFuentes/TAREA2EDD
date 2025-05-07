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
    float prueba;
} tipoCancion;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("      Base de Datos de Spotifind");
    puts("========================================");
    puts("(1)   Cargar Canciones.");
    puts("(2)   Buscar por Género.");
    puts("(3)   Buscar por Artista.");
    puts("(4)   Buscar por Tempo.");
    puts("(5)   Crear Lista de Reproducción.");
    puts("(6)   Agregar Canción a lista.");
    puts("(7)   Mostrar canciones de una lista.");
    puts("(8)   Salir.");
}

int main() {
    char opcion;
    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
        case '1':
            leer_canciones();
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
