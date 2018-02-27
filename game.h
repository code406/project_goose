/**
 * @brief Define la interfaz y las llamadas para cada comando
 *
 * @file game.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 17/02/2018
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"


/*
Estructura que define el juego
Consta de un mapa de casillas,
una variable que almacena el ultimo comando introducido,
un puntero a la estructura que define al jugador y
otro a la estructura que define un objeto.
*/
typedef struct _Game
{
  Player* player;
  Object* object[MAX_ID];
  Space* spaces[MAX_SPACES + 1];
  T_Command last_cmd;
} Game;




/*******************************************************************************
Funcion: game_create
Autor: David Palomo
Descripcion: Inicializa la estructura de tipo Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create(Game* game);


/*******************************************************************************
Funcion: game_create_from_file
Autor: David Palomo
Descripcion: Crea el game, carga las casillas del archivo y coloca player
  y object en posicion inicial
Argumentos:
  game    : Puntero a una estructura de tipo Game
  filename: Archivo del que se lee la disposicion de las casillas
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create_from_file(Game* game, char* filename);


/*******************************************************************************
Funcion: game_update
Autor: David Palomo
Descripcion: Actualiza el panel de comandos introducidos para mostrar
  el último comando introducido
Argumentos:
  game     : Puntero a una estructura de tipo Game
  T_Command: Enumeración que identifica cada comando con un número
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_update(Game* game, T_Command cmd);


/*******************************************************************************
Funcion: game_destroy
Autor: Arturo Morcillo
Descripcion: Elimina todas las casillas del Game, y libera la memoria reservada
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_destroy(Game* game);


/*******************************************************************************
Funcion: game_is_over
Autor: Arturo Morcillo
Descripcion: Termina el juego. De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Variable de tipo BOOL (TRUE o FALSE)
  Por el momento siempre devuelve FALSE
*******************************************************************************/
BOOL   game_is_over(Game* game);


/*******************************************************************************
Funcion: game_print_screen
Autor: David Palomo
Descripcion: De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_print_screen(Game* game);


/*******************************************************************************
Funcion: game_print_data
Autor: David Palomo
Descripcion: Imprime informacion de cada casilla, y la posicion del jugador
  y del objeto. Posiblemente quede obsoleta en futuras iteraciones.
  Por el momento es válida porque solo hay un jugador y un objeto.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void   game_print_data(Game* game);


/*******************************************************************************
Funcion: game_add_space
Autor: Arturo Morcillo
Descripcion: Crea una casilla. Al último elemento "vacío" (= NULL) de la
  tabla de tipo Space de game se le asigna el Space introducido como argumento.
Argumentos:
  game : Puntero a una estructura de tipo Game
  space: Puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_add_space(Game* game, Space* space);

/*******************************************************************************
Funcion: game_add_object
Autor: Arturo Morcillo
Descripcion: Crea un objeto. Al último elemento "vacío" (= NULL) de la
  tabla de tipo Object de game se le asigna el Object introducido como argumento.
Argumentos:
  game : Puntero a una estructura de tipo Game
  space: Puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_add_object(Game* game, Object* object);


/*******************************************************************************
Funcion: game_get_space
Autor: Arturo Morcillo
Descripcion: Devuelve la casilla de game que coincide con el id introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  Puntero a la estructura de tipo Space (casilla)
  Si no se introduce un id, o no encuentra una casilla que corresponda
  al id, devuelve NULL
*******************************************************************************/
Space* game_get_space(Game* game, Id id);


/*******************************************************************************
Funcion: game_get_player_location
Autor: Arturo Morcillo
Descripcion: Devuelve la posición del jugador de la estructura game.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un jugador.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_player_location(Game* game);


/*******************************************************************************
Funcion: game_set_player_location
Autor: Arturo Morcillo
Descripcion: Fija la posición del jugador en la id introducida.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un jugador.
Argumentos:
  game: Puntero a una estructura de tipo Game
  id  : Entero de tipo Id (long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_player_location(Game* game, Id id);


/*******************************************************************************
Funcion: game_set_object_location
Autor: Arturo Morcillo
Descripcion: Fija la posición del objeto en la id introducida.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un objeto.
Argumentos:
  object: Puntero a una estructura de tipo Object
  name  : Cadena de caracteres que se guardará en object->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_set_object_location(Game* game,Object *object ,Id space_id);


/*******************************************************************************
Funcion: game_get_object_location
Autor: David Palomo
Descripcion: Devuelve la posición del objeto de la estructura game.
  Posiblemente quede obsoleta en futuras iteraciones,
  es válida porque solo hay un objeto.
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_object_location(Game* game, Object *object);


/*******************************************************************************
Funcion: game_get_last_command
Autor: David Palomo
Descripcion: Devuelve el último comando introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command game_get_last_command(Game* game);


#endif
