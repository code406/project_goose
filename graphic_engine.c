#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"

/*
estructura _Graphic_engine. consta de 5 parametros tipo area que son
map, descript, banner, help y feedback y todos son punteros
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
Descripcion: Se encarga de destruir y de volverle a asignar al tablero sus componentes.
Argumentos:
  Ninguno
Return:
  Devuelve un puntero a estructura de punteros de tipo Area
*******************************************************************************/
Graphic_engine *graphic_engine_create()
{
  /*
  Al ser static, conservará el ultimo valor asignado
  Se comprueba si ya se ha creado el graphic_engine.
  Si es así, no se vuelve a crear y se devuelve el ge
  */
  static Graphic_engine *ge = NULL;
  if (ge)
    return ge;

  /*aqui se inicializan los parametros de todas las variables de gr (tipo Graphic_engine)*/
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
Descripcion: Se encarga de destruir cada area de la pantalla
Argumentos:
  un puntero a Graphic_engine (ge)
Return:
  nada (tipo void)
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge)
{
  /* Si no hace falta destruirlo, return */
  if (!ge)
    return;

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
Descripcion: Se encarga de dibujar cada area del juego.
Argumentos:
  un puntero a Graphic_engine (ge) y un puntero a Game (game)
Return:
  nada (tipo void)
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
    /* Obtiene la posicion actual, previa y siguiente */
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    /*TODO: Comprobar los comentarios como el siguiente (son 3) */
    /* Dibuja un "*" si la posicion previa coincide con la de un objeto */
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


    /* Dibuja un "*" si la posicion actual coincide con la de un objeto */
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


    /* Dibuja un "*" si la posicion siguiente coincide con la de un objeto */
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
  sprintf(str, "     following or f, previous or p, exit or e, get or g, drop or d");
  screen_area_puts(ge->help, str);

  /* Dibuja el area de feedback */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
