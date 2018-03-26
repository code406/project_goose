/**
 * @brief Define set.h
 * @file set.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
*/
#ifndef SET_H
#define SET_H


#include <stdio.h>
#include <stdlib.h>
#include "types.h"


/**
* @brief estructura Set
* Estructura de un conjunto, con una tabla de ids y la cantidad total
*/
typedef struct _Set Set;


/**
* @name set_create
* @author Arturo Morcillo
* @brief Reserva memoria para una estructura de tipo set e inicializa
* sus parametros con NO_ID y 0
* @file set.c
* @param Ninguno
* @return Un puntero a Set
*/
Set *set_create();


/**
* @name set_destroy
* @author Arturo Morcillo
* @brief Libera la memoria de una estructura set
* @file set.c
* @param ps Un puntero a Set
* @return nada (tipo void)
*/
void set_destroy (Set *ps);

/**
* @name set_add
* @author Arturo Morcillo
* @brief Añade una Id al array de la estructura tipo Set introducida y
* le suma uno a la cantidad de Ids almacenadas
* @file set.c
* @param ps Un puntero a Set
* @param Id un entero tipo long
* @return Un STATUS. Devuelve ERROR si algo falla
*/
STATUS set_add (Set *ps, Id id);


/**
* @name set_del
* @author Arturo Morcillo
* @brief Elimina una Id de la estructura Set introducida y le resta uno a
* la cantidad de Ids que hay almacenadas. Donde estaba la eliminada ahora hay NO_ID
* @file set.c
* @param ps Un puntero a Set
* @return una Id (La eliminada). Devuelve NO_ID si algo falla
*/
Id set_del (Set *ps);


/**
* @name set_isempty
* @author Arturo Morcillo
* @brief Comprueba si el Set introducido no tiene ninguna id almacenada
* como argumento y la cantidad total de estos.
* @file set.c
* @param ps Un puntero a Set
* @return Un BOOL. TRUE si esta vacia, FALSE si tiene alguna ID.
*/
BOOL set_isempty(Set *ps);


/**
* @name set_print
* @author Arturo Morcillo
* @brief Muestra por pantalla todos los Ids de la estructura set introducida
* como argumento y la cantidad total de estos.
* @file set.c
* @param ps Un puntero a Set
* @return Un STATUS. Devuelve ERROR si algo falla
*/
STATUS set_print(Set *ps);


/**
* @name get_id_pos
* @author Arturo Morcillo
* @brief Te devuelve el id de Set en la posicion introducida
* @file set.c
* @param ps Un puntero a Set
* @return Un id o NO_ID si falla algo.
*/
Id get_id_pos (Set *ps, int pos);


/**
* @name get_set_tope
* @author Arturo Morcillo
* @brief Devuelve la cantidad de ids que hay en un set
* @file set.c
* @param ps Un puntero a Set
* @return Un entero. si falla un 0..
*/
int get_set_tope(Set *ps);


/**
* @name remove_id
* @author Arturo Morcillo
* @brief Devuelve Elimina del set la Id introducida
* @file set.c
* @param ps Un puntero a Set
* @param id La Id introducida
* @return Un Status. ERROR si falla algo
*/
STATUS remove_id (Set *ps, Id id);


#endif
