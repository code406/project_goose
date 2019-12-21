/**
 * @brief Implementa el modulo principal del juego
 *
 * @file game.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 2.0.E
 * @date 21/04/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "game.h"
#include "game_management.h"
#include "command.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "die.h"
#include "link.h"


#define N_CALLBACK 17 /*!<Numero de comandos disponibles*/

#define ID_P 1   /*!<Id que se asigna al jugador  */
#define ID_D 1   /*!<Id que se asigna al dado     */
#define INI_P 0  /*!<Posicion inicial del jugador */

/**
* @struct _Game
* @brief  Implementacion de la definicion de la estructura _Game
*/
struct _Game{
  Player* player; /*!< Jugador*/
  Object* objects[MAX_ID + 1];/*!<Conjunto de objetos del juego*/
  Space* spaces[MAX_SPACES + 1];/*!<Espacios del juego*/
  Die* die;/*!<Dado del juego*/
  D_Command* last_cmd;/*!<Datos del ultimo comando realizado*/
  Link* links[MAX_LINKS+1];/*!<Enlaces de las casillas del juego*/
  char odesc[WORD_SIZE+1];/*!<Descripcion de los objetos del juego*/
  char sdesc[WORD_SIZE+1];/*!<Descripcion de los espacios del juego*/
  char lsdesc[WORD_SIZE+1];/*!<Descripcion detallada de los espacios del juego*/
  int game_rules_day;/*!<Contador de dia para game_rules*/
  int game_rules_next_action;/*!<Contador de pistas para game_rules*/
  int game_rules_notes;/*!<Contador de notas para game_rules*/
  int game_rules_n_cmd;/*!<Contador de comandos para game_rules*/
  int showmap;/*!<Variable que decide si se muestra o no el mapa*/
  BOOL game_is_over;
};

/*******************************************************************************
 *                    DECLARACION FUNCIONES PRIVADAS
 ******************************************************************************/

/**
* @typedef void (*callback_fn)(Game* game)
* @brief Define el tipo de funcion para los callbacks.
*/
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
void game_callback_move(Game* game);
void game_callback_check(Game* game);
void game_callback_turnon(Game* game);
void game_callback_turnoff(Game *game);
void game_callback_open(Game* game);
void game_callback_save(Game* game);
void game_callback_load(Game* game);
void game_callback_showmap(Game* game);



/**
* @static callback_fn game_callback_fn_list
* @brief Lista de las funciones callbacks disponibles
* Si el usuario introduce un comando, invoco a la función de este, que
* tiene un índice en la tabla. Así, se puede reducir el código con bucles.
* Cada uno apunta a una función game_callback_<cmd>.
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
  game_callback_right,
  game_callback_move,
  game_callback_check,
  game_callback_turnon,
  game_callback_turnoff,
  game_callback_open,
  game_callback_save,
  game_callback_load,
  game_callback_showmap
};

/**
* @name game_get_space_id_at
* @date   08-04-2018
* @author Javier Mateos
* @brief Obtiene el id de un espacio en funcion de la posicion en el vector spaces.
* @param game: juego en el que se encuentra el espacio.
* @param position: posicion en el vector spaces de la estructura game.
* @return Devuelve el id del espacio o NO_ID si se produce algun error.
*/

Id game_get_space_id_at(Game* game, int position);

/**
* @name game_get_link_id_at
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el identificador del link asociado a una posicion
* @param game Puntero a una estructura de tipo Game
* @param position entero (int)
* @return Entero de tipo Id (long) que identifica el link asociado a una posicion
*/

Id game_get_link_id_at(Game* game, int position);

/*----------------------  Fin de funciones privadas  -------------------------*/

/*******************************************************************************
*              IMPLEMENTACION DE LA INTERFAZ DEL JUEGO
******************************************************************************/

/*******************************************************************************
*
*       BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/*******************************************************************************
* Crea e inicializa el juego reservando memoria dinamica.
*******************************************************************************/

Game* game_create()
{
  Game *game;
  int i;

  game =(Game*)malloc(sizeof(Game));
  if(game == NULL)
    return NULL;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  /* Asigna un id al jugador*/
  game->player=player_create(ID_P);

  for (i = 0; i < MAX_ID; i++)
  {
    game->objects[i] = NULL;
  }

  /* Inicializa el comando y el dado de game */
  game->last_cmd = command_create();
  game->die = die_create(ID_D);

  /*Inicializa los enlaces de game*/
  for(i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }

  /* Inicializa las descripciones de objeto y casilla de game */
  strcpy(game->odesc, " " );
  strcpy(game->sdesc, " " );
  strcpy(game->lsdesc, " " );

  /*Inicializa el valor de showmap*/
  game->showmap = 0;

  /* Inicializa los campos relacionados con game_rules */
  game->game_rules_day = 0;
  game->game_rules_next_action = 0;
  game->game_rules_notes = -1;
  game->game_rules_n_cmd = 0;

  return game;
}

