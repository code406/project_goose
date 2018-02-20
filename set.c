/**
 * @brief Funciones necesarias para el manejo de conjuntos
 *
 * @file set.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 10-02-2018
 * @copyright GNU Public License
 */
/*
Estructura que almacena los jugadores
Consta de un array de punteros a Player y un entero para recorrerlo
*/
 struct Players{
   Player* player[MAX_PLAYERS];
   int tope; /*Para recorrer el array*/
 }
 /*
 Estructura que almacena los objetos
 Consta de un array de punteros a Object y un entero para recorrerlo
 */
 struct Objects{
   Object *object[MAX_OBJECTS];
   int tope; /*Para recorrer el array*/
 }
 /*
 Estructura que almacena los espacios
 Consta de un array de punteros a Space y un entero para recorrerlo
 */
 struct Spaces{
   Space *space[MAX_SPACES];
   int tope; /*Para recorrer el array*/
 }
 /*******************************************************************************
 Funcion: players_create
 Autor: Arturo Morcillo
 Descripcion: Reserva memoria (vacía por calloc) para un una estructura Players,
   e inicializa sus campos a NULL
 Argumentos:
   Ninguno
 Return:
   Puntero a estructura de tipo Players
 *******************************************************************************/
 Players * players_create() {
    Players *p;
    int i;
    p = (Players*)calloc(1,sizeof(Players));
    if (p==NULL)
      return NULL;

    p->tope = 0;

    for (i=0; i<MAX_PLAYERS; i++)
        p->player[i] = NULL;
    return p;
}
/*******************************************************************************
Funcion: players_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumenro
y la pone a NULL
Argumentos:
  p: Puntero a estructura tipo Players
Return:
  Nada (tipo void)
*******************************************************************************/
void players_destroy(Players *p) {
    int i;
    if (p==NULL)
      return;

    for (i=0; i<p->tope; i++)
        player_destroy (p->player[i]);

    free(p);
    p = NULL;
}
/*******************************************************************************
Funcion: players_add
Autor: Arturo Morcillo
Descripcion: Añade un jugador a la estructura Players
Argumentos:
  p: Puntero a la estructura player
  player_ EL jugador a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS players_add(Players *p, const Player *player) {
    if (p==NULL || player==NULL)
      return ERROR;
    if ( p->tope == MAX_PLAYERS-1)
      return ERROR;

    p->player[p->tope] = player_copy(player);
    if (p->player[p->tope]==NULL)
      return ERROR;

    p->tope++;
    return OK;
 }
 /*******************************************************************************
 Funcion: players_isempty
 Autor: Arturo Morcillo
 Descripcion: Comprueba si la estructura introducida esta vacia
 Argumentos:
   p: Puntero a players a comprobar si esta vacio
 Return:
   BOOL que nos indica si esta vacia o no
 *******************************************************************************/
 BOOL players_isempty(const Players *p) {
    if (p==NULL)
      return TRUE;
    if (p->tope==0)
      return TRUE;

    return FALSE;
}

/*******************************************************************************
Funcion: players_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de players (devuelve el ultimo)
Argumentos:
  p: puntero a la estructura de la que se extraera el Player
Return:
  Puntero a estructura de tipo Player
*******************************************************************************/
Player * players_pop(Players *p) {
    Player *temp;
    if (p==NULL)
      return NULL;

    if (players_isempty(p) == TRUE)
      return NULL;

    p->tope--;
    temp = player_copy(p->player[p->tope]);
    player_destroy (p->player[p->tope]);

    return temp;
}
/*******************************************************************************
Funcion: players_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Players introducida
Argumentos:
  p: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void players_print(const Players *p) {
    int n;
   /*compruebo los argumentos*/
   if (p == NULL || p->player == NULL || p->tope == 0)
    return 0;
  for (n=(p->tope-1);n>=0;n++){
    player_print(s->player[n]);
  }
}

/*******************************************************************************
Funcion: objects_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un una estructura Objects,
  e inicializa sus campos a NULL
Argumentos:
  Ninguno
Return:
  Puntero a estructura de tipo Objects
*******************************************************************************/
Objects * objects_create() {
   Objects *o;
   int i;
   o = (Objects*)calloc(1,sizeof(Objects));
   if (o==NULL)
     return NULL;

   o->tope = 0;

   for (i=0; i<MAX_OBJECTS; i++)
       o->object[i] = NULL;
   return o;
}
/*******************************************************************************
Funcion: objects_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumento
y la pone a NULL
Argumentos:
  o: Puntero a estructura tipo Objects
Return:
  Nada (tipo void)
*******************************************************************************/
void objects_destroy(Objects *o) {
    int i;
    if (o==NULL)
      return;

    for (i=0; i<o->tope; i++)
        object_destroy (o->object[i]);

    free(o);
    o = NULL;
}
/*******************************************************************************
Funcion: objects_add
Autor: Arturo Morcillo
Descripcion: Añade un jugador a la estructura Objects
Argumentos:
  o: Puntero a la estructura objects
  object: EL objeto a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS objects_add(Objects *o, const Object *object) {
    if (o==NULL || object==NULL)
      return ERROR;
    if ( o->tope == MAX_OBJECTS-1)
      return ERROR;

    p->object[o->tope] = object_copy(object);
    if (o->object[p->tope]==NULL)
      return ERROR;

    o->tope++;
    return OK;
 }
 /*******************************************************************************
 Funcion: objects_isempty
 Autor: Arturo Morcillo
 Descripcion: Comprueba si la estructura introducida esta vacia
 Argumentos:
   o: Puntero a objects a comprobar si esta vacio
 Return:
   BOOL que nos indica si esta vacia o no
 *******************************************************************************/
 BOOL objects_isempty(const Objects *o) {
    if (o==NULL)
      return TRUE;
    if (o->tope==0)
      return TRUE;

    return FALSE;
}

