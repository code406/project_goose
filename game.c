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

/**
* @name game_callback_fn_list
* @Autor David Palomo
* @brief Tabla con las funciones de llamada de cada comando.
* @file game.c
* @Util Si el usuario introduce un comando, invoco a la función de este, que
* tiene un índice en la tabla. Así, se puede reducir el código con bucles.
* @Elementos tipo callback_fn. Cada uno apunta a una función game_callback_<cmd>
* static hace que solo se pueda utilizar la tabla en este .c
*/

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
* @name game_get_space_id_at
* @author Arturo Morcillo
* @brief Devuelve la id de la casilla asociada a una posicion
* @fie game.c
* @param game Puntero a una estructura de tipo Game
* @param position  Entero (int)
* @return Entero de tipo Id (long) que identifica la casilla asociada a una posicion
*/

Id game_get_space_id_at(Game* game, int position);

/*----------------------  Fin de funciones privadas  -------------------------*/


/**
* @name game_create
* @Autor David Palomo
* @brief Inicializa la estructura de tipo Game
* @file game.c
* @arguments game Puntero a una estructura de tipo Game
* @return OK o ERROR, que pertenecen al enum STATUS
*/

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

  game->last_cmd = command_create();
  game->die = die_create(ID_D);

  return OK;
}

/**
* @name game_create_from_file
* @Autor David Palomo
* @brief Crea el game, carga las casillas del archivo y coloca player
*y object en posicion inicial
* @file die.c
* @argument game Puntero a una estructura de tipo Game
* @argument filename Archivo del que se lee la disposicion de las casillas
* @return OK o ERROR, que pertenecen al enum STATUS
*/

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
* @name game_destroy
* @author Arturo Morcillo
* @brief Elimina todas las casillas del Game, y libera la memoria reservada
* @file game.c
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

  command_destroy(game->last_cmd);
  game->last_cmd = NULL;

  return OK;
}

/**
* @name game_add_space
* @author Arturo Morcillo
* @briefCrea una casilla. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Space de game se le asigna el Space introducido como argumento.
* @file game.c
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
* @name game_add_object
* @author Arturo Morcillo
* @brief Crea un objeto. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Object de game se le asigna el Object introducido como argumento.
* @file game.c
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
* @name game_get_space_id_at
* @author Arturo Morcillo
* @brief Devuelve la id de la casilla asociada a una posicion
* @file game.c
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
* @name game_get_space
* @author Arturo Morcillo
* @brief Devuelve la casilla de game que coincide con el id introducido
* @file game.c
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
@name   game_get_status_command
@date   03-03-2018
@author   Javier Mateos
@brief   Devuelve el ultimo comando realizado.
@arguments   game: juego del que se obtiene el estado del comando.
@return   Devuelve una cadena de caracteres que contiene el estado del comando.
          o NULL si se produce algun error.
*/
const char* game_get_status_command(Game* game){

  return command_get_status(game->last_cmd);
}

/**
* @name game_set_player_location
* @author Arturo Morcillo
* @brief Fija la posición del jugador en la id introducida.
* @file game.c
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
* @name game_get_player_location
* @author Arturo Morcillo
* @briefDevuelve la posición del jugador de la estructura game.
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return Entero de tipo Id (long) que identifica una casilla
*/

Id game_get_player_location(Game* game)
{
  return (player_get_location(game->player));
}

/**
* @name game_set_object_location
* @author Arturo Morcillo
* @brief Fija la posición del objeto en la id introducida.
* @file game.c
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

/**
* @name game_get_object_location
* @author David Palomo
* @brief Devuelve la posición del objeto de la estructura game.
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @param object Puntero a estructura de tipo Object
* @return Entero de tipo Id (long) que identifica una casilla
*/

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

/**
* @name game_get_object_player
* @author David Palomo
* @brief Devuelve si el objeto es portado por un jugador.
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return BOOL, es decir, TRUE o FALSE
*/

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

/**
* @name game_update
* @author David Palomo
* @brief Actualiza el panel de comandos introducidos para mostrar
* el último comando introducido.
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @param cmd Enumeración que identifica cada comando con un número
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS game_update(Game* game, T_Command cmd) {
  if(command_set_t_cmd(game->last_cmd, cmd) == ERROR){
    return ERROR;
  }
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

/**
* @name game_get_last_command
* @author David Palomo
* @brief Devuelve el último comando introducido
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return Valor numérico de la enumeración T_Command que identifica a cada comando
*/

T_Command game_get_last_command(Game* game)
{
  return command_get_t_cmd(game->last_cmd);
}

/**
* @name game_print_data
* @author David Palomo
* @brief Imprime informacion de cada casilla, y la posicion del jugador
* y del objeto
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/

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
* @name game_is_over
* @author Arturo Morcillo
* @brief Termina el juego. De momento sin funcionalidad
* @file game.c
* @param game Puntero a una estructura de tipo Game
* @return Variable de tipo BOOL (TRUE o FALSE) Por el momento siempre devuelve FALSE
*/

BOOL game_is_over(Game* game)
{
  return FALSE;
}


/**
* @name game_object_get_id_from_name
* @author Arturo Morcillo
* @brief Te da el id de un objeto introduciendo su nombre.
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

void game_callback_unknown(Game* game) {
  /*En caso de que se desconozca el comando devolvemos ERROR para indicar que
  esa accion no es posible*/
  command_set_status(game->last_cmd, "ERROR");
}

void game_callback_exit(Game* game) {

  command_set_status(game->last_cmd, "OK");
}