/*******************************************************************************
* Crea el game, carga las casillas del archivo y coloca player en la posicion inicial
*******************************************************************************/
Game* game_create_from_file(char* filename)
{
  Game *game = NULL;

  /* Crea el game y lo comprueba */
  game = game_create();
  if (game == NULL)
    return NULL;

  game->game_is_over = FALSE;

  /* Carga los espacios del archivo */
  if (game_management_load_spaces(game, filename) == ERROR)
    return NULL;

  if (game_management_load_objects(game, filename) == ERROR)
    return NULL;

  if (game_management_load_links(game, filename) == ERROR)
    return NULL;

  /* Coloca a jugador su casilla inicial (INI_P) */
  game_set_player_location(game, game_get_space_id_at(game, INI_P));

  return game;
}

/*******************************************************************************
*  Elimina todas las casillas del Game, y libera la memoria reservada
*******************************************************************************/
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

  for (i = 0; (i < MAX_ID) && (game->objects[i] != NULL); i++)
  {
    /* Libera memoria correspondiente a cada objeto */
    object_destroy(game->objects[i]);
    game->objects[i] = NULL;
  }

  /* Libera memoria correspondiente al dado */
  die_destroy(game->die);
  game->die = NULL;

  /* Libera memoria correspondiente al jugador */
  player_destroy(game->player);
  game->player = NULL;

  command_destroy(game->last_cmd);
  game->last_cmd = NULL;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    /*Libera la memoria correspondiente a cada link*/
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }

  free(game);

  return OK;
}

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA ACCEDER A LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/*******************************************************************************
*   Devuelve el objeto de game que coincide con el id introducido
*******************************************************************************/
Object* game_get_object(Game* game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  /* Recorre los objectos del juego y devuelve el que coincide con ese id */
  for (i = 0; i < MAX_ID && game->objects[i] != NULL; i++)
  {
    if (id == object_get_id(game->objects[i]))
    {
      return game->objects[i];
    }
  }

  return NULL;
}

/*******************************************************************************
*  Devuelve la casilla de game que coincide con el id introducido
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
*  Devuelve los datos del ultimo comando introducido
*******************************************************************************/
D_Command* game_get_command(Game* game)
{
  return game->last_cmd;
}

/*******************************************************************************
*  Devuelve un puntero que apunta al jugador
*******************************************************************************/

Player* game_get_player(Game *game){
  if (game == NULL)
    return NULL;

  return game->player;
}

/*******************************************************************************
*  Devuelve la posición del jugador de la estructura game.
*******************************************************************************/
Id game_get_player_location(Game* game)
{
  return (player_get_location(game->player));
}



/*******************************************************************************
*  Devuelve si el objeto es portado por el jugador
*******************************************************************************/
BOOL game_check_object_player(Game* game, Object *object)
{
  Id object_id_aux;
  BOOL status = FALSE;


  if (!game || !object)
  {
    return FALSE;
  }

  /* Obtengo el id del objeto*/
  object_id_aux = object_get_id(object);

  /*Compruebo si el jugador lleva el objeto*/
  if(player_check_object(game->player, object_id_aux) == TRUE){
    status = TRUE;
  }

  return status;
}

/*******************************************************************************
*  Obtiene el id de un espacio en funcion de la posicion en el vector spaces.
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
*  Devuelve la id del objecto asociado a una posicion
*******************************************************************************/
Id game_get_object_id_at(Game* game, int position)
{
  /* Comprueba que la posicion sea correcta */
  if (position < 0 || position >= MAX_ID)
  {
    return NO_ID;
  }

  return object_get_id(game->objects[position]);
}

/*******************************************************************************
*  Devuelve la posición del objeto de la estructura game.
*******************************************************************************/
Id game_get_object_location(Game* game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NO_ID;
  }

  /*Comprobamos si el jugador lleva el objeto*/
  if(player_check_object(game->player, id) == TRUE){
    return game_get_player_location(game);
  }

  /*Recorro todos los espacios*/
  for(i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
    /*Vemos que espacio tiene el objeto del que queremos saber la ubicacion*/
    if(space_check_object(game->spaces[i], id) == TRUE){
      /*Obtenemos el identificador del espacio que tiene el objeto*/
      return space_get_id(game->spaces[i]);
    }
  }

  /*Si llegamos hasta aqui quiere decir que no hemos encontrado el objeto en ningun espacio*/
  return NO_ID;
}

/*******************************************************************************
*  Devuelve la descripcion del objeto
*******************************************************************************/
char* game_get_object_description(Game *game){

  if(game == NULL) return NULL;

  return game->odesc;
}

