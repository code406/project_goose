/**
 * @brief Implementacion de la interfaz del modulo game_management encargado de la lectura
 * de los ficheros con la configuracion del programa
 *
 * @file game_management.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0.
 * @date 08-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_management.h"
#include "game.h"
#include "space.h"
#include "object.h"
#include "link.h"


/*******************************************************************************
 *                   IMPLEMENTACION DE LA INTERFAZ game_management
 ******************************************************************************/

/*******************************************************************************
*	Lee el archivo y carga los datos en la estructura Space de game
*******************************************************************************/
STATUS game_management_load_spaces(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = " ";
  char name[WORD_SIZE] = " ";
  char description[WORD_SIZE] = " ";
  char long_description[WORD_SIZE] = " ";
  char* toks = NULL;
  char* cadena[MAX_GDESC];
  char cadena_aux[GDESC_LENGTH] = " ";
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up = NO_ID, down = NO_ID;
  Space* space = NULL;
  BOOL lit, ocupada;
  int i;



  /* Se ejecutará incluso aunque falle la carga de uno */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename || game == NULL)
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
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      strcpy(long_description, toks);
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
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      lit = (BOOL) atoi(toks);
      toks = strtok(NULL, "|");
      ocupada = (BOOL) atoi(toks);
      for(i=0; i<MAX_GDESC; i++)
        cadena[i] = strtok(NULL, "|");

      /* Solo se compila cuando DEBUG está definido */
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%i\n", id, name, north, east, south, west,up ,down,lit);
      for(i=0; i<MAX_GDESC; i++) printf("|%s", cadena[i]);
      printf("\n");
      #endif

      /*Crea un espacio*/
      space = space_create(id);

      /* Si ese espacio no esta vacio le asigna los valores leidos */
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_north_link(space, north);
        space_set_east_link(space, east);
        space_set_south_link(space, south);
        space_set_west_link(space, west);
        space_set_description(space, description);
        space_set_up_link(space, up);
        space_set_down_link(space, down);
        space_set_long_description(space, long_description);
        space_set_lit(space,lit);
        space_set_ocupada(space,ocupada);

        for(i=0; i<MAX_GDESC; i++){
          if (cadena[i] == NULL)
            space_set_gdesc(space, cadena_aux, i);
          else
            space_set_gdesc(space, cadena[i], i);
        }

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
*	Lee el archivo y carga los datos en la estructura Object de game
*******************************************************************************/

