/**
 * @brief Implementa la interfaz y las llamadas para cada comando
 *
 * @file game.c
 * @author Pareja
 * @version 1.0.E
 * @date 16/02/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"


#define N_CALLBACK 6 /* Numero de llamadas a comando de la lista */

#define ID_P 1   /* Id que se asigna al jugador  */
#define ID_O 1   /* Id que se asigna al objeto   */
#define INI_P 0  /* Posicion inicial del jugador */
#define INI_O 4  /* Posicion inicial del objeto  */


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
Autor: David Palomo
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
Funcion: game_get_space_id_at
Autor: Arturo Morcillo
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
Autor: Arturo Morcillo
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
Autor: David Palomo
Descripcion: Asigna la posicion del objeto a un id introducido que
  identifica una casilla
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game* game, Id id);

/*----------------------  Fin de funciones privadas  -------------------------*/



/*******************************************************************************
Funcion: game_create
Autor: David Palomo
Descripcion: Inicializa la estructura de tipo Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create(Game* game)
{
  int i;
  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  /* Asigna un id al jugador y al objeto */
  game->player=player_create(ID_P);
  game->object=object_create(ID_O);

  game_set_player_location(game, NO_ID);
  game_set_object_location(game, NO_ID);

  game->last_cmd = NO_CMD;

  return OK;
}


/*******************************************************************************
Funcion: game_create_from_file
Autor: David Palomo
Descripcion: Crea el game, carga las casillas del archivo y coloca player
  y object en posicion inicial
Argumentos:
  game    : Puntero a una estructura de tipo Game
  filename: Archivo del que se lee la disposicion de las casillas
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create_from_file(Game* game, char* filename)
{
  /* Crea el game y lo comprueba */
  if (game_create(game) == ERROR)
    return ERROR;
  /* Carga los espacios del archivo */
  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;
  /* Coloca a jugador y objeto en sus casillas iniciales (INI_P e INI_O) */
  game_set_player_location(game, game_get_space_id_at(game, INI_P));
  game_set_object_location(game, game_get_space_id_at(game, INI_O));
  return OK;
}


/*******************************************************************************
Funcion: game_destroy
Autor: Arturo Morcillo
Descripcion: Elimina todas las casillas del Game, y libera la memoria reservada
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_destroy(Game* game)
{
  int i = 0;
  /* Recorre las casillas del spaces de la estructura game, y las vacía */
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
  {
    /* Libera memoria y pone a NULL el puntero correspondiente a cada casilla */
    space_destroy(game->spaces[i]);
  }

  return OK;
}


/*******************************************************************************
Funcion: game_add_space
Autor: Arturo Morcillo
Descripcion: Crea una casilla. Al último elemento "vacío" (= NULL) de la
  tabla de tipo Space de game se le asigna el Space introducido como argumento.
Argumentos:
  game : Puntero a una estructura de tipo Game
  space: Puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_add_space(Game* game, Space* space)
{
  int i = 0;

  if (space == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}


/*******************************************************************************
Funcion: game_get_space_id_at
Autor: Arturo Morcillo
Descripcion: Devuelve la id de la casilla asociada a una posicion
Argumentos:
  game    : Puntero a una estructura de tipo Game
  position: Entero (int)
Return:
  Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*******************************************************************************/
Id game_get_space_id_at(Game* game, int position)
{
  /* Comprueba que la posicion sea correcta */
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}


/*******************************************************************************
Funcion: game_get_space
Autor: Arturo Morcillo
Descripcion: Devuelve la casilla de game que coincide con el id introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  Puntero a la estructura de tipo Space (casilla)
  Si no se introduce un id, o no encuentra una casilla que corresponda
  al id, devuelve NULL
*******************************************************************************/
Space* game_get_space(Game* game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }
  /* Recorre las casillas del juego y devuelve la que coincide con ese id */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}


/*******************************************************************************
Funcion: game_set_player_location
Autor: Arturo Morcillo
Descripcion: Fija la posición del jugador en la id introducida.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un jugador.
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_player_location(Game* game, Id id)
{
  if (id == NO_ID)
  {
    return ERROR;
  }

  /* Fija la posición del jugador que hay en game en la id introducida */
  if((player_set_location(game->player, id))==ERROR)
  {
    return ERROR;
  }

  return OK;
}


/*******************************************************************************
Funcion: game_get_player_location
Autor: Arturo Morcillo
Descripcion: Devuelve la posición del jugador de la estructura game.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un jugador.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_player_location(Game* game)
{
  return (player_get_location(game->player));
}


/*******************************************************************************
Funcion: game_set_object_location
Autor: Arturo Morcillo
Descripcion: Fija la posición del objeto en la id introducida.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un objeto.
Argumentos:
  object: Puntero a una estructura de tipo Object
  name  : Cadena de caracteres que se guardará en object->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game* game, Id space_id)
{
  int i;
  Id space_aux, object_id_aux;

  /* Comprueba los argumentos */
  if (!game || space_id == NO_ID)
  {
    return ERROR;
  }

  /* Recorre las casillas */
  for (i=0; i < MAX_SPACES; i++)
  {
    /* Obtiene la id de la casilla definida por la constante del bucle */
    space_aux = space_get_id(game->spaces[i]);
    /* Si coincide con el id introducido como argumento, coloca el objeto */
    if (space_aux == space_id)
    {
      object_id_aux = object_get_id(game->object);
      space_set_object(game->spaces[i], object_id_aux);
      return OK;
    }

  }
  return ERROR;
}


