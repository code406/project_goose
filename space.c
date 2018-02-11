/**
 * @brief Define una casilla y las funciones relacionadas con ella
 *
 * @file space.c
 * @author Glenson
 * @version 1.0
 * @date 11-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"


/* Crea la estructura Space, que contiene los datos de una casilla del juego */
struct _Space {
  /*Id = long*/
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  BOOL object;
};


/*******************************************************************************
Funcion: space_create
Descripcion: Reserva memoria para una estructura de tipo Space,
  que representa una casilla del juego.
Argumentos:
  id: variable de tipo Id (entero long) que identifica la casilla
Return:
  Puntero a una estructura de tipo Space (casilla)
*******************************************************************************/
Space* space_create(Id id) {
   /*Crea un puntero a Space*/
  Space *newSpace = NULL;

  /*Comprueba el argumento*/
  if (id == NO_ID)
    return NULL;

    /*Asigna memoria al puntero*/
  newSpace = (Space *) malloc(sizeof (Space));
  /*Comprueba la asignacion de memoria*/
  if (newSpace == NULL) {
    return NULL;
  }

  /* Inicializa los campos de la estructura */
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->object = FALSE; /* Al inicializar la casilla, no tiene objeto */

  /*Devuelve la veriable newSpace creada*/
  return newSpace;
}


/*******************************************************************************
Funcion: space_destroy
Descripcion: Libera la memoria reservada previamente para una estructura
  de tipo Space (que representa una casilla del juego) y asigna NULL al
  puntero a Space pasado como argumento.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}


/*******************************************************************************
Funcion: space_set_name
Descripcion: Asigna a la casilla especificada el nombre introducido.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  name : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_name(Space* space, char* name) {
  /*Comprueba los argumentos*/
  if (!space || !name) {
    return ERROR;
  }
  /*
  Le asigna a  space.name el nombre introducido
  y lo comprueba
  */
  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  /*Si todo va bien devuelve OK*/
  return OK;
}


/*******************************************************************************
Funcion: space_set_north
Descripcion: Asigna a la casilla que se encuentra al norte de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_south
Descripcion: Asigna a la casilla que se encuentra al sur de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_east
Descripcion: Asigna a la casilla que se encuentra al este de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_west
Descripcion: Asigna a la casilla que se encuentra al oeste de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_object
Descripcion: Coloca en la casilla especificada un objeto, o lo quita.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  value: variable de tipo BOOL  (FALSE: casilla sin objeto,
                                  TRUE: casilla con objeto)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_object(Space* space, BOOL value) {
  if (!space) {
    return ERROR;
  }
  space->object = value;
  return OK;
}


/*******************************************************************************
Funcion: space_get_name
Descripcion: Devuelve el nombre asignado a la casilla especificada.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Cadena de caracteres (nombre de la casilla)
  En caso de error, devuelve NO_ID.
*******************************************************************************/
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}


/*******************************************************************************
Funcion: space_get_id
Descripcion: Obtiene el id que identifica una casilla del juego.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Variable de tipo Id (entero long).
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}


/*******************************************************************************
Funcion: space_get_north
Descripcion: Devuelve el id de la casilla que se encuentra al norte
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al norte de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}


/*******************************************************************************
Funcion: space_get_south
Descripcion: Devuelve el id de la casilla que se encuentra al sur
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al sur de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}


/*******************************************************************************
Funcion: space_get_east
Descripcion: Devuelve el id de la casilla que se encuentra al este
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al este de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}


/*******************************************************************************
Funcion: space_get_west
Descripcion: Devuelve el id de la casilla que se encuentra al oeste
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al oeste de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}


/*******************************************************************************
Funcion: space_get_object
Descripcion: Indica si en la casilla especificada hay o no un objeto
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Variable de tipo BOOL (FALSE, TRUE)
  En caso de error, devuelve FALSE.
*******************************************************************************/
BOOL space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  return space->object;
}


/*******************************************************************************
Funcion: space_print
Descripcion: Muestra por pantalla la informacion de la casilla especificada:
  su id y nombre, los id de las casillas contiguas, y si hay algún objeto.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space)
  {
    return ERROR;
  }

  /* Imprime id y nombre de la estructura de tipo Space (casilla) */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);


  /* Si hay casillas contiguas (en cada dirección), imprime su id.
     Si no, informa de que no hay casillas contiguas en esa dirección */

  idaux = space_get_north(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux)
  {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }


  /* Imprime si hay o no un objeto en la casilla */
  if (space_get_object(space))
  {
    fprintf(stdout, "---> Object in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
