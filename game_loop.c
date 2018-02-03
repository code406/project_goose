/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"

int main(int argc, char *argv[])
{
	Game game;
	T_Command command = NO_CMD;
	Graphic_engine *gengine;


	// Si no invocas el programa bien ("./game  game_data_file")
	// porque no escribes 2 argumentos mínimo (argc < 2),
	// imprime error y explica cómo invocar el programa. Termina (return)
	if (argc < 2)
	{
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}


  // Intenta crear el juego a partir de game_data_file, que es el argv[1]
	// Si da error, muestra mensaje y termina (return)
	if (game_create_from_file(&game, argv[1]) == ERROR)
	{
		fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}


	// Intenta crear el graphic_engine. Si no consigue crear, el puntero es NULL,
	// muestra error, libera con game_destroy y termina (return)
	if ((gengine = graphic_engine_create()) == NULL)
	{
		fprintf(stderr, "Error while initializing graphic engine.\n");
		game_destroy(&game);
		return 1;
	}


	// Mientras usuario no da la orden de EXIT, y el juego no ha terminado,
	// se sigue "pintando" el juego y escaneando la introducción de comandos
	while ( (command != EXIT) && !game_is_over(&game) )
	{
		graphic_engine_paint_game(gengine, &game);
		command = get_user_input();
		game_update(&game, command);
	}


	// Cuando el loop termina, libera con game_destroy y graphic_engine_destroy,
	// y termina el programa
	game_destroy(&game);
	graphic_engine_destroy(gengine);
	return 0;

}
