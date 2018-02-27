/**
 * @brief Define object.c
 * @file object.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include "space.h"


/* Estructura que define un objeto */
typedef struct _Object{
  Id id;
  char name[WORD_SIZE+1];
} Object;


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
Object * object_create(Id id);


/*******************************************************************************
Funcion: object_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada para un objeto y pone el puntero a NULL
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_destroy (Object *object);


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
STATUS object_set_name(Object* object, char* name);


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
char * object_get_name(Object* object);


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
Id object_get_id(Object* object);


/*******************************************************************************
Funcion: object_print
Autor: David Palomo
Descripcion: Muestra por pantalla el id y el nombre del objeto
Argumentos:
  object: Puntero a una estructura de tipo Object
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS object_print(Object* object);

#endif
