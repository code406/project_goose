/**
 * @brief Implementa el modulo principal del juego
 *
 * @file game.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "set.h"
#include "die.h"


#define N_CALLBACK 9 /* Numero de llamadas a comando de la lista */

#define ID_P 1   /* Id que se asigna al jugador  */
#define ID_D 1   /* Id que se asigna al dado     */
#define INI_P 0  /* Posicion inicial del jugador */


/* Define el tipo de funcion para las llamadas */
typedef void (*callback_fn)(Game* game);

/* Funciones de llamada para cada comando. Se definen mas adelante */
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_get(Game* game);
void game_callback_drop(Game* game);
void game_callback_roll(Game* game);
void game_callback_left(Game* game);
void game_callback_right(Game* game);


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
  game_callback_drop,
  game_callback_roll,
  game_callback_left,
  game_callback_right
};


/*------------------------  Funciones privadas  ------------------------------*/
/**
* @brief game_get_space_id_at
* @author Arturo Morcillo
* Devuelve la id de la casilla asociada a una posicion
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param position  Entero (int)
* @return Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*/

Id game_get_space_id_at(Game* game, int position);

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

  game_set_player_location(game, NO_ID);
  for (i = 0; i < MAX_ID; i++)
  {
    game->object[i] = NULL;
  }

  game->last_cmd = NO_CMD;
  game->die = die_create(ID_D);
  game->param = " ";

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
  if (game_reader_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_reader_load_objects(game, filename) == ERROR)
    return ERROR;

  /* Coloca a jugador su casilla inicial (INI_P) */
  game_set_player_location(game, game_get_space_id_at(game, INI_P));
  return OK;
}

/**
* @brief game_destroy
* @author Arturo Morcillo
* Elimina todas las casillas del Game, y libera la memoria reservada
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS game_destroy(Game* game)
{
  int i = 0;

  /* Recorre las casillas del spaces de la estructura game, y las vacía */
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
  {
    /* Libera memoria correspondiente a cada casilla */
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; (i < MAX_ID) && (game->object[i] != NULL); i++)
  {
    /* Libera memoria correspondiente a cada objeto */
    object_destroy(game->object[i]);
    game->object[i] = NULL;
  }

  /* Libera memoria correspondiente al dado */
  die_destroy(game->die);
  game->die = NULL;

  /* Libera memoria correspondiente al jugador */
  player_destroy(game->player);
  game->player = NULL;

  return OK;
}

/**
* @brief game_add_space
* @author Arturo Morcillo
* Crea una casilla. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Space de game se le asigna el Space introducido como argumento.
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param space Puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/

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

/**
* @brief game_add_object
* @author Arturo Morcillo
* Crea un objeto. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Object de game se le asigna el Object introducido como argumento.
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param space Puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS game_add_object(Game* game, Object* object)
{
  int i = 0;

  if (game == NULL || object == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_ID) && (game->object[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_ID)
  {
    return ERROR;
  }

  game->object[i] = object;

  return OK;
}

/**
* @brief game_get_space_id_at
* @author Arturo Morcillo
* Devuelve la id de la casilla asociada a una posicion
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param position entero (int)
* @return Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*/

