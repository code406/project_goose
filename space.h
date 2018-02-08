/**
 * @brief It defines a space
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H


#include "types.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1



/*******************************************************************************
Funcion: space_create
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
Descripcion: Devuelve el nombre asignado a la casilla especificada.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Cadena de caracteres (nombre de la casilla)
  En caso de error, devuelve NO_ID.
*******************************************************************************/
const char* space_get_name(Space* space);




/*******************************************************************************
Funcion: space_set_north
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
Descripcion: Coloca en la casilla especificada un objeto, o lo quita.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  value: variable de tipo BOOL  (FALSE: casilla sin objeto,
                                  TRUE: casilla con objeto)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_object(Space* space, BOOL value);




/*******************************************************************************
Funcion: space_get_object
Descripcion: Indica si en la casilla especificada hay o no un objeto
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Variable de tipo BOOL (FALSE, TRUE)
  En caso de error, devuelve FALSE.
*******************************************************************************/
BOOL space_get_object(Space* space);




/*******************************************************************************
Funcion: space_print
Descripcion: Muestra por pantalla la informacion de la casilla especificada:
  su nombre e id, los id de las casillas contiguas, y si hay algún objeto.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_print(Space* space);




#endif
