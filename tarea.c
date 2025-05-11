#include "list.h"
#include "map.h"
#include "extra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARTIST 256
#define MAX_ID 512
#define MAX_ALBUM 256
#define MAX_TRACK 512
#define MAX_GENRE 256

// --- Estructuras ---

// Estructura de representa una canción y los datos de la misma.
typedef struct { 
    char id[MAX_ID];                // ID único de la canción.
    char artist[MAX_ARTIST];        // Nombre del autor/es de la canción.
    char album_name[MAX_ALBUM];     // Nombre del álbum al que la canción pertenece.
    char track_name[MAX_TRACK];     // Nombre de la canción.
    char track_genre[MAX_GENRE];    // Nombre del género al que pertenece la canción.
    float tempo;                    // Tempo en BPM (Beats per Minute) de la canción.
} tipoCancion;

// Estructura que representa un artista y una lista de canciones asociada.
typedef struct {
    char artist[MAX_ARTIST];        // Nombre del artista.
    List* canciones;                // Lista de canciones del artista.
} tipoArtista;


// --- Variables globales ---

Map* mapaCancionesPorID;            // Mapa para guardar cada canción por su ID único.
Map* mapaArtistas;                  // Mapa para guardar cada artista.
Map* mapaGeneros;                   // Mapa para guardar todos los géneros incluidos.
Map* listasReproduccion;            // Mapa para guardar todas las playlist creadas.

List* cancionesLentas;              // Lista que guarda todas las canciones con tempo < 80 BPM.
List* cancionesModeradas;           // Lista que guarda todas las canciones con tempo entre 80 y 120 BPM.
List* cancionesRapidas;             // Lista que guarda todas las canciones con tempo mayor a 120 BPM.

List* archivosCargados;             // Lista que guarda el nombre de todos los archivos csv ya cargados,
                                    // esto asegura que no se cargue 2 veces un mismo archivo.

                                    
// --- Funciones del programa ---

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
    puts("(6)   Agregar Canción a lista de Reproducción.");
    puts("(7)   Mostrar canciones de una lista de Reproducción.");
    puts("(8)   Salir.");
}

// 
int compararCanciones(void *a, void *b) {
  tipoCancion *c1 = (tipoCancion *)a;
  tipoCancion *c2 = (tipoCancion *)b;
  return strcmp(c1->id, c2->id); // o comparar más campos si quieres
}

