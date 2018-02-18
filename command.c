/**
 * @brief Interprete de comandos
 *
 * @file command.c
 * @author Pareja
 * @version 1.0.E
 * @date 16-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"

/* Tamaño máximo para la introducción de comando.
 Deberíamos cambiar a screen_gets la funcion de input */
#define CMD_LENGHT 256
#define N_CMD 7

/* Tabla de comandos que el usuario introduce (completos) */
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit",
                           "Following", "Previous","Get","Drop"};

/* Tabla de comandos que el usuario introduce (abreviados) */
char *short_cmd_to_str[N_CMD] ={"","","e","f","p","g","d"};


/*******************************************************************************
Funcion: get_user_input
Autor: David Palomo
Descripcion: Escanea el comando escrito por el usuario y lo transforma
  a un valor numérico definido en la enumeración T_Command.
Argumentos:
  Ninguno
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command get_user_input()
{
  /*Variable cmd tipo T_Command inicializada a -1*/
  T_Command cmd = NO_CMD;
  /*Variable input tipo cadena de caracteres, leerá el comando más adelante*/
  char input[CMD_LENGHT] = "";
  /*Variable i tipo entero inicializada a 2*/
  int i = UNKNOWN - NO_CMD + 1;

  /*Si escanea el comando bien*/
  if (scanf("%s", input) > 0)
  {
    /*cmd = 0*/
    cmd = UNKNOWN;

    /* Compara el comando introducido con la lista de comandos disponibles */
    while(cmd == UNKNOWN && i < N_CMD)
    {
      /* Si coincide con uno, le da a cmd el valor que le corresponde */
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i]))
      {
        cmd = i + NO_CMD;
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
