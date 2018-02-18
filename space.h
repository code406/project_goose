/**
 * @brief Define una casilla
 * @file space.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 18/02/2018
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"

/* Estructura que define una casilla del juego */
typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1


/*******************************************************************************
Funcion: space_create
Autor: David Palomo
Descripcion: Reserva memoria para una estructura de tipo Space,
  que representa una casilla del juego.
Argumentos:
  id: variable de tipo Id (entero long) que identifica la casilla
Return:
  Puntero a una estructura de tipo Space (casilla)
*******************************************************************************/
Space* space_create(Id id);


/*******************************************************************************
Funcion: space_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada previamente para una estructura
  de tipo Space (que representa una casilla del juego) y asigna NULL al
  puntero a Space pasado como argumento.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_destroy(Space* space);


/*******************************************************************************
Funcion: space_get_id
Autor: Arturo Morcillo
Descripcion: Obtiene el id que identifica una casilla del juego.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Variable de tipo Id (entero long).
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_id(Space* space);


/*******************************************************************************
Funcion: space_set_name
Autor: Arturo Morcillo
Descripcion: Asigna a la casilla especificada el nombre introducido.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  name : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_name(Space* space, char* name);


/*******************************************************************************
Funcion: space_get_name
Autor: Arturo Morcillo
Descripcion: Devuelve el nombre asignado a la casilla especificada.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Cadena de caracteres (nombre de la casilla)
  En caso de error, devuelve NULL.
*******************************************************************************/
const char* space_get_name(Space* space);


/*******************************************************************************
Funcion: space_set_north
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al norte de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_north(Space* space, Id id);


/*******************************************************************************
Funcion: space_get_north
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al norte
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al norte de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_north(Space* space);


/*******************************************************************************
Funcion: space_set_south
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al sur de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_south(Space* space, Id id);


/*******************************************************************************
Funcion: space_get_south
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al sur
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al sur de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_south(Space* space);


/*******************************************************************************
Funcion: space_set_east
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al este de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_east(Space* space, Id id);


/*******************************************************************************
Funcion: space_get_east
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al este
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al este de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_east(Space* space);


/*******************************************************************************
Funcion: space_set_west
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al oeste de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_west(Space* space, Id id);


/*******************************************************************************
Funcion: space_get_west
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al oeste
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al oeste de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_west(Space* space);


/*******************************************************************************
Funcion: space_set_object
Autor: Arturo Morcillo
Descripcion: Coloca en la casilla especificada un objeto, o lo quita.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  value: Entero de tipo id (long) que identifica un objeto
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_object(Space* space, Id value);


/*******************************************************************************
Funcion: space_get_object
Autor: Arturo Morcillo
Descripcion: Indica el id del objeto que hay en la casilla especificada
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Entero de tipo Id (long) que identifica un objeto.
  En caso de error, o de que no haya un objeto, devuelve NO_ID.
*******************************************************************************/
Id space_get_object(Space* space);


/*******************************************************************************
Funcion: space_print
Autor: David Palomo
Descripcion: Muestra por pantalla la informacion de la casilla especificada:
  su id y nombre, los id de las casillas contiguas, y qué objeto hay en ella.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_print(Space* space);


#endif
