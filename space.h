/**
 * @brief It defines a space
 * @file space.h
 * @author Arturo Morcillo
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
Descripcion: Su funcion es reservar memoria para una estructura tipo space.
Al Id le asigna el valor del argumento y al resto -1 ó 0
Argumentos:
  un Id (id)
Return:
  un puntero a Space
*******************************************************************************/

Space* space_create(Id id);

/*******************************************************************************
Funcion: space_destroy
Descripcion:Si la variable introducida es nula devuelve un error(0);
Si no es nula libera el espacio y a la variable introducida le asigna un NULL
Argumentos:
  un puntero a Space (space)
Return:
  un STATUS
*******************************************************************************/
STATUS space_destroy(Space* space);

/*******************************************************************************
Funcion: space_get_id
Descripcion: devolver el id del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_id(Space* space);

/*******************************************************************************
Funcion: space_set_name
Descripcion: Le asigna al Space introducido el nombre introducido
Argumentos:
  un puntero a Space (space) y un puntero a char (name)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_name(Space* space, char* name);
/*******************************************************************************
Funcion: space_get_name
Descripcion: devolver el nombre del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un puntero a char
*******************************************************************************/

const char* space_get_name(Space* space);

/*******************************************************************************
Funcion: space_set_north
Descripcion: le asigna al north del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_north(Space* space, Id id);

/*******************************************************************************
Funcion: space_get_north
Descripcion: devolver el id del north del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_north(Space* space);

/*******************************************************************************
Funcion: space_set_south
Descripcion: le asigna al south del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_south(Space* space, Id id);

/*******************************************************************************
Funcion: space_get_south
Descripcion: devolver el id del south del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_south(Space* space);

/*******************************************************************************
Funcion: space_set_east
Descripcion: le asigna al east del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_east(Space* space, Id id);

/*******************************************************************************
Funcion: space_get_east
Descripcion: devolver el id del east del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_east(Space* space);

/*******************************************************************************
Funcion: space_set_west
Descripcion: le asigna al west del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_west(Space* space, Id id);

/*******************************************************************************
Funcion: space_get_west
Descripcion: devolver el id del west del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_west(Space* space);

/*******************************************************************************
Funcion: space_set_object
Descripcion: le asigna al object del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_object(Space* space, Id value);

/*******************************************************************************
Funcion: space_get_object
Descripcion: devolver el id del object del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_object(Space* space);

/*******************************************************************************
Funcion: space_print
Descripcion: Muestra por pantalla las condiciones del espacio:
  -El nombre y el id;
  -Si hay norte, sur, este y oeste;
  -Si hay algún objeto
Argumentos:
  un puntero a Space (space)
Return:
  un STATUS
*******************************************************************************/

STATUS space_print(Space* space);

#endif
