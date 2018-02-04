/**
 * @brief Define la interfaz y las llamadas
          para cada comando
 *
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

/*Estructura que define el juego*/
/*Consta de un mapa (101 espacios), unos comandos,
la id del jugador y la id de los objetos*/
typedef struct _Game{
  /*Id = long*/
  Id player_location;
  Id object_location;
  Space* spaces[MAX_SPACES + 1];
  T_Command last_cmd;
} Game;

/*
Funcion que devuelve un STATUS y cuyo argumento
es una variable (estructura) tipo game
se encarga de inicializar la estructura tipo game tipo game
introducida, dandole valores de 0 ó -1.
Si todo va bien devuelve un OK
*/
STATUS game_create(Game* game);
/*
Funcion que devuelve un STATUS y cuyos argumentos
son un puntero a game y un filename
Crea el game, lo inicializa, carga los espacios del filename,
y fija la id del player y object a 0.
Si todo va bien devuelve un OK
*/
STATUS game_create_from_file(Game* game, char* filename);

STATUS game_update(Game* game, T_Command cmd);
/*
Funcion que devuelve una variable tipo STATUS (ERROR ó OK)
Se encarga de eliminar todos los espacion en el Game introducido
como argumento
*/
STATUS game_destroy(Game* game);
/*
Funcion que devuelve un BOOl y cuyo argumento es un puntero a GAME.
Devuelve siempre FALSE
*/
BOOL   game_is_over(Game* game);
void   game_print_screen(Game* game);
/*
Funcion tipo void cuyo argumento es un puntero a game
imprime una linea y despues las casillas
Te imprime la informacion de cada casilla
y luego te dice la player_location y la object_location
*/
void   game_print_data(Game* game);
/*
Funcion que devuelve un puntero a Space y cuyos
argumentos son un puntero a game y un Id
Si no se introduce un id devuelve NULL
Recorre los games.spaces y si el id de alguno
coindice con el introducido te lo devuelve. Si no
encuentra nada devuelve NULL
*/
Space* game_get_space(Game* game, Id id);
/*
Funcion que devuelve un Id y cuyo argumento es un puntero a GAME
devuelve la player_location
*/
Id     game_get_player_location(Game* game);
/*
Funcion que devuelve un Id y cuyo argumento es un puntero a GAME
devuelve la object_location
*/
Id     game_get_object_location(Game* game);
/*
Funcion que devuelve un comando y cuyo argumento es un puntero a game
Devuelve la game.last_cmd
*/
T_Command game_get_last_command(Game* game);
#endif