/*******************************************************************************
*  Devuelve la descripcion del espacio
*******************************************************************************/
char* game_get_space_description(Game *game){
  if(game == NULL) return NULL;

  return game->sdesc;
}

/*******************************************************************************
*  Devuelve la descripcion detallada del espacio
*******************************************************************************/
char* game_get_space_long_description(Game *game){
  if(game == NULL) return NULL;

  return game->lsdesc;
}

/*******************************************************************************
*  Obtiene el id de un objeto introduciendo su nombre.
*******************************************************************************/
Id game_object_get_id_from_name(const char* name, Game *game)
{
  int i;
  char *aux;

  if (!name || !game)
  {
    return NO_ID;
  }

  for (i=0; i < MAX_ID && game->objects[i] != NULL ;i++){
    aux = object_get_name (game->objects[i]);
    if (strcasecmp(name,aux)==0)
      return object_get_id(game->objects[i]);
  }

  return NO_ID;
}

/*******************************************************************************
*  Obtiene el identificador de un enlace dado su nombre.
*******************************************************************************/
Id game_link_get_id_from_name(const char* name, Game *game)
{
  int i;

  if (!name || !game)
  {
    return NO_ID;
  }

  for (i=0; i < MAX_LINKS && game->links[i] != NULL ;i++){
    if (strcasecmp(name, link_get_name(game->links[i])) == 0)
      return link_get_id(game->links[i]);
  }

  return NO_ID;
}

/*******************************************************************************
*  Devuelve el último comando introducido
*******************************************************************************/
T_Command game_get_last_command(Game* game)
{
  return command_get_t_cmd(game->last_cmd);
}

/*******************************************************************************
*  Devuelve el estado del ultimo comando realizado.
*******************************************************************************/
const char* game_get_status_command(Game* game){

  return command_get_status(game->last_cmd);
}

/*******************************************************************************
* Devuelve el puntero a link del juego que tiene el identificador del argumento
*******************************************************************************/
Link* game_get_link(Game* game, Id id){

  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  /* Recorre los links del juego y devuelve el que coincide con ese id */
  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (id == link_get_id(game->links[i]))
    {
      return game->links[i];
    }
  }

  return NULL;
}

/*******************************************************************************
* Devuelve el identificador del link asociado a una posicion
*******************************************************************************/
Id game_get_link_id_at(Game* game, int position)
{
  /* Comprueba que la posicion sea correcta */
  if (position < 0 || position >= MAX_LINKS)
  {
    return NO_ID;
  }

  return link_get_id(game->links[position]);
}

