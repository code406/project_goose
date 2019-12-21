/**
 * * @brief   Define la interfaz publica del modulo dialogue, necesario para que el usuario
 *          pueda ver una descripcion detallada de las acciones que ejecuta en el juego.
 *
 * * @file   gialogue.h
 * * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * * @version   v1.0
 * * @date   29-04-2018
 * * @copyright   GNU Public License
 *
 */
#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "game.h"
#include "command.h"

/**
* @typedef Dialogue
* @brief Definicion de la estructura de datos  Dialogue.
*/
typedef struct _Dialogue Dialogue;

/**
* @name   dialogue_create
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Crea e inicializa los datos del dialogo. Reserva Memoria. Tambien fija los valores de la parte 3 del dialogo
* @param  puntero a char que contiene el nombre del archivo plantilla con los dialogos
* @return   Devuelve un puntero al conjunto de datos del dialogo.
*/
Dialogue* dialogue_create(char* plantilla);

/**
* @name   dialogue_destroy
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Destruye el dialogo reservando memoria.
* @param  un puntero a dialogo
* @return   Devuelve un puntero al conjunto de datos del dialogo.
*/
void dialogue_destroy(Dialogue *pd);

/**
* @name   dialogue_set_last_cmd
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija el ultimo comando que se ha utilizado dentro del juego
* @param  un puntero a dialogo
* @param  un puntero a Game
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_last_cmd (Dialogue *pd, Game *game);

/**
* @name   dialogue_set_last_cmd_status
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija el estado ultimo comando que se ha utilizado dentro del juego
* @param  un puntero a dialogo
* @param  un puntero a Game
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_last_cmd_status (Dialogue *pd, Game *game);

/**
* @name   dialogue_set_plantilla
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija otra plantilla en el caso de que se quiera cambiar
* @param  un puntero a dialogo
* @param  un puntero a file
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_plantilla (Dialogue *pd, FILE *pf);

/**
* @name   dialogue_set_part1
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija la primera parte del mensaje a mostrar
* @param  un puntero a dialogo
* @param  un puntero a char
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_part1 (Dialogue *pd, char* part1);

/**
* @name   dialogue_set_part2
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija la segunda parte del mensaje a mostrar
* @param  un puntero a dialogo
* @param  un puntero a char
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_part2 (Dialogue *pd, char* part2);

/**
* @name   dialogue_set_part3
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   Fija la ultima parte del mensaje a mostrar
* @param  un puntero a dialogo
* @param  un puntero a char
* @param  un entero que dice que comando se cambiara
* @param  un entero que dice que campo especifico del comando se cambiara
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_part3 (Dialogue *pd,char *cadena ,int n_command, int option);

/**
* @name   dialogue_get_last_cmd
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   devuelve el contenido del campo last_cmd del dialogo
* @param  un puntero a dialogo
* @return   Un T_Command.
*/
T_Command dialogue_get_last_cmd (Dialogue *pd);

/**
* @name   dialogue_get_last_cmd_status
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   devuelve el contenido del campo last_cmd_Status del dialogo
* @param  un puntero a dialogo
* @return   Una cadena de caracteres.
*/
const char* dialogue_get_last_cmd_status (Dialogue *pd);

/**
* @name   dialogue_get_part1
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   devuelve el contenido del campo part1 del dialogo
* @param  un puntero a dialogo
* @return   Una cadena de caracteres.
*/
char* dialogue_get_part1 (Dialogue *pd);

/**
* @name   dialogue_get_part1
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   devuelve el contenido del campo part1 del dialogo
* @param  un puntero a dialogo
* @return   Una cadena de caracteres.
*/
char* dialogue_get_part2 (Dialogue *pd);

/**
* @name   dialogue_get_part3
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   devuelve el contenido del campo part3 del dialogo
* @param  un puntero a dialogo
* @return   Una cadena de caracteres.
*/
char* dialogue_get_part3 (Dialogue *pd,int n_cmd, int parte);

/**
* @name   dialogue_load_parts
* @date   29-04-2018
* @author   Arturo Morcillo
* @brief   AL igual que en game_management carga las partes 1 y 2 del dialogo
* @param  un puntero a dialogo
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_load_parts (Dialogue *pd);

/**
* @name   dialogue_set_caso
* @date   29-04-2018
* @author   David Palomo
* @brief   Elige que parte 3 de dialogue se va a imprimir
* @param  un puntero a dialogo
* @param  un puntero a Game
* @return   OK o ERROR que pertenecen al enum STATUS.
*/
STATUS dialogue_set_caso (Dialogue *pd, Game *game);

/**
* @name   dialogue_get_caso
* @date   29-04-2018
* @author   David Palomo
* @brief   Devuelve que caso de la parte 3 se devolverá
* @param  un puntero a dialogo
* @return   un entero.
*/
int dialogue_get_caso (Dialogue *pd);


#endif /*DIALOGUE_H*/
