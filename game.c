/**
 * @brief Implementa la interfaz y las llamadas
 *        para cada comando
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

#define N_CALLBACK 6

/* Define el tipo de funcion para las llamadas */
typedef void (*callback_fn)(Game* game);

/* Funciones de llamada para cada comando. Se definen mas adelante */
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_get(Game* game);
void game_callback_drop(Game* game);


/*******************************************************************************
Tabla: game_callback_fn_list
Descripcion: Tabla con las funciones de llamada de cada comando.
Util: Si el usuario introduce un comando, invoco a la función de este, que
  tiene un índice en la tabla. Así, se puede reducir el código con bucles.
Elementos: tipo callback_fn. Cada uno apunta a una función game_callback_<cmd>
static hace que solo se pueda utilizar la tabla en este .c
*******************************************************************************/
static callback_fn game_callback_fn_list[N_CALLBACK] =
{
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_get,
  game_callback_drop
};


/*------------------------  Funciones privadas  ------------------------------*/


/*******************************************************************************
Funcion: game_add_space
Descripcion: Crea una casilla. Al último elemento "vacío" (= NULL) de la
  tabla de tipo Space de game se le asigna el Space introducido como argumento.
Argumentos:
  game : Puntero a una estructura de tipo Game
  space: Puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_add_space(Game* game, Space* space);


/*******************************************************************************
Funcion: game_get_space_id_at
Descripcion: Devuelve la id de la casilla asociada a una posicion
Argumentos:
  game    : Puntero a una estructura de tipo Game
  position: Entero (int)
Return:
  Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*******************************************************************************/
Id     game_get_space_id_at(Game* game, int position);


/*******************************************************************************
Funcion: game_set_player_location
Descripcion: Asigna la posicion del jugador a un id introducido que
  identifica una casilla
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_player_location(Game* game, Id id);


/*******************************************************************************
Funcion: game_set_object_location
Descripcion: Asigna la posicion del objeto a un id introducido que
  identifica una casilla
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game* game, Id id);


/*----------------------  End of funciones privadas  -------------------------*/





/*******************************************************************************
Funcion: game_create
Descripcion: Inicializa la estructura de tipo Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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


/*******************************************************************************
Funcion: game_create_from_file
Descripcion: Crea el game, carga las casillas del archivo y coloca player
  y object en posicion inicial (0)
Argumentos:
  game    : Puntero a una estructura de tipo Game
  filename: Archivo del que se lee la disposicion de las casillas
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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


/*******************************************************************************
Funcion: game_destroy
Descripcion: Elimina todas las casillas del Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_destroy(Game* game) {
  int i = 0;
  /* Recorre las casillas del spaces de la estructura game, y las vacía */
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++){
    space_destroy(game->spaces[i]);
  }

  return OK;
}


/*******************************************************************************
Funcion: game_add_space
Descripcion: Crea una casilla. Al último elemento "vacío" (= NULL) de la
  tabla de tipo Space de game se le asigna el Space introducido como argumento.
Argumentos:
  game : Puntero a una estructura de tipo Game
  space: Puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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


/*******************************************************************************
Funcion: game_get_space_id_at
Descripcion: Devuelve la id de la casilla asociada a una posicion
Argumentos:
  game    : Puntero a una estructura de tipo Game
  position: Entero (int)
Return:
  Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*******************************************************************************/
Id game_get_space_id_at(Game* game, int position) {
  /*Comprueba que la posicion sea correcta*/
  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}


/*******************************************************************************
Funcion: game_get_space
Descripcion: Devuelve la casilla de game que coincide con el id introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  Puntero a la estructura de tipo Space (casilla)
  Si no se introduce un id, o no encuentra una casilla que corresponda
  al id, devuelve NULL
*******************************************************************************/
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }
  /* Recorre las casillas y devuelve game->spaces[i] si encuentra
     un space con ese id */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}


