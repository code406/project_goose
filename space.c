#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"



struct _Space {
  /*Id = long*/
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Id object;
};

/*******************************************************************************
Funcion: space_create
Descripcion: Su funcion es reservar memoria para una estructura tipo space.
Al Id le asigna el valor del argumento y al resto -1 ó 0
Argumentos:
  un Id (id)
Return:
  un puntero a Space
*******************************************************************************/


Space* space_create(Id id) {
   /*Crea un puntero a Space*/
  Space *newSpace = NULL;

  /*Comprueba el argumento*/
  if (id == NO_ID)
    return NULL;

    /*Asigna memoria al puntero*/
  newSpace = (Space *) calloc(1,sizeof (Space));
  /*Comprueba la asignacion de memoria*/
  if (newSpace == NULL) {
    return NULL;
  }

  /*Le asigna a newSpace.id el argumento introducido y a lo demas -1 o 0 */
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->object = NO_ID;

  /*Devuelve la veriable newSpace creada*/
  return newSpace;
}


/*******************************************************************************
Funcion: space_destroy
Descripcion:Si la variable introducida es nula devuelve un error(0);
Si no es nula libera el espacio y a la variable introducida le asigna un NULL
Argumentos:
  un puntero a Space (space)
Return:
  un STATUS
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
Descripcion: Le asigna al Space introducido el nombre introducido
Argumentos:
  un puntero a Space (space) y un puntero a char (name)
Return:
  un STATUS
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
Descripcion: le asigna al north del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
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
Descripcion: le asigna al south del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
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
Descripcion: le asigna al east del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
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
Descripcion: le asigna al west del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
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
Descripcion: le asigna al object del space introducido el id introducido
Argumentos:
  un puntero a Space (space) y un Id (id)
Return:
  un STATUS
*******************************************************************************/

STATUS space_set_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  space->object = value;
  return OK;
}

/*******************************************************************************
Funcion: space_get_name
Descripcion: devolver el nombre del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un puntero a char
*******************************************************************************/


const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

/*******************************************************************************
Funcion: space_get_id
Descripcion: devolver el id del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/*******************************************************************************
Funcion: space_get_north
Descripcion: devolver el id del north del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/


Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

/*******************************************************************************
Funcion: space_get_south
Descripcion: devolver el id del south del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/


Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/*******************************************************************************
Funcion: space_get_east
Descripcion: devolver el id del east del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/*******************************************************************************
Funcion: space_get_west
Descripcion: devolver el id del west del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/


Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

/*******************************************************************************
Funcion: space_get_object
Descripcion: devolver el id del object del Space introducido
Argumentos:
  un puntero a Space (space)
Return:
  un id
*******************************************************************************/


Id space_get_object(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->object;
}

/*******************************************************************************
Funcion: space_print
Descripcion: Muestra por pantalla las condiciones del espacio:
  -El nombre y el id;
  -Si hay norte, sur, este y oeste;
  -Si hay algún objeto
Argumentos:
  un puntero a Space (space)
Return:
  un STATUS
*******************************************************************************/

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