/*******************************************************************************
Funcion: game_get_object_location
Autor: David Palomo
Descripcion: Devuelve la posición del objeto de la estructura game.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un objeto.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_object_location(Game* game)
{
  int n;
  Id space_aux, object_aux, location;

  if (!game)
  {
    return NO_ID;
  }

  /* Obtiene el id del objeto desde la estructura game */
  object_aux = object_get_id(game->object);
  for (n=0;n<MAX_SPACES;n++)
  {
    /* Obtiene el id del objeto que haya en la casilla. Si no hay, será NO_ID */
    space_aux = space_get_object(game->spaces[n]);
    /* Si el id del objeto coincide con el id del objeto que hay en la casilla */
    if (space_aux == object_aux)
    {
      /* Devuelve el id de la casilla */
      location = space_get_id(game->spaces[n]);
      return location;
    }
  }
  return NO_ID;
}


/*******************************************************************************
Funcion: game_update
Autor: David Palomo
Descripcion: Actualiza el panel de comandos introducidos para mostrar
  el último comando introducido
Argumentos:
  game     : Puntero a una estructura de tipo Game
  T_Command: Enumeración que identifica cada comando con un número
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_update(Game* game, T_Command cmd)
{
  /* fija game->last_cmd al cmd introducido */
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}


/*******************************************************************************
Funcion: game_get_last_command
Autor: David Palomo
Descripcion: Devuelve el último comando introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command game_get_last_command(Game* game)
{
  return game->last_cmd;
}


/*******************************************************************************
Funcion: game_print_data
Autor: David Palomo
Descripcion: Imprime informacion de cada casilla, y la posicion del jugador
  y del objeto. Posiblemente quede obsoleta en futuras iteraciones.
  Por el momento es válida porque solo hay un jugador y un objeto.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_print_data(Game* game)
{
  int i = 0;
  /* Imprime una línea de guiones */
  printf("\n\n-------------\n\n");

  /* Imprime las casillas */
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  /* obtiene la posicion del jugador y del objeto y la mustra por pantalla */
  printf("=> Player location: %d\n", (int) (game_get_player_location(game)));
  printf("=> Object location: %d\n", (int) (game_get_object_location(game)));
  printf("prompt:> ");
}


/*******************************************************************************
Funcion: game_is_over
Autor: Arturo Morcillo
Descripcion: Termina el juego. De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Variable de tipo BOOL (TRUE o FALSE)
  Por el momento siempre devuelve FALSE
*******************************************************************************/
BOOL game_is_over(Game* game)
{
  return FALSE;
}


/*------- Implementación de las Funciones de llamada para cada comando -------*/

/*******************************************************************************
Funcion: game_callback_unknown
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando unknown (introducir un
  comando no contemplado en la lista). No ocurre nada.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_unknown(Game* game)
{
}


/*******************************************************************************
Funcion: game_callback_exit
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando exit (salir del juego).
  No ocurre nada.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_exit(Game* game)
{
}


/*******************************************************************************
Funcion: game_callback_following
Autor: Arturo Morcillo
Descripcion: Implementa la funcionalidad del comando following (avanzar)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_following(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  /* Recorre las casillas */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      /* Mueve al jugador hacia el sur (la siguiente casilla) */
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
	       game_set_player_location(game, current_id);
      }
      return;
    }
  }
}


/*******************************************************************************
Funcion: game_callback_previous
Autor: Arturo Morcillo
Descripcion: Implementa la funcionalidad del comando previous (retroceder)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_previous(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (NO_ID == space_id)
  {
    return;
  }

  /* Recorre las casillas */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      /* Mueve al jugador hacia el norte (la casilla anterior) */
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
	        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}


/*******************************************************************************
Funcion: game_callback_get
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando get (coger un objeto)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_get(Game* game)
{
  Id current_id = NO_ID;
  Space * current_space = NULL;
  Id object = NO_ID;

  /* Obtiene el id de la casilla en que se encuentra el jugador */
  current_id = game_get_player_location(game);

  if (NO_ID == current_id)
  {
    return;
  }

  /* Obtiene la casilla identificada por el id obtenido */
  current_space = game_get_space(game, current_id);

  if (current_space == NULL)
  {
    return;
  }

  /* Si el jugador está en una casilla con objeto,
  lo coge (se le asigna) y desaparece de la casilla */
  if (space_get_object(current_space) == NO_ID)
    return;

  object = object_get_id(game->object);
  player_set_object(game->player, object);

  /* Quita de la casilla el objeto */
  space_set_object(current_space, NO_ID);
}


/*******************************************************************************
Funcion: game_callback_drop
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando drop (soltar un objeto)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_drop(Game* game)
{
  Id current_id = NO_ID;
  Space * current_space = NULL;
  Id object = NO_ID;

  /* Obtiene el id de la casilla en que se encuentra el jugador */
  current_id = game_get_player_location(game);

  if (NO_ID == current_id)
  {
    return;
  }

  /* Obtiene la casilla identificada por el id obtenido */
  current_space = game_get_space(game, current_id);

  if (current_space == NULL)
  {
    return;
  }

  /* Si el jugador está en casilla sin objeto,
  lo deja (se le asigna NO_ID) y aparece en la casilla */
  if (space_get_object(current_space) == NO_ID)
  {
    object = object_get_id(game->object);
    player_set_object(game->player, NO_ID);

    /* Pone en la casilla el objeto */
    space_set_object(current_space, object);
  }
}
