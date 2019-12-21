/**
 *  @brief Modulo para obtener valores aleatorios en un rango establecido, como se consigue al tirar
 *        un dado.
 *
 *  @file die.h
 *  @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 *  @version v3.0
 *  @date 08-04-2018
 *  @copyright GNU Public License
 */

 #ifndef DIE_H
 #define DIE_H

 #define NO_ROLL 0 /*!< Valor con el que si inicia el campo ultima tirada del dado*/

#include "types.h"

/*
* @typedef Die
* @brief Definicion de la estructura que define un dado
*/
typedef struct _Die Die;

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR EL DADO
*
*******************************************************************************/

/**
* @name die_create
* @date   08-04-2018
* @author David Palomo
* @brief Reserva memoria (vacía por calloc) para un nuevo dado, e inicializa su id al especificado como argumento
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Die.
*/
Die * die_create(Id id);

/**
* @name die_destroy
* @date   08-04-2018
* @author David Palomo
* @brief Libera la memoria reservada para un dado y pone el puntero a NULL
* @param die Puntero a una estructura de tipo Die
* @return Devuelve OK si se libera con exito o ERROR si se produce algun fallo.
*/
STATUS die_destroy (Die * die);

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA MODIFICAR LA ESTRUCTURA DADO
*
*******************************************************************************/

/**
* @name die_roll
* @author David Palomo
* @date   08-04-2018
* @brief Lanza el dado para obtener un valor aleatorio de 1 a 6
* @param die Puntero a una estructura de tipo Die
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS die_roll (Die * die);

/******************************************************************************
*
*     BLOQUE DE FUNCIONES PARA ACCEDER A LOS CAMPOS DE LA ESTRUCTURA DIE
*
*******************************************************************************/

/**
* @name die_get_last_roll
* @author David Palomo
* @date   08-04-2018
* @brief Devuelve el último valor generado por el dado
* @file die.h
* @param die Puntero a una estructura de tipo Die
* @return Entero (int) con el último valor generado por el dado
*/
int die_get_last_roll (Die * die);

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA DEPURAR EL TAD DIE
*
*******************************************************************************/
/**
* @name die_roll
* @author David Palomo
* @date   08-04-2018
* @brief Imprime información sobre dado, mostrando su id y su último valor
* @file die.h
* @param die Puntero a una estructura de tipo Die
* @return  Devuelve OK si se libera con exito o ERROR si se produce algun fallo.
*/
STATUS die_print (Die * die);


#endif
