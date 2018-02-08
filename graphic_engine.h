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

typedef struct _Graphic_engine Graphic_engine;




/*******************************************************************************
Funcion: graphic_engine_create
Descripcion: Inicia el motor gráfico.
Argumentos:
  Ninguno
Return:
  Puntero a Graphic_engine, que es una estructura de punteros de tipo Area
*******************************************************************************/
Graphic_engine* graphic_engine_create();




/*******************************************************************************
Funcion: graphic_engine_destroy
Descripcion: Destruye el motor gráfico, es decir, elimina cada área del juego.
Argumentos:
  ge: Puntero a una estructura de tipo Graphic_engine
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge);




/*******************************************************************************
Funcion: graphic_engine_paint_game
Descripcion: Dibuja cada área de la interfaz del juego.
Argumentos:
  ge  : Puntero a una estructura de tipo Graphic_engine
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);




/*******************************************************************************
Funcion: graphic_engine_write_command
Descripcion:
  OJO!!!! ESTA FUNCIÓN ESTÁ SIN HACER, NO ESTÁ EN NINGÚN MÓDULO (TODO, Function not even coded)
Argumentos:
  ge : Puntero a una estructura de tipo Graphic_engine
  str: Puntero a char (cadena de caracteres)
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_write_command(Graphic_engine *ge, char *str);



#endif
