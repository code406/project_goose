/**
 * @brief Define un objeto y las funciones asociadas a objetos
 *
 * @file object.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "types.h"
#include "space.h"


/**
* @brief Estructura _Object
* Estructura que define un objeto, con un identificador (id) y un nombre
*/
struct _Object
{
  Id id;
  char name[WORD_SIZE+1];
};

/**
* @name object_create
* @author David Palomo
* @brief Reserva memoria (vacía por calloc) para un nuevo objeto,
*e inicializa su id al especificado como argumento
* @file object.c
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Object, que tiene un id y un nombre
*/

Object * object_create(Id id)
{
  Object * newObject = NULL;

  /* Asigna memoria para newObject, comprueba que se ha asignado bien y
  como usa calloc está inicializada a NULL */
  if(!(newObject = (Object*)calloc(1,sizeof(Object))))
    return NULL;

  /* Inicializa su id al especificado como argumento */
  newObject->id = id;

  return newObject;
}

/**
* @name object_destroy
* @author David Palomo
* @brief Libera la memoria reservada para un objeto y pone el puntero a NULL
* @file object.c
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS object_destroy (Object * object)
{
  if (!object)
    return ERROR;

  free(object);

  return OK;
}

/**
* @name object_set_name
* @author David Palomo
* @brief Asigna un nombre a un objeto
* @file object.c
* @param object Puntero a una estructura de tipo Object
* @param name Cadena de caracteres que se guardará en object->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS object_set_name(Object * object, char * name)
{
  /* Comprueba los argumentos */
  if (!object || !name)
  {
    return ERROR;
  }

  /* Le asigna a object.name el nombre introducido y lo comprueba  */
  if (!strcpy(object->name, name))
  {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}

/**
* @name object_get_name
* @author David Palomo
* @brief Devuelve el nombre asignado a un objeto
* @file object.c
* @param object Puntero a una estructura de tipo Object
* @return Cadena de caracteres con el nombre del objeto (object->name)
* Si el argumento introducido no es correcto, devuelve NULL
*/

char * object_get_name(Object * object)
{
  if (!object)
  {
    return NULL;
  }
  return object->name;
}

/**
* @name object_get_id
* @author David Palomo
* @brief Devuelve el id asignado a un objeto
* @file object.c
* @param object Puntero a una estructura de tipo Object
* @return Variable de tipo Id (long) que identifica al objeto (object->id)
* Si el argumento introducido no es correcto, devuelve NULL
*/

Id object_get_id(Object * object)
{
  if (!object)
  {
    return NO_ID;
  }
  return object->id;
}

/**
* @name object_print
* @author David Palomo
* @brief Muestra por pantalla el id y el nombre del objeto
* @file object.c
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/

STATUS object_print(Object * object)
{
  if (!object)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
