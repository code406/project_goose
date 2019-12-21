/**
 * @brief Implementa la interfaz publica del modulo game_rules, necesario para guiar las
 *        acciones del jugador.
 *
 * @file game_rules.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0.E
 * @date   22-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "game_rules.h"
#include "game.h"
#include "command.h"
#include "link.h"
#include "types.h"
#include "die.h"

/**
* @struct _Game_rules
* @brief  Implementacion de la definicion de la estructura Game_rules
*/
struct _Game_rules
{
  int next_action_c; /*!<Contador de la ultima accion realizada*/
  int notes_c; /*!<Contador para saber que notas mostrar*/
  int days_c; /*!<Contador para saber el dia en el que estamos*/
  int n_cmd; /*!<Contador del numero de comandos introducidos por el jugador*/
};

/*******************************************************************************
Crea las game_rules reservando memoria
*******************************************************************************/
Game_rules* game_rules_create(){
  Game_rules *game_rules_aux;

  game_rules_aux = (Game_rules*)calloc(1,sizeof(Game_rules));
  if (game_rules_aux == NULL)
    return NULL;
  /*inicializo los contadores a cero*/
  game_rules_aux->next_action_c = 0;
  game_rules_aux->notes_c = -1;
  game_rules_aux->days_c = 0;
  game_rules_aux->n_cmd = 0;
  /*Va indicando las acciones que debe realizar a continuacion el jugador*/

  return game_rules_aux;
}

/*******************************************************************************
Destruye los datos de las game_rules y libera su memoria
*******************************************************************************/
void game_rules_destroy (Game_rules *pgr){
  if (pgr == NULL)
    return;

  free (pgr);

}

/*******************************************************************************
Fija el valor del contador next_action de game_rules
*******************************************************************************/
STATUS game_rules_set_next_action_c (Game_rules *pgr, int n_a){
  if (pgr == NULL)
    return ERROR;

  pgr->next_action_c = n_a;

  return OK;
}

/*******************************************************************************
Fija el valor del contador notas de game_rules
*******************************************************************************/
STATUS game_rules_set_notes_c (Game_rules *pgr,int notes){
  if (pgr == NULL)
    return ERROR;

  pgr->notes_c = notes;

  return OK;
}

/*******************************************************************************
Fija el valor del contador days de game_rules
*******************************************************************************/
STATUS game_rules_set_days_c (Game_rules *pgr, int days){
  if (pgr == NULL)
    return ERROR;

  pgr->days_c =  days;

  return OK;
}

/*******************************************************************************
Fija el valor del contador del numero de comandos introducidos de game_rules
*******************************************************************************/
STATUS game_rules_set_n_cmd (Game_rules *pgr, int n_cmd){
  if (pgr == NULL)
    return ERROR;

  pgr->n_cmd = n_cmd;

  return OK;
}

/*******************************************************************************
obtiene el valor del contador de next_action de game_rules
*******************************************************************************/
int game_rules_get_next_action_c (Game_rules *pgr){
  if (pgr == NULL)
    return -1;

  return pgr->next_action_c;
}

/*******************************************************************************
obtiene el valor del contador de notes de game_rules
*******************************************************************************/
int game_rules_get_notes_c (Game_rules *pgr){
  if (pgr == NULL)
    return -1;

  return pgr->notes_c;
}

/*******************************************************************************
obtiene el valor del contador de days de game_rules
*******************************************************************************/
int game_rules_get_days_c (Game_rules *pgr){
  if (pgr == NULL)
    return -1;

  return pgr->days_c;
}

/*******************************************************************************
obtiene el valor del contador del numero de comandos introducidos de game_rules
*******************************************************************************/
int game_rules_get_n_cmd (Game_rules *pgr){
  if (pgr == NULL)
    return -1;

  return pgr->n_cmd;
}

