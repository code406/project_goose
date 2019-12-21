/**
 * @brief Define la interfaz del modulo game_management encargado de la lectura de los ficheros
 * con la configuracion del programa.
 *
 * @file game_management.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date 08-04-2018
 * @copyright GNU Public License
 */

#ifndef __game_management_H
#define __game_management_H


#include "game.h"
#include "types.h"


/**
* @name game_management_load_spaces
* @author Arturo Morcillo
* @brief Lee el archivo y carga los datos en la estructura Space de game
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_load_spaces(Game* game, char* filename);


/**
* @name game_management_load_objects
* @author Arturo Morcillo
* @brief Lee el archivo y carga los datos en la estructura Object de game
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_load_objects(Game* game, char* filename);

/**
* @name game_management_load_links
* @author Arturo Morcillo
* @brief Lee el archivo y crea los links correspondientes
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_load_links(Game* game, char* filename);

/**
* @name game_management_load_player
* @author Arturo Morcillo
* @brief Lee el archivo y carga los datos del jugador si hay
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_load_player(Game* game, char* filename);

STATUS game_management_load_game_rules(Game* game, char* filename);


/**
* @name game_management_save
* @author Arturo Morcillo
* @brief Crea un archivo de guardado similar al data.dat
* @param game Puntero a una estructura de tipo Game
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_save(Game* game);

/**
* @name game_management_load
* @author Arturo Morcillo
* @brief carga un archivo de guardado similar al data.dat
* @param game Puntero a una estructura de tipo Game
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_management_load(Game* game);



#endif
