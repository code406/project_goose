/**
 * @artiimor Se encarga de definir a un jugador y las
 *funciones asociadas a los jugadores.
 * @file player.c
 * @author Arturo Morcillo
 * @version 1.0
 * @date 08-02-2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "player.h"
 #include "types.h"
 #include "space.h"

 struct _Player{
   Id id;
   char name[WORD_SIZE+1];
   Space location;
   Object item;
 };

/*
Funcion que devuelve un puntero a Player y cuyo argumento es un ID
Se encarga de crear un nuevo player. Reserva memoria para él, le
aasigna la id y lo inicializa a 0 (con calloc).
*/
 Player *player_create(Id id){
   Player *newPlayer;
   /*Compruebo el argumento*/
   if(!id)
    return NULL;

    /*Asigno memoria para newPlayer, compruebo que se
    ha asignado bien y como uso calloc está inicializada
    a NULL*/
  if(!(newPlayer = (Player*)calloc(sizeof(Player))))
    return NULL;

  newPlayer->id = id;

  return newPlayer;

 }

/*
Funcion  que devuelve un STATUS y cuyo argumento es un puntero a player
se encarga de liberar memoria para el argumento introducido y de ponerlo a NULL.
Si algo falla devuelve ERROR
*/
 STATUS player_destroy (Player *player){
   if (!player)
    return ERROR;

  free(player);
  player = NULL;


  return OK;
 }
 /*
 Funcion que devuelve un STATUS y cuyo argumentos son
 un puntero a Player y una cadena de caracteres.
 Le asigna a player.name la cadena de caracteres introducida
 como argumento
 */
 STATUS player_set_name(Player* player, char* name) {
   /*Comprueba los argumentos*/
   if (!player || !name) {
     return ERROR;
   }
   /*
   Le asigna a  player.name el nombre introducido
   y lo comprueba
   */
   if (!strcpy(player->name, name)) {
     return ERROR;
   }
   /*Si todo va bien devuelve OK*/
   return OK;
 }
 /*
 Funcion que devuelve un STATUS y cuyo argumentos son
 un puntero a Player y una estructura tipo Space.
 Le asigna a player.location la cadena de caracteres introducida
 como argumento
 */
 STATUS player_set_location(Player* player, Space location) {
   /*Comprueba los argumentos*/
   if (!player || !location) {
     return ERROR;
   }
   player->location = location;
   }
   /*Si todo va bien devuelve OK*/
   return OK;
 }
 /*
 Funcion que devuelve un STATUS y cuyo argumentos son
 un puntero a Player y una estructura tipo object.
 Le asigna a player.object la estructura introducida
 como argumento
 */
 STATUS player_set_object(Player* player, Object object) {
   /*Comprueba los argumentos*/
   if (!player || !object) {
     return ERROR;
   }
   player->item = object;
   }
   /*Si todo va bien devuelve OK*/
   return OK;
 }

 /*
 Devuelve un puntero a char;
 Su argumento es un puntero a Player
 Devuelve el nombre del espjugador (player.name)
 Si algo falla devuelve NULL
 */
 const char * player_get_name(Player* player) {
   if (!player) {
     return NULL;
   }
   return player->name;
 }

 /*
 Devuelve un id;
 Su argumento es un puntero a Player
 Devuelve el id del jugador (player.id)
 Si algo falla devuelve NULL
 */
 Id player_get_id(player* player) {
   if (!player) {
     return NO_ID;
   }
   return player->id;
 }

 /*
 Devuelve una estructura tipo Space;
 Su argumento es un puntero a Player
 Devuelve el espacio del jugador (player.location)
 Si algo falla devuelve NULL
 */
 Space *player_get_location(player* player) {
   if (!player) {
     return NULL;
   }
   return player->location;
 }

 /*
 Devuelve una estructura tipo Object;
 Su argumento es un puntero a Player
 Devuelve un puntero al objeto del jugador (player.item)
 Si algo falla devuelve NULL
 */
 Space *player_get_item(player* player) {
   if (!player) {
     return NULL;
   }
   return player->item;
 }

 /*
 Devuelve un Status (ERROR = 0, OK = 1);
 Su argumento es un puntero a Player
 Si algo falla devuelve ERROR
 Muestra por pantalla:
   -El nombre y el id;
   -Si tiene objeto.

   Si se quisieran conocer las caracteristicas del objeto
   o del espacio se utilizarian otras funciones.
 */
 STATUS player_print(Player* player) {

   if (!player) {
     return ERROR;
   }

   fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

   if (player_get_object(player)) {
     fprintf(stdout, "---> The player has an item.\n");
   } else {
     fprintf(stdout, "---> The player has no item.\n");
   }

   return OK;
 }
