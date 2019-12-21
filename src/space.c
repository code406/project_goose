/**
 * @brief Implementa una casilla
 * @file space.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"


/**
* @struct _Space
* @brief Implementacion de la definicion de la estructura Space
*/
struct _Space
{
  Id id; /*!<Identificador de la casilla*/
  char name[WORD_SIZE + 1]; /*!<Nombre de la casilla*/
  Id north_link; /*!<Identificador del link al norte de la casilla*/
  Id south_link; /*!<Identificador del link al sur de la casilla*/
  Id east_link; /*!<Identificador del link al este de la casilla*/
  Id west_link; /*!<Identificador del link al oeste de la casilla*/
  Id up_link; /*!<Identificador del link por arriba de la casilla*/
  Id down_link; /*!<Identificador del link por debajo de la casilla*/
  Set *objects; /*!<Conjunto de objetos de la casilla*/
  char gdesc[MAX_GDESC][GDESC_LENGTH]; /*!<Descripcion grafica ASCII de la casilla*/
  char description[WORD_SIZE+1]; /*!<Descripcion de la casilla*/
  char long_description[WORD_SIZE+1]; /*!<Descripcion detallada de la casilla*/
  BOOL lit;
  BOOL ocupada;
};

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DE SPACE
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa un espacio reservando memoria dinamica
*******************************************************************************/
Space* space_create(Id id)
{
  int i;
  /* Crea un puntero a Space */
  Space *newSpace = NULL;

  /* Comprueba el argumento */
  if (id == NO_ID)
    return NULL;

  /* Reserva memoria para el puntero */
  newSpace = (Space *) calloc(1,sizeof (Space));
  /* Comprueba la asignacion de memoria */
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Inicializa el nombre e id DE la casilla, y sus descripciones */
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->description[0] = '\0';
  newSpace->long_description[0] = '\0';

  /* Inicializa los enlaces en cada dirección a NO_ID */
  newSpace->north_link = NO_ID;
  newSpace->south_link = NO_ID;
  newSpace->east_link = NO_ID;
  newSpace->west_link = NO_ID;
  newSpace->up_link = NO_ID;
  newSpace->down_link = NO_ID;

  /*Inicializa la descripcion ASCII*/
  for (i=0;i<MAX_GDESC;i++)
    strcpy(newSpace->gdesc[i]," ");

  /*Se crea el conjunto de objetos*/
  newSpace->objects = set_create();

  /* Inicializa el campo lit (si una casilla está iluminada) */
  newSpace->lit = TRUE;

  /* Devuelve la veriable newSpace creada */
  return newSpace;
}

/*******************************************************************************
*	 Libera la memoria asociada al espacio
*******************************************************************************/
STATUS space_destroy(Space* space)
{
  if (!space)
  {
    return ERROR;
  }
  if(space->objects != NULL)
    set_destroy (space->objects);

  free(space);

  return OK;
}

/*******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER LOS CAMPOS DE LA ESTRUCTURA PLAYER
*
*******************************************************************************/

/*******************************************************************************
*	Obtiene el id que identifica una casilla del juego.
*******************************************************************************/
Id space_get_id(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->id;
}

/*******************************************************************************
*	Devuelve el nombre asignado a la casilla especificada
*******************************************************************************/
char * space_get_name(Space* space)
{
  if (!space)
  {
    return NULL;
  }

  return space->name;
}

/*******************************************************************************
*	 Devuelve la descripcion de la casilla especificada
*******************************************************************************/
char* space_get_description(Space* space)
{
  if (space == NULL) return NULL;

  return space->description;
}

/*******************************************************************************
*  Devuelve la descripcion detallada de la casilla especificada
*******************************************************************************/
char* space_get_long_description(Space* space)
{
  if (space == NULL) return NULL;

  return space->long_description;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por el norte de
* la introducida
*******************************************************************************/
Id space_get_north_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->north_link;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por el sur de
* la introducida
*******************************************************************************/
Id space_get_south_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->south_link;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por el este de
* la introducida
*******************************************************************************/
Id space_get_east_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->east_link;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por el oeste de
* la introducida
*******************************************************************************/
Id space_get_west_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->west_link;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por arriba de
* la introducida
*******************************************************************************/
Id space_get_up_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->up_link;
}

/*******************************************************************************
* Devuelve el id del enlace que une la casilla con otra por debajo de
* la introducida
*******************************************************************************/
Id space_get_down_link(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->down_link;
}

/*******************************************************************************
* Devuelve si una casilla está iluminada.
*******************************************************************************/
BOOL space_get_lit(Space* space)
{
  if (!space)
  {
    return FALSE;
  }

  return space->lit;
}

/*******************************************************************************
* Devuelve si una casilla está ocupada.
*******************************************************************************/
BOOL space_get_ocupada(Space* space)
{
  if (!space)
  {
    return FALSE;
  }

  return space->ocupada;
}

/*******************************************************************************
*	 Devuelve el conjunto de identificadores del espacio
*******************************************************************************/
Id* space_get_ids_objects(Space* space)
{
  if (!space)
  {
    return NULL;
  }

  return set_get_ids(space->objects);
}

/*******************************************************************************
*	 La cadena correspondiente a la linea n+1 del dibujo
*******************************************************************************/
char* space_get_gdesc(Space* space, int n)
{
  if (space == NULL || n<0 || n>=MAX_GDESC)
    return NULL;

  return space->gdesc[n];
}

/*******************************************************************************
*	Comprueba si un objeto se encuentra en el Space introducido
*******************************************************************************/
BOOL space_check_object (Space *space, Id object_id)
{
  if(!space || object_id == NO_ID)
    return FALSE;

  return set_check_id(space->objects, object_id);
}

