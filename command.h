/**
 * @brief Interprete de comandos
 *
 * @file command.h
 * @author Pareja
 * @version 1.0.E
 * @date 16-02-2018
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H


/* Enumeración que define para cada comando del usuario un valor numérico */
typedef enum enum_Command
{
  NO_CMD =      -1,
  UNKNOWN,    /* 0 */
  EXIT,       /* 1 */
  FOLLOWING,  /* 2 */
  PREVIOUS,   /* 3 */
  GET,        /* 4 */
  DROP        /* 5 */
} T_Command;


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
T_Command get_user_input();


#endif
