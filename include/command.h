/**
 * * @brief   Define la interfaz publica del modulo command, necesario para que el usuario
 *          pueda realizar todas las acciones que provocan cambios en el estado del juego.
 *
 * * @file   command.h
 * * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * * @version   v3.0
 * * @date   08-04-2018
 * * @copyright   GNU Public License
 *
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include "types.h"

/**
* @typedef enum_Command
* @brief Valor numerico de los comandos disponibles para el usuario.
*/
typedef enum enum_Command {
    NO_CMD = -1,
    UNKNOWN,
    EXIT,       /*!<Comando para salir del juego 1*/
    FOLLOWING,  /*!<Comando para avanzar 2*/
    PREVIOUS,   /*!<Comando para retroceder 3*/
    GET,        /*!<Comando para coger un objecto 4*/
    DROP,       /*!<Comando para soltar un objeto 5*/
    ROLL,       /*!<Comando para lanzar el dado 6*/
    LEFT,       /*!<Comando para ir a la izquierda 7*/
    RIGHT,      /*!<Comando para ir a la derecha 8*/
    MOVE,       /*!<Comando para moverse en una direccion 9*/
    CHECK,      /*!<Comando para examinar los objetos 10*/
    TURNON,     /*!<Comando para ver si el objeto esta encendido 11*/
    TURNOFF,     /*!<Comando para ver si el objeto esta apagado 12*/
    OPEN,        /*!<Comando para abrir un enlace con un objeto 13*/
    SAVE,        /*!<Comando para guardar la partida 14*/
    LOAD,       /*!<Comando para cargar una partida guardada 15*/
    SHOWMAP     /*!<Comando para mostrar el mapa en el motor grafico 16*/
} T_Command;

/**
* @typedef D_Command
* @brief  Definicion de la estructura de datos Command
*/
typedef struct _Data_Command D_Command;

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL COMANDO
*
*******************************************************************************/

/**
* @name   command_create
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Crea e inicializa los datos del comando reservando memoria dinamica.
* @param
* @return   Devuelve un puntero al conjunto de datos del comando inicializado.
*/
D_Command* command_create();

/**
* @name   command_destroy
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Destruye y libera la memoria asignada a los datos del comando.
* @param   d_command puntero a los datos del comando que se destruyen.
* @return   Devuelve OK si todo sole correctamente o ERROR si se produce algun fallo.
*/
STATUS command_destroy(D_Command* d_command);

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER A LOS DATOS DEL COMANDO
*
*******************************************************************************/

/**
* @name   command_get_t_cmd
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Devuelve el tipo de comando.
* @param   d_command puntero a los datos del que se obtiene el tipo de comando.
* @return   Devuelve el valor del tipo de comando que contiene los datos del comando o NO_CMD si se produce algun fallo.
*/
T_Command command_get_t_cmd(const D_Command* d_command);

/**
* @name   command_get_obj_name
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Devuelve el identificador del objeto con el que interaccion el comando.
* @param   d_command puntero a los datos del que se obtiene el identificador.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el identificador del objeto o NULL en caso de que se produzca algun error.
*/
const char* command_get_obj_name(const D_Command* d_command);

/**
* @name   command_get_obj_name
* @date   24-04-2018
* @author   David Palomo
* @brief   Devuelve el identificador del enlace con el que interacciona el comando.
* @param   d_command puntero a los datos del que se obtiene el nombre de enlace.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el nombre del enlace o NULL en caso de que se produzca algun error.
*/
const char* command_get_link_name(const D_Command* d_command);

/**
* @name   command_get_direction
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Devuelve la direccion utilizada para el comando move.
* @param   d_command  puntero a los datos del que se obtiene el identificador.
* @return   Devuelve un puntero a una cadena de caracteres que contiene la direccion utilizada para el comando move.
*/
const char* command_get_direction(const D_Command* d_command);

/**
* @name   command_get_status
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Devuelve el estado del comando.
* @param   d_command puntero a los datos del comando del que se obtiene el estado.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el estado del comando o NULL si se produce algun error.
*/
const char* command_get_status(const D_Command* d_command);

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA MODIFICAR LOS DATOS DEL COMANDO
*
*******************************************************************************/
/**
* @name   command_set_direction
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Asigna la direccion utilizada para el comando move.
* @param d_command Puntero a los datos del comando donde se modifica el tipo.
* @param direction Cadena de caracteres que contiene la direccion utilizada para el comando move.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_direction(D_Command* d_command, char* direction);

/**
* @name   command_set_t_cmd
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Asigna el tipo de comando a los datos del mismo.
* @param   d_command puntero a los datos del comando donde se modifica el tipo.
* @param   t_cmd tipo de comando que se introduce.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_t_cmd(D_Command* d_command, T_Command t_cmd);

/**
* @name   command_set_obj_name
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Asigna el identificador del objeto con el que interacciona el comando.
* @param   d_command puntero a los datos del comando donde se modifica el tipo.
* @param   id_ob   cadena de caracteres que contiene el identificador del objeto que se introduce en los datos del comando.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_obj_name(D_Command* d_command, char* obj_name);

/**
* @name   command_set_link_name
* @date   24-04-2018
* @author   David Palomo
* @brief   Asigna el nombre del enlace con el que interacciona el comando.
* @param   d_command puntero a los datos del comando donde se modifica el nombre de enlace.
* @param   link_name   cadena de caracteres que contiene el nombre de enlace a asignar.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_link_name(D_Command* d_command, char* link_name);

/**
* @name   command_set_status
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Establece el estado del comando.
* @param   d_command puntero a los datos del comando donde se modifica el estado.
* @param   status  estado que se introduce en los datos del comando.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_status(D_Command* d_command, char* status);

/**
* @name   command_write_log
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Imprime en un fichero el resultado de la ejecucion del comando.
* @param   d_command puntero a los datos del comando del que se obtienem los datos.
* @param   pf  fichero ya abierto en el que se escribe dicha informacion.
* @return   Devuelve OK si todo sale correctamente o ERROR si se produce algun fallo.
*/
STATUS command_write_log(const D_Command* d_command, FILE* pf);

/**
* @name   get_user_input
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Lee el comando que introduce el usuario.
* @param   d_command puntero a los datos del comando introducido por el usuario.
* @return   Devuelve el tipo de comando que ha sido introducido por el usuario.
*/
T_Command get_user_input(D_Command* d_command);

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA DEPURAR EL TAD D_COMMAND
*
*******************************************************************************/

/**
* @name   command_print
* @date   08-04-2018
* @author   Javier Mateos
* @brief   Imprime la informacion del comando
* @param  d_command puntero a los datos del comando que se imprime
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_print(D_Command* D_Command);

#endif
