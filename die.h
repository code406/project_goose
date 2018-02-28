/**
 * @brief Define el dado
 *
 * @file die.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 20/02/2018
 * @copyright GNU Public License
 */

 #ifndef DIE_H
 #define DIE_H

 #define NO_ROLL 0

#include "types.h"

/* Estructura que define un dado */
typedef struct _Die Die;


/*******************************************************************************
Funcion: die_create
Autor: David Palomo
Descripcion: Reserva memoria (vacía por calloc) para un nuevo dado,
  e inicializa su id al especificado como argumento
Argumentos:
  id: Entero de tipo Id (long)
Return:
  Puntero a estructura de tipo Die, que tiene un id y un nombre
*******************************************************************************/
Die * die_create(Id id);


/*******************************************************************************
Funcion: die_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada para un dado y pone el puntero a NULL
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_destroy (Die * die);


/*******************************************************************************
Funcion: die_roll
Autor: David Palomo
Descripcion: Lanza el dado para obtener un valor aleatorio de 1 a 6
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_roll (Die * die);


/*******************************************************************************
Funcion: die_print
Autor: David Palomo
Descripcion: Imprime información sobre dado, mostrando su id y su último valor
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_print (Die * die);


/*******************************************************************************
Funcion: die_get_last_roll
Autor: David Palomo
Descripcion: Devuelve el último valor generado por el dado
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  Entero (int) con el último valor generado por el dado
*******************************************************************************/
STATUS die_get_last_roll (Die * die);


#endif
