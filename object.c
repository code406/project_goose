/**
 * @brief Define un objeto y las funciones asociadas a objetos
 *
 * @file object.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "types.h"
#include "space.h"


/*******************************************************************************
Funcion: object_create
Autor: David Palomo
Descripcion: Reserva memoria (vacía por calloc) para un nuevo objeto,
  e inicializa su id al especificado como argumento
Argumentos:
  id: Entero de tipo Id (long)
Return:
  Puntero a estructura de tipo Object, que tiene un id y un nombre
*******************************************************************************/
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


/*******************************************************************************
Funcion: object_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada para un objeto y pone el puntero a NULL
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_destroy (Object * object)
{
  if (!object)
    return ERROR;

  free(object);
  object = NULL;

  return OK;
}


/*******************************************************************************
Funcion: object_set_name
Autor: David Palomo
Descripcion: Asigna un nombre a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
  name  : Cadena de caracteres que se guardará en object->name
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
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


/*******************************************************************************
Funcion: object_get_name
Autor: David Palomo
Descripcion: Devuelve el nombre asignado a un objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  Cadena de caracteres con el nombre del objeto (object->name)
  Si el argumento introducido no es correcto, devuelve NULL
*******************************************************************************/
char * object_get_name(Object * object)
{
  if (!object)
  {
    return NULL;
  }
  return object->name;
}


/*******************************************************************************
Funcion: object_get_id
Descripcion: Devuelve el id asignado a un objeto
Autor: David Palomo
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  Variable de tipo Id (long) que identifica al objeto (object->id)
  Si el argumento introducido no es correcto, devuelve NULL
*******************************************************************************/
Id object_get_id(Object * object)
{
  if (!object)
  {
    return NO_ID;
  }
  return object->id;
}


/*******************************************************************************
Funcion: object_print
Autor: David Palomo
Descripcion: Muestra por pantalla el id y el nombre del objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_print(Object * object)
{
  if (!object)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}

/*******************************************************************************
Funcion: object_copy
Autor: Arturo Morcillo
Descripcion: Devuelve una copia del puntero introducido como argumento
Argumentos:
  po: puntero a una estructura de tipo Object
Return:
  Un puntero a la copia
*******************************************************************************/

Object *object_copy (Object *po){
  Object *aux;
  char *nombre;
  if (po == NULL)
    return NULL;

  aux = object_create(po->id);
  if(aux == NULL || aux->id != po->id)
    return NULL;

  nombre = (object_get_name(po));
  object_set_name(aux, nombre);
  if(aux->name == NULL)
    return NULL;


  return aux;
}
