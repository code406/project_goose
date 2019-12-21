/**
 * @brief Define la interfaz publica del motor grafico, necesario para generar los elementos
 *        necesarios para mostrar el estado del juego.
 *
 * @file graphic_engine.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "screen.h"
#include "space.h"
#include "graphic_engine.h"
#include "game.h"
#include "object.h"
#include "dialogue.h"

#define MAX_STR 255 /*!<Longitud maxima de la cadena str empleada en graphic_engine_paint_game*/
#define SPACE_WIDTH 59 /*!<Ancho de la casilla pintada en graphic_engine*/
#define MAX_MOV 5 /*!<Numero de movimientos hasta que se proporciona una pista*/
#define MAX_NOTES 12
#define MAX_NA 3
#define MAX_DAYS 5

/**
* @struct _Graphic_engine
* @brief Estructura que define el Graphic_engine, con punteros a las areas de la interfaz.
* Cada parametro es un puntero a estructura de tipo Area, que contiene
* posiciones y tamaños de areas de la interfaz.
*/
struct _Graphic_engine
{
  Area *map, /*!< Area de impresion del mapa*/
       *banner, /*!<Area de impresion del banner*/
       *help, /*!<Area de impresion de la ayuda*/
       *feedback, /*!<Area de impresion del feedback*/
       *rightpanel, /*!<Area de impresion del panel derecho*/
       *check, /*!<Area de impresion de descripciones (ckeck)*/
       *hints; /*!<Area de impresion de pistas de game_rules*/
};

/*******************************************************************************
 *              IMPLEMENTACION DE LA INTERFAZ GRAPHIC_ENGINE
 ******************************************************************************/

/*******************************************************************************
*	Crea e inicializa cada area de la interfaz de juego
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
  ge->map      = screen_area_init( 1, 1, 78, 26);
  ge->banner   = screen_area_init(19,28, 40,  1);
  ge->help     = screen_area_init( 1,29, 78,  2);
  ge->feedback = screen_area_init( 1,32, 78,  3);
  ge->rightpanel = screen_area_init(81,1,69, 25);
  ge->check    = screen_area_init(81,27, 69, 4);
  ge->hints    = screen_area_init(81,32, 69,  3);
                              /*x0, y0, Ancho, Alto*/
  return ge;
}

/*******************************************************************************
*	Destruye (libera memoria) cada area de la interfaz de juego
*******************************************************************************/
void graphic_engine_destroy(Graphic_engine *ge)
{
  /* Si no hace falta destruirlo, return */
  if (!ge)
    return;

  /* Libera la memoria reservada para cada area de la pantalla  */
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_area_destroy(ge->rightpanel);
  screen_area_destroy(ge->check);
  screen_area_destroy(ge->hints);

  /* Libera la memoria de screen y del graphic_engine */
  screen_destroy();
  free(ge);
}