void cargar_canciones() {
    puts("========================================");
    puts("          Cargar Canciones");
    puts("========================================");

    char ruta[256];
    printf("Ingrese la ruta del archivo CSV: ");
    scanf(" %[^\n]", ruta);

    if (archivoYaCargado(archivosCargados, ruta)){
        printf("Cuidado! el Archivo %s ya fue cargado antes...\n", ruta);
        return;
    }

    registrarArchivoCargado(archivosCargados, ruta);

    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo :( ...");
        return;
    }

    char **campos = leer_linea_csv(archivo, ','); // Leer encabezado
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
        if (searchMap(mapaCancionesPorID, cancion->id) == NULL){
            insertMap(mapaCancionesPorID, strdup(cancion->id), cancion);
        }
        else { continue; }
        // Guardar por artista
        List* artistas = split_string(cancion->artist, ";");
        for (char* artista = list_first(artistas); artista != NULL; artista = list_next(artistas)) {
            tipoArtista* tArtista = searchMap(mapaArtistas, artista);
            if (tArtista == NULL) {
                tArtista = (tipoArtista*) malloc(sizeof(tipoArtista));
                strncpy(tArtista->artist, artista, MAX_ARTIST);
                tArtista->canciones = list_create();
                insertMap(mapaArtistas, strdup(artista), tArtista);
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
        List* listaGenero = searchMap(mapaGeneros, cancion->track_genre);
        if (listaGenero == NULL) {
            listaGenero = list_create();
            insertMap(mapaGeneros, strdup(cancion->track_genre), listaGenero);
        }
        list_pushBack(listaGenero, cancion);

        contador++;
    }

    fclose(archivo);
    puts("\nProceso completado de forma exitosa !! :D");
    printf("Se cargaron %d canciones correctamente.\n", contador);
}

int comparar_canciones(const void *a, const void *b) {
    tipoCancion* cancionA = *(tipoCancion**)a;
    tipoCancion* cancionB = *(tipoCancion**)b;
    return strcmp(cancionA->track_name, cancionB->track_name);
}

void normalizar_genero(char* genero) {
    for (int i = 0; genero[i]; i++) {
        if (genero[i] == ' ')
            genero[i] = '-';
        else
            genero[i] = tolower(genero[i]);
    }
}

void buscar_por_genero() {
    
    if (firstMap(mapaGeneros) == NULL){
        puts("No se han encontrado géneros disponibles :(");
        return;
    }

    char generoBuscado[MAX_GENRE];
    puts("========================================");
    puts("          Géneros Disponibles");
    puts("========================================");
    Pair* par = firstMap(mapaGeneros);
    while (par != NULL) {
        printf("• %s\n", (char*)par->key);
        par = nextMap(mapaGeneros);
    }

    printf("Ingrese el género musical a buscar: ");
    scanf(" %[^\n]", generoBuscado);

    normalizar_genero(generoBuscado);

    List* canciones = searchMap(mapaGeneros, generoBuscado);
    if (canciones == NULL) {
        printf("No se encontraron canciones con el género '%s'.\n", generoBuscado);
        return;
    }

    tipoCancion* cancion = list_first(canciones);
    int cantidad = 0;

    printf("\nCanciones del género '%s':\n", generoBuscado);
    while (cancion != NULL) {
        // printf("• %s - %s (%.2f BPM)\n", cancion->artist, cancion->track_name, cancion->tempo);

        printf("# %d\n", cantidad + 1);
        printf("Artista:    %s\n", cancion->artist);
        printf("Título:     %s\n", cancion->track_name);
        printf("BPM:        %.2f\n\n", cancion->tempo);

        cancion = list_next(canciones);
        cantidad++;
    }

    if (cantidad == 0)
        printf("No hay canciones registradas para este género.\n");
}

void buscar_por_artista() {
    puts("========================================");
    puts("         Búsqueda por Artista");
    puts("========================================");
    char nombreArtista[MAX_ARTIST];
    printf("\nIngrese el nombre del artista: ");
    scanf(" %[^\n]", nombreArtista);

    tipoArtista* artista = searchMap(mapaArtistas, nombreArtista);
    if (artista == NULL) {
        printf("No se encontraron canciones del artista '%s' :( \n\n", nombreArtista);
        puts("Prueba escribiéndolo de forma capitalizada y con sus respectivas mayúsculas");
        puts("Por ejemplo: BTS, Pablo Chill-E, Dora The Explorer, etc...");
        return;
    }

    printf("\nCanciones de '%s':\n\n", artista->artist);
    tipoCancion* cancion = list_first(artista->canciones);
    int cantidad = 0;
    while (cancion != NULL) {

        printf("Título: %s\n", cancion->track_name);
        printf("ID:     %s\n", cancion->id);
        printf("Álbum:  %s\n", cancion->album_name);
        printf("Género: %s\n", cancion->track_genre);
        printf("Tempo:  %.2f BPM\n\n", cancion->tempo);

        // printf("• %s | Álbum: %s | Género: %s | Tempo: %.2f BPM\n",cancion->track_name,cancion->album_name,cancion->track_genre,cancion->tempo);
        cancion = list_next(artista->canciones);
        cantidad++;
    }

    if (cantidad == 0)
        printf("No hay canciones registradas para este artista.\n");
    else{
        printf("Hay %d canciones de %s registradas !", cantidad, artista->artist);
    }
}

char leer_opcion_tempo(){
    char opcion;
    int valido = 0;

    do {
        puts("========================================");
        puts("          BÚSQUEDA POR TEMPO");
        puts("========================================");
        puts("Seleccione una opción:");
        puts("  (1) Lentas     - Menos de 80 BPM");
        puts("  (2) Moderadas  - Entre 80 y 120 BPM");
        puts("  (3) Rápidas    - Más de 120 BPM");
        printf("Ingrese su opción (1/2/3): ");

        // Lee solo un carácter
        if (scanf(" %c", &opcion) == 1) {
            while (getchar() != '\n');  // Limpiar buffer
            if (opcion == '1' || opcion == '2' || opcion == '3') {
                valido = 1;
            } else {
                limpiarPantalla();
                printf("---Opción inválida. Intente nuevamente---\n\n");
            }
        } else {
            limpiarPantalla();
            printf("---Error de entrada. Intente nuevamente---\n\n");
            while (getchar() != '\n');  // Limpiar buffer en caso de error
        }
    } while (!valido);

    return opcion;
}

void buscar_por_tempo() {
    char opcion = leer_opcion_tempo();
    List* lista = NULL;
    const char* tipo = "";

    switch (opcion) {
        case '1':
            lista = cancionesLentas;
            tipo = "Lentas";
            break;
        case '2':
            lista = cancionesModeradas;
            tipo = "Moderadas";
            break;
        case '3':
            lista = cancionesRapidas;
            tipo = "Rápidas";
            break;
        default:
            printf("Opción no válida.\n");
            return;
    }

    tipoCancion* cancion = list_first(lista);
    int cantidad = 0;
    printf("\nCanciones %s:\n", tipo);
    while (cancion != NULL) {
        printf("• %s - %s | Álbum: %s | Género: %s | Tempo: %.2f BPM\n",cancion->artist, cancion->track_name, cancion->album_name,cancion->track_genre, cancion->tempo);
        cancion = list_next(lista);
        cantidad++;
    }

    if (cantidad == 0)
        printf("No se encontraron canciones en esta categoría.\n");
    else
        printf("\nTotal: %d canción(es).\n", cantidad);
}

void crear_lista_reproduccion() {
    puts("========================================");
    puts("         CREACIÓN DE PLAYLIST");
    puts("========================================");
    char nombreLista[256];
    printf("\nIngrese el nombre de la nueva lista de reproducción: ");
    scanf(" %[^\n]", nombreLista);

    if (searchMap(listasReproduccion, nombreLista) != NULL) {
        printf("Ya existe una lista con ese nombre, intenta con otro :/\n");
        return;
    }

    List* nuevaLista = list_create();
    insertMap(listasReproduccion, strdup(nombreLista), nuevaLista);

    printf("Lista '%s' creada exitosamente :D !!!\n", nombreLista);
}

void agregar_a_lista() {
    puts("========================================");
    puts("      AGREGAR CANCIÓN A PLAYLIST");
    puts("========================================");
    char idCancion[MAX_ID];
    char nombreLista[256];

    printf("\nIngrese el ID de la canción: ");
    scanf(" %[^\n]", idCancion);

    printf("Ingrese el nombre de la lista de reproducción: ");
    scanf(" %[^\n]", nombreLista);

    tipoCancion* cancion = searchMap(mapaCancionesPorID, idCancion);
    if (cancion == NULL) {
        printf("No se encontró la canción con ID '%s' :( \n", idCancion);
        return;
    }

    List* lista = searchMap(listasReproduccion, nombreLista);
    if (lista == NULL) {
        printf("No existe una lista con el nombre '%s' :( \n", nombreLista);
        return;
    }

    list_pushBack(lista, cancion);
    puts("\nMuy buena elección !");
    printf("'%s' de %s\n", cancion->track_name, cancion->artist);
    printf("Canción agregada exitosamente a la lista '%s' :D !!!\n", nombreLista);
}

void mostrar_lista() {
    if (firstMap(listasReproduccion) == NULL) {
        printf("No hay listas de reproducción creadas.\n");
        return;
    }
    puts("========================================");
    puts("         PLAYLIST DISPONIBLES");
    puts("========================================");

    Pair* par = firstMap(listasReproduccion);
    while (par != NULL) {
        printf("• %s\n", (char*)par->key);
        par = nextMap(listasReproduccion);
    }

    char nombreLista[256];
    printf("\nIngrese el nombre de la lista de reproducción: ");
    scanf(" %[^\n]", nombreLista);

    List* lista = searchMap(listasReproduccion, nombreLista);
    if (lista == NULL) {
        printf("\nNo se encontró la lista '%s' :( ...\n", nombreLista);
        return;
    }

    tipoCancion* cancion = list_first(lista);
    int contador = 0;
    printf("\nCanciones en la lista '%s':\n", nombreLista);
    while (cancion != NULL) {
        printf("• %s - %s | Álbum: %s | Género: %s | Tempo: %.2f BPM\n", cancion->artist, cancion->track_name, cancion->album_name, cancion->track_genre, cancion->tempo);
        cancion = list_next(lista);
        contador++;
    }

    if (contador == 0)
        printf("La lista está vacía.\n");
    else{
        printf("\nTotal: %d canción(es).\n", contador);
        if (contador < 10) { printf("Prueba añadiendo unas cuantas más!\n"); }
        else if (contador > 20) { printf("Una playlist muy consistente!\n"); }
        else if (contador > 50) { printf("Wow!!! Tienes muchas canciones! :D\n"); }
    }
}

// --- Main ---

int main() {
    mapaCancionesPorID = createMap(hash_string, is_equal_string);
    mapaArtistas = createMap(hash_string, is_equal_string);
    mapaGeneros = createMap(hash_string, is_equal_string);
    listasReproduccion = createMap(hash_string, is_equal_string);

    cancionesLentas = list_create();
    cancionesModeradas = list_create();
    cancionesRapidas = list_create();

    archivosCargados = list_create();

    char opcion;
    do {
        char lectura[256];
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %s", &lectura);

        if (!isdigit(lectura[0]) || lectura[1] != '\0'){
            while (getchar() != '\n');
            continue;
        }
        opcion = lectura[0];
        
        switch (opcion) {
        case '1':
            limpiarPantalla();
            cargar_canciones();
            break;
        case '2':
            limpiarPantalla();
            buscar_por_genero();
            break;
        case '3':
            limpiarPantalla();
            buscar_por_artista();
            break;
        case '4':
            limpiarPantalla();
            buscar_por_tempo();
            break;
        case '5':
            limpiarPantalla();
            crear_lista_reproduccion();
            break;
        case '6':
            limpiarPantalla();
            agregar_a_lista();
            break;
        case '7':
            limpiarPantalla();
            mostrar_lista();
            break;
        }

        presioneTeclaParaContinuar();

    } while (opcion != '8');

    return 0;
}
