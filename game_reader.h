/**
 * @brief Define la interfaz de game_reader.c
 *
 * @file game_reader.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 16-02-2018
 * @copyright GNU Public License
 */

#ifndef __GAME_READER_H
#define __GAME_READER_H

#include "command.h"
#include "game.h"
#include "space.h"


/*******************************************************************************
Funcion: game_load_spaces
Autor: Arturo Morcillo
Descripcion: Lee el archivo y carga los datos en la estructura Space de game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_load(Game* game, char* filename);


#endif
