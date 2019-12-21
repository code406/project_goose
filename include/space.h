/**
 * @brief Define la interfaz publica del modulo space, necesaria para determinar
 *        cada una de las posibles localizaciones.
 *
 * @file space.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define MAX_SPACES 100 /*!<Maximo numero de espacios*/
#define FIRST_SPACE 1 /*!<El tablero empieza por el espacio 1*/
#define MAX_GDESC 5 /*!<Numero maximo de cadenas de descripciones ASCII del espacio*/
#define GDESC_LENGTH 90 /*!<Tamaño máximo de cada línea de la descripcion ASCII del espacio*/

/**
* @typedef Space
* @brief  Definicion de la estructura de datos Space
*/
typedef struct _Space Space;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DE SPACE
*
*******************************************************************************/

/**
* @name space_create
* @date   08-04-2018
* @author David Palomo
* @brief Crea e inicializa un espacio reservando memoria dinamica
* @param id variable de tipo Id (entero long) que identifica la casilla
* @return Puntero a una estructura de tipo Space (casilla)
*/
Space* space_create(Id id);

/**
* @name space_destroy
* @date   08-04-2018
* @author David Palomo
* @brief Libera la memoria asociada al espacio
* @param space puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_destroy(Space* space);

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA PLAYER
*
*******************************************************************************/

/**
* @name space_get_id
* @date   08-04-2018
* @author David Palomo
* @brief Obtiene el id que identifica una casilla del juego.
* @param space puntero a una estructura de tipo Space (casilla)
* @return Variable de tipo Id (entero long). En caso de error, devuelve NO_ID.
*/
Id space_get_id(Space* space);

/**
* @name space_get_name
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el nombre asignado a la casilla especificada
* @param space puntero a una estructura de tipo Space (casilla)
* @return OK o Cadena de caracteres (nombre de la casilla) En caso de error, devuelve NULL.
*/
char* space_get_name(Space* space);

/**
* @name space_get_description
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve la descripcion de la casilla especificada
* @param space puntero a una estructura de tipo Space (casilla)
* @return Cadena de caracteres (descripcion de la casilla) En caso de error, devuelve NULL.
*/
char* space_get_description(Space* space);

/**
* @name space_get_long_description
* @date   20-04-2018
* @author David Palomo
* @brief Devuelve la descripcion detallada de la casilla especificada
* @param space puntero a una estructura de tipo Space (casilla)
* @return Cadena de caracteres (descripcion detallada de la casilla) En caso de error, devuelve NULL.
*/
char* space_get_long_description(Space* space);

/**
* @name space_get_north_link
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por el norte de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al norte de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_north_link(Space* space);

/**
* @name space_get_south_link
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por el sur de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al sur de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_south_link(Space* space);

/**
* @name space_get_east_link
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por el este de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al este de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_east_link(Space* space);

/**
* @name space_get_west_link
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por el oeste de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla al oeste de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_west_link(Space* space);

/**
* @name space_get_up_link
* @date   20-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por arriba de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla por arriba de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_up_link(Space* space);

/**
* @name space_get_down_link
* @date   20-04-2018
* @author David Palomo
* @brief Devuelve el id del enlace que une la casilla con otra por abajo de la introducida
* @param space puntero a una estructura de tipo Space (casilla)
* @return Id (entero long) de la casilla por abajo de la introducida, en caso de error, devuelve NO_ID.
*/
Id space_get_down_link(Space* space);

/**
* @name space_get_lit
* @date   20-04-2018
* @author David Palomo
* @brief Devuelve si una casilla está iluminada
* @param space puntero a una estructura de tipo Space (casilla)
* @return Un BOOL: TRUE si está iluminada y FALSE si no
*/
BOOL space_get_lit(Space* space);

/**
* @name space_get_ocupada
* @date   1-05-2018
* @author Arturo Morcillo
* @brief Devuelve si una casilla está ocupada
* @param space puntero a una estructura de tipo Space (casilla)
* @return Un BOOL: TRUE si está iluminada y FALSE si no
*/
BOOL space_get_ocupada(Space* space);

/**
* @name space_get_ids_objects
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el conjunto de identificadores del espacio
* @file space.h
* @param space puntero a una estructura de tipo Space (casilla)
* @return Una estructura tipo Id. En caso de error, o de que no haya objetos, devuelve NULL.
*/
Id* space_get_ids_objects(Space* space);

/**
* @name space_get_gdesc
* @date   08-04-2018
* @author David Palomo
* @brief La cadena correspondiente a la linea n+1 del dibujo
* @param space puntero a una estructura de tipo Space (casilla)
* @param n entero que cogemos(el gdesc en concreto)
* @return Un puntero a char (cadena de caracteres)
*/
char* space_get_gdesc(Space* space, int n);