/**-----------------------------------------------------------------------------
Modifica el estado del juego avanzando en una casilla la
posicion del jugador.
------------------------------------------------------------------------------*/
void game_callback_following(Game* game) {

  /*Variable auxiliares empleadas en el bucle*/
  Id current_id = NO_ID;
  Space* current_space;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  current_space = game_get_space(game, current_id);
  if(current_space == NULL){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al sur del jugador*/
  current_id = space_get_south(current_space);
  if (current_id != NO_ID) {
    /*Movemos el jugador al espacio situado al sur*/
	  game_set_player_location(game, current_id);
  }

  command_set_status(game->last_cmd, "OK");
  return;
}

/**-----------------------------------------------------------------------------
Modifica el estado del juego retrocediendo en una casilla la
posicion del jugador.
------------------------------------------------------------------------------*/
void game_callback_previous(Game* game) {

  /*Variable auxiliares empleadas en el bucle*/
  Id current_id = NO_ID;
  Space* current_space;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  current_space = game_get_space(game, current_id);
  if(current_space == NULL){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al norte del jugador*/
  current_id = space_get_north(current_space);
  if (current_id != NO_ID) {
    /*Movemos el jugador al espacio situado al norte*/
	  game_set_player_location(game, current_id);
  }

  command_set_status(game->last_cmd, "OK");
  return;
}

/**-----------------------------------------------------------------------------
Permite al jugador coger un objeto que esta en la misma casilla.
------------------------------------------------------------------------------*/
void game_callback_get(Game* game){

  Space* current_space = NULL;
  Id current_space_id = NO_ID;
  Id current_object_id = NO_ID;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_space_id = game_get_player_location(game);
  if (NO_ID == current_space_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  current_space = game_get_space(game, current_space_id);
  if(current_space == NULL){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  /*Obtenemos el identificador del objeto que quiere coger el jugador*/
  current_object_id = atol(command_get_id_obj(game->last_cmd));
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  /*Comprobamos que el objeto se encuentra en el espacio actual*/
  if(space_check_object(current_space, current_object_id) == TRUE){
    /*Borramos el identificador del objeto del conjunto de identificadores del
    espacio*/
    remove_id (space_get_objects(current_space), current_object_id);
    /*Asiganamos el id del objeto al jugador*/
    player_add_object(game->player, current_object_id);
    /*Cambiamos el estado del comando*/
    command_set_status(game->last_cmd, "OK");
    return;
  }
  /*Si el objeto no se encuentra en el espacio cambiamos el estado del comando
  a error*/
  command_set_status(game->last_cmd, "ERROR");

  return;
}

/**-----------------------------------------------------------------------------
Permite al jugador soltar un objeto en la casilla actual.
------------------------------------------------------------------------------*/
void game_callback_drop(Game* game){

  Space* current_space = NULL;
  Id current_space_id = NO_ID;
  Id current_object_id = NO_ID;

  /* TODO innecesario
  Comprobamos si el jugador tiene asociado un objeto
  if(player_get_object(game->player) == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  */

 /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_space_id = game_get_player_location(game);
  if (NO_ID == current_space_id) {
    return;
  }
  current_space = game_get_space(game, current_space_id);
  if(current_space == NULL){
    return;
  }

  /*Obtenemos el identificador del objeto que quiere soltar el jugador*/
  current_object_id = atol(command_get_id_obj(game->last_cmd));
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Comprobamos que el objeto se lo porta el jugador*/
  if(player_check_object(game->player, current_object_id) == TRUE){
    /*Borramos el identificador del objeto del conjunto de identificadores del
    espacio*/
    remove_id (player_get_objects(game->player), current_object_id);
    /*Asiganamos el id del objeto al jugador*/
    space_add_object(current_space, current_object_id);
    /*Cambiamos el estado del comando*/
    command_set_status(game->last_cmd, "OK");
    return;
  }



  command_set_status(game->last_cmd, "OK");
  return;
}

/**-----------------------------------------------------------------------------
Permite al jugador lanzar el dado.
------------------------------------------------------------------------------*/
void game_callback_roll(Game* game){

  if(die_roll(game->die) == ERROR){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  command_set_status(game->last_cmd, "OK");
  return;
}


/**-----------------------------------------------------------------------------
Permite al jugador ir hacia la izquierda en aquellas casillas que estan
conectadas por el oeste.
------------------------------------------------------------------------------*/
void game_callback_left(Game* game){

  /*Variable auxiliares empleadas en el bucle*/
  Id current_id = NO_ID;
  Space* current_space;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    return;
  }
  current_space = game_get_space(game, current_id);
  if(current_space == NULL){
    return;
  }

  /*Obtenemos el identificador del espacio situado al oeste del jugador*/
  current_id = space_get_west(current_space);
  if (current_id != NO_ID) {
    /*Movemos el jugador al espacio situado al oeste*/
	  game_set_player_location(game, current_id);
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  command_set_status(game->last_cmd, "OK");
  return;
}


/**-----------------------------------------------------------------------------
Permite al jugador ir hacia la derecha en aquellas casillas conectadas por
el este.
------------------------------------------------------------------------------*/
void game_callback_right(Game* game){

  /*Variable auxiliares empleadas en el bucle*/
  Id current_id = NO_ID;
  Space* current_space;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    return;
  }
  current_space = game_get_space(game, current_id);
  if(current_space == NULL){
    return;
  }

  /*Obtenemos el identificador del espacio situado al este del jugador*/
  current_id = space_get_east(current_space);
  if (current_id != NO_ID) {
    /*Movemos el jugador al espacio situado al este*/
	  game_set_player_location(game, current_id);
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

   command_set_status(game->last_cmd, "OK");
  return;
}
