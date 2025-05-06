#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leer_canciones(){
    // Intenta abrir el archivo CSV que contiene datos de películas
    FILE *archivo = fopen("data/song_dataset_.csv", "r");
    if (archivo == NULL) {
      perror(
          "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
      return;
    }
  
    char **campos;
    // Leer y parsear una línea del archivo CSV. La función devuelve un array de
    // strings, donde cada elemento representa un campo de la línea CSV procesada.
    campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  
    int k=0;
    // Lee cada línea del archivo CSV hasta el final
    while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
      k++;
      if (k>10) break; //carga primeras 1000 canciones
      printf("ID: %d\n", atoi(campos[0]));
      printf("Título cancion: %s\n", campos[4]);
  
      List* artistas = split_string(campos[2], ";");
  
      printf("Artistas: \n");
      for(char *artista = list_first(artistas); artista != NULL; 
                      artista = list_next(artistas))
          printf("  %s\n", artista);
  
      printf("Album: %s\n", campos[3]);
      printf("Género: %s\n", campos[20]);
      printf("Tempo: %.2f\n", atof(campos[18]));
      printf(" -------------------------------\n");
      
    }
    fclose(archivo); // Cierra el archivo después de leer todas las líneas
  
}

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

int main(){
    leer_canciones();
    return 0;
}
