/**
 * @brief Implementa la interfaz publica del modulo player, necesario para describir
 *        la informacion relacionada con el estado del jugador.
 *
 * @file player.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "types.h"
#include "inventory.h"


/**
* @struct _Player
* @brief  Implementacion de la definicion de la estructura Player
*/
struct _Player
{
  Id player_id; /*!<Identificador del jugador*/
  char name[WORD_SIZE+1]; /*!<Nombre del jugador*/
  Id space_id; /*!<Casilla en la que se encuentra el jugador*/
  Inventory *inventory; /*!<Inventario de objetos del jugador*/
};

/*******************************************************************************
*	Reserva memoria (vacía por calloc) para un nuevo jugador, e inicializa su id
* al especificado como argumento
*******************************************************************************/
Player* player_create(Id id)
{
  Player* newPlayer = NULL;

  /* Asigna memoria para newPlayer, comprueba que se ha asignado correctamente,
  y gracias a calloc está inicializada a NULL */
  if(!(newPlayer = (Player*)calloc(1,sizeof(Player))))
    return NULL;

  /* Inicializa su id al especificado como argumento */
  newPlayer->player_id = id;

  newPlayer->name[0] = '\0';

  newPlayer->space_id = NO_ID;

  if(!(newPlayer->inventory = inventory_create())){
    free(newPlayer);
    return NULL;
  }

  return newPlayer;
}

/*******************************************************************************
*	Libera la memoria reservada para un jugador y pone el puntero a NULL
*******************************************************************************/
STATUS player_destroy (Player *player)
{
  if (!player)
    return ERROR;

  inventory_destroy (player->inventory);
  player->inventory = NULL;

  free(player);

  return OK;
}

/*******************************************************************************
*	Asigna un nombre a un jugador
*******************************************************************************/
STATUS player_set_name(Player* player, const char* name)
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

/*******************************************************************************
*	Asigna una posicion a un jugador
*******************************************************************************/
STATUS player_set_location(Player* player, Id location)
{
  /*Comprueba los argumentos*/
  if (!player)
    return ERROR;

  player->space_id = location;
  /*Si todo va bien devuelve OK*/
  return OK;
}

/*******************************************************************************
*	Coloca en el player especificado un objeto.
*******************************************************************************/
STATUS player_add_object(Player* player, Id id)
{
  if (!player || id == NO_ID)
  {
    return ERROR;
  }

  if((inventory_add_id (player->inventory, id))==ERROR)
    return ERROR;

  return OK;
}

/*******************************************************************************
*	Quita el objeto del inventario del player
*******************************************************************************/
STATUS player_del_object(Player* player, Id id)
{
  if (!player || id == NO_ID)
  {
    return ERROR;
  }

  /*Comprobamos si el objeto se encuentra en el inventario del jugador*/
  if(inventory_check_id(player->inventory, id) == FALSE)
    return ERROR;

  inventory_del_id(player->inventory, id);

  return OK;
}

/*******************************************************************************
*	Devuelve el nombre asignado a un jugador.
*******************************************************************************/
char * player_get_name(Player* player)
{
  if (!player)
  {
    return NULL;
  }
  return player->name;
}

/*******************************************************************************
*	Devuelve el id asignado a un jugador.
*******************************************************************************/
Id player_get_id(Player* player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->player_id;
}

/*******************************************************************************
*	Devuelve la posicion o casilla en que se encuentra un jugador.
*******************************************************************************/
Id player_get_location(Player* player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->space_id;
}

/*******************************************************************************
*	Devuelve el conjunto de identificadores del inventario del jugador
*******************************************************************************/
Id* player_get_objects(Player* player)
{
  if (!player)
  {
    return NULL;
  }

  return inventory_get_ids(player->inventory);
}

/*******************************************************************************
*	Devuelve el numero de objetos del jugador
*******************************************************************************/
int player_get_num_objects(Player* player)
{
  int i;
  Id *ids;
  if (!player)
  {
    return 0;
  }

  ids = player_get_objects(player);
  for (i=0;ids[i] != NO_ID;i++);

  return i;
}

/*******************************************************************************
*	comprueba si un objeto se encuentra en el Player introducido
*******************************************************************************/
BOOL player_check_object (Player *player, Id object_id)
{

  if (player == NULL || object_id == NO_ID)
    return FALSE;

  return inventory_check_id(player->inventory, object_id);
}

/*******************************************************************************
*	Muestra por pantalla el nombre e id del jugador, y si porta o no un objeto
*******************************************************************************/
STATUS player_print(Player* player)
{

  if (!player)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->player_id, player->name);

  if (inventory_get_num_objects(player->inventory) == 0)
  {
    fprintf(stdout, "---> The player has %d item(s).\n",inventory_get_num_objects(player->inventory));
  }
  else
  {
    fprintf(stdout, "---> The player has no item.\n");
  }

  fprintf(stdout,"Inventario del Jugador:\n");

  inventory_print(player->inventory);

  return OK;
}
