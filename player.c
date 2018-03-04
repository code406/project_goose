/**
 * @artiimor Se encarga de definir a un jugador y las
 *funciones asociadas a los jugadores.
 * @file player.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 08-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "types.h"
#include "space.h"
#include "object.h"


/* Estructura que define un jugador, con un identificador (id) y un nombre,
un id que indica en qué casilla se encuentra, y otro que indica qué objeto porta */
struct _Player
{
  Id player_id;
  char name[WORD_SIZE+1];
  Id space_id;
  Set *objects;
};


/*******************************************************************************
Funcion: player_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un nuevo jugador,
  e inicializa su id al especificado como argumento
Argumentos:
  id: Entero de tipo Id (long)
Return:
  Puntero a estructura de tipo Player
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

  newPlayer->objects = set_create();

  return newPlayer;
}


/*******************************************************************************
Funcion: player_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria reservada para un jugador y pone el puntero a NULL
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS player_destroy (Player *player)
{
  if (!player)
    return ERROR;

  set_destroy (player->objects);
  player->objects = NULL;

  free(player);
  player = NULL;

  return OK;
}


/*******************************************************************************
Funcion: player_set_name
Autor: Arturo Morcillo
Descripcion: Asigna un nombre a un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
  name  : Cadena de caracteres que se guardará en player->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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


/*******************************************************************************
Funcion: player_set_location
Autor: Arturo Morcillo
Descripcion: Asigna una posicion a un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
  id    : Entero de tipo Id (long), con la posicion en que colocar al jugador
Return:
  OK o ERROR, que pertenecen al enum STATUS
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
Funcion: player_del_object
Autor: Arturo Morcillo
Descripcion: Quita el ultimo objeto de un jugador
Argumentos:
  space: puntero a una estructura de tipo Player (jugador)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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

/*******************************************************************************
Funcion: player_add_object
Autor: Arturo Morcillo
Descripcion: Coloca en la player especificado un objeto.
Argumentos:
  player: puntero a una estructura de tipo Player (jugador)
  value: Entero de tipo id (long) que identifica un objeto
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/

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





/*******************************************************************************
Funcion: player_get_name
Autor: Arturo Morcillo
Descripcion: Devuelve el nombre asignado a un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  Cadena de caracteres con el nombre del jugador (player->name)
  Si el argumento introducido no es correcto, devuelve NULL
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
Funcion: player_get_id
Autor: Arturo Morcillo
Descripcion: Devuelve el id asignado a un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  Entero de tipo Id (long) que identifica al jugador (player->id)
  Si el argumento introducido no es correcto, devuelve NO_ID
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
Funcion: player_get_location
Autor: Arturo Morcillo
Descripcion: Devuelve la posicion o casilla en que se encuentra un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  Entero de tipo Id (long) que identifica la casilla en que se encuentra
  el jugador (player->space_id)
  Si el argumento introducido no es correcto, devuelve NO_ID
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
Funcion: player_get_objects
Autor: Arturo Morcillo
Descripcion: Devuelve la estructura objects (tipo set) del jugador introducido
Argumentos:
  player: puntero a una estructura de tipo Player (jugador)
Return:
  Una estructura tipo Set.
  En caso de error, o de que no haya objetos, devuelve NULL.
*******************************************************************************/
Set *player_get_objects(Player* player)
{
  if (!player || player->objects == NULL)
  {
    return NULL;
  }



  return player->objects;
}


/*******************************************************************************
Funcion: player_print
Autor: Arturo Morcillo
Descripcion: Muestra por pantalla el nombre e id del jugador, y si porta o no
  un objeto
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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

/*******************************************************************************
Funcion: player_copy
Autor: Arturo Morcillo
Descripcion: Devuelve una copia del puntero introducido como argumento
Argumentos:
  pc: puntero a una estructura de tipo Player
Return:
  Un puntero a la copia
*******************************************************************************/

Player *player_copy (Player *pc){
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
