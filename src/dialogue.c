 /**
 * @brief Implementa la interfaz publica del modulo dialogue, necesario para
 *        que el jugador pueda ver una descripcion detallada de las acciones que ejecuta
 *
 * @file   dialogue.c
 * @author   Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version   v3.1
 * @date   29-04-2018
 * @copyright   GNU Public License
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "game.h"
#include "command.h"
#include "dialogue.h"

#define MAX_OPTIONS 4
#define N_CMD_DIALOGUE 8
#define N_CMD 17


/**
* @struct Dialogue
* @brief  Implementacion de la definicion de la estructura Dialogue
*/
struct _Dialogue {
  T_Command last_cmd; /*!<Ultimo comando*/
  const char *last_cmd_status; /*!<status del ultimo command*/
  FILE *plantilla; /*!<Plantilla en la que están los mensajes que se muestran*/
  char *part1; /*!<Primera parte del mensaje*/
  char *part2; /*!<Segunda parte del mensaje*/
  char *part3[N_CMD][MAX_OPTIONS+1];/*!<Tercera parte del mensaje*/
  int caso;
};

/*******************************************************************************
*	Crea e inicializa los datos del dialogo reservando memoria dinamica.
*******************************************************************************/
Dialogue* dialogue_create(char* plantilla){
  Dialogue* dialogue_aux;

  if (plantilla == NULL)
    return NULL;


  dialogue_aux = (Dialogue*)calloc(1,sizeof(Dialogue));
  if (dialogue_aux == NULL)
    return NULL;

  dialogue_aux->plantilla = fopen(plantilla,"r");
  if (plantilla == NULL){
    dialogue_destroy(dialogue_aux);
    return NULL;
  }

  dialogue_aux->last_cmd_status= "OK";
  dialogue_aux->part1= NULL;
  dialogue_aux->part2= NULL;
  dialogue_aux->part3[GET][0]=    "that object is not in this position";
  dialogue_aux->part3[GET][1]=     "that object is already in your bag";
  dialogue_aux->part3[DROP][0]=    "you cannot drop that object";
  dialogue_aux->part3[DROP][1]=    "that object is not in your bag" ;
  dialogue_aux->part3[MOVE][0]=    "it's not a good idea to move that way" ;
  dialogue_aux->part3[MOVE][1]=    "you can't access that place" ;
  dialogue_aux->part3[CHECK][0]=   "you might have misspelled its name" ;
  dialogue_aux->part3[CHECK][1]=   "that object is neither in this position nor in your bag" ;
  dialogue_aux->part3[TURNON][0]=  "no llevas ese objeto" ;
  dialogue_aux->part3[TURNON][1]=  "el objeto ya esta encendido" ;
  dialogue_aux->part3[TURNOFF][0]= "that object is not in your bag";
  dialogue_aux->part3[TURNOFF][1]= "that object is already turned off" ;
  dialogue_aux->part3[OPEN][0]=    "you might have misspelled the command. Try 'open <link> with <object>''" ;
  dialogue_aux->part3[OPEN][1]=    "that object can't open that door" ;
  dialogue_aux->part3[OPEN][2]=    "the door is already open" ;
  dialogue_aux->part3[UNKNOWN][0]=    " ";


  return dialogue_aux;
}

/*******************************************************************************
Destruye los datos del dialogo y libera su memoria
*******************************************************************************/
void dialogue_destroy(Dialogue *pd){
  if (pd == NULL)
    return;

  if (pd->plantilla != NULL)
    fclose(pd->plantilla);

  free (pd);

}

/*******************************************************************************
Fija el valor del campo last_cmd del dialogo
*******************************************************************************/
STATUS dialogue_set_last_cmd (Dialogue *pd, Game *game){
  if (pd == NULL || game == NULL)
    return ERROR;

  pd->last_cmd = game_get_last_command(game);

  if (pd->last_cmd == NO_CMD)
    return ERROR;

  return OK;

}

/*******************************************************************************
Fija el valor del campo last_cmd_status del dialogo
*******************************************************************************/
STATUS dialogue_set_last_cmd_status (Dialogue *pd, Game *game){
  if (pd == NULL || game == NULL)
    return ERROR;

  pd->last_cmd_status = game_get_status_command(game);

  if (pd->last_cmd_status == NULL){
      return ERROR;
    }


  return OK;

}
/*******************************************************************************
Fija el valor del campo plantilla del dialogo
*******************************************************************************/
STATUS dialogue_set_plantilla (Dialogue *pd, FILE *pf){
  if (pd == NULL || pf == NULL)
    return ERROR;

  if (pd->plantilla != NULL)
    fclose (pd->plantilla);

  pd->plantilla = pf;

  if (pd->plantilla == NULL)
    return ERROR;

  return OK;

}

