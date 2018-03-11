/**
 * @brief Implementa una casilla
 * @file space.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "set.h"


/* Estructura que define una casilla del juego, con un id que la identifica,
un nombre, el id de las casillas contiguas y el id del objeto que hay en ella
Incluye un set, y una tabla de cadena de caracteres para la descripcion ASCII */
struct _Space
{
  /*Id = long*/
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Set *objects;
  char gdesc[3][21];
};


/*******************************************************************************
Funcion: space_create
Autor: David Palomo
Descripcion: Reserva memoria para una estructura de tipo Space,
  que representa una casilla del juego.
Argumentos:
  id: variable de tipo Id (entero long) que identifica la casilla
Return:
  Puntero a una estructura de tipo Space (casilla)
*******************************************************************************/
Space* space_create(Id id)
{
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

  /* Inicializa los campos de la estructura */
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  /*Se inicializan todas las Ids a NO_ID*/
  newSpace->objects = set_create();

  /* Devuelve la veriable newSpace creada */
  return newSpace;
}


/*******************************************************************************
Funcion: space_destroy
Autor: David Palomo
Descripcion: Libera la memoria reservada previamente para una estructura
  de tipo Space (que representa una casilla del juego) y asigna NULL al
  puntero a Space pasado como argumento.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_destroy(Space* space)
{
  if (!space)
  {
    return ERROR;
  }

  set_destroy (space->objects);

  free(space);

  return OK;
}


/*******************************************************************************
Funcion: space_set_name
Autor: Arturo Morcillo
Descripcion: Asigna a la casilla especificada el nombre introducido.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  name : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_name(Space* space, char* name)
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
Funcion: space_set_north
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al norte de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_north(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->north = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_south
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al sur de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_south(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->south = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_east
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al este de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_east(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->east = id;
  return OK;
}


/*******************************************************************************
Funcion: space_set_west
Autor: David Palomo
Descripcion: Asigna a la casilla que se encuentra al oeste de la introducida
  un id que la identifica.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  id   : variable de tipo Id (entero long)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_west(Space* space, Id id)
{
  if (!space || id == NO_ID)
  {
    return ERROR;
  }

  space->west = id;
  return OK;
}


/*******************************************************************************
Funcion: space_del_object
Autor: Arturo Morcillo
Descripcion: Quita el ultimo objeto de una casilla
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_del_object(Space* space)
{
  if (!space)
  {
    return ERROR;
  }

  if((set_del (space->objects))==ERROR)
    return ERROR;

  return OK;
}


/*******************************************************************************
Funcion: space_add_object
Autor: Arturo Morcillo
Descripcion: Coloca en la casilla especificada un objeto.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  value: Entero de tipo id (long) que identifica un objeto
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_add_object(Space* space, Id value)
{
  if (!space)
  {
    return ERROR;
  }

  if((set_add (space->objects, value))==ERROR)
    return ERROR;

  return OK;
}


/*******************************************************************************
Funcion: space_get_name
Autor: Arturo Morcillo
Descripcion: Devuelve el nombre asignado a la casilla especificada.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Cadena de caracteres (nombre de la casilla)
  En caso de error, devuelve NULL.
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
Funcion: space_get_id
Autor: Arturo Morcillo
Descripcion: Obtiene el id que identifica una casilla del juego.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Variable de tipo Id (entero long).
  En caso de error, devuelve NO_ID.
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
Funcion: space_get_north
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al norte
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al norte de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_north(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->north;
}


/*******************************************************************************
Funcion: space_get_south
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al sur
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al sur de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_south(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->south;
}


/*******************************************************************************
Funcion: space_get_east
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al este
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al este de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_east(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->east;
}


/*******************************************************************************
Funcion: space_get_west
Autor: David Palomo
Descripcion: Devuelve el id de la casilla que se encuentra al oeste
  de la introducida
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Id (entero long) de la casilla al oeste de la introducida
  En caso de error, devuelve NO_ID.
*******************************************************************************/
Id space_get_west(Space* space)
{
  if (!space)
  {
    return NO_ID;
  }

  return space->west;
}


