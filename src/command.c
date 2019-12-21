/**
 * * @brief   Implementa la interfaz publica del modulo command, necesario para que el usuario pueda
 *			realizar todas las acciones que provocan cambios en el estado del juego.
 *
 * * @file   command.c
 * * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * * @version   v3.0
 * * @date   08-04-2018
 * * @copyright   GNU Public License
 *
 */

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "types.h"

#define CMD_LENGHT 50 /*!<Longitud maxima de caracteres del comando*/
#define N_CMD 18 /*!<Numero de comandos disponibles*/
#define CMD_OBJ 30 /*!<Longitud del identificador del objeto*/
#define CMD_DIR 10 /*!<Longitud del identificador de direccion (move)*/
#define CMD_STATUS 6 /*!<Longitud del estado del comando*/

/**
* @brief array cmd_to_str
* Posibles comandos introducidos por el usario
*/
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Get", "Drop", "Roll" , "Left" , "Right", "Move", "Check", "Turnon", "Turnoff", "Open","Save","Load", "ShowMap"};
/**
* @brief array short_cmd_to_str
* Posibles comandos abreviados introducidos por el usuario (abreviados)
*/
char *short_cmd_to_str[N_CMD] ={"","","e","f","p","g","d","x","l","r","m","c","to","tf", "o", "s", "l", "sm"};

/**
* @struct _Data_Command
* @brief  Implementacion de la definicion de la estructura Data_Command
*/
struct _Data_Command{
	T_Command t_cmd; /*!<Tipo de comando*/
	char obj_name[CMD_OBJ]; /*!<Objeto con el que interacciona el comando*/
	char link_name[CMD_OBJ]; /*!<Enlace con el que interacciona el comando*/
	char direction[CMD_DIR]; /*!<Direccion del comando move*/
	char status[CMD_STATUS]; /*!<Estado del comando*/
};

