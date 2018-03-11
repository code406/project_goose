/**
 * @brief Interprete de comandos
 *
 * @file command.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11-03-2018
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
  DROP,       /* 5 */
  ROLL,       /* 6 */
  LEFT,       /* 7 */
  RIGHT       /* 8 */
} T_Command;


/*******************************************************************************
Funcion: get_user_input
Autor: David Palomo
Descripcion: Escanea el comando escrito por el usuario y lo transforma
  a un valor numérico definido en la enumeración T_Command.
Argumentos:
  param: Cadena de caracteres donde se copia el parámetro del comando
         (para comandos como "get O1" o "drop O1")
  input: Cadena de caracteres con el comando introducido
Return:
  Valor numérico de la enumeración T_Command que identifica a cada comando
*******************************************************************************/
T_Command get_user_input(char* param, char* input);


#endif
