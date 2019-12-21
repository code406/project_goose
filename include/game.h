/**
 * @brief Define la interfaz publica del modulo Game, necesario para manejar el juego
 * y todos los elementos del mismo.
 *
 * @file game.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0.
 * @date 21-04-2018
 * @copyright GNU Public License
 *
 */

#ifndef GAME_H
#define GAME_H


#include "command.h"
#include "player.h"
#include "object.h"
#include "space.h"
#include "die.h"
#include "link.h"


/**
* @typedef Game
* @brief  definicion de la estructura de datos Game
*/
typedef struct _Game Game;

/******************************************************************************
*
*             BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR EL JUEGO
*
*******************************************************************************/

/**
* @name game_create
* @date   08-04-2018
* @author Javier Mateos
* @brief Inicializa la estructura de tipo Game
* @param No hay parametros
* @return Puntero tipo Game al juego creado
*/
Game* game_create();


/**
* @name game_create_from_file
* @date   08-04-2018
* @author Javier Mateos
* @brief Crea el game, carga las casillas del archivo y coloca player en la posicion inicial
* @argument filename Archivo del que se lee la informacion del juego
* @return Puntero de tipo Game al juego creado
*/
Game* game_create_from_file(char* filename);

/**
* @name game_destroy
* @date   08-04-2018
* @author Javier Mateos
* @brief Elimina todas las casillas del Game, y libera la memoria reservada
* @param game Puntero a una estructura de tipo Game
* @return OK si no se produce ningun error o ERROR si se produce algun fallo
*/
STATUS game_destroy(Game* game);

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA ACCEDER A LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/**
* @name game_get_space_id_at
* @date   08-04-2018
* @author Javier Mateos
* @brief Obtiene el id de un espacio en funcion de la posicion en el vector spaces.
* @param game: juego en el que se encuentra el espacio.
* @param position: posicion en el vector spaces de la estructura game.
* @return Devuelve el id del espacio o NO_ID si se produce algun error.
*/

Id game_get_space_id_at(Game* game, int position);

/**
* @name game_get_object
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el objeto de game que coincide con el id introducido
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long) correspondiente con el identificador del objeto
* @return Puntero a la estructura de tipo Object (objeto) Si no se introduce un id, o no encuentra una objeto que corresponda al id, devuelve NULL
*/
Object* game_get_object(Game* game, Id id);

/**
* @name game_get_space
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve la casilla de game que coincide con el id introducido
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return Puntero a la estructura de tipo Space (casilla) Si no se introduce un id, o no encuentra una casilla que corresponda al id, devuelve NULL
*/
Space* game_get_space(Game* game, Id id);

/**
* @name game_get_command
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve los datos del ultimo comando introducido
* @param game Puntero a una estructura de tipo Game
* @return Puntero a una estructura tipo D_Command(Datos del comando)
*/

D_Command* game_get_command(Game* game);

/**
* @name game_get_player
* @date   26-04-2018
* @author Arturo Morcillo
* @brief Devuelve los datos del jugador
* @param game Puntero a una estructura de tipo Game
* @return Puntero a una estructura tipo Player(Datos del jugador)
*/

Player* game_get_player(Game *game);

/**
* @name game_get_player_location
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve la posición del jugador de la estructura game.
* @param game Puntero a una estructura de tipo Game
* @return Entero de tipo Id (long) que identifica una casilla
*/
Id game_get_player_location(Game* game);

/**
* @name game_check_object_player
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto es portado por el jugador.
* @param game Puntero a una estructura de tipo Game
* @return Devuelve TRUE si lo lleva o FALSE si no lo lleva.
*/
BOOL game_check_object_player(Game* game, Object *object);

/**
* @name game_get_object_id_at
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve la id del objecto asociado a una posicion
* @param game Puntero a una estructura de tipo Game
* @param position  Entero (int)
* @return Identificador tipo Id del objeto en dicha posicion
*/

Id game_get_object_id_at(Game* game, int position);

/**
* @name game_get_object_location
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve la posición del objeto de la estructura game.
* @param game Puntero a una estructura de tipo Game
* @param id identificador del objeto
* @return Entero de tipo Id (long) que identifica una casilla
*/
Id game_get_object_location(Game* game, Id id);

/**
* @name game_get_object_description
* @date   08-04-2018
* @author Ines Martin
* @brief Devuelve la descripcion del objeto
* @param game Puntero a una estructura de tipo Game
* @return Cadena de caracteres con la descripcion del objeto. Si el argumento introducido no es correcto, devuelve NULL
*/
char* game_get_object_description(Game *game);

