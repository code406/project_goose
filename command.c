/**
 * @brief Interprete de comandos
 *
 * @file command.c
 * @author Arturo Morcillo, David Palomo
 * @version 1.0.E
 * @date 27-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "command.h"


#define N_CMD 10
#define CMD_LENGHT 100

/* Tabla de comandos que el usuario introduce (completos) */
char *cmd_to_str[N_CMD] = {"No command","Unknown","Exit","Following","Previous",
                           "Get","Drop","Roll","Left","Right"};

/* Tabla de comandos que el usuario introduce (abreviados) */
char *short_cmd_to_str[N_CMD] ={"","","e","f","p","g","d","x","l","r"};


/*******************************************************************************
Funcion: get_user_input
Autor: David Palomo
Descripcion: Escanea el comando escrito por el usuario y lo transforma
  a un valor numérico definido en la enumeración T_Command.
Argumentos:
  param: Cadena de caracteres donde se copia el parámetro del comando
         (para comandos como "get O1" o "drop O1")
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command get_user_input(char* param, char* input)
{
  char* toks = NULL;
  /*Variable cmd tipo T_Command inicializada a -1*/
  T_Command cmd = NO_CMD;
  /*Variable input tipo cadena de caracteres, leerá el comando más adelante*/
  /*Variable i tipo entero inicializada a 2*/
  int i = UNKNOWN - NO_CMD + 1;
  /* En caso de no requerir parametro, será '\0' */
  *param = '\0';


  if (input == NULL)
    return UNKNOWN;

  /*Si escanea el comando bien*/
  if (input != NULL)
  {
    input[strlen(input)-1] = '\0';
    /*cmd = 0*/
    cmd = UNKNOWN;

    /* toks es la primera palabra introducida (hasta espacio) */
    toks = strtok(input, " ");

    if (toks == NULL)
      return UNKNOWN;

    /* Compara el comando introducido con la lista de comandos disponibles */
    while(cmd == UNKNOWN && i < N_CMD)
    {
      /* Si coincide con uno, le da a cmd el valor que le corresponde */
      if (!strcasecmp(toks, short_cmd_to_str[i]) || !strcasecmp(toks, cmd_to_str[i]))
      {
        cmd = i + NO_CMD;
        toks = strtok(NULL, " ");

        if(toks==NULL)
        {
          if (cmd == GET || cmd == DROP)
          {
            return UNKNOWN;
          }
        }
        else
        {
          if (cmd == GET || cmd == DROP)
          {
            if (strcmp(toks,"O1") != 0 && strcmp(toks,"O2") != 0 && strcmp(toks,"O3") != 0 && strcmp(toks,"O4") != 0)
              return UNKNOWN;
            strcpy(param, toks);
          }
          else
          {
            return UNKNOWN;
          }
        }
      }
      /* Si no coincide, incrementa i para comparar con otro comando */
      else
      {
        i++;
      }
    }
  }

  /* la funcion devuelve el comando introducido */
  return cmd;
}
