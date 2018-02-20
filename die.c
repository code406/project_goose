/**
 * @brief Implementa el dado
 *
 * @file die.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 20/02/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"

/* Estructura que define un dado, con un id que lo identifica y un entero que
guarda el último valor aleatorio generado al tirar el dado. */
struct _Die
{
  Id id;
  int last_roll;
};


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
Die * die_create(Id id)
{
  Die * newDie = NULL;

  /* Asigna memoria para newDie, comprueba que se ha asignado bien y
  como usa calloc está inicializada a NULL */
  if(!(newDie = (Die*)calloc(1,sizeof(Die))))
    return NULL;

  /* Inicializa su id al especificado como argumento */
  newDie->id = id;

  return newDie;
}


/*******************************************************************************
Funcion: die_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada para un dado y pone el puntero a NULL
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_destroy (Die * die)
{
  if (!die)
    return ERROR;

  free(die);
  die = NULL;

  return OK;
}


/*******************************************************************************
Funcion: die_roll
Autor: David Palomo
Descripcion: Lanza el dado para obtener un valor aleatorio de 1 a 6
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_roll (Die * die)
{
  if (!die)
    return ERROR;

  /* srand utiliza la fecha para el aleatorio. Sólo debemos llamarla una vez */
  srand((unsigned)time(NULL));

  /* Asigna a last_roll un aleatorio entre 1 y 6 */
  die->last_roll = rand() % 6 + 1

  return OK;
}


/*******************************************************************************
Funcion: die_print
Autor: David Palomo
Descripcion: Imprime información sobre dado, mostrando su id y su último valor
Argumentos:
  die: Puntero a una estructura de tipo Die
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS die_print (Die * die)
{
  if (!die)
    return ERROR;

  /* Imprime id y último valor aleatorio generado por el dado */
  fprintf(stdout, "--> Die (Id: %ld; Last roll: %d)\n", die->id, die->last_roll);

  return OK;
}
