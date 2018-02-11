/**
 * @brief Define la interfaz y las llamadas
 *        para cada comando
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"


/*
Estructura que define el juego
Consta de un mapa de casillas (101 espacios),
una variable que almacena el ultimo comando introducido,
y las id de la posicion jugador y de los objetos
*/
typedef struct _Game{
  Id player_location;   /*Id = long*/
  Id object_location;
  Space* spaces[MAX_SPACES + 1];
  T_Command last_cmd;
} Game;


/*******************************************************************************
Funcion: game_create
Descripcion: Inicializa la estructura de tipo Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create(Game* game);


/*******************************************************************************
Funcion: game_create_from_file
Descripcion: Crea el game, carga las casillas del archivo y coloca player
  y object en posicion inicial (0)
Argumentos:
  game    : Puntero a una estructura de tipo Game
  filename: Archivo del que se lee la disposicion de las casillas
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_create_from_file(Game* game, char* filename);


/*******************************************************************************
Funcion: game_update
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
Descripcion: Elimina todas las casillas del Game
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS game_destroy(Game* game);


/*******************************************************************************
Funcion: game_is_over
Descripcion: Termina el juego. TODO: De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Variable de tipo BOOL (TRUE o FALSE)
  Por el momento siempre devuelve FALSE
*******************************************************************************/
BOOL game_is_over(Game* game);


/*******************************************************************************
Funcion: game_print_screen
Descripcion: TODO: De momento sin funcionalidad
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_print_screen(Game* game);


/*******************************************************************************
Funcion: game_print_data
Descripcion: Imprime informacion de cada casilla, y la posicion del jugador
  y del objeto. Posiblemente quede obsoleta en futuras iteraciones,
  ahora que hay estructuras y módulos para player y object
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void game_print_data(Game* game);


/*******************************************************************************
Funcion: game_get_space
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
Descripcion: Devuelve la posición del jugador (de la estructura game)
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para player
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_player_location(Game* game);


/*******************************************************************************
Funcion: game_get_object_location
Descripcion: Devuelve la posición del objeto (de la estructura game)
  Posiblemente quede obsoleta en futuras iteraciones, ahora que hay
  estructura y módulo para object
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Entero de tipo Id (long) que identifica una casilla
*******************************************************************************/
Id game_get_object_location(Game* game);


/*******************************************************************************
Funcion: game_get_last_command
Descripcion: Devuelve el último comando introducido
Argumentos:
  game: Puntero a una estructura de tipo Game
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command game_get_last_command(Game* game);


#endif
