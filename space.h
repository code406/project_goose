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

/*
Funcion space_create que devuelve un puntero a Space (La estructura anterior)
y cuyo argumento es una variable tipo Id (long)

Su funcion es reservar memoria para una estructura tipo space.
Al Id le asigna el valor del argumento y al resto -1 ó 0
*/
Space* space_create(Id id);

/*
Funcion que devuelve una variable tipo status y cuyo
argumento es un puntero a Space.

Si la variable introducida es nula devuelve un error(0);
*/
STATUS space_destroy(Space* space);

/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el id del espacio (space.id)
Si algo falla devuelve NULL
*/
Id space_get_id(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un puntero a char
LE asigna al Space introducido el nombre introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_name(Space* space, char* name);
/*
Devuelve un puntero a char;
Su argumento es un puntero a Space
Devuelve el nombre del espacio (space.name)
Si algo falla devuelve NULL
*/
const char* space_get_name(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de North introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_north(Space* space, Id id);

/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del norte del espacio (space.north)
Si algo falla devuelve NULL
*/
Id space_get_north(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de South introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_south(Space* space, Id id);

/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del sur del espacio (space.south)
Si algo falla devuelve NULL
*/
Id space_get_south(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de east introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_east(Space* space, Id id);

/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del este del espacio (space.east)
Si algo falla devuelve NULL
*/
Id space_get_east(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de west introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_west(Space* space, Id id);

/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del oeste del espacio (space.west)
Si algo falla devuelve NULL
*/
Id space_get_west(Space* space);

/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un BOOL
LE asigna al Space introducido el valor de object introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_object(Space* space, BOOL value);

/*
Devuelve un BOOL (true = 1, false = 0);
Su argumento es un puntero a Space
Devuelve el valor del object del espacio (space.object)
Si algo falla devuelve NULL
*/
BOOL space_get_object(Space* space);

/*
Devuelve un Status (ERROR = 0, OK = 1);
Su argumento es un puntero a Space
Si algo falla devuelve ERROR
Muestra por pantalla las condiciones del espacio:
  -El nombre y el id;
  -Si hay norte, sur, este y oeste;
  -Si hay algún objeto
*/
STATUS space_print(Space* space);

#endif
