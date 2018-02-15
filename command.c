/**
 * @brief Interprete de comandos
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
#define N_CMD 7

/*Tabla de cinco elementos del tipo puntero a char*/
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous","Get","Drop"};

/*Tabla de cinco elementos del tipo puntero a char*/
/*Abreviación de la tabla anterior*/
char *short_cmd_to_str[N_CMD] ={"","","e","f","p","g","d"};

/*Definición de la Función, no tiene argumentos*/
T_Command get_user_input(){
  /*Variable cmd tipo T_Command inicializada a -1*/
  T_Command cmd = NO_CMD;
  /*Variable input tipo cadena de caracteres, leerá el comando más adelante*/
  char input[CMD_LENGHT] = "";
  /*Variable i tipo entero inicializada a 0*/
  int i=UNKNOWN - NO_CMD + 1;

  /*Si escanea el comando bien*/
  if (scanf("%s", input) > 0){
    /*cmd = 0*/
    cmd = UNKNOWN;
    /*mientras cmd sea 0 e i sea menor que 5 va comparando el comando introducido con la lista de comandos*/
    while(cmd == UNKNOWN && i < N_CMD){
      /*Si coincide le da a cmd el valor que le corresponde*/
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){
        cmd = i + NO_CMD;
        }
        /*Si no coincide comprueba otro comando*/
      else{
           i++;
       }
    }
  }
      /*al final la funcion devuelve el comando introducido*/
       return cmd;
}
