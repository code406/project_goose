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
 #include "graphic_engine.h"
 #include "command.h"


int main(int argc, char *argv[])
{
 	Game game;
 	T_Command command = NO_CMD;
 	Graphic_engine *gengine;
  char param[WORD_SIZE+1] = " ";
  char input[WORD_SIZE+1] = " ";
  FILE *f = NULL;

  /* Si no se invoca el programa correctamente ("./goose <game_data_file>")
  porque no se introduce un minimo de 2 argumentos, imprime error y
  explica cómo invocar el programa. Termina (return). */
  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

 	/* Si se desea guardar un log ("./goose <game_data_file> -l <log_file>") */
  if (argc == 4)
  {
    f = fopen(argv[3],"w");
    if (f == NULL)
      fprintf(stderr,"Error al crear el LOG.\n");
  }

  /* Intenta crear el juego a partir de game_data_file, que es el argv[1]
 	Si da error, muestra mensaje y termina (return). */
 	if (game_create_from_file(&game, argv[1]) == ERROR)
 	{
 		fprintf(stderr, "Error while initializing game.\n");
    if (f != NULL)
      fclose (f);
 		return 1;
 	}

  game_set_param(&game,param);

 	/* Intenta crear el graphic_engine. Si no consigue crear, el puntero es NULL,
 	muestra error, libera con game_destroy y termina (return). */
 	if ((gengine = graphic_engine_create()) == NULL)
 	{
 		fprintf(stderr, "Error while initializing graphic engine.\n");
 		game_destroy(&game);
 		return 1;
 	}

 	/* Mientras usuario no da la orden de EXIT, y el juego no ha terminado,
 	se sigue "pintando" el juego y escaneando la introducción de comandos. */
 	while ((command != EXIT) && !game_is_over(&game))
 	{
 		graphic_engine_paint_game(gengine, &game);
    fgets(input, sizeof(input), stdin);
 		command = get_user_input(param,input);
    game_update(&game, command, param);
    if (f != NULL)
    {
      fprintf(f,"%s: ",input);
      if (game.command_status == OK)
        fprintf(f,"OK\n");
      else
        fprintf(f,"ERROR\n");
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
