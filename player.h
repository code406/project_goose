/**
 * @artiimor Define la interfaz de player.c
 * @file player.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 08-02-2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "space.h"


/* Estructura que define un jugador */
typedef struct _Player Player;


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
Player *player_create(Id id);


/*******************************************************************************
Funcion: player_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria reservada para un jugador y pone el puntero a NULL
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS player_destroy (Player *player);


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
STATUS player_set_name(Player* player, char* name);


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
STATUS player_set_location(Player* player, Id location);


/*******************************************************************************
Funcion: player_set_object
Autor: Arturo Morcillo
Descripcion: Asigna un objeto a un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
  id    : Entero de tipo Id (long) que identifica al objeto
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS player_set_object(Player* player, Id object);


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
const char * player_get_name(Player* player);


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
Id player_get_id(Player* player);


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
Id player_get_location(Player* player);


/*******************************************************************************
Funcion: player_get_item
Autor: Arturo Morcillo
Descripcion: Devuelve el id del objeto que porta un jugador
Argumentos:
  player: Puntero a una estructura de tipo Player
Return:
  Entero de tipo Id (long) que identifica un objeto
  Si el argumento introducido no es correcto, devuelve NO_ID
*******************************************************************************/
Id player_get_item(Player* player);


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
STATUS player_print(Player* player);

/*******************************************************************************
Funcion: player_copy
Autor: Arturo Morcillo
Descripcion: Devuelve una copia del puntero introducido como argumento
Argumentos:
  pc: puntero a una estructura de tipo Player
Return:
  Un puntero a la copia
*******************************************************************************/
Player *player_copy (Player *pc);


#endif
