/**
 * @brief Interprete de comandos
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H



/* Enumeración que define para cada comando del usuario un valor numérico */
typedef enum enum_Command {
  NO_CMD =      -1,
  UNKNOWN,    /* 0 */
  EXIT,       /* 1 */
  FOLLOWING,  /* 2 */
  PREVIOUS    /* 3 */
} T_Command;



/*******************************************************************************
Funcion: get_user_input
Descripcion: Escanea el comando escrito por el usuario y lo transforma
  a un valor numérico definido en la enumeración T_Command.
Argumentos:
  Ninguno
Return:
  Valor de la enumeración T_Command (del -1 al 3, incluidos)
*******************************************************************************/
T_Command get_user_input();



#endif
