/**
 * @brief Define un jugador
 * @file player.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "space.h"


/**
* @brief jugador
*
* Esta estructura define las caracteristicas de un jugador
* */
typedef struct _Player Player;


/**
* @name player_create
* @author Arturo Morcillo
* @brief Reserva memoria (vacía por calloc) para un nuevo jugador, e inicializa su id al especificado como argumento
* @file player
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Player
*/
Player* player_create(Id id);


/**
* @name player_destroy
* @author Arturo Morcillo
* @brief Libera la memoria reservada para un jugador y pone el puntero a NULL
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_destroy (Player *player);


/**
* @name player_set_name
* @author Arturo Morcillo
* @brief Asigna un nombre a un jugador
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @param name Cadena de caracteres que se guardará en player->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_set_name(Player* player, char* name);

/**
* @name player_set_location
* @author Arturo Morcillo
* @brief Asigna una posicion a un jugador
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_set_location(Player* player, Id location);


/**
* @name player_del_object
* @author Arturo Morcillo
* @brief Quita el ultimo objeto de un jugador
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @param id Entero de tipo Id (long), con la posicion en que colocar al jugador
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_del_object(Player* player);


/**
* @name player_add_object
* @author Arturo Morcillo
* @brief Coloca en el player especificado un objeto.
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @param value Entero de tipo id (long) que identifica un objeto
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_add_object(Player* player, Id value);

/**
* @name player_check_object
* @author Arturo Morcillo
* @brief comprueba si un objeto se encuentra en el Player introducido
* @file space.c
* @param ps puntero a una estructura de tipo Space (casilla)
* @param object_id Entero de tipo id (long) que identifica un objeto
* @return Un BOOL: TRUE si se encuentra y FALSE si no
*/

BOOL player_check_object (Player *ps, Id object_id);

/**
* @name player_get_name
* @author Arturo Morcillo
* @brief Devuelve el nombre asignado a un jugador.
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return Cadena de caracteres con el nombre del jugador (player->name). Si el argumento introducido no es correcto, devuelve NULL
*/
char * player_get_name(Player* player);


/**
* @name player_get_id
* @author Arturo Morcillo
* @brief Devuelve el id asignado a un jugador.
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica al jugador. Si el argumento introducido no es correcto, devuelve NO_ID
*/
Id player_get_id(Player* player);


/**
* @name player_get_location
* @author Arturo Morcillo
* @brief Devuelve la posicion o casilla en que se encuentra un jugador.
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return Entero de tipo Id (long) que identifica la casilla en que se encuentra el jugador (player->space_id). Si el argumento introducido no es correcto, devuelve NO_ID
*/
Id player_get_location(Player* player);


/**
* @name player_get_objects
* @author Arturo Morcillo
* @brief Devuelve la estructura objects (tipo set) del jugador introducido
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return Un puntero a estructura de tipo Set. En caso de error, o de que no haya objetos, devuelve NULL.
*/
Set* player_get_objects(Player* player);


/**
* @name player_print
* @author Arturo Morcillo
* @brief Muestra por pantalla el nombre e id del jugador, y si porta o no un objeto
* @file player.h
* @param player Puntero a una estructura de tipo Player
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS player_print(Player* player);


/**
* @name player_copy
* @author Arturo Morcillo
* @brief Devuelve una copia del puntero introducido como argumento
* @file player.h
* @param pc Puntero a una estructura de tipo Player
* @return Un puntero a la copia
*/
Player* player_copy (Player* pc);


#endif