/*******************************************************************************
Fija el valor del campo part1 del dialogo
*******************************************************************************/
STATUS dialogue_set_part1 (Dialogue *pd, char* part1){
  if (pd == NULL || part1 == NULL)
    return ERROR;
  pd->part1 = part1;

  return OK;
}

/*******************************************************************************
Fija el valor del campo part2 del dialogo
*******************************************************************************/
STATUS dialogue_set_part2 (Dialogue *pd, char* part2){
  if (pd == NULL || part2 == NULL)
    return ERROR;
  pd->part2 = part2;

  return OK;
}

/*******************************************************************************
Fija el valor del campo part3 que se quiera del dialogo
*******************************************************************************/
STATUS dialogue_set_part3 (Dialogue *pd,char *cadena ,int n_command, int option){
  if (pd == NULL || cadena == NULL || n_command <0 || n_command > N_CMD_DIALOGUE || option < 0 || option > MAX_OPTIONS)
    return ERROR;

  pd->part3[n_command][option] = cadena;

  return OK;
}

/*******************************************************************************
devuelve el valor del campo last_cmd del dialogo
*******************************************************************************/
T_Command dialogue_get_last_cmd (Dialogue *pd){
  if (pd == NULL || pd->last_cmd == NO_CMD)
    return UNKNOWN;

  return pd->last_cmd;
}

/*******************************************************************************
devuelve el valor del campo last_cmd_status del dialogo
*******************************************************************************/
const char* dialogue_get_last_cmd_status (Dialogue *pd){
  if (pd == NULL || pd->last_cmd_status == NULL)
    return "ERROR";

  return pd->last_cmd_status;
}

/*******************************************************************************
devuelve el valor del campo part1 del dialogo
*******************************************************************************/
char* dialogue_get_part1 (Dialogue *pd){
  if (pd == NULL || pd->part1 == NULL)
    return NULL;

  return pd->part1;
}

/*******************************************************************************
devuelve el valor del campo part2 del dialogo
*******************************************************************************/
char* dialogue_get_part2 (Dialogue *pd){
  if (pd == NULL || pd->part2 == NULL)
    return NULL;

  return pd->part2;
}

/*******************************************************************************
devuelve el valor del campo part3 que se quiera especifique del dialogo
*******************************************************************************/
char* dialogue_get_part3 (Dialogue *pd,int n_cmd, int parte){
  if (pd == NULL || pd->part3 == NULL || parte > MAX_OPTIONS)
    return NULL;


  printf("El n_cmd deberia ser: %d",n_cmd);

  return pd->part3[n_cmd][parte];
}

