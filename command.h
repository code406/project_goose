/**
 * @brief Interprete de compandos
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

/*Crea una enumeración, asi cada comando tiene asignado un valor numerico*/

typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  FOLLOWING,
  PREVIOUS} T_Command;

/*Funcion que devuelve un elemento del tipo T_Command */
/*No tiene argumentos*/

/*La funcion escaneará el comando escrito entero o solo su inicial*/
/*Devolverá un valor numérico relacionado con el comando (T_Command)*/
T_Command get_user_input();

#endif
