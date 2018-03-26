/**
 * @brief Funciones necesarias para el manejo de conjuntos
 *
 * @file set.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>

#include "set.h"
#include "types.h"


/**
* @brief estructura Set
* Estructura de un conjunto, con una tabla de ids y la cantidad total
*/
struct _Set
{
  Id id[MAX_ID];
  int cantidad;
};

/**
* @name set_create
* @author Arturo Morcillo
* @brief Reserva memoria para una estructura de tipo set e inicializa
* sus parametros con NO_ID y 0
* @file set.c
* @param Ninguno
* @return Un puntero a Set
*/

Set *set_create()
{
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

/**
* @name set_destroy
* @author Arturo Morcillo
* @brief Libera la memoria de una estructura set
* @file set.c
* @param ps Un puntero a Set
* @return nada (tipo void)
*/

void set_destroy (Set *ps)
{
  if (ps == NULL)
    return;

  free (ps);
}

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

STATUS set_add (Set *ps, Id id)
{
  if (ps == NULL || id == NO_ID)
    return ERROR;

  ps->id[ps->cantidad] = id;

  ps->cantidad++;

  return OK;
}

/**
* @name set_del
* @author Arturo Morcillo
* @brief Elimina una Id de la estructura Set introducida y le resta uno a
* la cantidad de Ids que hay almacenadas. Donde estaba la eliminada ahora hay NO_ID
* @file set.c
* @param ps Un puntero a Set
* @return una Id (La eliminada). Devuelve NO_ID si algo falla
*/
Id set_del (Set *ps)
{
  Id id_aux;
  if (ps == NULL)
    return NO_ID;

  id_aux = ps->id[(ps->cantidad - 1)];

  ps->id[ps->cantidad] = NO_ID;

  ps->cantidad--;

  return id_aux;
}

/**
* @name set_print
* @author Arturo Morcillo
* @brief Muestra por pantalla todos los Ids de la estructura set introducida
* como argumento y la cantidad total de estos.
* @file set.c
* @param ps Un puntero a Set
* @return Un STATUS. Devuelve ERROR si algo falla
*/

STATUS set_print(Set *ps)
{
  int n;

  if (ps == NULL)
    return ERROR;

  for (n=0;n<MAX_ID || n<ps->cantidad;n++)
    fprintf(stdout,"Elemento %d: %ld\n",n+1,ps->id[n]);

  fprintf(stdout,"Cantidad de elementos total: %d",n);

  return OK;
}

/**
* @name set_isempty
* @author Arturo Morcillo
* @brief Comprueba si el Set introducido no tiene ninguna id almacenada
* como argumento y la cantidad total de estos.
* @file set.c
* @param ps Un puntero a Set
* @return Un BOOL. TRUE si esta vacia, FALSE si tiene alguna ID.
*/

BOOL set_isempty(Set *ps)
{
  if (ps == NULL)
    return TRUE;
  if (ps->cantidad == 0)
    return TRUE;

  return FALSE;
}

/**
* @name get_id_pos
* @author Arturo Morcillo
* @brief Te devuelve el id de Set en la posicion introducida
* @file set.c
* @param ps Un puntero a Set
* @return Un id o NO_ID si falla algo.
*/

Id get_id_pos (Set *ps, int pos)
{
  Id id_aux;

  if (ps == NULL || pos < 0 || pos > ps->cantidad || set_isempty (ps) == TRUE)
    return NO_ID;

  id_aux = ps->id[pos];

  return id_aux;
}

/**
* @name get_set_tope
* @author Arturo Morcillo
* @brief Devuelve la cantidad de ids que hay en un set
* @file set.c
* @param ps Un puntero a Set
* @return Un entero. si falla un 0..
*/
int get_set_tope(Set *ps)
{
  int pos;

  if (ps == NULL)
    return 0;

  pos = ps->cantidad;

  return pos;
}

/**
* @name remove_id
* @author Arturo Morcillo
* @brief Devuelve Elimina del set la Id introducida
* @file set.c
* @param ps Un puntero a Set
* @param id La Id introducida
* @return Un Status. ERROR si falla algo
*/

STATUS remove_id (Set *ps, Id id)
{
  int i,n;
  STATUS encontrado = ERROR;
  Id id_aux;

  if (ps == NULL || id == NO_ID)
    return ERROR;

  for (i=0; i<ps->cantidad;i++)
  {
    id_aux = get_id_pos (ps, i);
    if(id == id_aux){
      for (n=i;n+1<MAX_ID && ps->id[n] != NO_ID;n++)
      {
        ps->id[n] = ps->id[n+1];
      }
      encontrado = OK;
      ps->cantidad--;
    }
  }

  return encontrado;
}