/*******************************************************************************
*
*    BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA SET
*
*******************************************************************************/

/*******************************************************************************
*	 Asigna a la casilla especificada el nombre introducido
*******************************************************************************/
STATUS space_set_name(Space* space, const char* name)
{
  /* Comprueba los argumentos */
  if (!space || !name)
  {
    return ERROR;
  }
  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
*	Asigna a la casilla especificada la descripcion
*******************************************************************************/
STATUS space_set_description(Space* space, char *description)
{
  if (space == NULL || description == NULL) return ERROR;

  strcpy(space->description, description);

  return OK;
}

/*******************************************************************************
* Asigna a la casilla especificada la descripcion detallada
*******************************************************************************/
STATUS space_set_long_description(Space* space, char *long_description)
{
  if (space == NULL || long_description == NULL) return ERROR ;

  strcpy(space->long_description, long_description);

  return OK;
}

/*******************************************************************************
*	   Asigna un identificador al enlace situado al norte de la casilla.
*******************************************************************************/
STATUS space_set_north_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->north_link = id;

  return OK;
}

/*******************************************************************************
*	   Asigna un identificador al enlace situado al sur de la casilla.
*******************************************************************************/
STATUS space_set_south_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->south_link = id;

  return OK;
}

/*******************************************************************************
*	  Asigna un identificador al enlace situado al este de la casilla.
*******************************************************************************/
STATUS space_set_east_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->east_link = id;
  return OK;
}

/*******************************************************************************
*	 Asigna un identificador al enlace situado al oeste de la casilla.
*******************************************************************************/
STATUS space_set_west_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->west_link = id;
  return OK;
}

/*******************************************************************************
*   Asigna un identificador al enlace situado por arriba de la casilla.
*******************************************************************************/
STATUS space_set_up_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->up_link = id;
  return OK;
}

/*******************************************************************************
*   Asigna un identificador al enlace situado por debajo de la casilla.
*******************************************************************************/
STATUS space_set_down_link(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  space->down_link = id;
  return OK;
}

/*******************************************************************************
*	 Coloca en la casilla especificada un objeto
*******************************************************************************/
STATUS space_add_object(Space* space, Id value)
{
  if (!space)
  {
    return ERROR;
  }

  if(set_add_id(space->objects, value) == ERROR)
    return ERROR;

  return OK;
}

/*******************************************************************************
*	 Devuelve la estructura objects (tipo set) del espacio introducido
*******************************************************************************/
STATUS space_del_object(Space* space, Id id)
{
  if (!space)
  {
    return ERROR;
  }

  if((set_remove_id (space->objects, id))==ERROR)
    return ERROR;

  return OK;
}

/*******************************************************************************
*	 Asigna a la casilla especificada la linea n+1 del dibujo o una serie de 7 espacios.
*******************************************************************************/
STATUS space_set_gdesc(Space* space, char* cadena, int n)
{
  /* Comprueba los argumentos */
  if (!space || !cadena || n<0 || n>=MAX_GDESC)
  {
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[n], cadena))
  {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
*   Asigna si la casilla especificada está iluminada
*******************************************************************************/
STATUS space_set_lit(Space* space, BOOL lit)
{
  if (!space || (lit!=TRUE && lit!=FALSE))
  {
    return ERROR;
  }

  space->lit = lit;
  return OK;
}

/*******************************************************************************
*   Asigna si la casilla especificada está ocupada
*******************************************************************************/
STATUS space_set_ocupada(Space* space, BOOL ocupada)
{
  if (!space || (ocupada!=TRUE && ocupada!=FALSE))
  {
    return ERROR;
  }

  space->ocupada = ocupada;
  return OK;
}

/*******************************************************************************
*
*            BLOQUE DE FUNCIONES PARA DEPURAR EL MODULO PLAYER
*
*******************************************************************************/

/*******************************************************************************
*	Muestra por pantalla la informacion de la casilla especificada.
*******************************************************************************/
STATUS space_print(Space* space)
{
  Id idaux = NO_ID;
  int i;

  if (!space)
  {
    return ERROR;
  }

  /* Imprime id y nombre de la estructura de tipo Space (casilla) */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* Imprime la descripcion de la estructura de tipo Space (casilla) */
  fprintf(stdout, "--> Description: %s)\n", space->description);

  /* Imprime la descripcion detallada de la estructura de tipo Space (casilla) */
  fprintf(stdout, "--> Long description: %s)\n", space->long_description);

  /* Imprime la descripcion detallada de la estructura de tipo Space (casilla) */
  for (i=0; i<MAX_GDESC; i++)
    fprintf(stdout, "--> ASCII description: %s)\n", space->gdesc[i]);

  /* Imprime el campo "lit" de la estructura de tipo Space (casilla) */
  if (space_get_lit(space) == TRUE)
  {
    fprintf(stdout, "---> La casilla está iluminada (lit: TRUE)\n");
  }
  else
  {
    fprintf(stdout, "---> La casilla no está iluminada (lit: FALSE)\n");
  }

  /* Si hay casillas contiguas (en cada dirección), imprime su id.
     Si no, informa de que no hay casillas contiguas en esa dirección */
  idaux = space_get_north_link(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south_link(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east_link(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west_link(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  idaux = space_get_up_link(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> Up link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No up link.\n");
  }

  idaux = space_get_west_link(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> Down link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No down link.\n");
  }

  /*Imprimimos el conjunto de objetos del espacio*/
  set_print(space->objects);

  return OK;
}