/**
* @name game_get_space_description
* @date   22-04-2018
* @author Ines Martin
* @brief Devuelve la descripcion del espacio
* @param game Puntero a una estructura de tipo Game
* @return Cadena de caracteres con la descripcion del espacio. Si el argumento introducido no es correcto, devuelve NULL
*/
char* game_get_space_long_description(Game *game);

/**
* @name game_get_space_long_description
* @date   22-04-2018
* @author Ines Martin
* @brief Devuelve la descripcion detallada del espacio
* @param game Puntero a una estructura de tipo Game
* @return Cadena de caracteres con la descripcion detallada del espacio. Si el argumento introducido no es correcto, devuelve NULL
*/
char* game_get_space_long_description(Game *game);

/**
* @name game_get_last_command
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el último comando introducido
* @param game Puntero a una estructura de tipo Game
* @return Valor numérico de la enumeración T_Command que identifica a cada comando
*/
T_Command game_get_last_command(Game* game);

/**
* @name game_get_status_command
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el estado del ultimo comando realizado.
* @param game juego del que se obtiene el estado del comando.
* @return Devuelve una cadena de caracteres que contiene el estado del comando o NULL si se produce algun error.
*/
const char* game_get_status_command(Game* game);

/**
* @name game_get_link
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el puntero a link del juego que tiene el identificador del argumento
* @param game Puntero a una estructura de tipo Game
* @param id identificador tipo Id del link
* @return Puntero a la estructura de tipo Link (enlace) Si no se introduce un id, o no encuentra un link que corresponda al id, devuelve NULL
*/
Link* game_get_link(Game* game, Id id);

/**
* @name game_get_space_north
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el identificador de la casilla al norte de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al norte
*/
Id game_get_space_north(Game* game, Id id);

/**
* @name game_get_space_east
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el identificador de la casilla al este de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al este
*/
Id game_get_space_east(Game* game, Id id);

/**
* @name game_get_space_south
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el identificador de la casilla al sur de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al sur
*/
Id game_get_space_south(Game* game, Id id);

/**
* @name game_get_space_west
* @date   08-04-2018
* @author Javier Mateos
* @brief Devuelve el identificador de la casilla al oeste de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al oeste
*/
Id game_get_space_west(Game* game, Id id);

/**
* @name game_get_space_up
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el identificador de la casilla de arriba de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al oeste
*/

Id game_get_space_up(Game* game, Id id);

/**
* @name game_get_space_down
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Devuelve el identificador de la casilla debajo de la posicion actual
* @param game Puntero a una estructura de tipo Game
* @param id Identificador tipo Id de la casilla actual
* @return Identificador tipo Id de la casilla al oeste
*/

Id game_get_space_down(Game* game, Id id);


/**
* @name game_get_last_roll
* @date   08-04-2018
* @author Javier Mateos
* @brief Obtiene el ultimo valor del dado del juego
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int con el ultimo valor del dado
*/
int game_get_last_roll(Game* game);

/**
* @name game_get_die
* @date   08-04-2018
* @author Javier Mateos
* @brief Obtiene el ultimo valor del dado del juego
* @param game Puntero a una estructura de tipo Game
* @return un puntero a die
*/
Die* game_get_die(Game *game);

/**
* @name game_get_game_rules_day
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Obtiene el valor game_rules_day de game
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int
*/
int game_get_game_rules_day (Game* game);

/**
* @name game_get_game_rules_next_action
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Obtiene el valor game_rules_next_action de game
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int
*/
int game_get_game_rules_next_action (Game* game);

/**
* @name game_get_game_rules_notes
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Obtiene el valor game_rules_notes de game
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int
*/
int game_get_game_rules_notes (Game* game);

/**
* @name game_get_game_rules_n_cmd
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Obtiene el valor game_rules_n_cmd de game
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int
*/
int game_get_game_rules_n_cmd (Game* game);

/**
* @name game_object_get_id_from_name
* @date   08-04-2018
* @author Arturo Morcillo
* @brief Obtiene el id de un objeto introduciendo su nombre.
* @param name Cadena de caracteres con el nombre de un objeto
* @param game Puntero a una estructura de tipo Game
* @return Identificador de tipo Id del objeto
*/
Id game_object_get_id_from_name(const char* name, Game *game);

/**
* @name game_link_get_id_from_name
* @date   24-04-2018
* @author David Palomo
* @brief Obtiene el id de un enlace dado su nombre.
* @param name Cadena de caracteres con el nombre de un enlace
* @param game Puntero a una estructura de tipo Game
* @return Identificador de tipo Id del enlace
*/
Id game_link_get_id_from_name(const char* name, Game *game);


