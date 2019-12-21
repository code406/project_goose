/**
 * @brief Define la interfaz publica del modulo inventory, necesario para que el jugador
 *        pueda llevar mas de un objeto.
 *
 * @file   inventory.h
 * @author   Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version   v3.0
 * @date   08-04-2018
 * @copyright   GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

/**
* @typedef Inventory
* @brief Definicion de la estructura de datos Inventory
*/
typedef struct _Inventory Inventory;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL INVENTARIO
*
*******************************************************************************/

/**
* @name   inventory_create
* @date   08-04-2018
* @author   Ines Martin
* @brief   Inicializa un inventario reservando memoria.
* @param
* @return   Puntero al inventario inicializado o NULL en caso de error.
*/
Inventory* inventory_create();

/**
* @name   inventory_destroy
* @date   08-04-2018
* @author   Ines Martin
* @brief   Elimina un inventario de objetos liberando la memoria asignada a dicho inventario.
* @param   inv  inventario a eliminar.
* @return   Devuelve OK si se elimina con exito o ERROR si se produce algun fallo.
*/
STATUS inventory_destroy(Inventory *inv);


/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA INVENTORY
*
*******************************************************************************/

/**
* @name   inventory_get_ids
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve un array de ids que contiene un inventario.
* @param   inv  inventario del que se obtienen los ids.
* @return   Devuelve un puntero a un array de ids o NULL si se produce algun error.
*/
Id* inventory_get_ids(Inventory* inv);

/**
* @name   inventory_get_num_objects
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve el numero de objetos del inventario
* @param   inv Puntero tipo inventory al inventario
* @return   Devuelve un entero con el numero maximo de objetos o 0 si se produce algun error.
*/
int inventory_get_num_objects(Inventory* inv);

/**
* @name   inventory_check_object
* @date   08-04-2018
* @author   Ines Martin
* @brief   Comprueba si un objeto esta en el inventario.
* @param  inv puntero tipo inventory al inventario
* @param id id del objeto que se eliminará
* @return  Devuelve TRUE si es cierto y FALSE si es falso.
*/
BOOL inventory_check_id(Inventory *inv, Id id);

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA INVENTORY
*
*******************************************************************************/

/**
* @name   inventory_set_num_objects
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna el numero maximo de objetos que puede contener el inventario.
* @param   inv   Puntero tipo inventory al inventario
* @param   num_objects   valor del numero maximo de objetos.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS inventory_set_num_objects(Inventory* inv, int num_objects);

/**
* @name   inventory_set_ids
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna al inventario otro set de ids.
* @param   inv  Puntero tipo inventory al inventario
* @param   ids   El nuevo set.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS inventory_set_ids(Inventory* inv, Set* ids);

/**
* @name   inventory_del_id
* @date   08-04-2018
* @author   Ines Martin
* @brief   Elimina un objeto del inventario.
* @param  inv Puntero tipo inventory al inventario
* @param id id del objeto que se eliminará
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS inventory_del_id(Inventory *inv, Id id);

/**
* @name   inventory_set_id
* @date   08-04-2018
* @author   Ines Martin
* @brief   Añade un objeto al inventario.
* @param  inv Puntero tipo inventory al inventario
* @param id id del objeto que se eliminará
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS inventory_add_id (Inventory *inv, Id id);

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO INVENTORY
*
*******************************************************************************/

/**
* @name   inventory_print
* @date   08-04-2018
* @author   Ines Martin
* @brief   Imprime el contenido de un inventario.
* @param   inv  Puntero tipo inventory al inventario
* @return   Devuelve OK si se imprime con exito o ERROR si se produce algun fallo.
*/
STATUS inventory_print(Inventory *inv);


#endif
