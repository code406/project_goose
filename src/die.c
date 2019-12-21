/**
 *  @brief Implementacion del modulo para obtener valores aleatorios en un rango establecido, como se consigue al tirar
 *        un dado.
 *
 *  @file die.c
 *  @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 *  @version v3.0
 *  @date 08-04-2018
 *  @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"
#include "types.h"

/*
* @struct _Die
* @brief Estructura que define un dado, con un id que lo identifica y un entero que
* guarda el último valor aleatorio generado al tirar el dado.
*/
struct _Die
{
  Id id; /*!<Identificador del dado*/
  int last_roll; /*!<Numero obtenido en la ultima tirada*/
};

/*******************************************************************************
 *                   IMPLEMENTACION DE LA INTERFAZ DIE
 ******************************************************************************/

/*******************************************************************************
*
*             BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR EL DADO
*
*******************************************************************************/

/*******************************************************************************
*	Reserva memoria (vacía por calloc) para un nuevo dado, e inicializa su id al
* especificado como argumento.
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
  newDie->last_roll = NO_ROLL;

  return newDie;
}

/*******************************************************************************
*	Libera la memoria reservada para un dado y pone el puntero a NULL.
*******************************************************************************/

STATUS die_destroy (Die * die)
{
  if (!die)
    return ERROR;

  free(die);

  return OK;
}

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA MODIFICAR LA ESTRUCTURA DADO
*
*******************************************************************************/

/*******************************************************************************
*	Lanza el dado para obtener un valor aleatorio de 1 a 6
*******************************************************************************/
STATUS die_roll (Die * die)
{
  if (!die)
    return ERROR;

  /* srand utiliza la fecha para el aleatorio. Sólo debemos llamarla una vez */
  srand((unsigned)time(NULL));

  /* Asigna a last_roll un aleatorio entre 1 y 6 */
  die->last_roll = rand() % 6 + 1;

  return OK;
}

/******************************************************************************
*
*     BLOQUE DE FUNCIONES PARA ACCEDER A LOS CAMPOS DE LA ESTRUCTURA DIE
*
*******************************************************************************/

/*******************************************************************************
*	Devuelve el último valor generado por el dado
*******************************************************************************/
int die_get_last_roll (Die * die)
{
  if (!die)
    return ERROR;

  /*Ultimo valor aleatorio generado por el dado */
  return die->last_roll;
}

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA DEPURAR EL TAD DIE
*
*******************************************************************************/

/*******************************************************************************
*	Imprime información sobre dado, mostrando su id y su último valor
*******************************************************************************/
STATUS die_print (Die * die)
{
  if (!die)
    return ERROR;

  /* Imprime id y último valor aleatorio generado por el dado */
  fprintf(stdout, "--> Die (Id: %ld; Last roll: %d)\n", die->id, die->last_roll);

  return OK;
}
