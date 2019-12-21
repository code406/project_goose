/**
 * @brief Define la interfaz publica del modulo player, necesario para describir
 *        la informacion relacionada con el estado del jugador.
 *
 * @file player.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"


/**
* @typedef Player
* @brief  Definicion de la estructura de datos Player
*/
typedef struct _Player Player;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL PLAYER
*
*******************************************************************************/

/**
* @name player_create
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Reserva memoria (vacía por calloc) para un nuevo jugador, e inicializa su id al especificado como argumento
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Player
*/

Player* player_create(Id id);

/**
* @name player_destroy
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Libera la memoria reservada para un jugador y pone el puntero a NULL
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_destroy (Player *player);

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA PLAYER
*
*******************************************************************************/

/**
* @name player_set_name
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Asigna un nombre a un jugador
* @param player Puntero a una estructura de tipo Player
* @param name Cadena de caracteres que se guardará en player->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_set_name(Player* player, const char* name);

/**
* @name player_set_location
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Asigna una posicion a un jugador
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_set_location(Player* player, Id location);

/**
* @name player_add_object
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Coloca en el player especificado un objeto.
* @param player Puntero a una estructura de tipo Player
* @param value Entero de tipo id (long) que identifica un objeto
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_add_object(Player* player, Id value);

/**
* @name player_del_object
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Quita el objeto del inventario del player
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_del_object(Player* player, Id id);

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA PLAYER
*
*******************************************************************************/

/**
* @name player_get_name
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el nombre asignado a un jugador.
* @param player Puntero a una estructura de tipo Player
* @return Cadena de caracteres con el nombre del jugador (player->name). Si el argumento introducido no es correcto, devuelve NULL
*/

char * player_get_name(Player* player);

/**
* @name player_get_id
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el id asignado a un jugador.
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica al jugador. Si el argumento introducido no es correcto, devuelve NO_ID
*/

Id player_get_id(Player* player);

/**
* @name player_get_location
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve la posicion o casilla en que se encuentra un jugador.
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica la casilla en que se encuentra el jugador (player->space_id). Si el argumento introducido no es correcto, devuelve NO_ID
*/

Id player_get_location(Player* player);

/**
* @name player_get_objects
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el conjunto de identificadores del inventario del jugador
* @param player Puntero a una estructura de tipo Player
* @return Un puntero a Id. En caso de error, o de que no haya objetos, devuelve NULL.
*/

Id* player_get_objects(Player* player);

/**
* @name player_get_inventory
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el numero de objetos del jugador
* @param player Puntero a una estructura de tipo Player
* @return Un entero con el numero de objetos que porta el jugador.
*/

int player_get_num_objects(Player* player);

/**
* @name player_check_object
* @date   08-04-2018
* @author Arturo Morcillo
* @brief comprueba si un objeto se encuentra en el Player introducido
* @param ps puntero a una estructura de tipo Space (casilla)
* @param object_id Entero de tipo id (long) que identifica un objeto
* @return Un BOOL: TRUE si se encuentra y FALSE si no
*/

BOOL player_check_object (Player *ps, Id object_id);

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO PLAYER
*
*******************************************************************************/

/**
* @name player_print
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Muestra por pantalla el nombre e id del jugador, y si porta o no un objeto
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS player_print(Player* player);

#endif
