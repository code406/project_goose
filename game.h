/**
 * @brief Define el modulo principal del juego
 *
 * @file game.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "die.h"


/**
* @brief Estructura _Game
* Estructura que define el juego
* Consta de un mapa de casillas,
* una variable que almacena el ultimo comando introducido,
* un puntero a la estructura que define al jugador y
* un conjunto de punteros a la estructura que define un objeto.
* También incluye un dado, y un parámetro y un STATUS para comandos.
*/
typedef struct _Game
{
  Player* player;
  Object* object[MAX_ID];
  Space* spaces[MAX_SPACES + 1];
  Die* die;
  D_Command* last_cmd;/*Datos del ultimo comando realizado*/
} Game;


/**
* @name game_create
* @Autor David Palomo
* @brief Inicializa la estructura de tipo Game
* @file game.h
* @arguments game Puntero a una estructura de tipo Game
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_create(Game* game);


/**
* @name game_create_from_file
* @Autor David Palomo
* @brief Crea el game, carga las casillas del archivo y coloca player
*y object en posicion inicial
* @file die.h
* @argument game Puntero a una estructura de tipo Game
* @argument filename Archivo del que se lee la disposicion de las casillas
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_create_from_file(Game* game, char* filename);


/**
* @name game_destroy
* @author Arturo Morcillo
* @brief Elimina todas las casillas del Game, y libera la memoria reservada
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_update(Game* game, T_Command cmd);

/**
* @name game_destroy
* @author Arturo Morcillo
* @brief Elimina todas las casillas del Game, y libera la memoria reservada
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_destroy(Game* game);


/**
* @name game_is_over
* @author Arturo Morcillo
* @brief Termina el juego. De momento sin funcionalidad
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return Variable de tipo BOOL (TRUE o FALSE) Por el momento siempre devuelve FALSE
*/
BOOL game_is_over(Game* game);

/**
* @name game_print_screen
* @author David Palomo
* @brief De momento sin funcionalidad
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/

void game_print_screen(Game* game);


/**
* @name game_print_data
* @author David Palomo
* @brief Imprime informacion de cada casilla, y la posicion del jugador
* y del objeto
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/
void game_print_data(Game* game);


/**
* @name game_add_space
* @author Arturo Morcillo
* @briefCrea una casilla. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Space de game se le asigna el Space introducido como argumento.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @param space Puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_add_space(Game* game, Space* space);


/**
* @name game_add_object
* @author Arturo Morcillo
* @brief Crea un objeto. Al último elemento "vacío" (= NULL) de la
* tabla de tipo Object de game se le asigna el Object introducido como argumento.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @param space Puntero a una estructura de tipo Space (casilla)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_add_object(Game* game, Object* object);


/**
* @name game_get_space
* @author Arturo Morcillo
* @brief Devuelve la casilla de game que coincide con el id introducido
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return Puntero a la estructura de tipo Space (casilla) Si no se introduce un id, o no encuentra una casilla que corresponda al id, devuelve NULL
*/
Space* game_get_space(Game* game, Id id);

/**
@name   game_get_status_command
@date   03-03-2018
@author   Javier Mateos
@brief   Devuelve el ultimo comando realizado.
@arguments   game: juego del que se obtiene el estado del comando.
@return   Devuelve una cadena de caracteres que contiene el estado del comando.
          o NULL si se produce algun error.
*/
const char* game_get_status_command(Game* game);


/**
* @name game_get_player_location
* @author Arturo Morcillo
* @brief Devuelve la posición del jugador de la estructura game.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return Entero de tipo Id (long) que identifica una casilla
*/
Id game_get_player_location(Game* game);


/**
* @name game_set_player_location
* @author Arturo Morcillo
* @brief Fija la posición del jugador en la id introducida.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS game_set_player_location(Game* game, Id id);


/**
* @name game_set_object_location
* @author Arturo Morcillo
* @brief Fija la posición del objeto en la id introducida.
* @file game.h
* @param object Puntero a una estructura de tipo Object
* @param name Cadena de caracteres que se guardará en object->name
* @return Entero de tipo Id (long) que identifica una casilla
*/
STATUS game_set_object_location(Game* game,Object *object ,Id space_id);


/**
* @name game_get_object_location
* @author David Palomo
* @brief Devuelve la posición del objeto de la estructura game.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @param object Puntero a estructura de tipo Object
* @return Entero de tipo Id (long) que identifica una casilla
*/
Id game_get_object_location(Game* game, Object *object);


/**
* @name game_get_object_player
* @author David Palomo
* @brief Devuelve si el objeto es portado por un jugador.
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return BOOL, es decir, TRUE o FALSE
*/
BOOL game_get_object_player(Game* game, Object *object);


/**
* @name game_get_last_command
* @author David Palomo
* @brief Devuelve el último comando introducido
* @file game.h
* @param game Puntero a una estructura de tipo Game
* @return Valor numérico de la enumeración T_Command que identifica a cada comando
*/
T_Command game_get_last_command(Game* game);





#endif
