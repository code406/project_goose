/**
 * @brief Funciones necesarias para el manejo de conjuntos
 *
 * @file set.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>

#include "set.h"
#include "types.h"


/**
* @struct _Set
* @brief Implementacion de la definicion de la estructura Set
*/
struct _Set
{
  Id id[MAX_ID]; /*!<Array de identificadores del conjunto*/
  int num; /*!Numero de identificadores en el conjunto*/
};

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL SET
*
*******************************************************************************/

/*******************************************************************************
*	Reserva memoria para una estructura de tipo set e inicializa sus parametros con
* NO_ID y 0
*******************************************************************************/
Set *set_create()
{
  Set *set;
  int i;

  set = (Set*)calloc(1,sizeof(Set));

  if (set == NULL)
    return NULL;

  /*Inicializamos todos sus campos con NO_ID*/
  for (i = 0; i < MAX_ID; i++)
    set->id[i] = NO_ID;

  set->num = 0;

  return set;
}

/*******************************************************************************
*	 Libera la memoria de una estructura set
*******************************************************************************/
STATUS set_destroy (Set *set)
{
  if (set == NULL)
    return ERROR;

  free (set);

  return OK;
}

/*******************************************************************************
*	 Añade una Id al array de la estructura tipo Set introducida y le suma uno a
*  la cantidad de Ids almacenadas
*******************************************************************************/
STATUS set_add_id (Set *set, Id id)
{
  if (set == NULL || id == NO_ID)
    return ERROR;

  set->id[set->num] = id;

  set->num++;

  return OK;
}

/*******************************************************************************
*	 Elimina del set la Id introducida
*******************************************************************************/
STATUS set_remove_id (Set *set, Id id)
{
  int i,n;
  STATUS encontrado = ERROR;

  if (set == NULL || id == NO_ID)
    return ERROR;

  for (i=0; i<set->num;i++)
  {
    if(id == set->id[i]){
      for (n=i;n+1<MAX_ID && set->id[n] != NO_ID;n++)
      {
        set->id[n] = set->id[n+1];
      }
      encontrado = OK;
      set->num--;
    }
  }

  return encontrado;
}

/*******************************************************************************
*	 Devuelve el conjunto de ids del set
*******************************************************************************/
Id* set_get_ids (Set *set)
{
  if (set == NULL)
    return NULL;

  return set->id;
}

/*******************************************************************************
*	 Te devuelve el id de Set en la posicion introducida
*******************************************************************************/
Id set_get_id_pos (Set *set, int pos)
{
  Id id_aux;

  if (set == NULL || pos > 0 || pos < MAX_ID)
    return NO_ID;

  id_aux = set->id[pos];

  return id_aux;
}

/*******************************************************************************
*	 Devuelve la cantidad de ids que hay en un set
*******************************************************************************/
int set_get_num(Set *set)
{
  int num;

  if (set == NULL)
    return 0;

  num = set->num;

  return num;
}

/*******************************************************************************
*	 Comprueba si el identificador se encuentra en el set
*******************************************************************************/
BOOL set_check_id(Set *set, Id id){

  int i;

  /*Buscamos dentro del array de ids*/
  for(i = 0; i < set->num; i++)
  {
    if(id == set->id[i])
    {
      return TRUE;
    }
  }

  return FALSE;
}

/*******************************************************************************
*	 Comprueba si un set esta vacio
*******************************************************************************/
BOOL set_isempty(Set *ps){
  if (ps == NULL)
    return TRUE;

  if (ps->id[0] == NO_ID)
    return TRUE;
  return FALSE;
}

/*******************************************************************************
*	 Muestra por pantalla todos los Ids de la estructura set introducida como
*  argumento y la cantidad total de estos.
*******************************************************************************/
STATUS set_print(Set *set)
{
  int n;

  if (set == NULL)
    return ERROR;

  printf("\n\n-------------\n\n");
  if(set_get_num(set) == MAX_ID){
    printf("=> Conjunto: Lleno \n");
  }
  else if(set_get_num(set) == 0){
    printf("=> Conjunto: Vacio \n");
  }
  else{
    printf("=> Conjunto: No lleno No vacio \n");
  }

  for (n = 0; n < MAX_ID || n < set->num ; n++)
    fprintf(stdout,"Id %d: %ld\n",n+1,set->id[n]);

  fprintf(stdout,"Numero de elementos en el conjunto: %d\n", set_get_num(set));

  printf("\n");

  return OK;
}
