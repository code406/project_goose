/**
 * @brief Implementa la interfaz y las llamadas
          para cada comando
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define N_CALLBACK 4

/**
   Define el tipo de funcion para las llamdas
*/
typedef void (*callback_fn)(Game* game);

/**
   Llamadas para comando
   Se definen mas adelante
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous};

/**
   Private functions
   Se definen mas adelante
*/

/*
Funcion que devuelve un STATUS y cuyo argumentos son
un puntero a GAME y un nombre de archivo.
Se encarga de leer el archivo y cargar los datos
en la estructura Game introducida como argumento
*/
STATUS game_load_spaces(Game* game, char* filename);
/*
Funcion que recibe como argumentos un puntero a Game
y un puntero a Space.
El último elemento de la tabla de tipo Space de game
que no tenga valor asignado (Es decir =NULL) es asignado
con el valor del Space introducido como argumento
*/
STATUS game_add_space(Game* game, Space* space);
/*
Funcion que devuelve un id y cuyos argumentos
son un puntero a game y un entero
Devuelve la id del espacio asociado a esa posicion (el entero)
*/
Id     game_get_space_id_at(Game* game, int position);
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y una id.
Fija game.player_location en la id introducida
*/
STATUS game_set_player_location(Game* game, Id id);
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y una id.
Fija game.object_location en la id introducida
*/
STATUS game_set_object_location(Game* game, Id id);

/**
   Implementa la interfaz
*/

/*
Funcion que devuelve un STATUS y cuyo argumento
es una variable (estructura) tipo game
se encarga de inicializar la estructura tipo game tipo game
introducida, dandole valores de 0 ó -1.
Si todo va bien devuelve un OK
*/
STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->player_location = NO_ID;
  game->object_location = NO_ID;
  game->last_cmd = NO_CMD;

  return OK;
}
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y un filename
Crea el game, lo inicializa, carga los espacios del filename,
y fija la id del player y object a 0.
Si todo va bien devuelve un OK
*/
STATUS game_create_from_file(Game* game, char* filename) {
  /*crea el game inicializado a 0 y lo comprueba*/
  if (game_create(game) == ERROR)
    return ERROR;
  /*carga los espacios del filename*/
  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;
  /*la id de player_location = 0*/
  game_set_player_location(game, game_get_space_id_at(game, 0));
  /*la id de object_location = 0*/
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/*
Funcion que devuelve una variable tipo STATUS (ERROR ó OK)
Se encarga de eliminar todos los espacion en el Game introducido
como argumento
*/
STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  return OK;
}

/*
Funcion que recibe como argumentos un puntero a Game
y un puntero a Space.
El último elemento de la tabla de tipo Space de game
que no tenga valor asignado (Es decir =NULL) es asignado
con el valor del Space introducido como argumento
*/

STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

/*
Funcion que devuelve un id y cuyos argumentos
son un puntero a game y un entero
Devuelve la id del espacio asociado a esa posicion (el entero)
*/
Id game_get_space_id_at(Game* game, int position) {
  /*Comprueba que la posicion sea correcta*/
  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/*
Funcion que devuelve un puntero a Space y cuyos
argumentos son un puntero a game y un Id
Si no se introduce un id devuelve NULL
Recorre los games.spaces y si el id de alguno
coindice con el introducido te lo devuelve. Si no
encuentra nada devuelve NULL
*/
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}

/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y una id.
Fija game.player_location en la id introducida
*/
STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  game->player_location = id;
  return OK;
}
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y una id.
Fija game.object_location en la id introducida
*/
STATUS game_set_object_location(Game* game, Id id) {

/*
  Este i no se utiliza
  int i = 0;
*/

  if (id == NO_ID) {
    return ERROR;
  }

  game->object_location = id;

  return OK;
}

/*
Funcion que devuelve un Id y cuyo argumento es un puntero a GAME
devuelve la player_location
*/

Id game_get_player_location(Game* game) {
  return game->player_location;
}
/*
Funcion que devuelve un Id y cuyo argumento es un puntero a GAME
devuelve la object_location
*/
Id game_get_object_location(Game* game) {
  return game->object_location;
}

/*
Funcion que devuelve un STATUS y cuyos argumentos son
un puntero a Game y n T_Command
fija game.last_cmd al cmd introducido
*/
STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

/*
Funcion que devuelve un comando y cuyo argumento es un puntero a game
Devuelve la game.last_cmd
*/
T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

/*
Funcion tipo void cuyo argumento es un puntero a game
imprime una linea y despues las casillas
Te imprime la informacion de cada casilla
y luego te dice la player_location y la object_location
*/
void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int) game->object_location);
  printf("=> Player location: %d\n", (int) game->player_location);
  printf("prompt:> ");
}

/*
Funcion que devuelve un BOOl¡L y cuyo argumento es un puntero a GAME.
Devuelve siempre FALSE
*/
BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}

void game_callback_following(Game* game) {
  int i = 0;
  Id current_id = NO_ID; /*id actual*/
  Id space_id = NO_ID; /*id del jugador */
  /*Le da el valor a space_id*/
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }
  /*Recorre los espacios*/
  /*Si coincide con el espacio actual
  te da la id del sur.  */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    /*Si coincide con el espacio actual
    te da la id del sur a current_id.  */
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_previous(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*
Funcion que devuelve un STATUS y cuyo argumentos son
un puntero a GAME y un nombre de archivo.
Se encarga de leer el archivo y cargar los datos
en la estructura Game introducida como argumento
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
