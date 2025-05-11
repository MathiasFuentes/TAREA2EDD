# Spotifind

**Spotifind** es una aplicación de consola escrita en C que permite gestionar una base de datos de canciones y realizar búsquedas eficientes por distintos criterios como género, artista o tempo. Además, permite crear listas de reproducción personalizadas.

---

# Compilación y ejecución
Este programa ha sido desarrollado en C y puede ejecutarse fácilmente desde el PC del usuario con Visual Studio Code, o en un proyecto de Replit.
### Requisitos

- Sistema con soporte para C (Linux, Windows o Mac).
- Compilador GCC instalado (como gcc).
- Visual Studio Code (opcional) con extensión C/C++.

## Cómo usar desde Visual Studio Code:

Primero debe asegurarse de que:
-   Tiene Visual Studio Code instalado.
-   Tiene una extensión de C/C++ instalada.
-   Debe instalar un compilador de C, dependiendo de su sistema operativo.
Luego, al tener los archivos descomprimidos en una carpeta, abrir esa carpeta en Visual Studio Code en file->open folder... y seleccionar la carpeta en la que guardó los archivos.

Desde una nueva terminal, que se abre desde el menú superior con terminal->new terminal, debe compilar de la siguiente forma:
```bash
gcc spotifind.c list.c map.c extra.c -o spotifind
```
Y para ejecutar el código:
```bash
./spotifind.exe
```
---
## Cómo usar desde Replit.

Para usar el código desde replit, se deben seguir los siguientes pasos:

-   Descomprimir el archivo .zip en una carpeta a su elección.
-   Crear una nueva app en replit, elegir C como plantilla, cambiar el nombre de la app a la que tu quieras y crear la app.
-   En el apartado de archivos, elimina el main.c que viene por defecto.
-   Después, en el mismo apartado, selecciona los 3 puntos y dale a upload folder.
-   Ahí se sube la carpeta donde descomprimiste el archivo zip.
-   Por último, se presiona Run, el botón verde centrado arriba.
---
# Funcionalidades

El programa cuenta con las siguientes funcionalidades :
- Cargar un archivo .csv con los datos de las canciones.
- Buscar canciones por género.
- Buscar canciones por artista.
- Buscar canciones por tempo (lentas, moderadas, rápidas).
- Crear lista de reproducción.
- Agregar canción por ID a una lista de reproducción.
- Mostrar alguna lista de reproducción creada.


## Problemas Conocidos
- Para buscar canciones por artista, hay que escribirlo tal cual, por ejemplo, si busca "drake", aparecerá como desconocido, aunque exista "Drake". 
- Si se modifica un archivo .csv en medio del proceso, no se podrá cargar de nuevo ya que se toma como archivo cargado.
- El archivo .csv se necesita que esté en el mismo formato que el archivo incluido en el .zip del proyecto, con el mismo orden de datos.
## A mejorar
- Nos hubiese gustado retocar más la interfaz y optimizar el uso de las listas.
- La lectura del archivo .csv sin importar el orden de los datos.

# Ejemplo de uso

Paso 1) Cargar el archivo .csv de las canciones, en este caso "song_dataset_.csv" :
```bash
========================================
          Cargar Canciones
========================================
Ingrese la ruta del archivo CSV: song_dataset_.csv

Proceso completado de forma exitosa !! :D
Se cargaron 114000 canciones correctamente.

Presione una tecla para continuar...
```
Paso 2) Crear una lista de reproducción :
```bash
========================================
         CREACIÓN DE PLAYLIST
========================================

Ingrese el nombre de la nueva lista de reproducción: Ejemplo
Lista 'Ejemplo' creada exitosamente :D !!!

Presione una tecla para continuar...
```
Paso 3) Buscar algún ID para unirlo a la lista :
```bash
========================================
         Búsqueda por Artista
========================================

Ingrese el nombre del artista: Dora The Explorer

Canciones de 'Dora The Explorer':

... // Se muestran todas las canciones...

Título: We Did It!
ID:     78752
Álbum:  Dora The Explorer
Género: party
Tempo:  145.09 BPM

Hay 58 canciones de Dora The Explorer registradas !
Presione una tecla para continuar...
```
Paso 4) Guardar el ID que encontré en mi lista :
```bash
========================================
      AGREGAR CANCIÓN A PLAYLIST
========================================

Ingrese el ID de la canción: 78752
Ingrese el nombre de la lista de reproducción: Ejemplo

Muy buena elección !
'We Did It!' de Dora The Explorer
Canción agregada exitosamente a la lista 'Ejemplo' :D !!!

Presione una tecla para continuar...
```
Luego de añadir unas cuantas canciones más...

Paso 5) Mostrar las canciones de una lista de reproducción :
```bash
========================================
         PLAYLIST DISPONIBLES
========================================
• Ejemplo

Ingrese el nombre de la lista de reproducción: Ejemplo

Canciones en la lista 'Ejemplo':
• Dora The Explorer - We Did It! | Álbum: Dora The Explorer | Género: party | Tempo: 145.09 BPM
• Metallica - For Whom The Bell Tolls - Remastered | Álbum: Ride The Lightning (Remastered) | Género: metal | Tempo: 117.90 BPM
• Nana Mouskouri - Se Que Volveras | Álbum: Nana Latina | Género: opera | Tempo: 95.31 BPM
• Pablo Chill-E - Majin Boo | Álbum: S.U.N.O | Género: latino | Tempo: 140.06 BPM

Total: 4 canción(es).
Prueba añadiendo unas cuantas más!

Presione una tecla para continuar...
```
### Contribuciones

Archivos extra y list : obtenidos desde el repl dado para empezar la tarea.

Creación archivos map usando hash table : Matías Fuentes

Implementación funciones principales: Bastián Guerra.

Implementación funciones adicionales: Bastián Guerra.

Corrección de errores e Implementación UI: Matías Fuentes.

Creación Readme.md : Matías Fuentes.

