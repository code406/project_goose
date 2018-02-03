/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 5

// son los comandos abreviados o completos que usuario introduce
// empiezan en N_CMD
char * cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous"};
char * short_cmd_to_str[N_CMD] = {"","","e","f","p"};

// Escanea la introducción de comandos del usuario
T_Command get_user_input()
{
  T_Command cmd = NO_CMD;       // cmd = -1
  char input[CMD_LENGHT] = "";

  // i se inicializa como 2
  int i = UNKNOWN - NO_CMD + 1;

  // Se escanea lo que el usuario introduce como comando
  // scanf retorna el numero de items asignados, se usa como Control de Error
  // Si es 0 o menor, no se ha recibido bien el comando introducido, y no sigue
  if (scanf("%s", input) > 0)
  {
    cmd = UNKNOWN; // cmd = 0

    // Como cmd = UNKNOWN, e i=2 es < 5, el while da al menos una vuelta
    // N_CMD = 5;  UNKNOWN = 0
    while(cmd == UNKNOWN && i < N_CMD)
    {
      // strcasecmp compara 2 cadenas convertidas a mayusculas. Si son =, da 0
      // si se introduce comando valido (coincide),
      if ( !strcasecmp(input, short_cmd_to_str[i]) || !strcasecmp(input, cmd_to_str[i]))
      {
        // si encuentra cadenas iguales en la posicion i=0, cmd = NO_CMD,
        // si es en la i=1, cmd = UNKNOWN ...
        cmd = i + NO_CMD;
      }
      else
      {
        // si no encuentra cadenas iguales, incrementa i para comparar con la siguiente
        i++;
      }
    }
  }

  // devuelve el comando para que otro módulo lo ejecute
  return cmd;
}
