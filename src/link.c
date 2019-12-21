/**
 * @brief Implementa la interfaz publica del modulo link, necesario para conectar
 *        los espacios
 *
 * @file   link.c
 * @author   Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version   v3.0
 * @date 11/03/2018
 * @copyright   GNU Public License
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "link.h"

/**
* @struct _Link
* @brief Implementacion de la definicion de la estructura Link
*/
struct _Link{
  Id id; /*!<Identificador del enlace*/
  char name[WORD_SIZE+1]; /*!<Nombre del enlace*/
  Id espacio_1; /*!<Identificador de la casilla derecha*/
  Id espacio_2; /*!<Identificador de la casilla izquierda*/
  BOOL linked; /*!<Estado del enlace, cerrado(FALSE) o abierto(TRUE)*/
};


/*******************************************************************************
 *                  IMPLEMENTACION DE LA INTERFAZ LINK
 ******************************************************************************/

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL ENLACE
*
*******************************************************************************/

/*******************************************************************************
*	Inicializa un enlace reservando memoria.
*******************************************************************************/
Link* link_create(Id id){

  Link *link = NULL;

  link= (Link*) malloc(sizeof(Link));
  if(link == NULL) return NULL;

  link->id = id;

  link->name[0] = '\0';

  link->espacio_1 = NO_ID;

  link->espacio_2 = NO_ID;

  link->linked = FALSE;

  return link;
}

/*******************************************************************************
*	Elimina la memoria asignada a dicho enlace.
*******************************************************************************/
STATUS link_destroy(Link* link){

  if( link == NULL ) return ERROR;

  free(link);

  return OK;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA LINK
*
*******************************************************************************/

/*******************************************************************************
*	Devuelve el identificador del enlace.
*******************************************************************************/
Id link_get_id(Link* link){

  if( link == NULL ) return NO_ID;

  return link->id;
}

/*******************************************************************************
*	Devuelve el nombre del enlace.
*******************************************************************************/
const char* link_get_name(Link* link){

  if( link == NULL) return NULL;

  return link->name;
}

/*******************************************************************************
*	Devuelve el identificador del enlace derecho.
*******************************************************************************/
Id link_get_espacio_1(Link* link){

  if( link == NULL ) return NO_ID;

  return link->espacio_1;
}

/*******************************************************************************
*	Devuelve el identificador del enlace izquierdo.
*******************************************************************************/
Id link_get_espacio_2(Link* link){

  if( link == NULL ) return NO_ID;

  return link->espacio_2;
}

/*******************************************************************************
*	Devuelve si el enlace está o no unido.
*******************************************************************************/
BOOL link_get_linked(Link* link){

  if( link == NULL ) return FALSE;

  return link->linked;
}

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA LINK
*
*******************************************************************************/

/*******************************************************************************
*	Asigna la variable name al campo name de la estructura del enlace.
*******************************************************************************/
STATUS link_set_name(Link* link, const char* name){

  if( link == NULL || name == NULL ) return ERROR;

  if(!strcpy(link->name, name)) return ERROR;

  return OK;
}

/*******************************************************************************
*	Asigna el valor del identificador de la casilla derecha del enlace.
*******************************************************************************/
STATUS link_set_espacio_1(Link* link, Id id){

  if( link == NULL || id == NO_ID )
    return ERROR;

  link->espacio_1 = id;

  return OK;
}

/*******************************************************************************
*	 Asigna el valor del identificador de la casilla izquierda del enlace.
*******************************************************************************/
STATUS link_set_espacio_2(Link* link, Id id){

  if( link == NULL || id == NO_ID )
    return ERROR;

  link->espacio_2 = id;

  return OK;
}

/*******************************************************************************
*	Asigna el valor de estado del enlace, abierto o cerrado.
*******************************************************************************/
STATUS link_set_linked(Link* link, BOOL linked){

  if( link == NULL || (linked!=TRUE && linked!=FALSE))
    return ERROR;

  link->linked = linked;

  return OK;
}

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO LINK
*
*******************************************************************************/

/*******************************************************************************
*	Imprime el contenido de un enlace.
*******************************************************************************/
STATUS link_print(Link* link){

  if( link == NULL ) return ERROR;

  fprintf(stdout,"Id: %ld || Nombre: %s || Casilla enlazada 1: %ld || Casilla enlazada 2: %ld ||",link->id, link->name, link->espacio_1, link->espacio_2);
  if(link->linked == TRUE){
    fprintf(stdout,"Linked: TRUE\n");
  }
  else{
    fprintf(stdout,"Linked: FALSE\n");
  }
  return OK;
}
