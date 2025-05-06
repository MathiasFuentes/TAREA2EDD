#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[100];
    char artists[100];
    char album_name[100];
    char track_name[100];
    int tempo;
    char track_genre[100];
} Canciones;

void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Base de Datos de Spotifind");
    puts("========================================");
    puts("1) Cargar Canciones");
    puts("2) Buscar por Género");
    puts("3) Buscar por Artista");
    puts("4) Buscar por Tempo");
    puts("5) Crear Lista de Reproducción");
    puts("6) Agregar Canción a lista");
    puts("7) Mostrar canciones de una lista");
    puts("8) Salir");
}

void leer_canciones() {
    FILE *archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char **campos;
    campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

    int k = 0;
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
        k++;
        if (k > 10) break; // Solo carga las primeras 10 canciones

        printf("ID: %d\n", atoi(campos[0]));
        printf("Título canción: %s\n", campos[4]);

        List *artistas = split_string(campos[2], ";");
        printf("Artistas:\n");
        for (char *artista = list_first(artistas); artista != NULL;
             artista = list_next(artistas)) {
            printf("  %s\n", artista);
        }

        printf("Álbum: %s\n", campos[3]);
        printf("Género: %s\n", campos[20]);
        printf("Tempo: %.2f\n", atof(campos[18]));
        printf(" -------------------------------\n");
    }

    fclose(archivo);
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