/*******************************************************************************
 *                   IMPLEMENTACION DE LA INTERFAZ COMMAND
 ******************************************************************************/

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA CREAR Y LIBERAR LOS DATOS DEL COMANDO
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
D_Command* command_create() {

	D_Command *newCommand = NULL;

	newCommand = (D_Command*) malloc(sizeof (D_Command));

	if (newCommand == NULL) {
    return NULL;
	}

	newCommand->t_cmd = NO_CMD;

	strcpy(newCommand->obj_name, "-1");
	strcpy(newCommand->direction, "none");
	strcpy(newCommand->link_name, "none");

	newCommand->status[0] = '\0';

  return newCommand;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_destroy(D_Command* d_command){

	if(d_command == NULL){
		return ERROR;
	}

	free(d_command);

	return OK;
}

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA ACCEDER A LOS DATOS DEL COMANDO
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
T_Command command_get_t_cmd(const D_Command* d_command){

	if(d_command == NULL){
		return NO_CMD;
	}

	return d_command->t_cmd;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
const char* command_get_obj_name(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->obj_name;
}

/*******************************************************************************
*	Devuelve el nombre del enlace almacenado en la estructura del comando.
*******************************************************************************/
const char* command_get_link_name(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->link_name;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
const char* command_get_direction(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->direction;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
const char* command_get_status(const D_Command* d_command){

	if(d_command == NULL){
		return NULL;
	}

	return d_command->status;
}

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA MODIFICAR LOS DATOS DEL COMANDO
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_set_t_cmd(D_Command* d_command, T_Command t_cmd){

	if(d_command == NULL || t_cmd == NO_CMD){
		return ERROR;
	}

	d_command->t_cmd = t_cmd;

	return OK;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_set_obj_name(D_Command* d_command, char* obj_name){

	if(d_command == NULL || obj_name == NULL){
		return ERROR;
	}

	/*Copiamos el contenido de la cadena en el campo correspondiente de la estructura*/
	if(!strcpy(d_command->obj_name, obj_name)){
		return ERROR;
	}

	return OK;
}

/*******************************************************************************
*	Asigna el nombre del enlace con que interactuar al pasado como argumento.
*******************************************************************************/
STATUS command_set_link_name(D_Command* d_command, char* link_name){

	if(d_command == NULL || link_name == NULL){
		return ERROR;
	}

	/*Copiamos el contenido de la cadena en el campo correspondiente de la estructura*/
	if(!strcpy(d_command->link_name, link_name)){
		return ERROR;
	}

	return OK;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_set_direction(D_Command* d_command, char* direction){

	if(d_command == NULL || direction == NULL){
		return ERROR;
	}

	/*Copiamos el contenido de la cadena en el campo correspondiente de la estructura*/
	if(!strcpy(d_command->direction, direction)){
		return ERROR;
	}

	return OK;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_set_status(D_Command* d_command, char* status){

	if(d_command == NULL || status == NULL){
		return ERROR;
	}

	if(!strcpy(d_command->status, status)){
		return ERROR;
	}

	return OK;
}

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
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

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
T_Command get_user_input(D_Command* d_command)
{
	T_Command cmd = NO_CMD;
	char input[CMD_LENGHT]; /* Donde se guardará el comando que escribe el usario */
	int i = UNKNOWN-NO_CMD+1; /* Para calcular el comando introducido. Se inicializa a 2 */
	char* toks = NULL; /* Almacenará las subcadenas al leer comando y parámetro */

	/*Restauramos las cadenas a sus valores iniciales para saber si el
	usuario mete o no los argumentos necesarios para algunos comandos*/
	strcpy(d_command->obj_name, "-1");
	strcpy(d_command->direction, "none");
	strcpy(d_command->link_name, "none");

  input[0] = 0;

	if (fgets(input, CMD_LENGHT, stdin) !=  NULL)
  {
		cmd = UNKNOWN;
		toks = strtok(input, " \n");
		if(toks != NULL)
    {
			while(cmd == UNKNOWN && i < N_CMD)
      {
				/* Comparamos el comando introducido con los definidos en la tabla */
  			if (!strcasecmp(toks,short_cmd_to_str[i]) || !strcasecmp(toks,cmd_to_str[i]))
        {
  				/* Calculamos que comando ha introducido el usario */
  				cmd = (T_Command) (i + NO_CMD);
  				/* Modificamos el tipo de comando en la estructura */
  				command_set_t_cmd(d_command, cmd);
  				/* Si el comando es get,drop,turnon o turnoff comprobamos que introduce además un id */
  				if(cmd == GET || cmd == DROP || cmd == CHECK || cmd == TURNON || cmd == TURNOFF)
          {
  					toks = strtok(NULL, " \n");

            /* En caso de que el comando no lleve un id, el estado será error */
            if(toks ==NULL)
  						command_set_status(d_command, "ERROR");

  					command_set_obj_name(d_command, toks);
  				}
					else if (cmd == MOVE)
					{
						toks = strtok(NULL, " \n");

            /* En caso de que el comando no lleve direccion, el estado será error */
            if(toks ==NULL)
  						command_set_status(d_command, "ERROR");

  					command_set_direction(d_command, toks);
					}
					else if (cmd == OPEN)
					{
						toks = strtok(NULL, " \n");

            /* En caso de que el comando no lleve enlace, el estado será error */
            if(toks ==NULL)
  						command_set_status(d_command, "ERROR");

  					command_set_link_name(d_command, toks);

						toks = strtok(NULL, " with \n");

						/* En caso de que el comando no lleve objeto, el estado será error */
						if(toks ==NULL)
							command_set_status(d_command, "ERROR");

						command_set_obj_name(d_command, toks);
					}
  			}
  			else
        {
					/* Se realiza el bucle hasta comprobar con todos los comandos disponibles */
					i++;
				}
			}
		}
	}
	return cmd;
}

/******************************************************************************
*
*      BLOQUE DE FUNCIONES PARA DEPURAR EL TAD D_COMMAND
*
*******************************************************************************/

/*******************************************************************************
*	Crea e inicializa los datos del comando reservando memoria dinamica.
*******************************************************************************/
STATUS command_print(D_Command* D_Command){

	T_Command cmd = NO_CMD;

	if(D_Command == NULL)
		return ERROR;

	cmd = command_get_t_cmd(D_Command);
	printf("Tipo de comando: %s || ", cmd_to_str[(int)cmd + 1]);

	if(cmd == GET || cmd == DROP || cmd == CHECK){
		printf("Objeto: %s || ", command_get_obj_name(D_Command));
	}
	else if(cmd == MOVE){
		printf("Direccion: %s || ", command_get_direction(D_Command));
	}
	else if(cmd == OPEN){
		printf("Enlace: %s || Objeto: %s || ", command_get_link_name(D_Command), command_get_obj_name(D_Command));
	}

	printf("Estado: %s\n", command_get_status(D_Command));

	return OK;
}