/*******************************************************************************
* Devuelve el identificador de la casilla al norte de la posicion actual
*******************************************************************************/
Id game_get_space_north(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al norte de la casilla*/
  link_id = space_get_north_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al norte de la casilla*/
  if(link_get_espacio_1(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }
}

/*******************************************************************************
* Devuelve el identificador de la casilla al este de la posicion actual
*******************************************************************************/
Id game_get_space_east(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al norte de la casilla*/
  link_id = space_get_east_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al este de la casilla*/
  if(link_get_espacio_1(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }

}

/*******************************************************************************
* Devuelve el identificador de la casilla al sur de la posicion actual
*******************************************************************************/
Id game_get_space_south(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al surde la casilla*/
  link_id = space_get_south_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al este de la casilla*/
  if(link_get_espacio_1(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }

}

/*******************************************************************************
* Devuelve el identificador de la casilla al oeste de la posicion actual
*******************************************************************************/
Id game_get_space_west(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al norte de la casilla*/
  link_id = space_get_west_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al este de la casilla*/
  if(link_get_espacio_1(link) == id)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }

}

/*******************************************************************************
* Devuelve el identificador de la casilla al oeste de la posicion actual
*******************************************************************************/
Id game_get_space_up(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al norte de la casilla*/
  link_id = space_get_up_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al este de la casilla*/
  if(link_get_espacio_1(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }

}

/*******************************************************************************
* Devuelve el identificador de la casilla al oeste de la posicion actual
*******************************************************************************/
Id game_get_space_down(Game* game, Id id){

  Id link_id = NO_ID;
  Space* current_space = NULL;
  Link* link = NULL;

  if(game == NULL || id == NO_ID){
    return NO_ID;
  }

  current_space = game_get_space(game, id);
  /*Obtenemos cual es el link situado al norte de la casilla*/
  link_id = space_get_down_link(current_space);
  if(link_id == NO_ID){
    return NO_ID;
  }
  link = game_get_link(game, link_id);

  /*Obtenemos el identificador del espacio situado al este de la casilla*/
  if(link_get_espacio_1(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_2(link);
  }
  else if(link_get_espacio_2(link) == id && link_get_linked(link) == TRUE)
  {
    return link_get_espacio_1(link);
  }
  else
  {
    return NO_ID;
  }

}

/*******************************************************************************
* Obtiene el ultimo valor del dado del juego
*******************************************************************************/
int game_get_last_roll(Game* game){

  if(game == NULL){
    return -1;
  }

  return die_get_last_roll(game->die);
}

/*******************************************************************************
* Obtiene el dado de la estructura game
*******************************************************************************/
Die* game_get_die(Game *game){
  if(game == NULL){
    return NULL;
  }

  return game->die;

}
/*******************************************************************************
* Obtiene el valor game_rules_day de game
*******************************************************************************/
int game_get_game_rules_day (Game* game){
  if(game == NULL){
    return -1;
  }

  return game->game_rules_day;
}

/*******************************************************************************
* Obtiene el valor game_rules_next_action de game
*******************************************************************************/
int game_get_game_rules_next_action (Game* game){
  if(game == NULL){
    return -1;
  }

  return game->game_rules_next_action;
}

/*******************************************************************************
* Obtiene el valor game_rules_notes de game
*******************************************************************************/
int game_get_game_rules_notes (Game* game){
  if(game == NULL){
    return -1;
  }

  return game->game_rules_notes;
}

/*******************************************************************************
* Obtiene el valor game_rules_n_cmd de game
*******************************************************************************/
int game_get_game_rules_n_cmd (Game* game){
  if(game == NULL){
    return -1;
  }

  return game->game_rules_n_cmd;
}

/*******************************************************************************
* Obtiene el valor showmap de game
*******************************************************************************/
int game_get_showmap (Game* game){
  if(game == NULL){
    return -1;
  }

  return game->showmap;
}

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA MODIFICAR LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/*******************************************************************************
* Fija la posición del jugador en el identificador de la casilla introducida
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
* Fija la posición del objeto en una casilla.
*******************************************************************************/
STATUS game_set_object_location(Game* game, Id id_object, Id space_id)
{
  int i;

  /*Comprobacion de que los argumentos son correctos*/
  if (game == NULL || id_object == NO_ID || space_id == NO_ID) {
    return ERROR;
  }

  for(i=0; i<MAX_SPACES; i++){
    /*Buscamos en el conjunto de objetos de cada espacio el id del objeto*/
    if(space_check_object(game->spaces[i], id_object) == TRUE){
      /*Eliminamos del conjunto de objetos del espacio el id del objeto*/
      if(space_del_object(game->spaces[i], id_object) == ERROR){
        return ERROR;
      }
    }
  }

  for(i=0; i<MAX_SPACES; i++){
    /*Buscamos el espacio con el identificador del argumento*/
    if(space_id == space_get_id(game->spaces[i])){
      /*Insertamos el id del objeto en el conjunto de objetos del espacio*/
      space_add_object(game->spaces[i], id_object);
    }
  }

  return OK;
}

/*******************************************************************************
* Fija el valor de game_rules_day
*******************************************************************************/
STATUS game_set_game_rules_day (Game* game, int day){
  if (game == NULL)
    return ERROR;

  game->game_rules_day = day;

  return OK;
}

/*******************************************************************************
* Fija el valor de game_rules_next_action
*******************************************************************************/
STATUS game_set_game_rules_next_action (Game* game, int n_a){
  if (game == NULL)
    return ERROR;

  game->game_rules_next_action = n_a;

  return OK;
}

/*******************************************************************************
* Fija el valor de game_rules_notes
*******************************************************************************/
STATUS game_set_game_rules_notes (Game* game, int notes){
  if (game == NULL)
    return ERROR;

  game->game_rules_notes = notes;

  return OK;
}

/*******************************************************************************
* Fija el valor de game_rules_day
*******************************************************************************/
STATUS game_set_game_rules_n_cmd (Game* game, int n_cmd){
  if (game == NULL)
    return ERROR;

  game->game_rules_n_cmd = n_cmd;

  return OK;
}

/*******************************************************************************
* Fija el valor de game_rules_day
*******************************************************************************/
STATUS game_set_game_is_over (Game* game, BOOL game_is_over){
  if (game == NULL)
    return ERROR;

  game->game_is_over = game_is_over;

  return OK;
}

/*******************************************************************************
* Establece el tipo de comando utilizado en el juego
*******************************************************************************/
STATUS game_set_last_t_cmd(Game* game, T_Command cmd){

  if(game == NULL || cmd == NO_CMD) return ERROR;

  command_set_t_cmd(game->last_cmd, cmd);

  return OK;
}

/*******************************************************************************
* Establece el tipo de comando utilizado en el juego
*******************************************************************************/
STATUS game_set_last_cmd_status(Game* game, char* status){

  if(game == NULL) return ERROR;

  command_set_status(game->last_cmd, status);

  return OK;
}

/*******************************************************************************
* Actualiza los datos del juego en funcion del comando recibido
*******************************************************************************/
STATUS game_update(Game* game, T_Command cmd) {
  if(command_set_t_cmd(game->last_cmd, cmd) == ERROR){
    return ERROR;
  }
  strcpy(game->odesc, " " );
  strcpy(game->sdesc, " " );
  strcpy(game->lsdesc, " " );
  game->showmap = 0;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

/*******************************************************************************
* Añade una casilla creada previamente al juego
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
* Añade un objeto creado previamente al juego
*******************************************************************************/
STATUS game_add_object(Game* game, Object* object)
{
  int i = 0;

  if (game == NULL || object == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_ID) && (game->objects[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_ID)
  {
    return ERROR;
  }

  game->objects[i] = object;

  return OK;
}

/*******************************************************************************
* Añade un link creado previamente al juego
*******************************************************************************/
STATUS game_add_link(Game* game, Link* link)
{
  int i = 0;

  if (game == NULL || link == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_LINKS) && (game->links[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_LINKS)
  {
    return ERROR;
  }

  game->links[i] = link;

  return OK;
}

/*******************************************************************************
* Se encarga de devolver si el juego deberia terminar o no
*******************************************************************************/
BOOL game_get_game_is_over(Game* game)
{
  return game->game_is_over;
}

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA DEPURAR LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/*******************************************************************************
* Imprime toda la informacion del TAD Game
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
  for (i = 0; i < MAX_ID && game->objects[i] != NULL; i++)
  {
    object_print(game->objects[i]);
  }

  /*Imprime el dado*/
  die_print(game->die);

  /*Imprime el comando*/
  printf("=> Datos del ultimo comando: ");
  command_print(game->last_cmd);

  printf("=> Links: \n");
  for(i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    link_print(game->links[i]);
  }

  printf("prompt:> ");
}

/******************************************************************************
*
*        IMPLEMENTACION DE LAS FUNCIONES CALLBACKS PARA CADA COMANDO
*
*******************************************************************************/

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


  Id current_id = NO_ID, south_id = NO_ID;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al sur del jugador*/
  south_id = game_get_space_south(game, current_id);
  if (south_id != NO_ID) {
    /*Movemos el jugador al espacio situado al sur*/
	  game_set_player_location(game, south_id);
    command_set_status(game->last_cmd, "OK");
    return;
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
  }

  return;
}

/**-----------------------------------------------------------------------------
Modifica el estado del juego retrocediendo en una casilla la
posicion del jugador.
------------------------------------------------------------------------------*/
void game_callback_previous(Game* game) {

  Id current_id = NO_ID, north_id = NO_ID;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al norte del jugador*/
  north_id = game_get_space_north(game, current_id);
  if (north_id != NO_ID) {
    /*Movemos el jugador al espacio situado al norte*/
	  game_set_player_location(game, north_id);
    command_set_status(game->last_cmd, "OK");
    return;
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
  }

  return;
}

/**-----------------------------------------------------------------------------
Permite al jugador coger un objeto que esta en la misma casilla.
------------------------------------------------------------------------------*/
void game_callback_get(Game* game){

  Space* current_space = NULL;
  Id current_space_id = NO_ID;
  Id current_object_id = NO_ID;
  const char* current_object_name = NULL;
  Object* current_object = NULL;

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

  /*Obtenemos el nombre del objeto que quiere coger el jugador*/
  current_object_name = command_get_obj_name(game->last_cmd);
  /*Obtenemos el identificador del objeto dado su nombre*/
  current_object_id = game_object_get_id_from_name(current_object_name, game);
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  /*Obtenemos el puntero al objeto del juego que quiere coger el jugador*/
  current_object = game_get_object(game, current_object_id);

  /*Comprobamos que el objeto se encuentra en el espacio actual*/
  if(space_check_object(current_space, current_object_id) == TRUE && object_get_movable(current_object) == TRUE){
    /*Borramos el identificador del objeto del conjunto de identificadores del
    espacio*/
    space_del_object (current_space, current_object_id);
    /*Asiganamos el id del objeto al jugador*/
    player_add_object(game->player, current_object_id);
    object_set_moved(game_get_object(game,current_object_id),TRUE);

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
  const char* current_object_name = NULL;

 /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_space_id = game_get_player_location(game);
  if (NO_ID == current_space_id) {
    return;
  }
  current_space = game_get_space(game, current_space_id);
  if(current_space == NULL){
    return;
  }

  /*Obtenemos el nombre del objeto que quiere coger el jugador*/
  current_object_name = command_get_obj_name(game->last_cmd);
  /*Obtenemos el identificador del objeto dado su nombre*/
  current_object_id = game_object_get_id_from_name(current_object_name, game);
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Comprobamos que el objeto lo porta el jugador*/
  if(player_check_object(game->player, current_object_id) == TRUE){
    /*Borramos el identificador del objeto del conjunto de identificadores del
    espacio*/
    player_del_object(game->player, current_object_id);
    /*Asiganamos el id del objeto al jugador*/
    space_add_object(current_space, current_object_id);
    /*Cambiamos el estado del comando*/
    command_set_status(game->last_cmd, "OK");
    return;
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
  }

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

  Id current_id = NO_ID, west_id = NO_ID;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al oeste del jugador*/
  west_id = game_get_space_west(game, current_id);
  if (west_id != NO_ID) {
    /*Movemos el jugador al espacio situado al oeste*/
    game_set_player_location(game, west_id);
    command_set_status(game->last_cmd, "OK");
    return;
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
  }

  return;
}


/**-----------------------------------------------------------------------------
Permite al jugador ir hacia la derecha en aquellas casillas conectadas por
el este.
------------------------------------------------------------------------------*/
void game_callback_right(Game* game){

  Id current_id = NO_ID, east_id = NO_ID;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id) {
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el identificador del espacio situado al este del jugador*/
  east_id = game_get_space_east(game, current_id);
  if (east_id != NO_ID) {
    /*Movemos el jugador al espacio situado al este*/
    game_set_player_location(game, east_id);
    command_set_status(game->last_cmd, "OK");
    return;
  }
  else{
    command_set_status(game->last_cmd, "ERROR");
  }

  return;
}


/**-----------------------------------------------------------------------------
Comando por el cual el jugador se mueve en la direccion especificada
------------------------------------------------------------------------------*/
void game_callback_move(Game* game) {

  /*Variable auxiliares empleadas en el bucle*/
  Id current_id = NO_ID, north_id = NO_ID, east_id = NO_ID, south_id = NO_ID, west_id = NO_ID;
  const char* command_dir = NULL;

  /*Obtenemos el espacio en el que se encuentra el jugador*/
  current_id = game_get_player_location(game);
  if (NO_ID == current_id)
  {
    command_set_status(game->last_cmd, "ERROR");
    command_set_direction(game->last_cmd, "none");
    return;
  }

  /*Obtenemos la direccion en la que quiere moverse el jugador*/
  command_dir = command_get_direction(game->last_cmd);

  /*Comparamos esa direccion con las 4 disponibles, y asignamos el id que corresponda*/
  if((strcasecmp(command_dir, "n")==0) || strcasecmp(command_dir, "north")==0)
  {
    /*Obtenemos el identificador del espacio situado al norte del jugador*/
    north_id = game_get_space_north(game, current_id);
    if (north_id != NO_ID && space_get_ocupada(game_get_space(game,game_get_space_north(game, current_id)))!= TRUE) {
      /*Movemos el jugador al espacio situado al norte*/
  	  game_set_player_location(game, north_id);
      command_set_status(game->last_cmd, "OK");
      command_set_direction(game->last_cmd, "north");
      return;
    }
    else{
      command_set_status(game->last_cmd, "ERROR");
      command_set_direction(game->last_cmd, "north");
      return;
    }
  }
  else if((strcasecmp(command_dir, "s")==0) || strcasecmp(command_dir, "south")==0)
  {
    /*Obtenemos el identificador del espacio situado al sur del jugador*/
    south_id = game_get_space_south(game, current_id);
    if (south_id != NO_ID && space_get_ocupada(game_get_space(game,game_get_space_south(game, current_id)))!= TRUE) {
      /*Movemos el jugador al espacio situado al sur*/
  	  game_set_player_location(game, south_id);
      command_set_status(game->last_cmd, "OK");
      command_set_direction(game->last_cmd, "south");
      return;
    }
    else{
      command_set_status(game->last_cmd, "ERROR");
      command_set_direction(game->last_cmd, "south");
      return;
    }
  }
  else if((strcasecmp(command_dir, "e")==0) || strcasecmp(command_dir, "east")==0)
  {
    /*Obtenemos el identificador del espacio situado al este del jugador*/
    east_id = game_get_space_east(game, current_id);
    if (east_id != NO_ID && space_get_ocupada(game_get_space(game,game_get_space_east(game, current_id)))!= TRUE && link_get_linked(game_get_link(game, space_get_east_link(game_get_space(game, current_id))))==TRUE) {
      /*Movemos el jugador al espacio situado al este*/
      game_set_player_location(game, east_id);
      command_set_status(game->last_cmd, "OK");
      command_set_direction(game->last_cmd, "east");
      return;
    }
    else{
      command_set_status(game->last_cmd, "ERROR");
      command_set_direction(game->last_cmd, "east");
      return;
    }
  }
  else if((strcasecmp(command_dir, "w")==0) || strcasecmp(command_dir, "west")==0)
  {
    /*Obtenemos el identificador del espacio situado al oeste del jugador*/
    west_id = game_get_space_west(game, current_id);
    if (west_id != NO_ID && space_get_ocupada(game_get_space(game,game_get_space_west(game, current_id)))!= TRUE && link_get_linked(game_get_link(game, space_get_west_link(game_get_space(game, current_id))))==TRUE) {
      /*Movemos el jugador al espacio situado al oeste*/
      game_set_player_location(game, west_id);
      command_set_status(game->last_cmd, "OK");
      command_set_direction(game->last_cmd, "west");
      return;
    }
    else{
      command_set_status(game->last_cmd, "ERROR");
      command_set_direction(game->last_cmd, "west");
      return;
      }
    }
    else if((strcasecmp(command_dir, "u")==0) || strcasecmp(command_dir, "up")==0)
    {
      /*Obtenemos el identificador del espacio situado encima del jugador*/
      east_id = game_get_space_up(game, current_id);
      if (east_id != NO_ID) {
        /*Movemos el jugador al espacio situado al este*/
        game_set_player_location(game, east_id);
        command_set_status(game->last_cmd, "OK");
        command_set_direction(game->last_cmd, "up");
        return;
      }
      else{
        command_set_status(game->last_cmd, "ERROR");
        command_set_direction(game->last_cmd, "up");
        return;
        }
      }
      else if((strcasecmp(command_dir, "d")==0) || strcasecmp(command_dir, "down")==0)
      {
        /*Obtenemos el identificador del espacio situado debajo del jugador*/
        east_id = game_get_space_down(game, current_id);
        if (east_id != NO_ID) {
          /*Movemos el jugador al espacio situado al este*/
          game_set_player_location(game, east_id);
          command_set_status(game->last_cmd, "OK");
          command_set_direction(game->last_cmd, "down");
          return;
        }
        else{
          command_set_status(game->last_cmd, "ERROR");
          command_set_direction(game->last_cmd, "down");
          return;
        }
  }
  else
  {
    command_set_status(game->last_cmd, "ERROR");
    command_set_direction(game->last_cmd, "that way");
    return;
  }

}

/**-----------------------------------------------------------------------------
Comando que permite examinar los objetos obteniendo su descripcion
------------------------------------------------------------------------------*/
void game_callback_check(Game *game){

 /*Variable auxiliares empleadas en el bucle*/
  Id current_space_id = NO_ID, current_object_id = NO_ID;
  Space * current_space = NULL;
  const char* current_object_name = NULL;
  Object * object = NULL;

  if(strcasecmp(command_get_obj_name(game->last_cmd), "s") == 0 ||
     strcasecmp(command_get_obj_name(game->last_cmd), "space") == 0){
    /*Obtenemos el espacio en el que se encuentra el jugador*/
    current_space_id = game_get_player_location(game);
    if (NO_ID == current_space_id) {
      return;
    }
    current_space = game_get_space(game, current_space_id);
    if(current_space == NULL){
      return;
    }
    if (space_get_lit(current_space) == TRUE){
      strcpy(game->lsdesc, space_get_long_description(current_space));
    }
    else{
      strcpy(game->lsdesc, space_get_description(current_space));
    }

  }else{
    /*Obtenemos el espacio en el que se encuentra el jugador*/
    current_space_id = game_get_player_location(game);
    if (NO_ID == current_space_id) {
      return;
    }
    current_space = game_get_space(game, current_space_id);
    if(current_space == NULL){
      return;
    }

    if(space_get_lit(current_space) == TRUE){
      /*Obtenemos la descripcion detallada del objeto que quiere coger el jugador*/
      current_object_name = command_get_obj_name(game->last_cmd);
      /*Obtenemos el identificador del objeto dado su descripcion*/
      current_object_id = game_object_get_id_from_name(current_object_name, game);
      if(current_object_id == NO_ID){
        command_set_status(game->last_cmd, "ERROR");
        return;
      }
      /*Obtenemos el objeto del que voy a obtener su descripcion*/
      object = game_get_object(game, current_object_id);

      if(object_get_moved(object) == TRUE){
        /*Obtenemos la descripcion detallada del objeto que quiere coger el jugador*/
        if(game_check_object_player(game, object) || space_check_object(current_space, object_get_id(object))){
          strcpy(game->odesc, object_get_far_description(object));
        }else{
          command_set_status(game->last_cmd, "ERROR");
          return;
        }
      }
      else{
        /*Obtenemos la descripcion detallada del objeto que quiere coger el jugador*/
        if(game_check_object_player(game, object) || space_check_object(current_space, object_get_id(object))){
          strcpy(game->odesc, object_get_description(object));
        }else{
          command_set_status(game->last_cmd, "ERROR");
          return;
        }
      }
    }
    else{
      strcpy(game->odesc, " ");
    }
  }

  command_set_obj_name(game->last_cmd, "space");
  command_set_status(game->last_cmd, "OK");
  return ;
}

/**-----------------------------------------------------------------------------
Comando que permite encender los objetos
------------------------------------------------------------------------------*/
void game_callback_turnon(Game *game){

  /*Variable auxiliares empleadas en el bucle*/
  Id current_object_id;
  const char* current_object_name = NULL;
  Object * current_object = NULL;

  /*Obtenemos el nombre del objeto que quiere coger el jugador*/
  current_object_name = command_get_obj_name(game->last_cmd);
  /*Obtenemos el identificador del objeto dado su nombre*/
  current_object_id = game_object_get_id_from_name(current_object_name, game);
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  /*Obtenemos el puntero al objeto del juego que quiere coger el jugador*/
  current_object = game_get_object(game, current_object_id);

  /*Comprobamos si el objeto se puede iluminar*/
  if(object_get_light_space(current_object) == TRUE && object_get_on(current_object) == FALSE){
    object_set_on(current_object, TRUE);
  } else{
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Si el objeto no se encuentra en el espacio cambiamos el estado del comando
  a error*/
  command_set_status(game->last_cmd, "OK");

  return;
}

/**-----------------------------------------------------------------------------
Comando que permite apagar los objetos
------------------------------------------------------------------------------*/
void game_callback_turnoff(Game *game){

  /*Variable auxiliares empleadas en el bucle*/
  Id current_object_id;
  const char* current_object_name = NULL;
  Object * current_object = NULL;

  /*Obtenemos el nombre del objeto que quiere coger el jugador*/
  current_object_name = command_get_obj_name(game->last_cmd);
  /*Obtenemos el identificador del objeto dado su nombre*/
  current_object_id = game_object_get_id_from_name(current_object_name, game);
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  /*Obtenemos el puntero al objeto del juego que quiere coger el jugador*/
  current_object = game_get_object(game, current_object_id);

  /*Comprobamos si el objeto se puede iluminar*/
  if(object_get_light_space(current_object) == TRUE && object_get_on(current_object) == TRUE){
    object_set_on(current_object, FALSE);
  } else{
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Si el objeto no se encuentra en el espacio cambiamos el estado del comando
  a error*/
  command_set_status(game->last_cmd, "OK");

  return;
}

/**-----------------------------------------------------------------------------
Comando que permite abrir un enlace mediante un objeto que porta el jugador
------------------------------------------------------------------------------*/
void game_callback_open(Game *game){

  /*Declaración de variables*/
  Id current_space_id = NO_ID, current_object_id = NO_ID, link_id = NO_ID;
  Space * current_space = NULL;
  Link* link = NULL;
  const char* current_object_name = NULL;
  const char* link_name = NULL;
  Object * object = NULL;

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

  /*Obtenemos el enlace que se va a abrir*/
  link_name = command_get_link_name(game->last_cmd);
  printf("%s",link_name);
  link_id = game_link_get_id_from_name(link_name, game);
  if(link_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  link = game_get_link(game, link_id);
  if(link == NULL){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Obtenemos el objeto que se va a utilizar para abrir el enlace*/
  current_object_name = command_get_obj_name(game->last_cmd);
  current_object_id = game_object_get_id_from_name(current_object_name, game);
  if(current_object_id == NO_ID){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }
  object = game_get_object(game, current_object_id);
  if(object == NULL){
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  /*Si el objeto es portado por el jugador, el enlace está cerrado y el objeto puede abrirlo, se abre*/
  if(game_check_object_player(game, object)==TRUE && link_get_linked(link)==FALSE && object_get_open_link(object) == link_id){
    link_set_linked(link, TRUE);
  }else{
    command_set_status(game->last_cmd, "ERROR");
    return;
  }

  command_set_status(game->last_cmd, "OK");
  return ;
}

/**-----------------------------------------------------------------------------
Comando que permite guardar la partida
------------------------------------------------------------------------------*/
void game_callback_save(Game *game){

    if((game_management_save(game))==ERROR){
      command_set_status(game->last_cmd,"ERROR");
      return;
    }

  command_set_status(game->last_cmd, "OK");

  return;
}

/**-----------------------------------------------------------------------------
Comando que permite cargar la partida
------------------------------------------------------------------------------*/
void game_callback_load(Game *game){

    if((game_management_load(game))==ERROR){
      command_set_status(game->last_cmd,"ERROR");
      return;
    }

  command_set_status(game->last_cmd, "OK");

  return;
}

/**-----------------------------------------------------------------------------
Comando que permite abrir el mapa
------------------------------------------------------------------------------*/
void game_callback_showmap(Game *game){

  if(game_check_object_player(game, game_get_object(game, 14)) == TRUE){
    game->showmap = 1;
    command_set_status(game->last_cmd, "OK");
    return;
  }
  command_set_status(game->last_cmd, "ERROR");
  return;
}