STATUS game_management_load_objects(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = " ";
  char name[WORD_SIZE] = " ";
  char description[WORD_SIZE] = " ";
  char far_description[WORD_SIZE] = " ";
  char* toks = NULL;
  BOOL movable,moved,hidden,light_space,on;
  Id id = NO_ID, space_id = NO_ID,open_link = NO_ID;
  Object* object = NULL;

  /* Se ejecutará incluso aunque falle la carga de uno */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename || game == NULL)
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
      toks = strtok(NULL, "|");
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      movable = (BOOL) atoi(toks);
      toks = strtok(NULL, "|");
      moved = (BOOL)atoi(toks);
      toks = strtok(NULL, "|");
      hidden =(BOOL) atoi(toks);
      toks = strtok(NULL, "|");
      open_link = atol(toks);
      toks = strtok(NULL, "|");
      light_space = (BOOL)atoi(toks);
      toks = strtok(NULL, "|");
      on = (BOOL)atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(far_description, toks);

      /* Solo se compila cuando DEBUG está definido */
      #ifdef DEBUG
        printf("Leido: %ld|%s|%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%s\n", id, name, space_id, description,movable,moved,hidden,open_link,light_space,on,far_description);
      #endif

      /*Crea un objeto*/
      object = object_create(id);

      /* Si ese objeto no esta vacio le asigna los valores leidos */
      if (object != NULL)
      {
        if((object_set_name(object,name))==ERROR)
          status = ERROR;

        if((object_set_description(object,description))==ERROR)
          status = ERROR;
        if((object_set_movable(object,movable))==ERROR)
          printf("movable");
        if((object_set_moved(object,moved))==ERROR)
          printf("moved");
        if((object_set_hidden(object,hidden))==ERROR)
          printf("Hidden");
        if((object_set_open_link(object,open_link))==ERROR)
          printf("open link");
        if((object_set_light_space(object,light_space))==ERROR)
          printf("light space");
        if((object_set_on(object,on))==ERROR)
          printf("set on");
        if((object_set_far_description(object,far_description))==ERROR)
          printf("far description");

        /*Tras eso añade ese objeto a game*/
        if((game_add_object(game, object))==ERROR){
          printf("Error en add_object\n");
          status = ERROR;
        }


        if((game_set_object_location(game, id, space_id))==ERROR){
          status = ERROR;
          printf("Error en set_object_location para el objeto con id %ld\n",id);
        }

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
*	Lee el archivo y crea los links correspondientes
*******************************************************************************/

STATUS game_management_load_links(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = " ";
  char name[WORD_SIZE] = " ";
  char* toks = NULL;

  Id id = NO_ID, espacio_1 = NO_ID, espacio_2 = NO_ID;
  BOOL linked;
  Link* link = NULL;



  /* Se ejecutará incluso aunque falle la carga de uno */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename || game == NULL)
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
    /* Si los 3 primeros caracteres de la linea leida son "#l:" */
    if (strncmp("#l:", line, 3) == 0)
    {
      /* strtok divide una cadena en elementos con separadores ("|") */
      /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      espacio_1 = atol(toks);
      toks = strtok(NULL, "|");
      espacio_2 = atol(toks);
      toks = strtok(NULL, "|");
      linked =(BOOL) atoi(toks);


      /* Solo se compila cuando DEBUG está definido */
      #ifdef DEBUG
        printf("Leido: %ld|%s|%ld|%ld|%d\n", id, name, espacio_1, espacio_1, linked);
      #endif

      /*Crea un espacio*/
      link = link_create(id);

      /* Si ese espacio no esta vacio le asigna los valores leidos */
      if (link != NULL)
      {
        link_set_name(link, name);
        link_set_espacio_1(link,espacio_1);
        link_set_espacio_2(link,espacio_2);
        link_set_linked(link,linked);
        game_add_link(game, link);
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
*	Lee el archivo y carga los datos del jugador en game
*******************************************************************************/
STATUS game_management_load_player(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = " ";
  /*char name[WORD_SIZE] = " ";*/
  char* toks = NULL;

  Id space_id = NO_ID;/*,object = NO_ID;*/


  /* Se ejecutará incluso aunque falle la carga de uno */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename || game == NULL)
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
    /* Si los 3 primeros caracteres de la linea leida son "#l:" */
    if (strncmp("#p:", line, 3) == 0)
    {
      /* strtok divide una cadena en elementos con separadores ("|") */
      /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
      toks = strtok(line + 3, "|");
      space_id = atol(toks);
      game_set_player_location(game,game_get_space_id_at(game, space_id-1));
      toks = strtok(NULL, "|");
      while(atol(toks) != -1){
        player_add_object(game_get_player(game),atol(toks));
        toks = strtok(NULL, "|");
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
*	Lee el archivo y carga los datos de game_rules en game
*******************************************************************************/
STATUS game_management_load_game_rules(Game* game, char* filename)
{
  /* Declara variables y las inicializa */
  FILE* file = NULL;
  char line[WORD_SIZE] = " ";
  /*char name[WORD_SIZE] = " ";*/
  char* toks = NULL;

  int day=0,n_cmd=0,notes=0,next_action=0;


  /* Se ejecutará incluso aunque falle la carga de uno */
  STATUS status = OK;

  /* comprueba argumentos */
  if (!filename || game == NULL)
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
    /* Si los 3 primeros caracteres de la linea leida son "#l:" */
    if (strncmp("#g:", line, 3) == 0)
    {
      /* strtok divide una cadena en elementos con separadores ("|") */
      /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
      toks = strtok(line + 3, "|");
      day = atoi(toks);
      toks = strtok(NULL, "|");
      n_cmd = atoi(toks);
      toks = strtok(NULL, "|");
      notes = atoi(toks);
      toks = strtok(NULL, "|");
      next_action = atoi(toks);

    }
  }

  game_set_game_rules_day(game,day);
  game_set_game_rules_n_cmd(game,n_cmd);
  game_set_game_rules_notes(game,notes);
  game_set_game_rules_next_action(game,next_action);

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
*	Crea un archivo de guardado identido al data.dat con la informacion del juego
*******************************************************************************/

STATUS game_management_save(Game* game){
  int i,n;
  const char *name;
  Id* ids;
  Id id;
  /*Para spaces:*/
  Space *space_aux;
  Id north,east,south,west,up,down;
  char *space_description;
  char *space_long_description;
  char* cadena[MAX_GDESC];
  char cadena_aux[GDESC_LENGTH] = " ";
  BOOL lit,ocupada;
  /*Para objects*/
  Object *object_aux;
  BOOL movable,moved,hidden,light_space,on;
  char *description;
  char *far_description;
  Id space_id = NO_ID,open_link = NO_ID;
  /*Para links*/
  Link* link_aux = NULL;
  Id espacio_1,espacio_2;
  BOOL linked;
  FILE * f;

  if (game == NULL)
    return ERROR;


  f = fopen ("partida.dat","w");
  /*Primero cargo los espacios utilizando game_get_space*/
  for (i=1;i<MAX_SPACES && (space_aux = game_get_space(game,i)) != NULL;i++){
    /*Id,descripcion,nombre,norte,sur,este,oeste,cadena0,cadena1,cadena2*/
    id = space_get_id(space_aux);
    name = space_get_name(space_aux);
    north = space_get_north_link(space_aux);
    east = space_get_east_link(space_aux);
    south = space_get_south_link(space_aux);
    west = space_get_west_link(space_aux);
    for(n=0; n<MAX_GDESC; n++){
      cadena[n] = space_get_gdesc(space_aux, n);
      if (cadena[n] == NULL)
        cadena[n] = cadena_aux;
    }
    space_description = space_get_description(space_aux);
    up = space_get_up_link(space_aux);
    down = space_get_down_link(space_aux);
    lit = space_get_lit(space_aux);
    ocupada = space_get_ocupada(space_aux);
    space_long_description = space_get_long_description(space_aux);

    fprintf(f,"#s:%ld|%s|%s|%s|%ld|%ld|%ld|%ld|%ld|%ld|%i|%i", id,space_description,space_long_description ,name, north, east, south, west,up, down,lit,ocupada);
    for(n=0; n<MAX_GDESC; n++)
      fprintf(f,"|%s", cadena[n]);

    fprintf(f,"|\n");
  }
  for (i=1;i<MAX_ID && (object_aux = game_get_object(game,i)) != NULL;i++){
    if (object_aux == NULL)
      printf("NULL raro");
    id = object_get_id(object_aux);
    name = object_get_name(object_aux);
    space_id = game_get_object_location(game, id);
    description = object_get_description(object_aux);
    far_description = object_get_far_description(object_aux);
    movable = object_get_movable(object_aux);
    moved = object_get_moved(object_aux);
    hidden = object_get_hidden(object_aux);
    light_space = object_get_light_space(object_aux);
    on = object_get_on(object_aux);


    fprintf(f,"#o:%ld|%s|%ld|%s|%d|%d|%d|%ld|%d|%d|%s\n", id, name, space_id, description,movable,moved,hidden,open_link,light_space,on,far_description);
    printf("escribiendo objetos");
  }

  for (i=1;MAX_ID && (link_aux = game_get_link(game,i)) != NULL;i++){
    id = link_get_id(link_aux);
    name = link_get_name(link_aux);
    espacio_1 = link_get_espacio_1(link_aux);
    espacio_2 = link_get_espacio_2(link_aux);
    linked = link_get_linked(link_aux);


    fprintf(f,"#l:%ld|%s|%ld|%ld|%d\n", id, name, espacio_1, espacio_2, linked);
  }
  fprintf(f,"#p:%ld|",game_get_player_location(game));
  for (i=0,ids = player_get_objects(game_get_player(game));ids[i] != NO_ID;i++){
    fprintf(f,"%ld|",ids[i]);
  }
  fprintf(f,"-1\n");
  fprintf(f,"#g:%i|%i|%i|%i\n",game_get_game_rules_day(game),game_get_game_rules_n_cmd(game),game_get_game_rules_notes(game),game_get_game_rules_next_action(game));




  fclose(f);

  return OK;


}

/*******************************************************************************
*	carga un archivo de guardado identido al data.dat con la informacion del juego
*******************************************************************************/

STATUS game_management_load(Game* game){

  if (game == NULL)
    return ERROR;
  game_destroy(game);
  game = game_create();
  game_management_load_spaces(game,"partida.dat");
  game_management_load_objects(game,"partida.dat");
  game_management_load_links(game,"partida.dat");
  game_management_load_player(game,"partida.dat");
  game_management_load_game_rules(game,"partida.dat");
  return OK;

}
