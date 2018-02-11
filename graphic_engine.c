/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "graphic_engine.h"


/* Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
Area es una estructura con posiciones y tamaños de las mismas. */
struct _Graphic_engine {
  Area *map,
       *descript,
       *banner,
       *help,
       *feedback;
};


/*******************************************************************************
Funcion: graphic_engine_create
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
  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}


/*******************************************************************************
Funcion: graphic_engine_destroy
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

  /* Destruye cada area de la pantalla  */
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  /* Libera la memoria */
  screen_destroy();
  free(ge);
}


/*******************************************************************************
Funcion: graphic_engine_paint_game
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
  char obj='\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];

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
    if (game_get_object_location(game) == id_back)
      obj='*';
    else
      obj=' ';

    if (id_back != NO_ID) {
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla actual.
    Tendrá un "*" si en la casilla hay un objeto */
    if (game_get_object_location(game) == id_act)
      obj='*';
    else
      obj=' ';

    if (id_act != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla siguiente.
    Tendrá un "*" si en la casilla hay un objeto */
    if (game_get_object_location(game) == id_next)
      obj='*';
    else
      obj=' ';

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
    }
  }


  /* Dibuja el area de descripcion (description) */
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game)) != NO_ID){
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }

  /* Dibuja el area del banner */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Dibuja el area de help */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     following or f, previous or p, or exit or e");
  screen_area_puts(ge->help, str);

  /* Dibuja el area de feedback */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
