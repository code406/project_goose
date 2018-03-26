/**
 * @brief Define un objeto
 * @file object.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include "space.h"


/**
* @brief Estructura _Object
* Estructura que define un objeto
*/
typedef struct _Object Object;


/**
* @name object_create
* @author David Palomo
* @brief Reserva memoria (vacía por calloc) para un nuevo objeto,
*e inicializa su id al especificado como argumento
* @file object.h
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Object, que tiene un id y un nombre
*/
Object * object_create(Id id);


/**
* @name object_destroy
* @author David Palomo
* @brief Libera la memoria reservada para un objeto y pone el puntero a NULL
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_destroy (Object *object);


/**
* @name object_set_name
* @author David Palomo
* @brief Asigna un nombre a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @param name Cadena de caracteres que se guardará en object->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_set_name(Object* object, char* name);


/**
* @name object_get_name
* @author David Palomo
* @brief Devuelve el nombre asignado a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return Cadena de caracteres con el nombre del objeto (object->name)
* Si el argumento introducido no es correcto, devuelve NULL
*/
char * object_get_name(Object* object);


/**
* @name object_get_id
* @author David Palomo
* @brief Devuelve el id asignado a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return Variable de tipo Id (long) que identifica al objeto (object->id)
* Si el argumento introducido no es correcto, devuelve NULL
*/
Id object_get_id(Object* object);


/**
* @name object_print
* @author David Palomo
* @brief Muestra por pantalla el id y el nombre del objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_print(Object* object);

#endif
