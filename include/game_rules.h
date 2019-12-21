/**
 * * @brief   Define la interfaz publica del modulo game_rules, necesario para que el usuario
 *          pueda ver una descripcion detallada de las acciones que ejecuta en el juego.
 *
 * * @file   game_rules.h
 * * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * * @version   v1.0
 * * @date   29-04-2018
 * * @copyright   GNU Public License
 *
 */
#ifndef GAME_RULES_H
#define GAME_RULES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "command.h"
#include "link.h"
#include "types.h"

/**
* @typedef Game_rules
* @brief Definicion de la estructura de datos  Game_rules.
*/

typedef struct _Game_rules Game_rules;

/**
* @name game_rules_create
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Crea las reglas del juego reservando memoria
* @return Devuelve el Un puntero a game_rules
*/
Game_rules* game_rules_create();

/**
* @name game_rules_destroy
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Destruye las reglas del juego liberando la memoria reservada
* @param Un puntero a game_rules
* @return nada (tipo void)
*/
void game_rules_destroy (Game_rules *pgr);

/**
* @name game_rules_set_next_action_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de next action dentro de las game_rules
* @param Un puntero a game_rules
* @param entero
* @return Ok o ERROR que pertenecen al enum STATUS
*/
STATUS game_rules_set_next_action_c (Game_rules *pgr, int n_a);

/**
* @name game_rules_set_notes_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Fija el valor del contador de notes dentro de las game_rules
* @param Un puntero a game_rules
* @param un entero
* @return Ok o ERROR que pertenecen al enum STATUS
*/
STATUS game_rules_set_notes_c (Game_rules *pgr,int notes);

/**
* @name game_rules_set_days_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Fija el valor del contador de days dentro de las game_rules
* @param Un puntero a game_rules
* @param un entero
* @return Ok o ERROR que pertenecen al enum STATUS
*/
STATUS game_rules_set_days_c (Game_rules *pgr, int days);

/**
* @name game_rules_set_n_cmd
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Fija el valor del contador del numero de comandos introducidos dentro de las game_rules
* @param Un puntero a game_rules
* @param un entero
* @return Ok o ERROR que pertenecen al enum STATUS
*/
STATUS game_rules_set_n_cmd (Game_rules *pgr, int n_cmd);

/**
* @name game_rules_get_next_action_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief devuelve el valor del contador de next_action de game_rules
* @param Un puntero a game_rules
* @return un entero
*/
int game_rules_get_next_action_c (Game_rules *pgr);

/**
* @name game_rules_get_notes_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief devuelve el valor del contador de notes de game_rules
* @param Un puntero a game_rules
* @return un entero
*/
int game_rules_get_notes_c (Game_rules *pgr);

/**
* @name game_rules_get_days_c
* @date   01-05-2018
* @author Arturo Morcillo
* @brief devuelve el valor del contador de days de game_rules
* @param Un puntero a game_rules
* @return un entero
*/
int game_rules_get_days_c (Game_rules *pgr);

/**
* @name game_rules_get_n_cmd
* @date   01-05-2018
* @author Arturo Morcillo
* @brief devuelve el valor del contador del numero de comandos introducidos de game_rules
* @param Un puntero a game_rules
* @return un entero
*/
int game_rules_get_n_cmd (Game_rules *pgr);

/**
* @name game_rules_update
* @date   01-05-2018
* @author Arturo Morcillo
* @brief Funcion que se encarga de que el estado del juego avance cuando sucedan determinados eventos
* @param Un puntero a game_rules
* @param Un puntero a game
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_rules_update (Game *game,Game_rules *pgr);



#endif

