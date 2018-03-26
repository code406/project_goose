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


/**
* @brief Estructura _Graphic_engine
* Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
* Cada parametro es un puntero a estructura de tipo Area, que contiene
* posiciones y tamaños de areas de la interfaz.
*/
typedef struct _Graphic_engine Graphic_engine;


/**
* @name graphic_engine_create
* @author David Palomo
* @brief Genera y define cada area de la interfaz de juego
* @file graphic_engine.h
* @param Ninguno
* @return Puntero a la estructura de tipo Graphic_engine inicializada,
* que contiene a su vez punteros a estructura de tipo Area
*/
Graphic_engine* graphic_engine_create();


/**
* @name graphic_engine_destroy
* @author David Palomo
* @brief Destruye (libera memoria) cada area de la interfaz de juego
* @file graphic_engine.h
* @param ge Puntero a una estructura de tipo Graphic_engine,
* que contiene a su vez punteros a estructura de tipo Area
* @return Ninguno (void)
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
* @name graphic_engine_paint_game
* @author David Palomo
* @brief Dibuja cada area de la interfaz del juego
* @file graphic_engine.h
* @param ge Puntero a una estructura de tipo Graphic_engine,
* que contiene a su vez punteros a estructura de tipo Area
* @param game: Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
* @name graphic_engine_write_command
* @author David Palomo
* @brief De momento sin funcionalidad
* @file graphic_engine.h
* @param ge Puntero a una estructura de tipo Graphic_engine,
* que contiene a su vez punteros a estructura de tipo Area
* @param str Cadena de caracteres
* @return Ninguno (void)
*/

void graphic_engine_write_command(Graphic_engine *ge, char *str);


#endif
