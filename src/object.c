/**
 * @brief Implementa la interfaz publica del modulo object, necesario para determinar las
 *        caracteristicas de un objeto.
 *
 * @file object.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0.E
 * @date   22-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "types.h"


/**
* @struct _Object
* @brief  Implementacion de la definicion de la estructura Object
*/
struct _Object
{
  Id id; /*!<Identificador del objeto*/
  char name[WORD_SIZE+1]; /*!<Nombre del objeto*/
  char description[WORD_SIZE+1]; /*!<Descripcion del objeto cuando está en su ubicación original*/
  char long_description[WORD_SIZE+1]; /*!<Descripcion detallada del objeto cuando está en su ubicación original*/
  BOOL movable; /*!<Indica si el objeto se puede mover de su ubicación*/
  BOOL moved; /*!<Indica si el objeto movible ha sido movido*/
  BOOL hidden; /*!<Indica si el objeto está oculto*/
  Id open_link; /*!<Identificador el enlace que puede abrir el objeto*/
  BOOL light_space; /*!<Indica si el objeto puede iluminar un espacio*/
  BOOL on; /*!<Indica si el objeto que puede iluminar esta encendido o no*/
  char far_description[WORD_SIZE+1]; /*!<Descripcion del objeto cuando NO está en su ubicación original*/
};

/*******************************************************************************
 *                   IMPLEMENTACION DE LA INTERFAZ OBJECT
 ******************************************************************************/

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL OBJETO
*
*******************************************************************************/

/*******************************************************************************
*	Reserva memoria (vacía por calloc) para un nuevo objeto, e inicializa su id
* al especificado como argumento
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

  /*Inicializamos el nombre, la descripción y la descripcion secundaria del objeto*/
  newObject->name[0] = '\0';
  newObject->description[0] = '\0';
  newObject->long_description[0] = '\0';
  newObject->far_description[0] = '\0';

  /*Inicializamos el campo movable del objeto, por defecto, no se puede mover*/
  newObject->movable = FALSE;

  /*Inicializamos el campo moved del objeto, por defecto no se han movido*/
  newObject->moved = FALSE;

  /*Inicializamos el campo hidden del objeto, por defecto son visisbles*/
  newObject->hidden = FALSE;

  /*Inicializamos el campo open_link, por defecto no puede abrir nada*/
  newObject->open_link = NO_ID;

  /*Inicializamos el campo light_space, por defecto no iluminan un espacio*/
  newObject->light_space = TRUE;

  /*Inicializamos el campo on, por defecto el objeto esta apagado*/
  newObject->on = FALSE;

  return newObject;
}

