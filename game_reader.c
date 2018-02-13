/**
 * @artiimor implementa las funcionalidades necesarias para la
 *carga de espacios
 * @file game_reader.c
 * @author Arturo Morcillo
 * @version 1.0
 * @date 08-02-2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "game_reader.h"
 #include "game.h"
 #include "command.h"/*Vienen en game_reader.h pero*/
 #include "space.h"  /*Las incluyo para facilitar la lectura*/

 /*
 Funcion que devuelve un STATUS y cuyo argumentos son
 un puntero a GAME y un nombre de archivo.
 Se encarga de leer el archivo y cargar los datos
 en la estructura Game introducida como argumento

 La puedo poner sim problema porque no utiliza la Estructura
 game como tal, solo la utiliza en otras funciones.

 De esta forma cojo la funcionalidad de cargar espacios y
 las otras funciones de game deberian funcionar perfectamente.

 En otras iteraciones habría que añadir lectores de jugadores y
 objetos, pero ahora solo necesito poner esta funcionalidad.
 */

 STATUS game_load_spaces(Game* game, char* filename) {
   /*Declara variables y las inicialia como 0,1 ó NULL*/
   FILE* file = NULL;
   char line[WORD_SIZE] = "";
   char name[WORD_SIZE] = "";
   char* toks = NULL;
   Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
   Space* space = NULL;
   /*Suponemos que la fucion devolverá OK*/
   STATUS status = OK;

   /*comprueba argumentos*/
   if (!filename) {
     return ERROR;
   }
   /*Abre el archivo y comprueba que lo ha abierto bien*/
   file = fopen(filename, "r");
   if (file == NULL) {
     return ERROR;
   }
   /*Mientras lea lineas y las almacene en "line"*/
   while (fgets(line, WORD_SIZE, file)) {
     /*Si los 3 primeros caracteres de la palabra leida
     son "#s:"*/
     if (strncmp("#s:", line, 3) == 0) {
       /*Le asigna a las variables el valor Leido
       desde el archivo.*/
       toks = strtok(line + 3, "|");
       id = atol(toks);
       toks = strtok(NULL, "|");
       strcpy(name, toks);
       toks = strtok(NULL, "|");
       north = atol(toks);
       toks = strtok(NULL, "|");
       east = atol(toks);
       toks = strtok(NULL, "|");
       south = atol(toks);
       toks = strtok(NULL, "|");
       west = atol(toks);
 #ifdef DEBUG
       printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
 #endif
   /*Crea un espacio*/
       space = space_create(id);
       /*Si ese espacio no esta vacio se encarga
       de asignarle los valores leidos anteriormente*/
       if (space != NULL) {
 	space_set_name(space, name);
 	space_set_north(space, north);
 	space_set_east(space, east);
 	space_set_south(space, south);
 	space_set_west(space, west);
   /*Tras eso añade ese espacio a game*/
 	game_add_space(game, space);
       }
     }
   }

   /*Comprueba si ha habido algun error con el file
   y si lo hay la funcion devuelve error*/
   if (ferror(file)) {
     status = ERROR;
   }
   /*Cierra el file*/
   fclose(file);

   return status;
 }