/**
* @name game_get_showmap
* @date   06-05-2018
* @author David Palomo
* @brief Obtiene el valor showmap de game
* @param game Puntero a una estructura de tipo Game
* @return Variable tipo int
*/
int game_get_showmap (Game* game);

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA MODIFICAR LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/**
* @name game_set_player_location
* @date   08-04-2018
* @author Javier Mateos
* @brief Fija la posición del jugador en el identificador de la casilla introducida
* @param game Puntero a una estructura de tipo Game
* @param id Entero de tipo Id (long)
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_set_player_location(Game* game, Id id);

/**
* @name game_set_object_location
* @date   08-04-2018
* @author Javier Mateos
* @brief Fija la posición del objeto en una casilla.
* @param game Puntero a una estructura de tipo game
* @param id_object Identificador tipo id del objeto
* @param space_id Identificador tipo id del espacio
* @return Entero de tipo Id (long) que identifica una casilla
*/
STATUS game_set_object_location(Game* game, Id id_object, Id space_id);

/**
* @name game_set_game_rules_day
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de game_rules_day
* @param game Puntero a una estructura de tipo game
* @param day entero
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_game_rules_day (Game* game, int day);

/**
* @name game_set_game_rules_next_action
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de game_rules_next_action
* @param game Puntero a una estructura de tipo game
* @param n_a entero
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_game_rules_next_action (Game* game, int n_a);

/**
* @name game_set_game_rules_notes
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de game_rules_notes
* @param game Puntero a una estructura de tipo game
* @param notes entero
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_game_rules_notes (Game* game, int notes);

/**
* @name game_set_game_rules_n_cmd
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de game_rules_n_cmd
* @param game Puntero a una estructura de tipo game
* @param n_cmd entero
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_game_rules_n_cmd (Game* game, int n_cmd);

/**
* @name game_set_game_is_over
* @date   02-05-2018
* @author Arturo Morcillo
* @brief Fija el valor de game_rules_n_cmd
* @param game Puntero a una estructura de tipo game
* @param game_is_over BOOL define si el juego esta terminado o no
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_game_is_over (Game* game, BOOL game_is_over);

/**
* @name game_set_last_t_cmd
* @date   06-05-2018
* @author Javier Mateos
* @brief Establece el tipo de comando utilizado en el juego
* @param game Puntero a una estructura de tipo game
* @param cmd Comando tipo T_Command(enumeracion)
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_last_t_cmd(Game* game, T_Command cmd);

/**
* @name game_set_last_cmd_status
* @date   06-05-2018
* @author Javier Mateos
* @brief Establece el estado del comando utilizado en el juego
* @param game Puntero a una estructura de tipo game
* @param status cadena con el estado del comando
* @return OK o ERROR que pertenecen al enum STATUS
*/
STATUS game_set_last_cmd_status(Game* game, char* status);


/**
* @name game_destroy
* @date   08-04-2018
* @author Javier Mateos
* @brief Actualiza los datos del juego en funcion del comando recibido
* @param game Puntero a una estructura de tipo Game
* @param cmd Comando tipo T_Command(enumeracion)
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS game_update(Game* game, T_Command cmd);

/**
* @name game_add_space
* @date   08-04-2018
* @author Javier Mateos
* @brief  Añade una casilla creada previamente al juego
* @param game Puntero a una estructura de tipo Game
* @param space Puntero a una estructura de tipo Space (casilla)
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_add_space(Game* game, Space* space);

/**
* @name game_add_object
* @date   08-04-2018
* @author Javier Mateos
* @brief Añde un objeto creado previamente al juego
* @param game Puntero a una estructura de tipo Game
* @param Object Puntero a una estructura de tipo Objet (objeto)
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_add_object(Game* game, Object* object);

/**
* @name game_add_link
* @date   08-04-2018
* @author Javier Mateos
* @brief Añade un link creado previamente al juego
* @param game Puntero a una estructura de tipo Game
* @param link Puntero a una estructura de tipo Link (enlace)
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS game_add_link(Game* game, Link* link);

/**
* @name game_is_over
* @date   08-04-2018
* @author Javier Mateos
* @brief Se encarga de terminar el juego si así se requiere
* @param game Puntero a una estructura de tipo Game
* @return Variable de tipo BOOL (TRUE o FALSE) Por el momento siempre devuelve FALSE
*/
BOOL game_get_game_is_over(Game* game);

/******************************************************************************
*
*        BLOQUE DE FUNCIONES PARA DEPURAR LOS ELEMENTOS DEL JUEGO
*
*******************************************************************************/

/**
* @name game_print_screen
* @date   08-04-2018
* @author Javier Mateos
* @brief De momento sin funcionalidad
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/
void game_print_screen(Game* game);

/**
* @name game_print_data
* @date   08-04-2018
* @author David Palomo
* @brief Imprime toda la informacion del TAD Game
* @param game Puntero a una estructura de tipo Game
* @return Ninguno (void)
*/
void game_print_data(Game* game);


#endif