/*******************************************************************************
* Libera la memoria reservada para un objeto y pone el puntero a NULL
*******************************************************************************/
STATUS object_destroy (Object * object)
{
  if (!object)
    return ERROR;

  free(object);

  return OK;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA MODIFICAR LOS DATOS DEL OBJETO
*
*******************************************************************************/

/*******************************************************************************
* Asigna un nombre a un objeto
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
* Asigna la descripcion a un objeto
*******************************************************************************/
STATUS object_set_description(Object * object, char * description)
{
  /* Comprueba los argumentos */
  if (!object || !description)
  {
    return ERROR;
  }

  /* Le asigna a object.description la descripcion introducida y lo comprueba */
  if (!strcpy(object->description, description))
  {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
* Asigna la descripcion detallada a un objeto
*******************************************************************************/
STATUS object_set_long_description(Object * object, char * long_description)
{
  /* Comprueba los argumentos */
  if (!object || !long_description)
  {
    return ERROR;
  }

  /* Le asigna a object.long_description la descripcion detallada introducida y lo comprueba */
  if (!strcpy(object->long_description, long_description))
  {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
* Asigna la descripcion del objeto cuando este no se encuentra en su ubicacion
* original
*******************************************************************************/
STATUS object_set_far_description(Object * object, char * far_description)
{
  /* Comprueba los argumentos */
  if (!object || !far_description)
  {
    return ERROR;
  }

  /* Le asigna a object.far_description la descripcion introducida y lo comprueba */
  if (!strcpy(object->far_description, far_description))
  {
    return ERROR;
  }

  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
* Asigna si el objeto se puede mover de su ubicacion
*******************************************************************************/
STATUS object_set_movable(Object* object, BOOL boolean){

  if(object == NULL){
    return ERROR;
  }

  object->movable = boolean;

  return OK;
}

/*******************************************************************************
* Asigna si el objeto se ha movido de su ubicacion original
*******************************************************************************/
STATUS object_set_moved(Object* object, BOOL boolean){

  if(object == NULL /*|| object->movable == FALSE*/){
    return ERROR;
  }

  object->moved = boolean;

  return OK;
}

/*******************************************************************************
* Asigna si el objeto está oculto
*******************************************************************************/
STATUS object_set_hidden(Object* object, BOOL boolean){

  if(object == NULL){
    return ERROR;
  }

  object->hidden = boolean;

  return OK;
}

/*******************************************************************************
* Asigna el identificador del link que puede abrir el objeto
*******************************************************************************/
STATUS object_set_open_link(Object* object, Id id){

  if(object == NULL){
    return ERROR;
  }

  object->open_link = id;

  return OK;
}

/*******************************************************************************
* Asigna si el objeto puede iluminar un espacio
*******************************************************************************/
STATUS object_set_light_space(Object* object, BOOL boolean){

  if(object == NULL){
    return ERROR;
  }

  object->light_space = boolean;

  return OK;
}

/*******************************************************************************
* Asigna si el objeto está encendido o no
*******************************************************************************/
STATUS object_set_on(Object* object, BOOL boolean){

  if(object == NULL /*|| object->light_space == FALSE*/){
    return ERROR;
  }

  object->on = boolean;

  return OK;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER A LOS DATOS DEL OBJETO
*
*******************************************************************************/

/*******************************************************************************
* Devuelve el id asignado a un objeto
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
* Devuelve el nombre asignado a un objeto
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
* Devuelve la descripcion asignado a un objeto
*******************************************************************************/
char * object_get_description(Object * object)
{
  if (!object)
  {
    return NULL;
  }
  return object->description;
}

/*******************************************************************************
* Devuelve la descripcion asignada a un objeto cuando este no está en su ubicacion
* original
*******************************************************************************/
char * object_get_far_description(Object * object)
{
  if (!object)
  {
    return NULL;
  }
  return object->far_description;
}

/*******************************************************************************
* Devuelve si el objeto se puede mover o no
*******************************************************************************/
BOOL object_get_movable(Object * object)
{
  if (!object)
  {
    return BOOLEAN_ERROR;
  }
  return object->movable;
}

/*******************************************************************************
* Devuelve si el objeto ha sido movido o no
*******************************************************************************/
BOOL object_get_moved(Object * object)
{
  if (!object)
  {
    return BOOLEAN_ERROR;
  }
  return object->moved;
}

/*******************************************************************************
* Devuelve si el objeto está oculto o no
*******************************************************************************/
BOOL object_get_hidden(Object * object)
{
  if (!object)
  {
    return BOOLEAN_ERROR;
  }
  return object->hidden;
}

/*******************************************************************************
* Devuelve el identificador del link que puede abrir el objeto
*******************************************************************************/
Id object_get_open_link(Object * object)
{
  if (!object)
  {
    return NO_ID;
  }
  return object->open_link;
}

/*******************************************************************************
* Devuelve si el objeto puede iluminar un espacio
*******************************************************************************/
BOOL object_get_light_space(Object * object)
{
  if (!object)
  {
    return BOOLEAN_ERROR;
  }
  return object->light_space;
}

/*******************************************************************************
* Devuelve si el objeto está encendido o no
*******************************************************************************/
BOOL object_get_on(Object * object)
{
  if (!object)
  {
    return BOOLEAN_ERROR;
  }
  return object->on;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA DEPURAR LOS DATOS DEL OBJETO
*
*******************************************************************************/

/*******************************************************************************
* Muestra por pantalla los datos del objeto
*******************************************************************************/
STATUS object_print(Object * object)
{
  if (!object)
  {
    return ERROR;
  }

  printf("\n\n------------------------------------------------------------\n\n");
  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Description: %s; Far Description: %s; Open Link: %ld)\n", object->id, object->name, object->description, object->far_description, object->open_link);
  if(object->movable == TRUE){
    fprintf(stdout, "--> El objeto puede moverse.\n");
    if(object->moved == TRUE){
      fprintf(stdout, "-->El objeto ha sido movido.\n");
    }
    else{
      fprintf(stdout, "-->El objeto no ha sido movido.\n");
    }
  }
  else{
    fprintf(stdout, "-->El objeto no puede moverse.\n");
  }

  if(object->hidden == TRUE){
    fprintf(stdout, "-->El objeto está oculto.\n");
  }
  else{
    fprintf(stdout, "-->El objeto no está oculto.\n");
  }

  if(object->light_space == TRUE){
    fprintf(stdout, "-->El objeto puede iluminar un espacio.\n");
    if(object->on == TRUE){
      fprintf(stdout, "-->El objeto está encendido.\n");
    }
    else{
      fprintf(stdout, "-->El objeto está apagado.\n");
    }
  }
  else{
    fprintf(stdout, "-->El objeto no puede iluminar un espacio.\n");
  }
  printf("\n\n------------------------------------------------------------\n\n");

  return OK;
}