/*******************************************************************************
Funcion: players_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de objects (devuelve el ultimo)
Argumentos:
  o: puntero a la estructura de la que se extraera el Object
Return:
  Puntero a estructura de tipo Object
*******************************************************************************/
Object * objects_pop(Objects *o) {
    Object *temp;
    if (o==NULL)
      return NULL;

    if (objects_isempty(o) == TRUE)
      return NULL;

    o->tope--;
    temp = object_copy(o->object[o->tope]);
    object_destroy (o->object[o->tope]);

    return temp;
}
/*******************************************************************************
Funcion: objects_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Objectss introducida
Argumentos:
  o: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void objects_print(const Object *o) {
    int n;
   /*compruebo los argumentos*/
   if (o == NULL || o->object == NULL || o->tope == 0)
    return;
  for (n=(o->tope-1);n>=0;n++){
    object_print(s->player[n]);
  }
}

/*******************************************************************************
Funcion: spaces_create
Autor: Arturo Morcillo
Descripcion: Reserva memoria (vacía por calloc) para un una estructura Spaces,
  e inicializa sus campos a NULL
Argumentos:
  Ninguno
Return:
  Puntero a estructura de tipo Spaces
*******************************************************************************/
Spaces * spaces_create() {
   Spaces *s;
   int i;
   s = (Spaces*)calloc(1,sizeof(Spaces));
   if (s==NULL)
     return NULL;

   s->tope = 0;

   for (i=0; i<MAX_PLAYERS; i++)
       s->space[i] = NULL;
   return p;
}
/*******************************************************************************
Funcion: spaces_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria de la estructura introducida como argumenro
y la pone a NULL
Argumentos:
  s: Puntero a estructura tipo Spaces
Return:
  Nada (tipo void)
*******************************************************************************/

void spaces_destroy(Spaces *s) {
   int i;
   if (s==NULL)
     return;

   for (i=0; i<s->tope; i++)
       space_destroy (s->space[i]);

   free(s);
   s = NULL;
}

/*******************************************************************************
Funcion: spaces_add
Autor: Arturo Morcillo
Descripcion: Añade un espacio a la estructura Spaces
Argumentos:
  p: Puntero a la estructura space
  space: EL espacio a añadir
Return:
  Un Status que indica si la funcion ha ido bien o no
*******************************************************************************/
STATUS spaces_add(Spaces *s, const Space *space) {
   if (s==NULL || space==NULL)
     return ERROR;
   if ( s->tope == MAX_SPACES-1)
     return ERROR;

   s->space[p->tope] = space_copy(space);
   if (s->space[s->tope]==NULL)
     return ERROR;

   s->tope++;
   return OK;
}
/*******************************************************************************
Funcion: players_isempty
Autor: Arturo Morcillo
Descripcion: Comprueba si la estructura introducida esta vacia
Argumentos:
  s: Puntero al Spaces a comprobar si esta vacio
Return:
  BOOL que nos indica si esta vacia o no
*******************************************************************************/

BOOL spaces_isempty(const Spaces *s) {
   if (s==NULL)
     return TRUE;
   if (s->tope==0)
     return TRUE;

   return FALSE;
}

/*******************************************************************************
Funcion: spaces_pop
Autor: Arturo Morcillo
Descripcion: sacas un elemento del array de spaces (devuelve el ultimo)
Argumentos:
  s: puntero a la estructura de la que se extraera el Space
Return:
  Puntero a estructura de tipo Space
*******************************************************************************/
Space * spaces_pop(Spaces *s) {
   Space *temp;
   if (s==NULL)
     return NULL;

   if (spaces_isempty(s) == TRUE)
     return NULL;

   s->tope--;
   temp = space_copy(s->space[s->tope]);
   space_destroy (s->space[s->tope]);

   return temp;
}
/*******************************************************************************
Funcion: spaces_print
Autor: Arturo Morcillo
Descripcion:  imprimir todos los elementos de la estructura Spaces introducida
Argumentos:
  p: puntero a la estructura a imprimir
Return:
  Nada (tipo void)
*******************************************************************************/
void spaces_print(const Spaces *s) {
   int n;
  /*compruebo los argumentos*/
  if (s == NULL || s->space == NULL || s->tope == 0)
   return;
 for (n=(s->tope-1);n>=0;n++){
   space_print(s->player[n]);
 }
}