/*******************************************************************************
Funcion: space_get_objects
Autor: Arturo Morcillo
Descripcion: Devuelve la estructura objects (tipo set) del espacio introducido
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Una estructura tipo Set.
  En caso de error, o de que no haya objetos, devuelve NULL.
*******************************************************************************/
Set* space_get_objects(Space* space)
{
  if (!space || space->objects == NULL)
  {
    return NULL;
  }

  return space->objects;
}


/*******************************************************************************
Funcion: check_object
Autor: Arturo Morcillo
Descripcion:  comprueba si un objeto se encuentra en el Space introducido
Argumentos:
  Un puntero a Space (ps) y el id del objeto (object_id)
Return:
  Un BOOL: TRUE si se encuentra y FALSE si no
*******************************************************************************/
BOOL check_object (Space *ps, Id object_id)
{
  Set *aux;
  Id id_aux;
  int n;

  if (ps == NULL || object_id == NO_ID)
    return FALSE;

  aux = space_get_objects (ps);
  if (aux == NULL)
    return FALSE;

  for (n=0;n<MAX_ID;n++)
  {
    id_aux = get_id_pos (aux, n);
    if (id_aux != NO_ID)
    {
      if (id_aux == object_id)
      {
        return TRUE;
      }
    }
  }

  return FALSE;
}


/*******************************************************************************
Funcion: space_print
Autor: David Palomo
Descripcion: Muestra por pantalla la informacion de la casilla especificada:
  su id y nombre, los id de las casillas contiguas, y qué objeto hay en ella.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_print(Space* space)
{
  Set *aux;
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
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
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

  /* Imprime si hay o no un objeto en la casilla, y cuál es su id */
  if ((aux = space_get_objects(space)) != NULL)
  {
    set_print(aux);
    set_destroy(aux);
    aux = NULL;
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
    set_destroy(aux);
    aux = NULL;
  }

  return OK;
}


/*******************************************************************************
Funcion: space_set_gdesc_0
Autor: Arturo Morcillo
Descripcion: Asigna a la casilla especificada la primera linea del dibujo o una serie de 7 espacios.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  cadena : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_gdesc_0(Space* space, char* cadena)
{
  /* Comprueba los argumentos */
  if (!space || !cadena)
  {
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[0], cadena))
  {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}


/*******************************************************************************
Funcion: space_set_gdesc_1
Autor: Arturo Morcillo
Descripcion: Asigna a la casilla especificada la segunda linea del dibujo o una serie de 7 espacios.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  cadena : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_gdesc_1(Space* space, char* cadena)
{
  /* Comprueba los argumentos */
  if (!space || !cadena)
  {
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[1], cadena))
  {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}

/*******************************************************************************
Funcion: space_set_gdesc_2
Autor: Arturo Morcillo
Descripcion: Asigna a la casilla especificada la tercera linea del dibujo o una serie de 7 espacios.
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
  cadena : cadena de caracteres
Return:
  OK o ERROR, que pertenecen al enum STATUS
*******************************************************************************/
STATUS space_set_gdesc_2(Space* space, char* cadena)
{
  /* Comprueba los argumentos */
  if (!space || !cadena)
  {
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[2], cadena))
  {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}


/*******************************************************************************
Funcion: space_get_gdesc_0
Autor: Arturo Morcillo
Descripcion: La cadena correspondiente a la primera linea del dibujo
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Un puntero a char (cadena de caracteres)
*******************************************************************************/
char* space_get_gdesc_0(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[0];
}


/*******************************************************************************
Funcion: space_get_gdesc_1
Autor: Arturo Morcillo
Descripcion: La cadena correspondiente a la segunda linea del dibujo
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Un puntero a char (cadena de caracteres)
*******************************************************************************/
char* space_get_gdesc_1(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[1];
}


/*******************************************************************************
Funcion: space_get_gdesc_2
Autor: Arturo Morcillo
Descripcion: La cadena correspondiente a la segunda linea del dibujo
Argumentos:
  space: puntero a una estructura de tipo Space (casilla)
Return:
  Un puntero a char (cadena de caracteres)
*******************************************************************************/
char* space_get_gdesc_2(Space* space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc[2];
}
