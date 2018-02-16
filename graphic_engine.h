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
estructura _Graphic_engine. consta de 5 parametros tipo area que son
map, descript, banner, help y feedback y todos son punteros
*/
typedef struct _Graphic_engine Graphic_engine;

/*******************************************************************************
Funcion: graphic_engine_create
Descripcion: Se encarga de destruir y de volverle a asignar al tablero sus componentes.
Argumentos:
  Ninguno
Return:
  Devuelve un puntero a estructura de punteros de tipo Area
*******************************************************************************/

Graphic_engine* graphic_engine_create();

/*******************************************************************************
Funcion: graphic_engine_destroy
Descripcion: Se encarga de destruir cada area de la pantalla
Argumentos:
  un puntero a Graphic_engine (ge)
Return:
  nada (tipo void)
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge);

/*******************************************************************************
Funcion: graphic_engine_paint_game
Descripcion: Se encarga de dibujar cada area del juego.
Argumentos:
  un puntero a Graphic_engine (ge) y un puntero a Game (game)
Return:
  nada (tipo void)
*******************************************************************************/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
