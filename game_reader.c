/**
 * @brief Funcionalidades para la carga de espacios
 *
 * @file game_reader.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 16-02-2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "game_reader.h"
 #include "game.h"
 #include "command.h"
 #include "space.h"
 #include "set.h"


 /*******************************************************************************
 Funcion: game_load_spaces
 Autor: Arturo Morcillo
 Descripcion: Lee el archivo y carga los datos en la estructura Space de game
 Argumentos:
  game: Puntero a una estructura de tipo Game
 Return:
  OK o ERROR, que pertenecen al enum STATUS
 *******************************************************************************/
 /*
 La puedo poner sin problema porque no utiliza la estructura game como tal,
 solo la utiliza en otras funciones. De esta forma cojo la funcionalidad de
 cargar espacios y las otras funciones de game deberian funcionar perfectamente.
 En otras iteraciones habría que añadir lectores de jugadores y objetos,
 pero ahora solo necesito poner esta funcionalidad.
 */
 STATUS game_load_spaces(Game* game, char* filename)
 {
   /* Declara variables y las inicializa */
   FILE* file = NULL;
   char line[WORD_SIZE] = "";
   char name[WORD_SIZE] = "";
   char* toks = NULL;
   char *cadena0 = NULL;
   char* cadena1=NULL;
   char* cadena2=NULL;
   char cadena_aux[20] = "                 ";
   Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
   Space* space = NULL;


   /* Como es importante que se ejectute completamente, en vez de un "return" en
    caso de error, se utiliza un status que se devolverá al final, para que la
    ejecución no se detenga a medias.*/
   STATUS status = OK;

   /* comprueba argumentos */
   if (!filename)
   {
     return ERROR;
   }

   /* Abre el archivo y comprueba que se ha abierto correctamente */
   file = fopen(filename, "r");
   if (file == NULL)
   {
     return ERROR;
   }

   /* Escanea el archivo por lineas (WORD_SIZE es el maximo) y las almacena en line */
   while (fgets(line, WORD_SIZE, file))
   {
     /* Si los 3 primeros caracteres de la linea leida son "#s:" */
     if (strncmp("#s:", line, 3) == 0)
     {
       /* strtok divide una cadena en elementos con separadores ("|") */
       /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
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
       cadena0 = strtok(NULL, "|");
       cadena1 = strtok(NULL, "|");
       cadena2 = strtok(NULL, "|");


       /* Solo se compila cuando DEBUG está definido */
       #ifdef DEBUG
         printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s\n", id, name, north, east, south, west,cadena0,cadena1,cadena2);
       #endif

       /*Crea un espacio*/
       space = space_create(id);

       /* Si ese espacio no esta vacio le asigna los valores leidos */
       if (space != NULL)
       {
         space_set_name(space, name);
         space_set_north(space, north);
         space_set_east(space, east);
         space_set_south(space, south);
         space_set_west(space, west);
         if (cadena0 == NULL)
          space_set_gdesc_0(space, cadena_aux);
         else
          space_set_gdesc_0(space, cadena0);

          if (cadena1 == NULL)
           space_set_gdesc_1(space, cadena_aux);
          else
           space_set_gdesc_1(space, cadena1);

           if (cadena2 == NULL)
            space_set_gdesc_2(space, cadena_aux);
           else
            space_set_gdesc_2(space, cadena2);

         /*Tras eso añade ese espacio a game*/
         game_add_space(game, space);
       }
     }
   }

   /* Si hay error con el archivo, status pasa a ser ERROR */
   if (ferror(file))
   {
     status = ERROR;
   }

   /* Cierra el archivo */
   fclose(file);

   return status;
 }

 /*******************************************************************************
Funcion: game_load_objects
Autor: Arturo Morcillo
Descripcion: Lee el archivo y carga los datos en la estructura Object de game
Argumentos:
 game: Puntero a una estructura de tipo Game
Return:
 OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
/*
Similar a la de cargar espacios
*/
STATUS game_load_objects(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, space_id = NO_ID;
  Object* object = NULL;

  /* Inicializa status a OK para que se ejecute incluso aunque falle la carga
    de un solo espacio */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename)
  {
    return ERROR;
  }

  /* Abre el archivo y comprueba que se ha abierto correctamente */
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  /* Escanea el archivo por lineas (WORD_SIZE es el maximo) y las almacena en line */
  while (fgets(line, WORD_SIZE, file))
  {
    /* Si los 3 primeros caracteres de la linea leida son "#o:" */
    if (strncmp("#o:", line, 3) == 0)
    {
      /* strtok divide una cadena en elementos con separadores ("|") */
      /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);

      /* Solo se compila cuando DEBUG está definido */
      #ifdef DEBUG
        printf("Leido: %ld|%s|%ld\n", id, name, space_id);
      #endif

      /*Crea un objeto*/
      object = object_create(id);

      /* Si ese objeto no esta vacio le asigna los valores leidos */
      if (object != NULL)
      {
      if((object_set_name(object,name))==ERROR)
        status = ERROR;
        /*Tras eso añade ese objeto a game*/
        if((game_add_object(game, object))==ERROR)
          status = ERROR;

        if((game_set_object_location(game,object ,space_id))==ERROR)
          status = ERROR;

      }
    }
  }

  /* Si hay error con el archivo, status pasa a ser ERROR */
  if (ferror(file))
  {
    status = ERROR;
  }

  /* Cierra el archivo */
  fclose(file);

  return status;
}
