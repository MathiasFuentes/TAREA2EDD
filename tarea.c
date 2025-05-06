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

void presioneTeclaParaContinuar() {
    printf("\nPresiona Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}

void limpiarPantalla() {
    #ifdef _WIN32
      system("cls");  // Windows
    #else
      system("clear"); // Linux y macOS
    #endif
    }

int main() {
  char opcion;
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
        
      break;
    case '2':

      break;
    case '3':
      break;
    case '4':
      
      break;
    case '5':
      break;
    case '6':
      break;
    case '7':
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