/*******************************************************************************
*	 Dibuja cada area de la interfaz del juego
*******************************************************************************/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_left = NO_ID, id_right = NO_ID;
  Space* space_act = NULL;
  Space* space_prev = NULL;
  Space* space_next = NULL;
  Id object_aux = NO_ID;
  char* obj[MAX_ID];
  char str[MAX_STR];
  int i;
  int j;
  int printpos; /*Almacenará el numero de caracteres impresos por sprintf*/
  char *gdesc[MAX_GDESC];
  const char* status;
  /*Cadenas de game_rules*/
  char *notes[MAX_NOTES];
  char *next_action[MAX_DAYS][MAX_NA];
  Dialogue* dialogue = NULL;

  dialogue = dialogue_create("dialogue.dat");
  dialogue_set_last_cmd(dialogue,game);
  dialogue_set_last_cmd_status (dialogue, game);
  dialogue_load_parts(dialogue);
  dialogue_set_caso(dialogue,game);


  /*Dia 1*/
  next_action[0][0] = "A true gentleman can't work with an empty belly. Let's head to the    cafeteria and have some lunch.";
  next_action[0][1] = "I shall ask questions to the hotel owner. He may help me out with      the case. He might be in his office.";
  next_action[0][2] = "A true gentleman knows when it's time to sleep";
  /*Dia 2*/
  next_action[1][0] = "The cleaning staff might have a master key to open rooms";
  next_action[1][1] = "Rooms seem to be occupied, but there's nobody in the cleaning room    right now.";
  next_action[1][2] = "A true gentleman knows when it's time to sleep";
  /*Dia 3*/
  next_action[2][0] = "I need to investigate all rooms, evidence awaits!";
  next_action[2][1] = "So many Boticolas around make a gentleman thirsty! Let's get          something to drink from the minibar";
  next_action[2][2] = "A true gentleman knows when it's time to sleep";
  /*Dia 4*/
  next_action[3][0] = "I think something went unnoticed in the cleaning room...";
  next_action[3][1] = "A true gentleman knows when it's time to sleep";
  /*Final*/
  next_action[4][0] = "Comstock argues with a Spanish man in the backyard. They woke me up.   My window looks out on the backyard...";
  /*Muestra las notas que va tomando el profesor*/
  notes[0] = "As a favor in return to inspector Grosky, I have to investigate           the Satoshi Hotel. The owners' income has ecalated quickly,          in a very suspicious way. Are they laundering money? ";
  notes[1] = "This hotel ONLY serves Boticolas. They've some sort of agreement          with the 'Boti Inc.' brand, I guess.";
  notes[2] = "The hotel owner is Zackary James Comstock, one peculiar gentleman";
  notes[3] = "Hmm... Comstock's stick feels extremely sticky! (No pun intended)";
  notes[4] = "I bet the cleaning staff have a master key that opens every room.";
  notes[5] = "There are a lot of empty Boticola bottles in the cleaning room. ";
  notes[6] = "Word puzzle! If you change the order of the letters of 'Boti Inc',        you get the word 'Bitcoin'! How curious!";
  notes[7] = "The label in the bottles I found in my minibar is very badly stuck.       There's even a bit of glue residue...";
  notes[8] = "The note said 'Barrer hacia dentro'. 'Barrer' is the Spanish word         for 'sweep'. Does this lead us back to the cleaning room?";
  notes[9] = "A hidden room full of computers! That's what the note meant!";
  notes[10] = "Why so many computers? Are they automating some kind of process?";
  notes[11] = "That makes sense! Comstock mined Bitcoin on those PCs, and passed        the money through the bottles, with printed codes on labels!         The fake labels were swapped and stuck! CASE SOLVED!";


  /* Resetea el mapa y dibuja el area interior del mapa */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    /* Obtiene la estructura de tipo Space para id_act (casilla actual),
    y el id de las casillas anterior y siguiente respecto del jugador */
    space_act = game_get_space(game, id_act);
    id_back = game_get_space_north(game, id_act);
    id_next = game_get_space_south(game, id_act);
    id_left = game_get_space_west(game, id_act);
    id_right = game_get_space_east(game, id_act);

    /* Dibuja la casilla actual, con los objetos y una descripcion ASCII */
    for (i=0; i<MAX_ID; i++)
    {
      obj[i] = "  ";
    }

    for (i=0, j=0; i<=MAX_ID; i++)
    {
      object_aux = game_get_object_id_at(game, i);
      if(object_aux != NO_ID)
      {
        if (game_get_object_location(game, object_aux) == id_back)
        {
          obj[j] = object_get_name(game_get_object(game, object_aux));
          j++;
        }
      }
    }

    /* Dibuja la casilla anterior, con los objetos y una descripcion ASCII */
    if (id_back != NO_ID)
    {
      space_prev = game_get_space(game, id_back);
      for(i=0; i<MAX_GDESC; i++)
        gdesc[i] = space_get_gdesc(space_prev,i);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos], " %s",space_get_description(space_prev));
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
      printpos += sprintf(&str[printpos], "|");
      screen_area_puts(ge->map, str);

      for (j=2; j<MAX_GDESC; j++){
        printpos = sprintf(str, "                 |");
        printpos += sprintf(&str[printpos], "%s",gdesc[j]);
        for(i=printpos; i<SPACE_WIDTH; i++) printpos+=sprintf(&str[i], " ");
        printpos += sprintf(&str[i], "|");
        screen_area_puts(ge->map, str);
      }

      printpos = sprintf(str, "                 |");
      for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
      printpos += sprintf(&str[printpos], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos], "  %s  %s  %s  %s",obj[0], obj[1], obj[2], obj[3]);
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos-1], "+-----------------------------------------+");
      screen_area_puts(ge->map, str);

      sprintf(str, "                            ^ %s", link_get_name(game_get_link(game, space_get_north_link(space_act))));
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla actual, con los objetos y una descripcion ASCII */
    for (i=0; i<MAX_ID; i++)
    {
      obj[i] = "  ";
    }

    for (i=0, j=0; i<=MAX_ID; i++)
    {
      object_aux = game_get_object_id_at(game, i);
      if(object_aux != NO_ID)
      {
        if (game_get_object_location(game, object_aux) == id_act && game_check_object_player(game, game_get_object(game, object_aux)) != TRUE && object_get_hidden(game_get_object(game, object_aux)) != TRUE)
        {
          obj[j] = object_get_name(game_get_object(game, object_aux));
          j++;
        }
      }
    }

    if (id_act != NO_ID)
    {
      for(i=0; i<MAX_GDESC; i++)
        gdesc[i] = space_get_gdesc(space_act,i);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos-1], "+-----------------------------------------+");
      screen_area_puts(ge->map, str);
      /* Casillas a ambos lados */
      if (id_left != NO_ID && id_right != NO_ID)
      {
        printpos = sprintf(str, "     %10s  |", link_get_name(game_get_link(game, space_get_west_link(space_act))));
        printpos += sprintf(&str[printpos], " %s",space_get_description(space_act));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[i], "|");
        printpos = sprintf(&str[printpos], "  %s", link_get_name(game_get_link(game, space_get_east_link(space_act))));
        screen_area_puts(ge->map, str);

        printpos = sprintf(str, "  %10s <-- |", space_get_name(game_get_space(game, game_get_space_west(game, id_act))));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[printpos], "|");
        sprintf(&str[printpos], " --> %s", space_get_name(game_get_space(game, game_get_space_east(game, id_act))));
        screen_area_puts(ge->map, str);
      }
      /* Casilla en el lado izquierdo */
      else if (id_left != NO_ID && id_right == NO_ID)
      {
        printpos = sprintf(str, "     %10s  |", link_get_name(game_get_link(game, space_get_west_link(space_act))));
        printpos += sprintf(&str[printpos], " %s",space_get_description(space_act));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[i], "|");
        screen_area_puts(ge->map, str);

        printpos = sprintf(str, "  %10s <-- |", space_get_name(game_get_space(game, game_get_space_west(game, id_act))));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[printpos], "|");
        screen_area_puts(ge->map, str);
      }
      /* Casilla en el lado derecho */
      else if (id_left == NO_ID && id_right != NO_ID)
      {
        printpos = sprintf(str, "                 |");
        printpos += sprintf(&str[printpos], " %s",space_get_description(space_act));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[i], "|");
        if(space_get_lit(game_get_space(game, id_act)) == TRUE)
          printpos = sprintf(&str[printpos], "  %s", link_get_name(game_get_link(game, space_get_east_link(space_act))));
        screen_area_puts(ge->map, str);

        printpos = sprintf(str, "                 |");
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[printpos], "|");
        if(space_get_lit(game_get_space(game, id_act)) == TRUE)
          sprintf(&str[printpos], " --> %s", space_get_name(game_get_space(game, game_get_space_east(game, id_act))));
        screen_area_puts(ge->map, str);
      }
      /* Sin casillas a los lados */
      else
      {
        printpos = sprintf(str, "                 |");
        printpos += sprintf(&str[printpos], " %s",space_get_description(space_act));
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[printpos], "|");
        screen_area_puts(ge->map, str);

        printpos = sprintf(str, "                 |");
        for(i=printpos; i<SPACE_WIDTH; i++) printpos += sprintf(&str[i], " ");
        printpos += sprintf(&str[printpos], "|");
        screen_area_puts(ge->map, str);
      }

      for(j=0; j<MAX_GDESC; j++){
        printpos = sprintf(str, "                 |");
        printpos += sprintf(&str[printpos], "%s",gdesc[j]);
        for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
        sprintf(&str[i], "|");
        screen_area_puts(ge->map, str);
      }

      printpos = sprintf(str, "                 |");
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos], "   _~_");
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos], "  %s  %s  %s  %s",obj[0], obj[1], obj[2], obj[3]);
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos-1], "+-----------------------------------------+");
      screen_area_puts(ge->map, str);
    }


    /* Dibuja la casilla siguiente, con los objetos y una descripcion ASCII */
    if (id_next != NO_ID) {
      space_next = game_get_space(game, id_next);
      for(i=0; i<MAX_GDESC; i++)
        gdesc[i] = space_get_gdesc(space_next,i);

      sprintf(str, "                            v %s", link_get_name(game_get_link(game, space_get_south_link(space_act))));
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos-1], "+-----------------------------------------+");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      printpos += sprintf(&str[printpos], " %s",space_get_description(space_next));
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      printpos = sprintf(str, "                 |");
      for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
      sprintf(&str[i], "|");
      screen_area_puts(ge->map, str);

      for(j=0; j<MAX_GDESC-2; j++){
        printpos = sprintf(str, "                 |");
        printpos += sprintf(&str[printpos], "%s",gdesc[j]);
        for(i=printpos; i<SPACE_WIDTH; i++) sprintf(&str[i], " ");
        sprintf(&str[i], "|");
        screen_area_puts(ge->map, str);
      }
    }
  }



  /* Dibuja el area del banner */
  screen_area_puts(ge->banner, " Professor Triton and the Cryptic Hotel ");


  /* Dibuja el area de help */
  screen_area_clear(ge->help);
  sprintf(str, " Command list:  move(m)   get(g)   drop(d)   check(c)   open(o)   showmap(sm)");
  screen_area_puts(ge->help, str);
  sprintf(str, "                turnon(to)     turnoff(tf)   save(s)    load(l)   exit(e)");
  screen_area_puts(ge->help, str);


  /* Dibuja el area de feedback */
  screen_area_clear(ge->feedback);
  status = dialogue_get_last_cmd_status(dialogue);

  command_print(game_get_command(game));

  printf("%s",command_get_direction(game_get_command(game)));


  if (game_get_last_command(game) == UNKNOWN){
    sprintf(str, " %s", dialogue_get_part1(dialogue));
    screen_area_puts(ge->feedback, str);
  }
  else if (game_get_last_command(game) == SHOWMAP){
    if(strcmp(status, "ERROR") == 0){
      sprintf(str, " You can't open the map because you don't have it in your bag");
      screen_area_puts(ge->feedback, str);
    }
    else{
      sprintf(str, " The hotel map is being displayed");
      screen_area_puts(ge->feedback, str);
    }
  }
  else if(game_get_last_command(game) == FOLLOWING || game_get_last_command(game) == PREVIOUS || game_get_last_command(game) == LEFT || game_get_last_command(game) == RIGHT){
      sprintf(str, " That command is not listed... Perhaps you are a dev?");
      screen_area_puts(ge->feedback, str);
  }
  else if(game_get_last_command(game) == NO_CMD){
    sprintf(str, " ");
    screen_area_puts(ge->feedback, str);
  }
  else if(strcmp(status, "OK") == 0){
    if (game_get_last_command(game) == MOVE){
      sprintf(str, " %s %s %s", dialogue_get_part1(dialogue), command_get_direction(game_get_command(game)), dialogue_get_part2(dialogue));
      screen_area_puts(ge->feedback, str);
    }
    else{
      sprintf(str, " %s %s %s", dialogue_get_part1(dialogue), command_get_obj_name(game_get_command(game)), dialogue_get_part2(dialogue));
      screen_area_puts(ge->feedback, str);
    }
  }
  else{
    printf("%d",dialogue_get_caso(dialogue));
    if (command_get_t_cmd(game_get_command(game)) == MOVE){
      sprintf(str, " %s %s %s %s", dialogue_get_part1(dialogue), command_get_direction(game_get_command(game)), dialogue_get_part2(dialogue), dialogue_get_part3(dialogue, dialogue_get_last_cmd(dialogue), dialogue_get_caso(dialogue)));
        screen_area_puts(ge->feedback, str);
    }
    else{
      sprintf(str, " %s %s %s %s", dialogue_get_part1(dialogue), command_get_obj_name(game_get_command(game)), dialogue_get_part2(dialogue), dialogue_get_part3(dialogue, dialogue_get_last_cmd(dialogue), dialogue_get_caso(dialogue)));
        screen_area_puts(ge->feedback, str);
    }
  }


  /* Dibuja el area de rightpanel */
  screen_area_clear(ge->rightpanel);
  if (game_get_showmap(game) == 1 && strcasecmp(command_get_status(game_get_command(game)),"OK")==0){
    sprintf(str, " ");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "   _Ground Floor_     ____1st Floor (Rooms)____     __2nd Floor_ ");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |     ___      |   |           ___           |   |    ___     |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |    |_L_|     |   |          |_L_|          |   |   |_L_|    |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |    _| |__    |   |   ______  | |  ______   |   |   _ \\_     |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |   |      |   |   |  | 102  \\|   |/  101 |  |   |  |    |_   |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |   |_Hall_|   |   |  |_____| |   | |_____|  |   |  |      |  |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |   _| |_      |   |   ______ |   | ______   |   |  |______|  |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |  |     |     |   |  | 104  \\|   |/  101 |  |   |  Cleaning  |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |  |_Cafe|     |   |  |_____| |___| |_____|  |   |     Room   |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "  |______________|   |_________________________|   |____________|");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, " ");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, " ");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "        ___3rd Floor (Suites)____     ___4th Floor____________");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |           ___           |   |    _________           |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |   _____  |_L_|          |   |   |         |          |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |  |     |  | |   _____   |   |   | Balcony |_______   |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |  | 202  \\|   | |     |  |   |   |________/ Office |  |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |  |_____| |   |/  201 |  |   |            |________|  |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |          |___| |_____|  |   |                        |");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "       |_________________________|   |________________________|");
    screen_area_puts(ge->rightpanel, str);
  }
  else{
    sprintf(str, " Professor's Bag:");
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, " ");
    printpos = 0;
    for (i=0; i<=MAX_ID; i++)
    {
      if((object_aux = game_get_object_id_at(game, i)) != NO_ID)
      {
        if (game_check_object_player(game, game_get_object(game, object_aux)) != FALSE)
        {
          printpos += sprintf(&str[printpos], "   %s", object_get_name(game_get_object(game, object_aux)));
        }
      }
    }
    screen_area_puts(ge->rightpanel, str);
    sprintf(str, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    screen_area_puts(ge->rightpanel, str);


    sprintf(str, " Professor's Notes:");
    screen_area_puts(ge->rightpanel, str);
    for(i=-1; i<=game_get_game_rules_notes(game); i++){
      sprintf(str, "   %s", notes[i+1]);
      screen_area_puts(ge->rightpanel, str);
    }
  }


  /* Dibuja el area de descripcion (check) */
  screen_area_clear(ge->check);
  if (strcmp(game_get_object_description(game)," ")!=0)
  {
    sprintf(str, "  %s", game_get_object_description(game));
    screen_area_puts(ge->check, str);
  }
  else if (strcmp(game_get_space_long_description(game)," ")!=0)
  {
    sprintf(str, "  %s", game_get_space_long_description(game));
    screen_area_puts(ge->check, str);
  };


  /* Dibuja el area de pistas (hints) */
  screen_area_clear(ge->hints);
  if (game_get_game_rules_n_cmd(game) > MAX_MOV){
    /*Ese seria pgr->next_action[pgr->days_c][pgr->next_action_c]*/
    sprintf(str, " %s",next_action[game_get_game_rules_day(game)][game_get_game_rules_next_action(game)]);
  }
  else
    sprintf(str, "  ");

  screen_area_puts(ge->hints, str);
  sprintf(str, "  ");
  screen_area_puts(ge->hints, str);


  /* Pasa a la terminal */
  screen_paint();
  printf("prompt:> ");

  dialogue_destroy(dialogue);
}
