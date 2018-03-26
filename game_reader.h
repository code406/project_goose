/**
 * @brief Define la interfaz de game_reader.c
 *
 * @file game_reader.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11-03-2018
 * @copyright GNU Public License
 */

#ifndef __GAME_READER_H
#define __GAME_READER_H

#include "command.h"
#include "game.h"
#include "space.h"


/**
* @name game_reader_load_spaces
* @author Arturo Morcillo
* @brief Lee el archivo y carga los datos en la estructura Space de game
* @fie game_reader.h
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_reader_load_spaces(Game* game, char* filename);


/**
* @name game_reader_load_objects
* @author Arturo Morcillo
* @brief Lee el archivo y carga los datos en la estructura Object de game
* @fie game_reader.h
* @param game Puntero a una estructura de tipo Game
* @param filename cadena de caracteres con el nombre del archivo del que se lee
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_reader_load_objects(Game* game, char* filename);

#endif
