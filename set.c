/**
 * @brief Funciones necesarias para el manejo de conjuntos
 *
 * @file set.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>

#include "set.h"
#include "types.h"

struct _Set{
  Id id[MAX_ID];
  int cantidad;
};

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

Set *set_create(){
  Set *set;
  int n;

  set = (Set*)calloc(1,sizeof(Set));

  if (set == NULL)
    return NULL;

  /*Inicializamos todos sus campos con NO_ID*/
  for (n=0;n<MAX_ID;n++)
    set->id[n] = NO_ID;

  set->cantidad = 0;

  return set;
}

/*******************************************************************************
Funcion: set_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de una estructura set
Argumentos:
  Un puntero a Set (ps)
Return:
  nada (tipo void)
*******************************************************************************/

void set_destroy (Set *ps){
  if (ps == NULL)
    return;

  free (ps);

}

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

STATUS set_add (Set *ps, Id id){

  if (ps == NULL || id == NO_ID)
    return ERROR;

  ps->id[ps->cantidad] = id;

  ps->cantidad++;

  return OK;
}

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

Id set_del (Set *ps){
  Id id_aux;
  if (ps == NULL)
    return NO_ID;

  id_aux = ps->id[(ps->cantidad - 1)];

  ps->id[ps->cantidad] = NO_ID;

  ps->cantidad--;

  return id_aux;

}

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

STATUS set_print(Set *ps){
  int n;

  if (ps == NULL)
    return ERROR;

  for (n=0;n<MAX_ID || n<ps->cantidad;n++)
    fprintf(stdout,"Elemento %d: %ld\n",n+1,ps->id[n]);

  fprintf(stdout,"Cantidad de elementos total: %d",n);

  return OK;

  }

/*******************************************************************************
Funcion: set_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si el Set introducido no tiene ninguna id almacenada
Argumentos:
  Un puntero a Set (ps)
Return:
  Un BOOL. TRUE si esta vacia, FALSE si tiene alguna ID.
*******************************************************************************/

BOOL set_isempty(Set *ps)
{
  if (ps == NULL)
    return TRUE;
  if (ps->cantidad == 0)
    return TRUE;

  return FALSE;
}

/*******************************************************************************
Funcion: get_id_pos
Autor: Arturo Morcillo
Descripcion: Te devuelve el id de Set en la posicion introducida
Argumentos:
  Un puntero a Set (ps) y un entero (pos)
Return:
  Un id o NO_ID si falla algo
*******************************************************************************/

Id get_id_pos (Set *ps, int pos){
  Id id_aux;

  if (ps == NULL || pos < 0 || pos > ps->cantidad || set_isempty (ps) == TRUE)
    return NO_ID;

  id_aux = ps->id[pos];

  return id_aux;
}

/*******************************************************************************
Funcion: get_set_tope
Autor: Arturo Morcillo
Descripcion: Devuelve la cantidad de ids que hay en un set
Argumentos:
  Un puntero a Set (ps).
Return:
  Un entero. si falla un 0.
*******************************************************************************/

int get_set_tope(Set *ps){
  int pos;

  if (ps == NULL)
    return 0;

  pos = ps->cantidad;


  return pos;
}
