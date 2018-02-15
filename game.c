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
#include "game_reader.h"
#include "player.h"
#include "object.h"


#define N_CALLBACK 4
#define ID_INI 1

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
Id game_get_space_id_at(Game* game, int position);
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y una id.
Fija game.player_location en la id introducida
*/
STATUS game_set_player_location(Game* game, Id id);


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
/*
*
*aqui
*
*
*/
STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  game->player=player_create(ID_INI);
  game->object=object_create(ID_INI);
  player_set_location(game->player, NO_ID);
  game_set_object_location(game, NO_ID);
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
/*
*
Revisar si es game->player o game.player
*
*/
STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }
  if((player_set_location(game->player, id))==ERROR)
    return ERROR;

  return OK;
}


/*
Funcion que devuelve un Id y cuyo argumento es un puntero a GAME
devuelve la player_location
*/

Id game_get_player_location(Game* game) {
  Id aux;
  aux = player_get_location(game->player);
  return aux;
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
y luego te dice la player_location
*/
void game_print_data(Game* game) {
  int i = 0;
  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Player location: %d\n", (int) (player_get_location(game->player)));
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

/*******************************************************************************
Funcion: TODO COMENTAR BIEN
Descripcion: Devuelve el id de la localizacion de un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  Variable de tipo Id (long) que identifica al objeto (object->id)
  Si el argumento introducido no es correcto, devuelve NULL
*******************************************************************************/
Id game_get_object_location(Game *game) {
  int n;
  Id space_aux,object_aux,object_id_aux;

  if (!game) {
    return NO_ID;
  }

  object_aux = object_get_id(game->object);
  for (n=0;n<MAX_SPACES;n++){
    space_aux = space_get_object(game->spaces[n]);
    if (space_aux == object_aux){
      object_id_aux = object_get_id(game->object);
      return object_id_aux;
    }
  }
  return NO_ID;
}

/*******************************************************************************
Funcion: object_set_name TODO COMENTAR
Descripcion: Asigna una localizacion a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
  name  : Cadena de caracteres que se guardará en object->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game * game, Id space_id) {
  int n;
  Id space_aux,object_id_aux;
  /* Comprueba los argumentos */
  if (!game || space_id == NO_ID) {
    return ERROR;
  }

  for (n=0;n<MAX_SPACES;n++){
    space_aux = space_get_id(game->spaces[n]);
    if (space_aux == space_id){
      object_id_aux = object_get_id(game->object);
      space_set_object(game->spaces[n], object_id_aux);
      return OK;
    }

}
  return ERROR;

}