/*******************************************************************************
Accediendo a la plantilla se cargan los valores de part1 y part2 del dialogo
*******************************************************************************/
STATUS dialogue_load_parts (Dialogue *pd){

  char line[WORD_SIZE] = " ";
  char* toks = NULL;
  char *cadena1 = NULL;
  char *cadena2 = NULL;



  if (pd == NULL || pd->plantilla == NULL)
    return ERROR;

    while (fgets(line, WORD_SIZE, pd->plantilla))
    {
      /* Si los 3 primeros caracteres de la linea leida son "#u:" */
      /*caso unknown*/
      if (pd->last_cmd == UNKNOWN){
        if (strncmp("#u:", line, 3) == 0)
        {
          /* strtok divide una cadena en elementos con separadores ("|") */
          /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
          toks = strtok(line + 3, "|");
          cadena1=toks;
          cadena2=" ";
          break;
        }
      }
      /*para get*/
      else if (pd->last_cmd == GET){
        if (strcmp(pd->last_cmd_status,"ERROR") == 0){
          if (strncmp("#ge", line, 3) == 0)
          {
            /* strtok divide una cadena en elementos con separadores ("|") */
            /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
            toks = strtok(line + 3, "|");
            cadena1 = toks;
            toks = strtok(NULL, "|");
            cadena2 = toks;
            break;
          }
        }
        else{
          if (strncmp("#go", line, 3) == 0)
          {
            /* strtok divide una cadena en elementos con separadores ("|") */
            /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
            toks = strtok(line + 3, "|");
            cadena1 = toks;
            toks = strtok(NULL, "|");
            cadena2 = toks;
            break;
          }
        }
      }

      /*para drop*/
      else if (pd->last_cmd == DROP){
        if (strcmp(pd->last_cmd_status,"ERROR") == 0){
          if (strncmp("#de", line, 3) == 0)
          {
            /* strtok divide una cadena en elementos con separadores ("|") */
            /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
            toks = strtok(line + 3, "|");
            cadena1 = toks;
            toks = strtok(NULL, "|");
            cadena2 = toks;
            break;
          }
        }
        else{
          if (strncmp("#do", line, 3) == 0)
          {
            /* strtok divide una cadena en elementos con separadores ("|") */
            /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
            toks = strtok(line + 3, "|");
            cadena1 = toks;
            toks = strtok(NULL, "|");
            cadena2 = toks;
            break;
            }
          }
        }
        /*para move*/
        else if (pd->last_cmd == MOVE){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#me", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1=  toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#mo", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1=toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              printf("%s\n%s",cadena1,cadena2);
              break;
            }
          }
        }
        /*para check*/
        else if (pd->last_cmd == CHECK){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#ce", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#co", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
        }
        /*para turnon*/
        else if (pd->last_cmd == TURNON){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#ee", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#eo", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
        }
        /*para turnoff*/
        else if (pd->last_cmd == TURNOFF){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#ae", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#ao", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
        }

        /*para open*/
        else if (pd->last_cmd == OPEN){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#oe", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#oo", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
        }

        /*para save*/
        else if (pd->last_cmd == SAVE){
          if (strcmp(pd->last_cmd_status,"ERROR") == 0){
            if (strncmp("#se", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
          else{
            if (strncmp("#so", line, 3) == 0)
            {
              /* strtok divide una cadena en elementos con separadores ("|") */
              /* Se asigna a las variables el valor leido desde el archivo (con enteros long)*/
              toks = strtok(line + 3, "|");
              cadena1 = toks;
              toks = strtok(NULL, "|");
              cadena2 = toks;
              break;
            }
          }
        }

      }
      printf("\n\n%s\n\n%s",cadena1,cadena2);
    dialogue_set_part1(pd,cadena1);
    dialogue_set_part2(pd,cadena2);

    return OK;

}

/*******************************************************************************
Se elige el caso correspondiente a la parte 3 de dialogue
*******************************************************************************/
STATUS dialogue_set_caso (Dialogue *pd, Game *game){
  T_Command last_cmd = UNKNOWN;



  if (game == NULL ||  pd == NULL)
    return ERROR;

  last_cmd = pd->last_cmd;

    if(last_cmd == GET){
      if(game_check_object_player(game, game_get_object(game, game_object_get_id_from_name(command_get_obj_name(game_get_command(game)),game))) == TRUE){
        pd->caso = 1;
      }

      else{
        pd->caso = 0;
      }

    }
    else if(last_cmd == DROP){
      if(game_check_object_player(game, game_get_object(game, game_object_get_id_from_name(command_get_obj_name(game_get_command(game)),game))) == FALSE)
        pd->caso = 1;
      else
        pd->caso = 0;
    }
    else if(last_cmd == MOVE){
      if(die_get_last_roll(game_get_die(game))%2 == 0)
        pd->caso = 0;
      else
        pd->caso = 1;
    }
    else if(last_cmd == CHECK){
      if(game_object_get_id_from_name(command_get_obj_name(game_get_command(game)),game)==NO_ID)
        pd->caso = 0;
      else
        pd->caso = 1;
    }
    else if(last_cmd == TURNON || last_cmd == TURNOFF){
      if(game_check_object_player(game, game_get_object(game, game_object_get_id_from_name(command_get_obj_name(game_get_command(game)),game))) == FALSE)
        pd->caso = 0;
      else
        pd->caso = 1;
    }

    else if(last_cmd == OPEN){
      if(link_get_linked(game_get_link(game, game_link_get_id_from_name(command_get_link_name(game_get_command(game)),game))) == TRUE)
        pd->caso = 2;
      else if (game_check_object_player(game, game_get_object(game, game_object_get_id_from_name(command_get_obj_name(game_get_command(game)),game))) == FALSE)
        pd->caso = 1;
      else
        pd->caso = 0;
    }

  return OK;
}

/*******************************************************************************
Se devuelve el caso de la parte 3 de dialogue que se va a necesitar
*******************************************************************************/
int dialogue_get_caso (Dialogue *pd){
  if (pd == NULL)
    return -1;

  return pd->caso;
}