Id game_get_space_id_at(Game* game, int position)
{
  /* Comprueba que la posicion sea correcta */
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/**
* @brief game_get_space
* @author Arturo Morcillo
* Devuelve la casilla de game que coincide con el id introducido
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return Puntero a la estructura de tipo Space (casilla) Si no se introduce un id, o no encuentra una casilla que corresponda al id, devuelve NULL
*/
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

/**
* @brief game_set_player_location
* @author Arturo Morcillo
* Fija la posición del jugador en la id introducida.
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/

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

/**
* @brief game_get_player_location
* @author Arturo Morcillo
* Devuelve la posición del jugador de la estructura game.
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @return Entero de tipo Id (long) que identifica una casilla
*/

Id game_get_player_location(Game* game)
{
  return (player_get_location(game->player));
}

/**
* @brief game_set_object_location
* @author Arturo Morcillo
* Fija la posición del objeto en la id introducida.
* @fie game.c
* @param object Puntero a una estructura de tipo Object
* @param name Cadena de caracteres que se guardará en object->name
* @return Entero de tipo Id (long) que identifica una casilla
*/

STATUS game_set_object_location(Game* game,Object *object ,Id space_id)
{
  int i;
  Id space_aux, object_id_aux;

  /* Comprueba los argumentos */
  if (!game || space_id == NO_ID || object == NULL)
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
      object_id_aux = object_get_id(object);
      space_add_object(game->spaces[i], object_id_aux);
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
  game  : Puntero a una estructura de tipo Game
  object: Puntero a estructura de tipo Object
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_object_location(Game* game, Object *object)
{
  int n,i;
  Id space_id_aux, object_id_aux, location;
  Set *set_aux;


  if (!game || !object)
  {
    return NO_ID;
  }


  /* Obtengo el id del objeto cuya localizacion quiero saber */
  object_id_aux = object_get_id(object);
  /*Recorro todos los espacios*/
  for (n=0;n<MAX_SPACES;n++)
  {
    /*Obtengo todos los objetos de cada espacio*/
    set_aux = space_get_objects (game->spaces[n]);
    /*  */
    for (i=0; i<get_set_tope(set_aux) ;i++){
      space_id_aux = get_id_pos (set_aux, i);
      /* Si el id del objeto coincide con el id del objeto que hay en la casilla */
      if (space_id_aux == object_id_aux)
      {
        /* Devuelve el id de la casilla */
        location = space_get_id(game->spaces[n]);
        return location;
      }
    }

  }
  /*Si llegamos hasta aqui quiere decir que no hemos encontrado el objeto en ningun espacio*/
  return NO_ID;
}


/*******************************************************************************
Funcion: game_get_object_player
Autor: David Palomo
Descripcion: Devuelve si el objeto es portado por un jugador.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un jugador.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  BOOL, es decir, TRUE o FALSE
*******************************************************************************/
BOOL game_get_object_player(Game* game, Object *object)
{
  int i;
  Id player_id_aux, object_id_aux;
  Set *set_aux;

  if (!game || !object)
  {
    return FALSE;
  }

  /* Obtengo el id del objeto cuya localizacion quiero saber */
  object_id_aux = object_get_id(object);
  /*Recorro todos los espacios*/
    /*Obtengo todos los objetos de cada espacio*/
    set_aux = player_get_objects (game->player);
    /*  */
    for (i=0; i<get_set_tope(set_aux) ;i++){
      player_id_aux = get_id_pos (set_aux, i);
      /* Si el id del objeto coincide con el id del objeto que hay en la casilla */
      if (player_id_aux == object_id_aux)
      {
        /* Devuelve TRUE si el objeto lo lleva un jugador */
        return TRUE;
      }
    }

  /*Si llegamos hasta aqui quiere decir que no hemos encontrado el objeto en ningun espacio*/
  return FALSE;
}


/*******************************************************************************
Funcion: game_update
Autor: David Palomo
Descripcion: Actualiza el panel de comandos introducidos para mostrar
  el último comando introducido
Argumentos:
  game : Puntero a una estructura de tipo Game
  cmd  : Enumeración que identifica cada comando con un número
  param: Cadena de caracteres con el parametro del comando (para get y drop)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_update(Game* game, T_Command cmd,char* param)
{
  /* fija game->last_cmd al cmd introducido */
  game->last_cmd = cmd;
  game->param = param;
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
  for (i = 0; i < MAX_ID && game->object[i] != NULL; i++)
  {
    printf("=> Object location: %d\n", (int) (game_get_object_location(game,game->object[i])));
  }
  /* TODO: Imprimir el dado */
  printf("prompt:> ");
}

/**
* @brief game_is_over
* @author Arturo Morcillo
* Termina el juego. De momento sin funcionalidad
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @return Variable de tipo BOOL (TRUE o FALSE) Por el momento siempre devuelve FALSE
*/

BOOL game_is_over(Game* game)
{
  return FALSE;
}

/**
* @brief game_set_param
* @author Arturo Morcillo
* Fija el param de la estructura game (necesario para get y drop)
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param param Cadena de caracteres con el parametro del comando (para get y drop)
* @return nada (tipo void)
*/

void game_set_param(Game *game,char *param)
{
  game->param = param;
}

/**
* @brief game_object_get_id_from_name
* @author Arturo Morcillo
* Te da el id de un objeto introduciendo su nombre.
* @file game.c
* @param name Cadena de caracteres con el nombre de un objeto
* @param game Puntero a una estructura de tipo Game
* @return nada (tipo void)
*/

Id game_object_get_id_from_name(char* name, Game *game)
{
  int i;
  char *aux;
  if (!name || !game)
  {
    return NO_ID;
  }

  for (i=0; i<MAX_ID;i++){
    aux = object_get_name (game->object[i]);
    if (strcasecmp(name,aux)==0)
      return object_get_id(game->object[i]);
  }

  return NO_ID;

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
  game->command_status = ERROR;
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
  game->command_status = OK;
}

/**
* @brief game_callback_following
* @author Arturo Morcillo
* Implementa la funcionalidad del comando following (avanzar)
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return nada (tipo void)
*/

void game_callback_following(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game->command_status = ERROR;
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
         game->command_status = OK;
         return;
      }
      else{
        game->command_status = ERROR;
        return;
      }

    }
  }
  game->command_status = OK;
}

