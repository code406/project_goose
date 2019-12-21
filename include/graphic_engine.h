/**
 * @brief Define la interfaz publica del motor grafico, necesario para generar los elementos
 *        necesarios para mostrar el estado del juego.
 *
 * @file graphic_engine.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"
#include "dialogue.h"


/**
* @typedef Graphic_engine
* @brief Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
* Cada parametro es un puntero a estructura de tipo Area, que contiene
* posiciones y tamaños de areas de la interfaz.
*/
typedef struct _Graphic_engine Graphic_engine;

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR EL MOTOR GRAFICO
*
*******************************************************************************/

/**
* @name graphic_engine_create
* @date   08-04-2018
* @author David Palomo
* @brief Crea e inicializa cada area de la interfaz de juego
* @param Ninguno
* @return Puntero a la estructura de tipo Graphic_engine inicializada,
* que contiene a su vez punteros a estructura de tipo Area
*/
Graphic_engine* graphic_engine_create();


/**
* @name graphic_engine_destroy
* @date   08-04-2018
* @author David Palomo
* @brief Destruye (libera memoria) cada area de la interfaz de juego
* @param ge Puntero a una estructura de tipo Graphic_engine,
* @return Ninguno (void)
*/
void graphic_engine_destroy(Graphic_engine *ge);

/******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS PARAMETROS DEL MOTOR GRAFICO
*
*******************************************************************************/

/**
* @name graphic_engine_paint_game
* @date   08-04-2018
* @author David Palomo
* @brief Dibuja cada area de la interfaz del juego
* @param ge Puntero a una estructura de tipo Graphic_engine
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
* @name graphic_engine_write_command
* @date   08-04-2018
* @author David Palomo
* @brief De momento sin funcionalidad
* @param ge Puntero a una estructura de tipo Graphic_engine
* @param str Cadena de caracteres
* @return Ninguno (void)
*/

void graphic_engine_write_command(Graphic_engine *ge, char *str);


#endif
