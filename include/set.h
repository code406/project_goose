/**
 * @brief Define la interfaz publica del modulo set, necesaria para contener listas
 *        de identificadores numericos no repetidos.
 *
 * @file set.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
*/
#ifndef SET_H
#define SET_H


#include <stdio.h>
#include <stdlib.h>

#include "types.h"


/**
* @typedef Player
* @brief  Definicion de la estructura de datos Player
*/
typedef struct _Set Set;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL SET
*
*******************************************************************************/

/**
* @name set_create
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Reserva memoria para una estructura de tipo set e inicializa sus parametros con NO_ID y 0
* @param
* @return Un puntero a Set
*/
Set *set_create();


/**
* @name set_destroy
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Libera la memoria de una estructura set
* @param set Un puntero a Set
* @return nada (tipo void)
*/
STATUS set_destroy (Set *set);

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA SET
*
*******************************************************************************/

/**
* @name set_add_id
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Añade una Id al array de la estructura tipo Set introducida y le suma uno a la cantidad de Ids almacenadas
* @param set Un puntero a Set
* @param Id un entero tipo long
* @return Un STATUS. Devuelve ERROR si algo falla
*/
STATUS set_add_id (Set *set, Id id);

/**
* @name set_remove_id
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Elimina del set la Id introducida
* @param set Un puntero a Set
* @param id La Id introducida
* @return Un Status. ERROR si falla algo
*/
STATUS set_remove_id (Set *set, Id id);

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA PLAYER
*
*******************************************************************************/

/**
* @name set_get_id
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el conjunto de ids del set
* @param set Un puntero a Set
* @return Un Status. ERROR si falla algo
*/
Id* set_get_ids (Set *set);

/**
* @name set_get_id_pos
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Te devuelve el id de Set en la posicion introducida
* @param set Un puntero a Set
* @param pos variable tipo int
* @return Un id o NO_ID si falla algo.
*/
Id set_get_id_pos (Set *set, int pos);

/**
* @name set_get_num
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve la cantidad de ids que hay en un set
* @param set Un puntero a Set
* @return Un entero. si falla un 0..
*/
int set_get_num(Set *set);

/**
* @name set_check_id
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Comprueba si el identificador se encuentra en el set
* @param set Un puntero a Set
* @param id La Id introducida
* @return Devuelve TRUE si se encuentra o FALSE en caso contrario.
*/
BOOL set_check_id(Set *set, Id id);

/**
* @name set_isempty
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Comprueba si un set esta vacio
* @date   08-04-2018
* @param set Un puntero a Set
* @return BOOL
*/
BOOL set_isempty(Set *ps);

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO PLAYER
*
*******************************************************************************/

/**
* @name set_print
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Muestra por pantalla todos los Ids de la estructura set introducida como argumento y la cantidad total de estos.
* @param set Un puntero a Set
* @return Un STATUS. Devuelve ERROR si algo falla
*/
STATUS set_print(Set *set);


#endif
