/** 
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
/*
TODO: Comentar que parametros tiene la estructura Area
*/
typedef struct _Graphic_engine Graphic_engine;

/*
Genera el graphic_engine
Carece de argumentos. Devuelve un puntero a estructura de punteros de tipo Area
*/
Graphic_engine* graphic_engine_create();

/*  Funcion void que destruye cada area de la pantalla  */
void graphic_engine_destroy(Graphic_engine *ge);

/* Funcion void que dibuja cada area del juego */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
