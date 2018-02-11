/**
 * @artiimor Define la interfaz de player.c
 * @file player.h
 * @author Arturo Morcillo
 * @version 1.0
 * @date 08-02-2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "space.h"

typedef struct _Player Player;

/*
Funcion que devuelve un puntero a Player y cuyo argumento es un ID
Se encarga de crear un nuevo player.
*/
Player *player_create(Id id);

/*
Funcion  que devuelve un STATUS y cuyo argumento es un puntero a player
se encarga de liberar memoria para el argumento introducido y de ponerlo a NULL.
Si algo falla devuelve ERROR
*/
STATUS player_destroy (Player *player);

/*
Funcion que devuelve un STATUS y cuyo argumentos son
un puntero a Player y una cadena de caracteres.
Le asigna a player.name la cadena de caracteres introducida
como argumento
*/
STATUS player_set_name(Player* player, char* name);

/*
Funcion que devuelve un STATUS y cuyo argumentos son
un puntero a Player y una estructura tipo Space.
Le asigna a player.location la estructura introducida
como argumento
*/
STATUS player_set_location(Player* player, Space location);

/*
Funcion que devuelve un STATUS y cuyo argumentos son
un puntero a Player y una estructura tipo object.
Le asigna a player.object la estructura introducida
como argumento
*/
STATUS player_set_object(Player* player, Object object);

/*
Devuelve un puntero a char;
Su argumento es un puntero a Player
Devuelve el nombre del jugador (player.name)
Si algo falla devuelve NULL
*/
const char * player_get_name(Player* player);

/*
Devuelve un id;
Su argumento es un puntero a Player
Devuelve el id del jugador (player.id)
Si algo falla devuelve NULL
*/
Id player_get_id(player* player);

/*
Devuelve una estructura tipo Space;
Su argumento es un puntero a Player
Devuelve un puntero al espacio del jugador (player.location)
Si algo falla devuelve NULL
*/
Space *player_get_location(player* player);

/*
Devuelve una estructura tipo Object;
Su argumento es un puntero a Player
Devuelve un puntero al objeto del jugador (player.item)
Si algo falla devuelve NULL
*/
Space *player_get_item(player* player);

/*
Devuelve un Status (ERROR = 0, OK = 1);
Su argumento es un puntero a Player
Si algo falla devuelve ERROR
Muestra por pantalla:
  -El nombre y el id;
  -Si tiene objeto.

  Si se quisieran conocer las caracteristicas del objeto
  o del espacio se utilizarian otras funciones.
*/
STATUS player_print(Player* player);

#endif
