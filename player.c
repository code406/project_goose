/**
 * @brief Define un jugador y las funciones asociadas al jugador
 *
 * @file player.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "types.h"
#include "space.h"
#include "object.h"


/**
* @brief jugador
* Estructura que define un jugador, con un identificador (id) y un nombre,
*un id que indica en qué casilla se encuentra, y otro que indica qué objeto porta
*/
struct _Player
{
  Id player_id;
  char name[WORD_SIZE+1];
  Id space_id;
  Set *objects;
};

/**
* @brief player_create
* @author Arturo Morcillo
* Reserva memoria (vacía por calloc) para un nuevo jugador, e inicializa su id al especificado como argumento
* @file player.c
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Player
*/

Player* player_create(Id id)
{
  Player* newPlayer = NULL;

  /* Asigna memoria para newPlayer, comprueba que se ha asignado correctamente,
  y gracias a calloc está inicializada a NULL */
  if(!(newPlayer = (Player*)calloc(1,sizeof(Player))))
    return NULL;

  /* Inicializa su id al especificado como argumento */
  newPlayer->player_id = id;

  newPlayer->objects = set_create();

  return newPlayer;
}

/**
* @brief player_destroy
* @author Arturo Morcillo
* Libera la memoria reservada para un jugador y pone el puntero a NULL
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_destroy (Player *player)
{
  if (!player)
    return ERROR;

  set_destroy (player->objects);

  free(player);

  return OK;
}

/**
* @brief player_set_name
* @author Arturo Morcillo
* Asigna un nombre a un jugador
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @param name Cadena de caracteres que se guardará en player->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_set_name(Player* player, char* name)
{
  /* Comprueba los argumentos */
  if (!player || !name)
  {
    return ERROR;
  }

  /* Le asigna a  player.name el nombre introducido y lo comprueba */
  if (!strcpy(player->name, name))
  {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}

/**
* @brief player_set_location
* @author Arturo Morcillo
* Asigna una posicion a un jugador
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_set_location(Player* player, Id location)
{
  /*Comprueba los argumentos*/
  if (!player)
    return ERROR;

  player->space_id = location;
  /*Si todo va bien devuelve OK*/
  return OK;
}

/**
* @brief player_del_object
* @author Arturo Morcillo
* Quita el ultimo objeto de un jugador
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_del_object(Player* player)
{
  if (!player)
  {
    return ERROR;
  }

  if((set_del (player->objects))==ERROR)
    return ERROR;

  return OK;
}

/**
* @brief player_add_object
* @author Arturo Morcillo
* Coloca en el player especificado un objeto.
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @param value Entero de tipo id (long) que identifica un objeto
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_add_object(Player* player, Id value)
{
  if (!player)
  {
    return ERROR;
  }

  if((set_add (player->objects, value))==ERROR)
    return ERROR;

  return OK;
}

/**
* @brief player_get_name
* @author Arturo Morcillo
* Devuelve el nombre asignado a un jugador.
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return Cadena de caracteres con el nombre del jugador (player->name). Si el argumento introducido no es correcto, devuelve NULL
*/

char * player_get_name(Player* player)
{
  if (!player)
  {
    return NULL;
  }
  return player->name;
}

/**
* @brief player_get_id
* @author Arturo Morcillo
* Devuelve el id asignado a un jugador.
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica al jugador. Si el argumento introducido no es correcto, devuelve NO_ID
*/

Id player_get_id(Player* player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->player_id;
}

/**
* @brief player_get_location
* @author Arturo Morcillo
* Devuelve la posicion o casilla en que se encuentra un jugador.
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica la casilla en que se encuentra el jugador (player->space_id). Si el argumento introducido no es correcto, devuelve NO_ID
*/

Id player_get_location(Player* player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->space_id;
}

/**
* @brief player_get_objects
* @author Arturo Morcillo
* Devuelve la estructura objects (tipo set) del jugador introducido
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return Un puntero a estructura de tipo Set. En caso de error, o de que no haya objetos, devuelve NULL.
*/

Set* player_get_objects(Player* player)
{
  if (!player || player->objects == NULL)
  {
    return NULL;
  }

  return player->objects;
}

/**
* @brief player_print
* @author Arturo Morcillo
* Muestra por pantalla el nombre e id del jugador, y si porta o no un objeto
* @file player.c
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_print(Player* player)
{
  Set *set_aux = NULL;
  if (!player)
  {
    return ERROR;
  }

  set_aux = player_get_objects(player);
  if (set_aux == NULL)
    return ERROR;


  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->player_id, player->name);

  if (get_set_tope(set_aux) != 0)
  {
    fprintf(stdout, "---> The player has %d item(s).\n",get_set_tope(set_aux));
  }
  else
  {
    fprintf(stdout, "---> The player has no item.\n");
  }

  return OK;
}

/**
* @brief player_copy
* @author Arturo Morcillo
* Devuelve una copia del puntero introducido como argumento
* @file player.c
* @param pc Puntero a una estructura de tipo Player
* @return Un puntero a la copia
*/
Player* player_copy (Player* pc)
{
  Player *aux;
  Set *set_aux;
  Id id_aux;
  char *nombre;
  if (pc == NULL)
    return NULL;

  aux = player_create(pc->player_id);
  if(aux == NULL)
    return NULL;

  nombre = player_get_name(pc);
  player_set_name(pc, nombre);
  if(aux->name == NULL)
    return NULL;

  id_aux = player_get_location(pc);
  player_set_location(aux, id_aux);
  if(aux->space_id == NO_ID)
    return NULL;

  id_aux = NO_ID;

  set_aux = player_get_objects(pc);
  aux->objects = set_aux;
  if(aux->objects == NULL)
      return NULL;

  return aux;
}