/**
* @name space_check_object
* @date   08-04-2018
* @author David Palomo
* @brief comprueba si un objeto se encuentra en el Space introducido
* @param space puntero a una estructura de tipo Space (casilla)
* @param object_id Entero de tipo id (long) que identifica un objeto
* @return Un BOOL: TRUE si se encuentra y FALSE si no
*/
BOOL space_check_object (Space *ps, Id object_id);

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA SET
*
*******************************************************************************/

/**
* @name space_set_name
* @date   08-04-2018
* @author David Palomo
* @brief Asigna a la casilla especificada el nombre introducido
* @param space puntero a una estructura de tipo Space (casilla)
* @param name cadena de caracteres
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS space_set_name(Space* space, const char* name);

/**
* @name space_set_description
* @date   08-04-2018
* @author David Palomo
* @brief Asigna a la casilla especificada la descripcion
* @param space puntero a una estructura de tipo Space (casilla)
* @param description cadena de caracteres
* @return Ninguno(void)
*/
STATUS space_set_description(Space* space, char *description);

/**
* @name space_set_long_description
* @date   20-04-2018
* @author David Palomo
* @brief Asigna a la casilla especificada la descripcion
* @param space puntero a una estructura de tipo Space (casilla)
* @param long_description cadena de caracteres
* @return Ninguno(void)
*/
STATUS space_set_long_description(Space* space, char *long_description);

/**
* @name space_set_north_link
* @date   08-04-2018
* @author David Palomo
* @brief Asigna un identificador al enlace situado al norte de la casilla.
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_north_link(Space* space, Id id);

/**
* @name space_set_south_link
* @date   08-04-2018
* @author David Palomo
* @brief  Asigna un identificador al enlace situado al sur de la casilla.
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_south_link(Space* space, Id id);

/**
* @name space_set_east_link
* @date   08-04-2018
* @author David Palomo
* @brief  Asigna un identificador al enlace situado al este de la casilla.
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_east_link(Space* space, Id id);

/**
* @name space_set_west_link
* @date   08-04-2018
* @author David Palomo
* @brief Asigna un identificador al enlace situado al oeste de la casilla.
* @brief Asigna un identificador al enlace situado al oeste de la casilla
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_west_link(Space* space, Id id);

/**
* @name space_set_up_link
* @date   20-04-2018
* @author David Palomo
* @brief Asigna un identificador al enlace situado por arriba de la casilla
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_west_link(Space* space, Id id);

/**
* @name space_set_up_link
* @date   20-04-2018
* @author David Palomo
* @brief Asigna un identificador al enlace situado por arriba de la casilla
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_up_link(Space* space, Id id);

/**
* @name space_set_down_link
* @date   20-04-2018
* @author David Palomo
* @brief Asigna un identificador al enlace situado por debajo de la casilla..
* @param space puntero a una estructura de tipo Space (casilla)
* @param id variable de tipo Id (entero long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_down_link(Space* space, Id id);

/**
* @name space_add_object
* @date   08-04-2018
* @author David Palomo
* @brief Coloca en la casilla especificada un objeto
* @param space puntero a una estructura de tipo Space (casilla)
* @param value Entero de tipo id (long) que identifica un objeto
* @return OK o ERROR que pertenecen al enum STATUS
*/

STATUS space_add_object(Space* space, Id id);

/**
* @name space_get_objects
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve la estructura objects (tipo set) del espacio introducido
* @param space puntero a una estructura de tipo Space (casilla)
* @return Una estructura tipo Set. En caso de error, o de que no haya objetos, devuelve NULL.
*/
STATUS space_del_object(Space* space, Id id);


/**
* @name space_set_gdesc
* @date   08-04-2018
* @author David Palomo
* @brief Asigna a la casilla especificada la linea n+1 del dibujo o una serie de 7 espacios.
* @param space puntero a una estructura de tipo Space (casilla)
* @param cadena cadena de caracteres
* @param n entero que cogemos(el gdesc en concreto)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_gdesc(Space* space, char* cadena, int n);

/**
* @name space_set_lit
* @date   20-04-2018
* @author David Palomo
* @brief  Asigna si la casilla especificada está iluminada
* @param space puntero a una estructura de tipo Space (casilla)
* @param lit BOOL (TRUE para iluminar la casilla o FALSE para no iluminarla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_lit(Space* space, BOOL lit);

/**
* @name space_set_ocupada
* @date   01-05-2018
* @author Arturo Morcillo
* @brief  Asigna si la casilla especificada está ocupada
* @param space puntero a una estructura de tipo Space (casilla)
* @param lit BOOL (TRUE para iluminar la casilla o FALSE para no iluminarla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_set_ocupada(Space* space, BOOL ocupada);

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO PLAYER
*
*******************************************************************************/

/**
* @name space_print
* @date   08-04-2018
* @author David Palomo
* @brief Muestra por pantalla la informacion de la casilla especificada.
* @param space puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS space_print(Space* space);

#endif