/**
* @brief game_callback_previous
* @author Arturo Morcillo
* Implementa la funcionalidad del comando previous (retroceder)
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return nada (tipo void)
*/

void game_callback_previous(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (NO_ID == space_id)
  {
    game->command_status = ERROR;
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
      game->command_status = OK;
      return;
    }
  }
  game->command_status = OK;
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
  Id object_id = NO_ID;
  Set *set_aux = NULL;

  /* Obtiene el id de la casilla en que se encuentra el jugador */
  current_id = game_get_player_location(game);

  if (NO_ID == current_id)
  {
    game->command_status = ERROR;
    return;
  }

  /* Obtiene la casilla identificada por el id obtenido */
  current_space = game_get_space(game, current_id);

  if (current_space == NULL)
  {
    game->command_status = ERROR;
    return;
  }

  /* Si el jugador está en la casilla en la que se encuentra ese objeto,
  lo coge (se le asigna) y desaparece de la casilla */
  set_aux = space_get_objects(current_space);
  if (set_aux == NULL || set_isempty(set_aux) == TRUE)
  {
    game->command_status = ERROR;
    return;
  }

  object_id = game_object_get_id_from_name(game->param,game);
  if (object_id == NO_ID)
  {
    game->command_status = ERROR;
    return;
  }
  printf("Got %ld",object_id);

  if (space_check_object (current_space, object_id) == TRUE)
  {
    if(remove_id (set_aux, object_id) == ERROR)
    {
      game->command_status = ERROR;
      return;
    }
    if(player_add_object(game->player, object_id) == ERROR)
    {
      game->command_status = ERROR;
      return;
    }
  }
  else
  {
    game->command_status = OK;
    return;
  }

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
  int i;
  Id current_id = NO_ID;
  Space * current_space = NULL;
  Set *set_aux = NULL;
  Set *player_set = NULL;
  Id object_id = NO_ID;
  Object *object;

  player_set = player_get_objects(game->player);
  if (set_isempty(player_set) == TRUE)
  {
    game->command_status = ERROR;
    return;
  }

  /* Obtiene el id de la casilla en que se encuentra el jugador */
  current_id = game_get_player_location(game);

  if (NO_ID == current_id)
  {
    game->command_status = ERROR;
    return;
  }

  /* Obtiene la casilla identificada por el id obtenido */
  current_space = game_get_space(game, current_id);

  if (current_space == NULL)
  {
    game->command_status = ERROR;
    return;
  }

  object_id = game_object_get_id_from_name(game->param,game);
  printf("Got %ld",object_id);

  /* El jugador deja de llevar objeto y aparece en la casilla */
  set_aux = space_get_objects(current_space);

  if (set_aux == NULL){
    game->command_status = ERROR;
    return;
  }

  if(remove_id (player_set, object_id) == ERROR)
  {
    game->command_status = ERROR;
    return;
  }

  for (i=0, object = game->object[0]; i<MAX_ID && object_get_id(object) != object_id; i++, object = game->object[i]);


  /* Pone en la casilla el objeto */
  game_set_object_location(game, object ,current_id);
  game->command_status = OK;

}


/*******************************************************************************
Funcion: game_callback_roll
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando roll (tirar el dado)
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_roll(Game* game)
{
  die_roll(game->die);
  game->command_status = OK;
}


/*******************************************************************************
Funcion: game_callback_left
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando left (moverse hacia izquierda)
  Se utiliza "west".
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_left(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game->command_status = ERROR;
    return;
  }

  /* Recorre las casillas */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      /* Mueve al jugador hacia el oeste (la casilla a la izquierda) */
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
	       game_set_player_location(game, current_id);
         game->command_status = OK;
      }
      else{
        game->command_status = ERROR;
        return;
      }
      return;
    }
  }
}


/*******************************************************************************
Funcion: game_callback_right
Autor: David Palomo
Descripcion: Implementa la funcionalidad del comando right (moverse hacia derecha)
  Se utiliza "east".
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_callback_right(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  /* Asigna la posicion del jugador a space_id, y realiza la comprobacion */
  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game->command_status = ERROR;
    return;
  }

  /* Recorre las casillas */
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      /* Mueve al jugador hacia el este (la casilla a la derecha) */
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
	       game_set_player_location(game, current_id);
         game->command_status = OK;
      }
      else{
        game->command_status = ERROR;
        return;
      }
    }
  }
}
