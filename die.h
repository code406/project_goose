/**
 * @brief Define el dado
 *
 * @file die.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11-03-2018
 * @copyright GNU Public License
 */

 #ifndef DIE_H
 #define DIE_H

 #define NO_ROLL 0

#include "types.h"

/*
* @brief Estructura _Die
* Estructura que define un dado
*/typedef struct _Die Die;


/**
* @name die_create
* @Autor David Palomo
* @brief Reserva memoria (vacía por calloc) para un nuevo dado,
* e inicializa su id al especificado como argumento
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Die, que tiene un id y un nombre
*/
Die * die_create(Id id);


/**
* @name die_destroy
* @Autor David Palomo
* @brief Libera la memoria reservada para un dado y pone el puntero a NULL
* e inicializa su id al especificado como argumento
* @param die Puntero a una estructura de tipo Die
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS die_destroy (Die * die);


/**
* @name die_roll
* @Autor David Palomo
* @brief Lanza el dado para obtener un valor aleatorio de 1 a 6
* @file die.h
* @param die Puntero a una estructura de tipo Die
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS die_roll (Die * die);


/**
* @name die_roll
* @Autor David Palomo
* @brief Imprime información sobre dado, mostrando su id y su último valor
* @file die.h
* @param die Puntero a una estructura de tipo Die
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS die_print (Die * die);


/**
* @name die_get_last_roll
* @Autor David Palomo
* @brief Devuelve el último valor generado por el dado
* @file die.h
* @param die Puntero a una estructura de tipo Die
* @return Entero (int) con el último valor generado por el dado
*/
STATUS die_get_last_roll (Die * die);


#endif
