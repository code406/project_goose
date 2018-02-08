#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

/*
Crea una estructura llamada game_set_player_location
*/

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



/*
Funcion space_create. Devuelve un puntero a Space (La estructura anterior)
y cuyo argumento es una variable tipo Id (long)

Su funcion es reservar memoria para una estructura tipo space.
Al Id le asigna el valor del argumento y a las coordenadas, NO_ID.
*/
Space* space_create(Id id){
   /*Crea un puntero a Space*/
  Space *newSpace = NULL;

  /*Comprueba el argumento*/
  if (id == NO_ID)
    return NULL;

  /*Asigna memoria al puntero*/
  newSpace = (Space *) malloc(sizeof (Space));
  /*Comprueba la asignacion de memoria*/
  if (newSpace == NULL){
    return NULL;
  }

  /*Le asigna a newSpace.id el argumento introducido y a lo demas -1 o 0 */
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east  = NO_ID;
  newSpace->west  = NO_ID;

  newSpace->object = FALSE;

  /*Devuelve la variable newSpace creada*/
  return newSpace;
}



/*
Funcion que devuelve una variable tipo status y cuyo
argumento es un puntero a Space.
Si la variable introducida es nula devuelve un error(0);
Si no es nula libera el espacio y a la variable introducida le asigna un NULL
*/
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un puntero a char
LE asigna al Space introducido el nombre introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
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



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de North introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de South introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de east introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un Id
LE asigna al Space introducido el valor de west introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}



/*
Devuelve un OK =1 ó un ERROR = 0;
Sus argumentos son un puntero a Space y un BOOL
LE asigna al Space introducido el valor de object introducido
Si algo falla devuelve ERROR y si va bien OK.
*/
STATUS space_set_object(Space* space, BOOL value) {
  if (!space) {
    return ERROR;
  }
  space->object = value;
  return OK;
}



/*
Devuelve un puntero a char;
Su argumento es un puntero a Space
Devuelve el nombre del espacio (space.name)
Si algo falla devuelve NULL
*/
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}



/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el id del espacio (space.id)
Si algo falla devuelve NO_ID
*/
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}



/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del norte del espacio (space.north)
Si algo falla devuelve NO_ID
*/
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}



/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del sur del espacio (space.south)
Si algo falla devuelve NO_ID
*/
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}



/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del este del espacio (space.east)
Si algo falla devuelve NO_ID
*/
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}



/*
Devuelve un id;
Su argumento es un puntero a Space
Devuelve el valor del oeste del espacio (space.west)
Si algo falla devuelve NO_ID
*/
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}



/*
Devuelve un BOOL (true = 1, false = 0);
Su argumento es un puntero a Space
Devuelve el valor del object del espacio (space.object)
Si algo falla devuelve FALSE
*/
BOOL space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  return space->object;
}



/*
Devuelve un Status (ERROR = 0, OK = 1);
Su argumento es un puntero a Space
Si algo falla devuelve ERROR
Muestra por pantalla las condiciones del espacio:
  -El nombre y el id;
  -Si hay norte, sur, este y oeste;
  -Si hay algún objeto
*/
STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (space_get_object(space)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
