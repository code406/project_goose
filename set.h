/**
 * @brief Define set.c
 * @file set.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
*/
#ifndef SET_H
#define SET_H


#include <stdio.h>
#include <stdlib.h>
#include "types.h"



typedef struct _Set Set;

/*******************************************************************************
Funcion: set_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria para una estructura de tipo set e inicializa
sus parametros con NO_ID y 0-
Argumentos:
  Ninguno
Return:
  Un puntero a Set
*******************************************************************************/

Set *set_create();

/*******************************************************************************
Funcion: set_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de una estructura set
Argumentos:
  Un puntero a Set (ps)
Return:
  nada (tipo void)
*******************************************************************************/

void set_destroy (Set *ps);

/*******************************************************************************
Funcion: set_add
Autor: Arturo Morcillo
Descripcion: Añade una Id al array de la estructura tipo Set introducida y
le suma uno a la cantidad de Ids almacenadas
Argumentos:
  Un puntero a Set (ps) y una id
Return:
  Un STATUS. Devuelve ERROR si ago falla
*******************************************************************************/

STATUS set_add (Set *ps, Id id);

/*******************************************************************************
Funcion: set_del
Autor: Arturo Morcillo
Descripcion: Elimina una Id de la estructura Set introducida y le resta uno a
la cantidad de Ids que hay almacenadas. Donde estaba la eliminada ahora hay NO_ID
Argumentos:
  Un puntero a Set (ps)
Return:
  una Id (La eliminada). Devuelve NO_ID si algo falla
*******************************************************************************/

Id set_del (Set *ps);

/*******************************************************************************
Funcion: set_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si el Set introducido no tiene ninguna id almacenada
Argumentos:
  Un puntero a Set (ps)
Return:
  Un BOOL. TRUE si esta vacia, FALSE si tiene alguna ID.
*******************************************************************************/

BOOL set_isempty(Set *ps);

/*******************************************************************************
Funcion: set_print
Autor: Arturo Morcillo
Descripcion: Muestra por pantalla todos los Ids de la estructura set introducida
como argumento y la cantidad total de estos.
Argumentos:
  Un puntero a Set (ps)
Return:
  Un STATUS. Devuelve ERROR si ago falla
*******************************************************************************/

STATUS set_print(Set *ps);

/*******************************************************************************
Funcion: get_id_pos
Autor: Arturo Morcillo
Descripcion: Te devuelve el id de Set en la posicion introducida
Argumentos:
  Un puntero a Set (ps) y un entero (pos)
Return:
  Un id o NO_ID si falla algo
*******************************************************************************/

Id get_id_pos (Set *ps, int pos);

/*******************************************************************************
Funcion: get_set_tope
Autor: Arturo Morcillo
Descripcion: Devuelve la cantidad de ids que hay en un set
Argumentos:
  Un puntero a Set (ps).
Return:
  Un entero. si falla un 0.
*******************************************************************************/

int get_set_tope(Set *ps);

/*******************************************************************************
Funcion: remove_id
Autor: Arturo Morcillo
Descripcion: Elimina del set la Id introducida
Argumentos:
  Un puntero a Set (ps) y una id.
Return:
  Un Status
*******************************************************************************/

STATUS remove_id (Set *ps, Id id);


#endif
