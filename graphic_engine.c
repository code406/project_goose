/**
 * @brief Motor grafico (interfaz de juego)
 *
 * @file graphic_engine.h
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 17-02-2017
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "graphic_engine.h"
#include "die.h"

#define N_OBJ 4


/*
Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
Cada parametro es un puntero a estructura de tipo Area, que contiene
posiciones y tamaños de areas de la interfaz.
*/
struct _Graphic_engine
{
  Area *map,
       *descript,
       *banner,
       *help,
       *feedback;
};


/*******************************************************************************
Funcion: graphic_engine_create
Autor: David Palomo
Descripcion: Genera y define cada area de la interfaz de juego
Argumentos:
  Ninguno
Return:
  Puntero a la estructura de tipo Graphic_engine inicializada,
  que contiene a su vez punteros a estructura de tipo Area
*******************************************************************************/
Graphic_engine *graphic_engine_create()
{
  /* Al ser static, conservará el ultimo valor asignado.
  Se comprueba si ya se ha creado el graphic_engine.
  Si es así, no se vuelve a crear y se devuelve el ge */
  static Graphic_engine *ge = NULL;
  if (ge)
    return ge;

  /* Se inicializa la pantalla y se reserva memoria para el graphic engine */
  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  /* Define areas y tamaños para cada seccion */
  ge->map      = screen_area_init( 1, 1, 48, 23);
  ge->descript = screen_area_init(50, 1, 29, 23);
  ge->banner   = screen_area_init(28,25, 23,  1);
  ge->help     = screen_area_init( 1,26, 78,  2);
  ge->feedback = screen_area_init( 1,29, 78,  3);

  return ge;
}


/*******************************************************************************
Funcion: graphic_engine_destroy
Autor: David Palomo
Descripcion: Destruye (libera memoria) cada area de la interfaz de juego
Argumentos:
  ge: Puntero a una estructura de tipo Graphic_engine,
      que contiene a su vez punteros a estructura de tipo Area
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge)
{
  /* Si no hace falta destruirlo, return */
  if (!ge)
    return;

  /* Libera la memoria reservada para cada area de la pantalla  */
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  /* Libera la memoria de screen y del graphic_engine */
  screen_destroy();
  free(ge);
}


/*******************************************************************************
Funcion: graphic_engine_paint_game
Autor: David Palomo
Descripcion: Dibuja cada area de la interfaz del juego
Argumentos:
  ge  : Puntero a una estructura de tipo Graphic_engine,
        que contiene a su vez punteros a estructura de tipo Area
  game: Puntero a una estructura de tipo Game
Return:
  Ninguno (void)
*******************************************************************************/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space* space_act = NULL;
  char* obj[N_OBJ];
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];
  int i;

  for (i=0; i<N_OBJ; i++)
  {
    obj[i] = "  ";
  }

  /* Resetea el mapa y dibuja el area interior del mapa */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    /* Obtiene la estructura de tipo Space para id_act (casilla actual),
    y el id de las casillas anterior y siguiente respecto del jugador */
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);


    /* Dibuja la casilla anterior.
    Tendrá un "*" si en la casilla hay un objeto */
    /*Tengo que comprobar todos los objetos*/

    /*
    for (i=0; i<MAX_ID && game->object[i]!= NULL && !strcmp(obj[i],"  "); i++){
      if (game_get_object_location(game,game->object[i]) == id_back){
        obj[i] = object_get_name(game->object[i]);
      }
    }
    */

    if (id_back != NO_ID) {
      sprintf(str, "  |                 %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %s  %s  %s  %s   |",obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla actual.
    Tendrá un "*" si en la casilla hay un objeto */
    /*
    for (i=0; i<MAX_ID && game->object[i]!= NULL && !strcmp(obj[i],"  "); i++){
      if (game_get_object_location(game,game->object[i]) == id_act){
        obj[i] = object_get_name(game->object[i]);
      }
    }
    */

    if (id_act != NO_ID) {
      sprintf(str, "  +-------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D              %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %s  %s  %s  %s   |",obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-------------------+");
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla siguiente.
    Tendrá un "*" si en la casilla hay un objeto */
    /*
    for (i=0; i<MAX_ID && game->object[i]!= NULL && !strcmp(obj[i],"  "); i++){
      if (game_get_object_location(game,game->object[i]) == id_next){
        obj[i] = object_get_name(game->object[i]);
      }
    }
    */

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-------------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                   |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %s  %s  %s  %s   |",obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
    }
  }


  /* Dibuja el area de descripcion (description) */
  screen_area_clear(ge->descript);
  sprintf(str, " Object location:");
  screen_area_puts(ge->descript, str);
  for (i=0;i<MAX_ID && game->object[i]!= NULL;i++)
  {
    if ((obj_loc = game_get_object_location(game,game->object[i])) != NO_ID)
    {
      sprintf(str, "    %s:%d",object_get_name(game->object[i]), (int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }
  sprintf(str, " Player items:");
  screen_area_puts(ge->descript, str);
  for (i=0;i<MAX_ID && game->object[i]!= NULL;i++)
  {
    if ((obj_loc = game_get_object_player(game, game->object[i])) != FALSE)
    {
      sprintf(str, "    %s",object_get_name(game->object[i]));
      screen_area_puts(ge->descript, str);
    }
  }

  sprintf(str, " Last die value: %d", die_get_last_roll(game->die));
  screen_area_puts(ge->descript, str);



  /* Dibuja el area del banner */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Dibuja el area de help */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "    following(f) previous(p) right(r) left(l) get(g) drop(d) roll(x) exit(e)");
  screen_area_puts(ge->help, str);

  /* Dibuja el area de feedback */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s %s", cmd_to_str[last_cmd-NO_CMD],game->param);
  screen_area_puts(ge->feedback, str);

  /* Pasa a la terminal */
  screen_paint();
  printf("prompt:> ");
}
