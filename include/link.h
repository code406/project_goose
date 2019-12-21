/**
 * @brief Define la interfaz publica del modulo link, necesario para conectar
 *        los espacios.
 *
 * @file   link.h
 * @author   Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version   v3.0
 * @date   08-04-2018
 * @copyright   GNU Public License
 *
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

#define MAX_LINKS 32 /*!<Numero maximo de links*/

/**
* @typedef Link
* @brief  Definicion de la estructura de datos Link
*/
typedef struct _Link Link;

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL LINK
*
*******************************************************************************/

/**
* @name   link_create
* @date   08-04-2018
* @author   Ines Martin
* @brief   Inicializa un enlace reservando memoria.
* @param   id
* @return   Puntero al enlace inicializado o NULL en caso de error.
*/
Link* link_create(Id id);

/**
* @name   link_destroy
* @date   08-04-2018
* @author   Ines Martin
* @brief   Elimina la memoria asignada a dicho enlace.
* @param   link enlace a eliminar.
* @return   Devuelve OK si se elimina con exito o ERROR si se produce algun fallo.
*/
STATUS link_destroy(Link* link);


/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA LINK
*
*******************************************************************************/

/**
* @name   link_get_id
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve el identificador del enlace.
* @param   link   enlace del que se obtiene su identificador.
* @return   Devuelve el indentificador del enlace o NO_ID si se produce algun error.
*/
Id link_get_id(Link* link);

/**
* @name   link_get_name
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve el nombre del enlace.
* @param   link   enlace del que se obtiene el nombre.
* @return   Devuelve el nombre del enlace o NULL si se produce algun error.
*/
const char* link_get_name(Link* link);

/**
* @name   link_get_espacio_1
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve el identificador del enlace derecho.
* @param   link   enlace del que voy a obtener la casilla derecha.
* @return   Devuelve el identificador de la casilla derecha del enlace o NO_ID si se produce algun error.
*/
Id link_get_espacio_1(Link* link);

/**
* @name   link_get_espacio_2
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve el identificador del enlace izquierdo.
* @param   link   enlace del que voy a obtener la casilla izquierda.
* @return   Devuelve el identificador de la casilla izquierda del enlace o NO_ID si se produce algun error.
*/
Id link_get_espacio_2(Link* link);

/**
* @name   link_get_linked
* @date   08-04-2018
* @author   Ines Martin
* @brief   Devuelve si el enlace está o no unido.
* @param   link  enlace del que voy a obtener su estado.
* @return   Devuelve el estado del enlace o NO_ID si se produce algun error.
*/
BOOL link_get_linked(Link* link);


/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA LINK
*
*******************************************************************************/

/**
* @name   link_set_name
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna la variable name al campo name de la estructura del enlace.
* @param   link  enlace al que le voy a asignar el nombre.
* @param	 name  nombre del enlace.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS link_set_name(Link* link, const char* name);

/**
* @name   link_set_espacio_1
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna el valor del identificador de la casilla derecha del enlace.
* @param   link  enlace al que le voy a asignar la casilla derecha.
* @param	 id    identificador de la casilla derecha.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS link_set_espacio_1(Link* link, Id id);

/**
* @name   link_set_espacio_2
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna el valor del identificador de la casilla izquierda del enlace.
* @param   link   enlace al que le voy a asignar la casilla izquierda.
* @param	 id     identificador de la casilla izquierda.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS link_set_espacio_2(Link* link, Id id);

/**
* @name   link_set_linked
* @date   08-04-2018
* @author   Ines Martin
* @brief   Asigna el valor de estado del enlace, abierto o cerrado.
* @param   link     enlace al que le voy a asignar su estado.
* @param	 linked   estado del enlace.
* @return    Devuelve OK si se asigna con exito o ERROR si se produce algun fallo.
*/
STATUS link_set_linked(Link* link, BOOL linked);


/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO LINK
*
*******************************************************************************/

/**
* @name   link_print
* @date   08-04-2018
* @author   Ines Martin
* @brief   Imprime el contenido de un enlace.
* @param   link   enlace a imprimir
* @return   Devuelve OK si se imprime con exito o ERROR si se produce algun fallo.
*/
STATUS link_print(Link *link);


#endif