/*******************************************************************************
Funcion: game_set_player_location
Descripcion: Fija la posición del jugador en la id introducida.
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para player
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  /* Fija game.player_location en la id introducida */
  game->player_location = id;
  return OK;
}


/*******************************************************************************
Funcion: game_set_object_location
Descripcion: Fija la posición del objeto en la id introducida
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para object
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game* game, Id id) {
  /*
  Este i no se utiliza
  int i = 0;
  */
  if (id == NO_ID) {
    return ERROR;
  }

  /* Fija game.object_location en la id introducida */
  game->object_location = id;

  return OK;
}


/*******************************************************************************
Funcion: game_get_player_location
Descripcion: Devuelve la posición del jugador (de la estructura game)
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para player
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_player_location(Game* game) {
  return game->player_location;
}


/*******************************************************************************
Funcion: game_get_object_location
Descripcion: Devuelve la posición del objeto (de la estructura game)
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para object
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_object_location(Game* game) {
  return game->object_location;
}


/*******************************************************************************
Funcion: game_update
Descripcion: Actualiza el panel de comandos introducidos para mostrar
  el último comando introducido
Argumentos:
  game     : Puntero a una estructura de tipo Game
  T_Command: Enumeración que identifica cada comando con un número
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_update(Game* game, T_Command cmd) {
  /* fija game.last_cmd al cmd introducido */
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}


/*******************************************************************************
Funcion: game_get_last_command
Descripcion: Devuelve el último comando introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}


/*******************************************************************************
Funcion: game_print_data
Descripcion: Imprime informacion de cada casilla, y la posicion del jugador
  y del objeto. Posiblemente quede obsoleta en futuras iteraciones,
  ahora que hay estructuras y módulos para player y object
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_print_data(Game* game) {
  int i = 0;
  /* Imprime una línea de guiones */
  printf("\n\n-------------\n\n");

  /* Imprime las casillas */
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  /* obtiene player_location y object_location de la estructura game */
  printf("=> Object location: %d\n", (int) game->object_location);
  printf("=> Player location: %d\n", (int) game->player_location);
  printf("prompt:> ");
}


/*******************************************************************************
Funcion: game_is_over
Descripcion: Termina el juego. TODO: De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Variable de tipo BOOL (TRUE o FALSE)
  Por el momento siempre devuelve FALSE
*******************************************************************************/
BOOL game_is_over(Game* game) {
  return FALSE;
}



/* Implementación de las Funciones de llamada para cada comando */

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}


/*******************************************************************************
Funcion: game_callback_following
Descripcion: Implementa la funcionalidad del comando following (avanzar)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
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
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    /* Si coincide con el espacio actual
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


/*******************************************************************************
Funcion: game_callback_previous
Descripcion: Implementa la funcionalidad del comando previous (retroceder)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
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
Funcion: game_callback_get
Descripcion: Implementa la funcionalidad del comando get (coger un objeto)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_get(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Space * current_space = NULL;
  Player * player = NULL;
  Object * object = NULL;

  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    return;
  }

  /* Si el jugador está en casilla con objeto,
  lo coge (se le asigna) y desaparece de la casilla */
  if (space_get_object(current_space) == TRUE){
    /* TODO: Falta obtener el player y el objeto */
    player_set_object(player, object);

    /* Quitar de la casilla el objeto */
    space_set_object(current_space, FALSE);
    game->object_location = NO_ID;
  }

}


/*******************************************************************************
Funcion: game_callback_drop
Descripcion: Implementa la funcionalidad del comando drop (soltar un objeto)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_drop(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Space * current_space = NULL;
  Player * player = NULL;
  Object * object = NULL;

  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    return;
  }

  /* Si el jugador está en casilla sin objeto,
  lo deja (se le asigna) y aparece en la casilla */
  if (space_get_object(current_space) == FALSE){
    /* TODO: Falta obtener el player y el objeto */
    player_set_object(player, NULL);

    /* Poner en la casilla el objeto */
    space_set_object(current_space, TRUE);
    game->object_location = current_id;
  }

}
