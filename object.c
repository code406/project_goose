/**
 * @brief Se encarga de definir a un objeto y las
 *funciones asociadas a los objetos.
 * @file object.c
 * @author Glenson
 * @version 1.0
 * @date 10-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "types.h"
#include "space.h"

/* Estructura que define un objeto, con un identificador (id) y un nombre */
struct _Object{
  Id id;
  char name[WORD_SIZE+1];
};


/*******************************************************************************
Funcion: object_create
Descripcion: Reserva memoria (vacía por calloc) para un nuevo objeto,
  e inicializa su id al especificado como argumento
Argumentos:
  id: Entero de tipo Id (long)
Return:
  Puntero a estructura de tipo Object, que tiene un id y un nombre
*******************************************************************************/
Object * object_create(Id id){
  Object * newObject;

  /* Asigna memoria para newObject, comprueba que se ha asignado bien y
  como usa calloc está inicializada a NULL*/
  if(!(newObject = (Object*)calloc(sizeof(Object))))
    return NULL;

  /* Inicializa su id al especificado como argumento */
  newObject->id = id;

  return newObject;
}


/*******************************************************************************
Funcion: object_destroy
Descripcion: Libera la memoria reservada para un objeto y pone el puntero a NULL
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_destroy (Object * object){
  if (!object)
    return ERROR;

  free(object);
  object = NULL;

  return OK;
}


/*******************************************************************************
Funcion: object_set_name
Descripcion: Asigna un nombre a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
  name  : Cadena de caracteres que se guardará en object->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_set_name(Object * object, char * name) {
  /* Comprueba los argumentos */
  if (!object || !name) {
    return ERROR;
  }

  /* Le asigna a object.name el nombre introducido y lo comprueba  */
  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}


/*******************************************************************************
Funcion: object_get_name
Descripcion: Devuelve el nombre asignado a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  Cadena de caracteres con el nombre del objeto (object->name)
  Si el argumento introducido no es correcto, devuelve NULL
*******************************************************************************/
const char * object_get_name(Object * object) {
  if (!object)
  {
    return NULL;
  }
  return object->name;
}


/*******************************************************************************
Funcion: object_get_id
Descripcion: Devuelve el id asignado a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  Variable de tipo Id (long) que identifica al objeto (object->id)
  Si el argumento introducido no es correcto, devuelve NULL
*******************************************************************************/
Id object_get_id(Object * object) {
  if (!object)
  {
    return NO_ID;
  }
  return object->id;
}


/*******************************************************************************
Funcion: object_print
Descripcion: Muestra por pantalla el id y el nombre del objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_print(Object * object) {
  if (!object)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
