/**
 * @brief Define el motor grafico
 *
 * @file graphic_engine.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"


/*
Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
Cada parametro es un puntero a estructura de tipo Area, que contiene
posiciones y tamaños de areas de la interfaz.
*/
typedef struct _Graphic_engine Graphic_engine;


/*******************************************************************************
Funcion: graphic_engine_create
Autor: David Palomo
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
Autor: David Palomo
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
Autor: David Palomo
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
Autor: David Palomo
Descripcion: De momento sin funcionalidad
Argumentos:
ge : Puntero a una estructura de tipo Graphic_engine,
     que contiene a su vez punteros a estructura de tipo Area
str: Cadena de caracteres
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_write_command(Graphic_engine *ge, char *str);


#endif