/*******************************************************************************
Funcion que se encarga de que el estado del juego avance cuando sucedan determinados eventos
*******************************************************************************/
STATUS game_rules_update (Game *game, Game_rules *pgr){
  D_Command *last_cmd;

  if (pgr == NULL || game == NULL)
    return ERROR;

  last_cmd = game_get_command(game);
  die_roll (game_get_die(game));


  /*Hay que ver si hay que poner una pista*/

  /*Revisar si hay que mostrar alguna nota mas*/
  /*se imprime hasta la nota pgr->notes_c*/
  /*Dia 1*/
  /*Primero hay que ver la cafeteria*/
  if (pgr->days_c == 0){
    if (pgr->notes_c == -1){
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && (strcasecmp(command_get_obj_name(last_cmd), "s") == 0 ||strcasecmp(command_get_obj_name(last_cmd), "space") == 0) && game_get_player_location(game) == 2){
        pgr->notes_c ++;
        pgr->next_action_c++;
        pgr->n_cmd = 0;
      }

    }
    /*Luego hablas con comstock y se abre el link a su campo de cricket*/
    if (pgr->notes_c == 0){
      /*Cuando hablas con comstock*/
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && (strcasecmp(command_get_obj_name(last_cmd), "s") == 0 ||strcasecmp(command_get_obj_name(last_cmd), "space") == 0) && game_get_player_location(game) == 23){
        pgr->notes_c ++;
        /*Se muestra el minicricket*/
        link_set_linked(game_get_link(game, 11),TRUE);
        space_set_lit(game_get_space(game,23),FALSE);
        pgr->n_cmd = 0;
      }
      }
      if (pgr->notes_c == 1){
        /*Cuando usas el palo*/
        if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && (strcasecmp(command_get_obj_name(last_cmd), "CricketStick") == 0) && command_get_t_cmd(last_cmd) == CHECK && game_check_object_player(game,game_get_object(game, 13))){
          pgr->notes_c ++;
          /*Cambian las descripciones y puedes dormir*/
          space_set_lit(game_get_space(game,24),FALSE);
          object_set_moved(game_get_object(game,4),TRUE);
          pgr->next_action_c++;
          pgr->n_cmd = 0;
          }
        }
      /*A dormir. Primer dia finito*/
      if (pgr->notes_c == 2){
        if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Bed") == 0){
          /*Despues de dormir*/
          object_set_moved(game_get_object(game,4),FALSE);
          pgr->next_action_c = 0;
          pgr->days_c++;
          pgr->notes_c++;
          pgr->n_cmd = 0;
          }
        }
  }
  /*Ahora estamos en el segundo dia.*/
  if (pgr->days_c == 1){
    if (pgr->notes_c == 3 && pgr->next_action_c == 0){
      if ((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "CleaningCart") == 0) && (command_get_t_cmd(last_cmd) == CHECK)){
        object_set_hidden(game_get_object(game,15),FALSE);
      }

    }
    /*Coges las Llaves*/
    if (pgr->notes_c == 3 && pgr->next_action_c == 0){
      if (((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "Key") == 0) && (command_get_t_cmd(last_cmd) == GET && game_check_object_player(game,game_get_object(game, 15)))) || player_check_object(game_get_player(game),15)==TRUE){
        pgr->next_action_c ++ ;
        pgr->n_cmd = 0;
        /*La habitacion de layton esta desocupada. Puedes entrar*/
        space_set_ocupada(game_get_space(game,7),FALSE);
      }
    }
    /*Revisas la habitacion de limpieza*/
    if (pgr->notes_c == 3 && pgr->next_action_c == 1){
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && (strcasecmp(command_get_obj_name(last_cmd), "s") == 0 ||strcasecmp(command_get_obj_name(last_cmd), "space") == 0) && game_get_player_location(game) == 11){
        pgr->next_action_c++;
        pgr->notes_c ++;
        object_set_moved(game_get_object(game,4),TRUE);
        pgr->n_cmd = 0;
      }
    }
    if (pgr->notes_c == 4){
      /*A dormir*/
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Bed") == 0){
        object_set_moved(game_get_object(game,4),FALSE);
        pgr->next_action_c = 0;
        pgr->days_c++;
        pgr->n_cmd = 0;
        pgr->notes_c++;
        space_set_ocupada(game_get_space(game,21),FALSE);
        link_set_linked(game_get_link(game,21),FALSE);
        }
      }

  }
  /*Tercer Dia del señor.*/
  if (pgr->days_c == 2){
    if (pgr->next_action_c == 0){
      /*TODO revisar a partir de aqui*/
      /*Cuando revisas la foto*/
      if ((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "RubbishBin") == 0) && (command_get_t_cmd(last_cmd) == CHECK)){
        pgr->next_action_c ++ ;
        pgr->n_cmd = 0;
        /*Tienes que checkear tu minibar. La llave abre luego el link de detras del armario*/
        object_set_hidden(game_get_object(game,18),FALSE);

      }
      if ((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "Note") == 0) && (command_get_t_cmd(last_cmd) == CHECK)){
        pgr->next_action_c ++ ;
        pgr->n_cmd = 0;
        pgr->notes_c++;
        /*Tienes que checkear tu minibar. La llave abre luego el link de detras del armario*/
        object_set_moved(game_get_object(game,1),TRUE);
        object_set_open_link(game_get_object(game,15),9);
      }
    }
    /*Despues de beberte una rica boticola a dormir*/
    if (pgr->next_action_c == 1){
      if ((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "Minibar") == 0) && (command_get_t_cmd(last_cmd) == CHECK)){
        pgr->next_action_c++;
        pgr->notes_c ++;
        object_set_moved(game_get_object(game,2),FALSE);
        pgr->n_cmd = 0;
        object_set_moved(game_get_object(game,4),TRUE);
      }
    }
    /*Duermes*/
    if (pgr->next_action_c == 2){
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Bed") == 0){
        object_set_moved(game_get_object(game,4),FALSE);
        pgr->next_action_c = 0;
        pgr->notes_c ++;
        pgr->days_c++;
        pgr->n_cmd = 0;
        object_set_moved(game_get_object(game,19),TRUE);
        }
      }

  }
  /*Cuarto dia*/
  if (pgr->days_c == 3){
    if (pgr->next_action_c == 0){
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Wardrobe") == 0){
        space_set_lit(game_get_space(game,11),TRUE);
        }
      /*Despues de checkear el cuarto de limpieza*/
      if ((strcasecmp(command_get_status(last_cmd),"OK") == 0) && (strcasecmp(command_get_obj_name(last_cmd), "space") == 0 ||strcasecmp(command_get_obj_name(last_cmd), "s") == 0) && (command_get_t_cmd(last_cmd) == CHECK && game_get_player_location(game) == 12)){
        pgr->next_action_c ++ ;
        pgr->n_cmd = 0;
        pgr->notes_c++;
        object_set_moved(game_get_object(game,4),TRUE);
      }
    }

    if (pgr->next_action_c == 1){
      /*A dormir*/
      if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Bed") == 0){
        object_set_moved(game_get_object(game,4),FALSE);
        pgr->next_action_c = 0;
        pgr->notes_c ++;
        pgr->days_c++;
        pgr->n_cmd = 9000;
        object_set_moved(game_get_object(game,20),TRUE);
        }
      }

  }
  /*Miras por la ventana y aparcao*/
  if (pgr->days_c == 4){
    if (strcasecmp(command_get_status(last_cmd),"OK") == 0 && strcasecmp(command_get_obj_name(last_cmd), "Window") == 0){

      pgr->notes_c++;

    }
    else if (pgr->notes_c >= 10){

      game_set_game_is_over(game,TRUE);
      printf("\n\nCongratulations! You solved the case! The evil Zackary James Comstock used Boticolas to make illegal Bitcoin transactions!\n");
    }
  }



  pgr->n_cmd++;


  return OK;
}
