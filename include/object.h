/**
 * @brief Define la interfaz publica del modulo object, necesario para determinar las
 *        caracteristicas de un objeto.
 *
 * @file object.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0.E
 * @date   22-04-2018
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"


/**
* @typedef Object
* @brief  Definicion de la estructura de datos Object
*/
typedef struct _Object Object;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL OBJETO
*
*******************************************************************************/

/**
* @name object_create
* @date   08-04-2018
* @author David Palomo
* @brief Reserva memoria (vacía por calloc) para un nuevo objeto, e inicializa su id al especificado como argumento
* @file object.h
* @param id Entero de tipo Id (long)
* @return Puntero a estructura de tipo Object, que tiene un id y un nombre
*/
Object * object_create(Id id);


/**
* @name object_destroy
* @date   08-04-2018
* @author David Palomo
* @brief Libera la memoria reservada para un objeto y pone el puntero a NULL
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_destroy (Object *object);

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA OBJECT
*
*******************************************************************************/

/**
* @name object_set_name
* @date   08-04-2018
* @author David Palomo
* @brief Asigna un nombre a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @param name Cadena de caracteres que se guardará en object->name
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_set_name(Object* object, char* name);

/**
* @name object_set_description
* @date   08-04-2018
* @author Ines Martin
* @brief Asigna la descripcion a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @param description Cadena de caracteres que se guardará en object->description
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_set_description(Object * object, char * description);

/**
* @name object_set_long_description
* @date   22-04-2018
* @author Ines Martin
* @brief Asigna la descripcion detallada a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @param long_description Cadena de caracteres que se guardará en object->long_description
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_set_long_description(Object * object, char * long_description);

/**
* @name object_set_far_description
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna la descripcion a un objeto cuando este no se encuentra en la ubicacion original
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @param far_description Cadena de caracteres que se guardará en object->far_description
* @return Devuelve OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS object_set_far_description(Object * object, char * far_description);

/**
* @name object_set_movable
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna si el objeto se puede mover de su ubicacion con TRUE o FALSE en caso contrario
* @param object Puntero a una estructura de tipo Object
* @param boolean Dato tipo BOOL
* @return OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS object_set_movable(Object* object, BOOL boolean);

/**
* @name object_set_moved
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna si el objeto se ha movido de su ubicacion original
* @param object Puntero a una estructura de tipo Object
* @param boolean Dato tipo BOOL
* @return OK si todo sale bien o ERROR si se produce algun fallo o el objeto no puede moverse
*/
STATUS object_set_moved(Object* object, BOOL boolean);

/**
* @name object_set_hidden
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna si el objeto está oculto
* @param object Puntero a una estructura de tipo Object
* @param boolean Dato tipo BOOL
* @return OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS object_set_hidden(Object* object, BOOL boolean);

/**
* @name object_set_open_link
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna el identificador del link que puede abrir el objeto
* @param object Puntero a una estructura de tipo Object
* @param id Identificador del link que puede abrir el objeto
* @return OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS object_set_open_link(Object* object, Id id);

/**
* @name object_set_light_space
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna si el objeto puede iluminar un espacio
* @param object Puntero a una estructura de tipo Object
* @param boolean Dato tipo BOOL
* @return OK si todo sale bien o ERROR si se produce algun fallo
*/
STATUS object_set_light_space(Object* object, BOOL boolean);

/**
* @name object_set_on
* @date   21-04-2018
* @author Javier Mateos
* @brief Asigna si el objeto está encendido o no
* @param object Puntero a una estructura de tipo Object
* @param boolean Dato tipo BOOL
* @return OK si todo sale bien o ERROR si se produce algun fallo o no puede iluminar un espacio
*/
STATUS object_set_on(Object* object, BOOL boolean);

/*******************************************************************************
*
*     BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA OBJECT
*
*******************************************************************************/

/**
* @name object_get_id
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el id asignado a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return Variable de tipo Id (long) que identifica al objeto (object->id), si el argumento introducido no es correcto, devuelve NULL
*/
Id object_get_id(Object* object);

/**
* @name object_get_name
* @date   08-04-2018
* @author David Palomo
* @brief Devuelve el nombre asignado a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return Cadena de caracteres con el nombre del objeto (object->name), si el argumento introducido no es correcto, devuelve NULL
*/
char * object_get_name(Object* object);

/**
* @name object_get_description
* @date   08-04-2018
* @author Ines Martin
* @brief Devuelve la descripcion asignado a un objeto
* @file object.h
* @param object Puntero a una estructura de tipo Object
* @return Cadena de caracteres con la descripcion del objeto (object->description), si el argumento introducido no es correcto, devuelve NULL
*/
char * object_get_description(Object * object);

/**
* @name object_get_far_description
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve la descripcion asignaao a un objeto cuando este no está en su ubicacion original
* @param object Puntero a una estructura de tipo Object
* @return Cadena de caracteres con la descripcion del objeto (object->far_description) o NULL si se produce algun error
*/
char * object_get_far_description(Object * object);

/**
* @name object_get_movable
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto se puede mover o no
* @param object Puntero a una estructura de tipo Object
* @return Devuelve TRUE si se puede mover, FALSE si no se puede mover o BOOLEAN_ERROR si se produce algun error
*/
BOOL object_get_movable(Object * object);

/**
* @name object_get_moved
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto ha sido movido
* @param object Puntero a una estructura de tipo Object
* @return Devuelve TRUE si se ha movido, FALSE en caso contrario o BOOLEAN_ERROR si se produce algun error
*/
BOOL object_get_moved(Object * object);

/**
* @name object_get_hidden
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto está oculto o no
* @param object Puntero a una estructura de tipo Object
* @return Devuelve TRUE si está oculto, FALSE en caso contrario o BOOLEAN_ERROR si se produce algun error
*/
BOOL object_get_hidden(Object * object);

/**
* @name object_get_open_link
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto puedo abrir un determinado enlace
* @param object Puntero a una estructura de tipo Object
* @return Devuelve el identificador del link que puede abrir o NO_ID si no abre ninguno o se produce algun error
*/
Id object_get_open_link(Object * object);

/**
* @name object_get_light_space
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto puede iluminar o no un espacio
* @param object Puntero a una estructura de tipo Object
* @return Devuelve TRUE si puede iluminar, FALSE en caso contrario o BOOLEAN_ERROR si se produce algun error
*/
BOOL object_get_light_space(Object * object);

/**
* @name object_get_on
* @date   21-04-2018
* @author Javier Mateos
* @brief Devuelve si el objeto esta encendido o no
* @param object Puntero a una estructura de tipo Object
* @return Devuelve TRUE si está encendido, FALSE en caso contrario o BOOLEAN_ERROR si se produce algun error
*/
BOOL object_get_on(Object * object);
/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO OBJECT
*
*******************************************************************************/

/**
* @name object_print
* @date   08-04-2018
* @author David Palomo
* @brief Muestra por pantalla los datos del objeto
* @param object Puntero a una estructura de tipo Object
* @return OK o ERROR, que pertenecen al enum STATUS
*/
STATUS object_print(Object* object);

#endif
