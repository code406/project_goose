/**
 * * @brief   Implementa la interfaz publica del modulo command, necesario para que el usuario pueda
 *			realizar todas las acciones que provocan cambios en el estado del juego.
 *
 * * @file   command.c
 * * @author   Ines Martin y Javier Mateos
 * * @version   v2.4
 * * @date   06-03-2018
 * * @copyright   GNU Public License
 *
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "types.h"

#define CMD_LENGHT 30 /*Longitud maxima de caracteres del comando*/
#define N_CMD 10 /*Numero de comandos disponibles*/
#define CMD_OBJ 3 /*Longitud del identificador del objeto*/
#define CMD_STATUS 6 /*Longitud del estado del comando*/

/**
* * @brief array cmd_to_str
*Posibles comandos introducidos por el usario
*/
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Get", "Drop", "Roll" , "Left" , "Right"};
/**
* * @brief array short_cmd_to_str
*vPosibles comandos abreviados introducidos por el usuario (abreviados)
*/
char *short_cmd_to_str[N_CMD] ={"","","e","f","p", "g","d", "x", "l", "r"};

/**
* * @brief estructura _Data_Command
* Implementacion de la definicion de la estructura Data_Command
*/
struct _Data_Command{
	T_Command t_cmd; /*Tipo de comando*/
	char id_obj[CMD_OBJ]; /*Objeto con el que interacciona el comando*/
	char status[CMD_STATUS]; /*Estado del comando*/
};

/*******************************************************************************
 *                   IMPLEMENTACION DE LA INTERFAZ COMMAND
 ******************************************************************************/

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
D_Command* command_create() {

	D_Command *newCommand = NULL;

	newCommand = (D_Command*) malloc(sizeof (D_Command));

	if (newCommand == NULL) {
    return NULL;
	}

	newCommand->t_cmd = NO_CMD;

	newCommand->id_obj[0] = '-';
	newCommand->id_obj[1] = '1';
	newCommand->status[0] = '\0';

  return newCommand;
}

/**
* @name   command_destroy
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Destruye y libera la memoria asignada a los datos del comando.
* @arguments   d_command: puntero a los datos del comando que se destruyen.
* @return   Devuelve OK si todo sole correctamente o ERROR si se produce algun fallo.
*/
STATUS command_destroy(D_Command* d_command){

	if(d_command == NULL){
		return ERROR;
	}

	free(d_command);

	return OK;
}

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
T_Command command_get_t_cmd(const D_Command* d_command){

	if(d_command == NULL){
		return NO_CMD;
	}

	return d_command->t_cmd;
}

/**
* @name   command_get_id_obj
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Devuelve el identificador del objeto con el que interaccion el comando.
* @arguments   d_command: puntero a los datos del que se obtiene el identificador.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el identificador
          del objeto o NULL en caso de que se produzca algun error.
*/
const char* command_get_id_obj(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->id_obj;
}

/**
* @name   command_get_status
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Devuelve el estado del comando.
* @arguments   d_command: puntero a los datos del comando del que se obtiene el estado.
* @return   Devuelve un puntero a una cadena de caracteres que contiene el estado del
          comando o NULL si se produce algun error.
*/
const char* command_get_status(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->status;
}

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
STATUS command_write_log(const D_Command* d_command, FILE* pf){

	T_Command last_cmd = NO_CMD; /*Almacenará el comando de los datos de la estructura D_Command*/
	const char* status = NULL; /*Variable para guardar el estado de la estructura D_Command*/

	if(d_command == NULL || pf == NULL){
		return ERROR;
	}

	/*Obtenemos el ultimo comando escrito por el usuario*/
	last_cmd = command_get_t_cmd(d_command);

	/*Obtenemos el estado del ultimo comando*/
	status = command_get_status(d_command);

	/*Imprimimos el ultimo comando seguido de su estado*/
	fprintf(pf, "%s: %s\n", cmd_to_str[last_cmd-NO_CMD], status);

	return OK;
}


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
STATUS command_set_t_cmd(D_Command* d_command, T_Command t_cmd){

	if(d_command == NULL || t_cmd == NO_CMD){
		return ERROR;
	}

	d_command->t_cmd = t_cmd;

	return OK;
}

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
STATUS command_set_id_obj(D_Command* d_command, char* id_obj){

	if(d_command == NULL || id_obj == NULL){
		return ERROR;
	}

	/*Copiamos el contenido de la cadena en el campo correspondiente de la estructura*/
	if(!strcpy(d_command->id_obj, id_obj)){
		return ERROR;
	}

	return OK;
}

/**
* @name   command_set_status
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Establece el estado del comando.
* @arguments   d_command: puntero a los datos del comando donde se modifica el estado.
             id_ob: estado que se introduce en los datos del comando.
* @return   Devuelve OK si todo sale bien o ERROR si se produce algun fallo.
*/
STATUS command_set_status(D_Command* d_command, char* status){

	if(d_command == NULL || status == NULL){
		return ERROR;
	}

	if(!strcpy(d_command->status, status)){
		return ERROR;
	}

	return OK;
}

/**
* @name   get_user_input
* @date   06-03-2018
* @author   Javier Mateos
* @brief   Lee el comando que introduce el usuario.
* @arguments   id_object: identificador del objeto introducido por el usario en caso
                        de que utilice el comando grasp.
* @return   Devuelve el comando que ha sido introducido por el usuario.
*/
T_Command get_user_input(D_Command* d_command){

	/*Inicializamos el comando a -1*/
	T_Command cmd = NO_CMD;

	/*Cadena de texto donde se almacena el comando escrito por el usario*/
	char input[CMD_LENGHT];

	/*Variable auxiliar para calcular el comando introducido por el usario incializada a 2*/
	int i=UNKNOWN - NO_CMD + 1;

	/*Variable que almacenara las subcadenas que contendran la informacion necesaria para
	completar los campos de la estructura D_Command*/
	char* toks = NULL;

    input[0] = 0;
	if (fgets(input, CMD_LENGHT, stdin) !=  NULL){

		cmd = UNKNOWN;
		toks = strtok(input, " \n");
		if(toks != NULL){

			while(cmd == UNKNOWN && i < N_CMD){

				/*Comparamos el comando introducido por el usario con los posibles comandos definidos en el juego*/
  			if (!strcasecmp(toks,short_cmd_to_str[i]) || !strcasecmp(toks,cmd_to_str[i])){
  				/*Calculamos que comando ha introducido el usario*/
  				cmd = i + NO_CMD;
  				/*Modificamos el tipo de comando en la estructura*/
  				command_set_t_cmd(d_command, cmd);
  				/*Si el comando introducido es grasp comprobamos que introduce el identificador del objeto que quiere coger*/
  				if(cmd == GRASP){
  					toks = strtok(NULL, " \n");
  					if(toks ==NULL){
							/*En caso de que el comando no vaya acompañado de un identificador se establece error al estado del comando*/
  						command_set_status(d_command, "ERROR");
  					}
  					command_set_id_obj(d_command, toks);
  				}
  			}
  			else{
					/*Se realiza el bucle hasta comprobar con todos los comandos disponibles*/
					i++;
				}
			}
		}
	}
	return cmd;
}
