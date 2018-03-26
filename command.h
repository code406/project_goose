/**
 * * @brief   Define la interfaz publica del modulo command, necesario para que el usuario
 *          pueda realizar todas las acciones que provocan cambios en el estado del juego.
 *
 * * @file   command.h
 * * @author   Ines Martin y Javier Mateos
 * * @version   v2.4
 * * @date   06-03-2018
 * * @copyright   GNU Public License
 *
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include "types.h"

/*Valor numerico de los comandos disponibles para el usuario*/
typedef enum enum_Command {
    NO_CMD = -1,
    UNKNOWN,
    EXIT,       /*Comando para salir del juego 1*/
    FOLLOWING,  /*Comando para avanzar 2*/
    PREVIOUS,   /*Comando para retroceder 3*/
    GRASP,      /*Comando para coger un objecto 4*/
    DROP,       /*Comando para soltar un objeto 5*/
    ROLL,       /*Comando para lanzar el dado 6*/
    LEFT,       /*Comando para ir a la izquierda 7*/
    RIGHT       /*Comando para ir a la derecha 8*/
} T_Command;

/*Definicion de la estructura de datos Command*/
typedef struct _Data_Command D_Command;

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL COMANDO

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/**
* @name   command_create
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Crea e inicializa los datos del comando reservando memoria dinamica.
* @arguments
* @return   Devuelve un puntero al conjunto de datos del comando inicializado.
*/
D_Command* command_create();

/**
* @name   command_destroy
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Destruye y libera la memoria asignada a los datos del comando.
* @arguments   d_command: puntero a los datos del comando que se destruyen.
* @return   Devuelve OK si todo sole correctamente o ERROR si se produce algun fallo.
*/
STATUS command_destroy(D_Command* d_command);

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

     BLOQUE DE FUNCIONES PARA ACCEDER A LOS CAMPOS DE LA ESTRUCTURA D_COMMAND

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/**
* @name   command_get_t_cmd
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Devuelve el tipo de comando.
* @arguments   d_command: puntero a los datos del que se obtiene el tipo de comando.
* @return   Devuelve el valor del tipo de comando que contiene los datos del comando
          o NO_CMD si se produce algun fallo.
*/
T_Command command_get_t_cmd(const D_Command* d_command);

/**
* @name   command_get_id_obj
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Devuelve el identificador del objeto con el que interaccion el comando.
* @arguments   d_command: puntero a los datos del que se obtiene el identificador.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el identificador
          del objeto o NULL en caso de que se produzca algun error.
*/
const char* command_get_id_obj(const D_Command* d_command);

/**
* @name   command_get_status
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Devuelve el estado del comando.
* @arguments   d_command: puntero a los datos del comando del que se obtiene el estado.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el estado del
          comando o NULL si se produce algun error.
*/
const char* command_get_status(const D_Command* d_command);

/**
* @name   command_write_log
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Imprime en cada iteracion en un fichero el resultado de la ejecucion del
         comando.
* @arguments   d_command: puntero a los datos del comando del que se obtienem los datos.
             pf: fichero ya abierto en el que se escribe dicha informacion.
* @return   Devuelve OK si todo sale correctamente o ERROR si se produce algun fallo.
*/
STATUS command_write_log(const D_Command* d_command, FILE* pf);

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

     BLOQUE DE FUNCIONES PARA MODIFICAR LOS CAMPOS DE LA ESTRUCTURA D_COMMAND

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/**
* @name   command_set_t_cmd
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Asigna el tipo de comando a los datos del mismo.
* @arguments   d_command: puntero a los datos del comando donde se modifica el tipo.
             t_cmd: tipo de comando que se introduce.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_t_cmd(D_Command* d_command, T_Command t_cmd);

/**
* @name   command_set_id_obj
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Asigna el identificador del objeto con el que interacciona el comando.
* @arguments   d_command: puntero a los datos del comando donde se modifica el tipo.
             id_ob: cadena de caracteres que contiene el identificador del objeto
                    que se introduce en los datos del comando.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_id_obj(D_Command* d_command, char* id_obj);

/**
* @name   command_set_status
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Establece el estado del comando.
* @arguments   d_command: puntero a los datos del comando donde se modifica el estado.
             id_ob: estado que se introduce en los datos del comando.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_status(D_Command* d_command, char* status);

/**
* @name   get_user_input
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Lee el comando que introduce el usuario.
* @arguments   id_object: identificador del objeto introducido por el usario en caso
                        de que utilice el comando grasp.
* @return   Devuelve el comando que ha sido introducido por el usuario.
*/
T_Command get_user_input(D_Command* d_command);


#endif
