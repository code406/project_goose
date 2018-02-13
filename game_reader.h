/**
 * @artiimor Define la interfaz de game_reader.c
 * @file game_reader.h
 * @author Arturo Morcillo
 * @version 1.0
 * @date 08-02-2018
 * @copyright GNU Public License
 */

 #ifndef __GAME_READER_H
 #define __GAME_READER_H

 #include "command.h"
 #include "game.h"
 #include "space.h"

 /*
 Funcion que devuelve un STATUS y cuyo argumentos son
 un puntero a GAME y un nombre de archivo.
 Se encarga de leer el archivo y cargar los datos
 en la estructura Game introducida como argumento
 */
 STATUS game_load_spaces(Game* game, char* filename);



 #endif
