/**
 * @brief Implementa la interfaz publica del modulo inventory, necesario para
 *        que el jugador pueda llevar mas de un objeto
 *
 * @file   inventory.c
 * @author   Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version   v3.1
 * @date   25-03-2018
 * @copyright   GNU Public License
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "set.h"

/**
* @struct _Inventory
* @brief Implementacion de la definicion de la estructura _Inventory
*/
struct _Inventory{
  Set *ids; /*!<Array de objetos del inventario.*/
  int num_objects; /*!<Numero maximo de objetos que el usuario puede portar.*/
};


/*******************************************************************************
 *                  IMPLEMENTACION DE LA INTERFAZ INVENTORY
 ******************************************************************************/

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL INVENTARIO
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa un inventario reservando memoria
*******************************************************************************/
Inventory* inventory_create(){

  Inventory *inv = NULL;

  inv = (Inventory*) malloc(sizeof(Inventory));
  if(inv == NULL) return NULL;

  inv->num_objects = MAX_ID;

  inv->ids=set_create();

  if (inv->ids == NULL){
    free(inv);
    inv = NULL;
    return NULL;
  }

  return inv;
}

/*******************************************************************************
*Elimina un inventario de objetos liberando la memoria asignada a dicho inventario.
*******************************************************************************/
STATUS inventory_destroy(Inventory *inv){

  if( inv == NULL ) return ERROR;

  if (inv->ids != NULL){
    set_destroy(inv->ids);
    inv->ids = NULL;
  }

  free(inv);

  return OK;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA INVENTORY
*
*******************************************************************************/

/*******************************************************************************
* Devuelve un array de ids que contiene un inventario.
*******************************************************************************/
Id* inventory_get_ids(Inventory* inv){

  if( inv == NULL ) return NULL;

  return set_get_ids(inv->ids);
}

/*******************************************************************************
* Devuelve el numero de objetos que contiene el inventario
*******************************************************************************/
int inventory_get_num_objects(Inventory* inv){

  if( inv == NULL ) return 0;

  return inv->num_objects;
}

/*******************************************************************************
* Comprueba si un objeto esta en el inventario.
*******************************************************************************/
BOOL inventory_check_id(Inventory *inv, Id id)
{
  if (inv == NULL || id == NO_ID)
    return FALSE;

  return set_check_id(inv->ids, id);
}


/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA INVENTORY
*
*******************************************************************************/

/*******************************************************************************
* Asigna el numero maximo de objetos que puede contener el inventario
*******************************************************************************/
STATUS inventory_set_num_objects(Inventory* inv, int num_objects){
  if( inv == NULL)
    return ERROR;

  inv->num_objects = num_objects;

  return OK;
}

/*******************************************************************************
* Asigna al inventario otro set de ids.
*******************************************************************************/
STATUS inventory_set_ids(Inventory* inv, Set* ids){

  if(inv == NULL || ids == NULL)
    return ERROR;

  inv->ids = ids;

  return OK;
}

/*******************************************************************************
* Elimina un objeto del inventario.
*******************************************************************************/
STATUS inventory_del_id(Inventory *inv, Id id)
{

  if (inv == NULL || id == NO_ID)
    return ERROR;

  if((set_remove_id (inv->ids, id)) == ERROR)
    return ERROR;

  return OK;
}

/*******************************************************************************
* Añade un objeto al inventario.
*******************************************************************************/
STATUS inventory_add_id (Inventory *inv, Id id)
{

  if (inv == NULL || id == NO_ID)
    return ERROR;

  /*Compruebo que no he ocupado el maximo de objetos*/
  if (set_get_num(inv->ids) == inv->num_objects)
    return ERROR;

  set_add_id(inv->ids, id);

  return OK;
}

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO INVENTORY
*
*******************************************************************************/

/*******************************************************************************
* Imprime el contenido de un inventario.
*******************************************************************************/
STATUS inventory_print(Inventory *inv){

  /*Control de que los argumentos son correctos*/
  if(inv == NULL) return ERROR;

  printf("\n\n-------------\n\n");
  if(set_get_num(inv->ids) == inv->num_objects){
    printf("=> Inventory: Lleno \n => Numero maximo de ids: %d\n", set_get_num(inv->ids));
  }
  else if(set_get_num(inv->ids) == 0){
    printf("=> Inventory: Vacio \n => Numero maximo de ids: %d\n", set_get_num(inv->ids));
  }
  else{
    printf("=> Inventory: No lleno No vacio \n => Numero maximo de ids: %d\n", set_get_num(inv->ids));
  }

  set_print(inv->ids);
  printf("\n\n-------------\n\n");

  return OK;
}
