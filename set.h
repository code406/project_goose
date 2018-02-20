/**
 * @brief Define set.c
 * @file set.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "player.h"
#include "space.h"

#define MAX_PLAYERS 10
#define MAX_OBJECTS 10
#define MAX_SPACES 40
/*
Estructura que almacena los jugadores
Consta de un array de punteros a Player y un entero para recorrerlo
*/
typedef struct _Players Players;
/*
Estructura que almacena los objetos
Consta de un array de punteros a Object y un entero para recorrerlo
*/
typedef struct _Objects Objects;
/*
Estructura que almacena los espacios
Consta de un array de punteros a Space y un entero para recorrerlo
*/
typedef struct _Spaces Spaces;

/*******************************************************************************
Funcion: players_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un una estructura Players,
  e inicializa sus campos a NULL
Argumentos:
  Ninguno
Return:
  Puntero a estructura de tipo Players
*******************************************************************************/
Players * players_create();

/*******************************************************************************
Funcion: players_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumenro
y la pone a NULL
Argumentos:
  p: Puntero a estructura tipo Players
Return:
  Nada (tipo void)
*******************************************************************************/
void players_destroy(Players *p);

/*******************************************************************************
Funcion: players_add
Autor: Arturo Morcillo
Descripcion: Añade un jugador a la estructura Players
Argumentos:
  p: Puntero a la estructura player
  player_ EL jugador a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS players_add(Players *p, const Player *player);

/*******************************************************************************
Funcion: players_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si la estructura introducida esta vacia
Argumentos:
  p: Puntero a players a comprobar si esta vacio
Return:
  BOOL que nos indica si esta vacia o no
*******************************************************************************/
BOOL players_isempty(const Players *p);

/*******************************************************************************
Funcion: players_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de players (devuelve el ultimo)
Argumentos:
  p: puntero a la estructura de la que se extraera el Player
Return:
  Puntero a estructura de tipo Player
*******************************************************************************/
Player * players_pop(Players *p);

/*******************************************************************************
Funcion: players_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Players introducida
Argumentos:
  p: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void players_print(const Players *p);

/*******************************************************************************
Funcion: objects_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un una estructura Objects,
  e inicializa sus campos a NULL
Argumentos:
  Ninguno
Return:
  Puntero a estructura de tipo Objects
*******************************************************************************/
Objects * objects_create();

/*******************************************************************************
Funcion: objects_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumento
y la pone a NULL
Argumentos:
  o: Puntero a estructura tipo Objects
Return:
  Nada (tipo void)
*******************************************************************************/
void objects_destroy(Objects *o);

/*******************************************************************************
Funcion: objects_add
Autor: Arturo Morcillo
Descripcion: Añade un jugador a la estructura Objects
Argumentos:
  o: Puntero a la estructura objects
  object: EL objeto a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS objects_add(Objects *o, const Object *object);

/*******************************************************************************
Funcion: objects_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si la estructura introducida esta vacia
Argumentos:
  o: Puntero a objects a comprobar si esta vacio
Return:
  BOOL que nos indica si esta vacia o no
*******************************************************************************/
BOOL objects_isempty(const Objects *o);

/*******************************************************************************
Funcion: players_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de objects (devuelve el ultimo)
Argumentos:
  o: puntero a la estructura de la que se extraera el Object
Return:
  Puntero a estructura de tipo Object
*******************************************************************************/
Object * objects_pop(Objects *o);

/*******************************************************************************
Funcion: objects_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Objectss introducida
Argumentos:
  o: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void objects_print(const Object *o);

/*******************************************************************************
Funcion: spaces_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un una estructura Spaces,
  e inicializa sus campos a NULL
Argumentos:
  Ninguno
Return:
  Puntero a estructura de tipo Spaces
*******************************************************************************/
Spaces * spaces_create();

/*******************************************************************************
Funcion: spaces_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumenro
y la pone a NULL
Argumentos:
  s: Puntero a estructura tipo Spaces
Return:
  Nada (tipo void)
*******************************************************************************/

void spaces_destroy(Spaces *s);

/*******************************************************************************
Funcion: spaces_add
Autor: Arturo Morcillo
Descripcion: Añade un espacio a la estructura Spaces
Argumentos:
  p: Puntero a la estructura space
  space: EL espacio a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS spaces_add(Spaces *s, const Space *space);

/*******************************************************************************
Funcion: players_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si la estructura introducida esta vacia
Argumentos:
  s: Puntero al Spaces a comprobar si esta vacio
Return:
  BOOL que nos indica si esta vacia o no
*******************************************************************************/

BOOL spaces_isempty(const Spaces *s);

/*******************************************************************************
Funcion: spaces_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de spaces (devuelve el ultimo)
Argumentos:
  s: puntero a la estructura de la que se extraera el Space
Return:
  Puntero a estructura de tipo Space
*******************************************************************************/
Space * spaces_pop(Spaces *s);

/*******************************************************************************
Funcion: spaces_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Spaces introducida
Argumentos:
  p: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void spaces_print(const Spaces *s);
