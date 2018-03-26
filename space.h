/**
 * @brief Define una casilla
 * @file space.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"


/**
* @brief estructura Space
* Estructura que define una casilla del juego
*/
typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1


/**
* @name space_create
* @author David Palomo
* @brief Reserva memoria para una estructura de tipo Space,
* que representa una casilla del juego
* @file space.c
* @param id variable de tipo Id (entero long) que identifica la casilla
* @return Puntero a una estructura de tipo Space (casilla)
*/
Space* space_create(Id id);


/**
* @name space_destroy
* @author David Palomo
* @brief Libera la memoria reservada previamente para una estructura
* de tipo Space (que representa una casilla del juego) y asigna NULL al
* puntero a Space pasado como argumento.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_destroy(Space* space);


/**
* @name space_get_id
* @author Arturo Morcillo
* @brief Obtiene el id que identifica una casilla del juego.
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @return Variable de tipo Id (entero long). En caso de error, devuelve NO_ID.
*/
Id space_get_id(Space* space);


/**
* @name space_set_name
* @author Arturo Morcillo
* @brief Asigna a la casilla especificada el nombre introducido
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @param name cadena de caracteres
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS space_set_name(Space* space, char* name);


/**
* @name space_get_name
* @author Arturo Morcillo
* @brief Devuelve el nombre asignado a la casilla especificada
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @return OK o Cadena de caracteres (nombre de la casilla) En caso de error, devuelve NULL.
*/
char* space_get_name(Space* space);


/**
* @name space_set_north
* @author David Palomo
* @brief Asigna a la casilla que se encuentra al norte de la introducida
* un id que la identifica.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_north(Space* space, Id id);


/**
* @name space_get_north
* @author David Palomo
* @brief Devuelve el id de la casilla que se encuentra al norte
* de la introducida
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida
* En caso de error, devuelve NO_ID.
*/
Id space_get_north(Space* space);


/**
* @name space_set_south
* @author David Palomo
* @brief Asigna a la casilla que se encuentra al sur de la introducida
* un id que la identifica.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_south(Space* space, Id id);


/**
* @name space_get_south
* @author David Palomo
* @brief Devuelve el id de la casilla que se encuentra al sur
* de la introducida
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida
* En caso de error, devuelve NO_ID.
*/
Id space_get_south(Space* space);


/**
* @name space_set_east
* @author David Palomo
* @brief Asigna a la casilla que se encuentra al este de la introducida
* un id que la identifica.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_east(Space* space, Id id);


/**
* @name space_get_east
* @author David Palomo
* @brief Devuelve el id de la casilla que se encuentra al este
* de la introducida
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida
* En caso de error, devuelve NO_ID.
*/
Id space_get_east(Space* space);


/**
* @name space_set_west
* @author David Palomo
* @brief Asigna a la casilla que se encuentra al oeste de la introducida
* un id que la identifica.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_west(Space* space, Id id);


/**
* @name space_get_west
* @author David Palomo
* @brief Devuelve el id de la casilla que se encuentra al oeste
* de la introducida
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida
* En caso de error, devuelve NO_ID.
*/
Id space_get_west(Space* space);


/**
* @name space_add_object
* @author Arturo Morcillo
* @brief Coloca en la casilla especificada un objeto
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @param value Entero de tipo id (long) que identifica un objeto
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS space_add_object(Space* space, Id value);


/**
* @name space_get_objects
* @author Arturo Morcillo
* @brief Devuelve la estructura objects (tipo set) del espacio introducido
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @return Una estructura tipo Set. En caso de error, o de que no haya objetos, devuelve NULL.
*/
Set* space_get_objects(Space* space);


/**
* @name space_check_object
* @author Arturo Morcillo
* @brief comprueba si un objeto se encuentra en el Space introducido
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @param object_id Entero de tipo id (long) que identifica un objeto
* @return Un BOOL: TRUE si se encuentra y FALSE si no
*/
BOOL space_check_object (Space *ps, Id object_id);


/**
* @name space_print
* @author David Palomo
* @brief Muestra por pantalla la informacion de la casilla especificada:
* su id y nombre, los id de las casillas contiguas, y qué objeto hay en ella.
* @file space.c
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida
* En caso de error, devuelve NO_ID.
*/
STATUS space_print(Space* space);


/**
* @name space_set_gdesc
* @author Arturo Morcillo
* @brief Asigna a la casilla especificada la linea n+1 del dibujo o una serie de 7 espacios.
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @param cadena cadena de caracteres
* @param n entero que cogemos(el gdesc en concreto)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_gdesc(Space* space, char* cadena, int n);


/**
* @name space_get_gdesc
* @author Arturo Morcillo
* @brief La cadena correspondiente a la linea n+1 del dibujo
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @param n entero que cogemos(el gdesc en concreto)
* @return Un puntero a char (cadena de caracteres)
*/
char* space_get_gdesc(Space* space,int n);

#endif
