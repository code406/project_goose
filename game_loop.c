/**
 * @brief Bucle de ejecución del juego
 *
 * @file game_loop.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11-03-2018
 * @copyright GNU Public License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "string.h"
 #include "graphic_engine.h"
 #include "command.h"


int main(int argc, char *argv[])
{
 	Game game;
 	T_Command command = NO_CMD;
 	Graphic_engine *gengine;
  FILE *f = NULL;

  /* Si no se invoca el programa correctamente ("./goose <game_data_file>")
  porque no se introduce un minimo de 2 argumentos, imprime error y
  explica cómo invocar el programa. Termina (return). */
  if (argc < 2){
    fprintf(stderr, "Error de argumentos\n");
    return 1;
  }

 	/* Si se desea guardar un log ("./goose <game_data_file> -l <log_file>") */
  if (argc == 4 && strcmp(argv[2],"-l")==0)
  {
    f = fopen(argv[3],"w");
    if (f == NULL)
      fprintf(stderr,"Error al crear el LOG.\n");
  }

  /* Intenta crear el juego a partir de game_data_file, que es el argv[1]
 	Si da error, muestra mensaje y termina (return). */
 	if (game_create_from_file(&game, "data.dat") == ERROR)
 	{
 		fprintf(stderr, "Error while initializing game.\n");
    if (f != NULL)
      fclose (f);
 		return 1;
 	}

 	/* Intenta crear el graphic_engine. Si no consigue crear, el puntero es NULL,
 	muestra error, libera con game_destroy y termina (return). */
 	if ((gengine = graphic_engine_create()) == NULL)
 	{
 		fprintf(stderr, "Error while initializing graphic engine.\n");
 		game_destroy(&game);
 		return 1;
 	}

  /*Bucle principal del juego, lee el comando introducido por el usuario y actualiza
el estado el juego modificando los elementos en funcion del comando*/
while ( (command != EXIT) && !game_is_over(&game) ){
  /*Imprimimos en pantalla la visualizacion del juego*/
  graphic_engine_paint_game(gengine, &game);
  /*Pedimos al usuario que introduzca un comando*/
  command = get_user_input(game.last_cmd);
  /*Actualizamos el juego a partir del nuevo comando*/
  game_update(&game, command);
  if(f != NULL){
    /*Guardamos el comando realizado y su estado en el fichero*/
    command_write_log(game.last_cmd, f);
    /*Comprobamos si se produce algun error al escribir en el fichero*/
    if(ferror(f)){
      game_destroy(&game);
      graphic_engine_destroy(gengine);
      fclose(f);
      return 1;
    }
  }
}

 	/* Cuando el loop termina, libera con game_destroy y graphic_engine_destroy,
 	y termina el programa. */
 	game_destroy(&game);
  if (f != NULL)
    fclose (f);
 	graphic_engine_destroy(gengine);

 	return 0;
}
