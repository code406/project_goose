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
Descripcion: Genera y define cada area de la interfaz de juego
Argumentos:
  Ninguno
Return:
  Puntero a la estructura de tipo Graphic_engine inicializada,
  que contiene a su vez punteros a estructura de tipo Area
*******************************************************************************/
Graphic_engine* graphic_engine_create();


/*******************************************************************************
Funcion: graphic_engine_destroy
Descripcion: Destruye (libera memoria) cada area de la interfaz de juego
Argumentos:
  ge: Puntero a una estructura de tipo Graphic_engine,
      que contiene a su vez punteros a estructura de tipo Area
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge);


/*******************************************************************************
Funcion: graphic_engine_paint_game
Descripcion: Dibuja cada area de la interfaz del juego
Argumentos:
  ge  : Puntero a una estructura de tipo Graphic_engine,
        que contiene a su vez punteros a estructura de tipo Area
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);


/*******************************************************************************
Funcion: graphic_engine_write_command
Descripcion: TODO: De momento sin funcionalidad
Argumentos:
  ge : Puntero a una estructura de tipo Graphic_engine,
       que contiene a su vez punteros a estructura de tipo Area
  str: Cadena de caracteres
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_write_command(Graphic_engine *ge, char *str);


#endif
