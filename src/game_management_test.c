/**
 * @brief Pruebas del modulo game_management
 *
 * @file game_management_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_management.h"
#include "game_management_test.h"
#include "test.h"
#include "game.h"
#include "space.h"
#include "link.h"
#include "object.h"
#include "set.h"
#include "command.h"

#define MAX_TESTS 12 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo game_management.
 *
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta
 *      la prueba indicada
 *
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module game_management:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_game_management_load_spaces();
    if (all || test == 2) test2_game_management_load_spaces();
    if (all || test == 3) test3_game_management_load_spaces();
    if (all || test == 4) test4_game_management_load_spaces();
    if (all || test == 5) test1_game_management_load_objects();
    if (all || test == 6) test2_game_management_load_objects();
    if (all || test == 7) test3_game_management_load_objects();
    if (all || test == 8) test4_game_management_load_objects();
    if (all || test == 9) test1_game_management_load_links();
    if (all || test == 10) test2_game_management_load_links();
    if (all || test == 11) test3_game_management_load_links();
    if (all || test == 12) test4_game_management_load_links();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_game_management_load_spaces() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_spaces(game,"") == ERROR);

}
void test2_game_management_load_spaces() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_spaces(game," ") == ERROR);

}
void test3_game_management_load_spaces() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_spaces(game,"data.dat") == ERROR);

}

void test4_game_management_load_spaces() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_spaces(game,"data.dat") == OK);
}

void test1_game_management_load_objects() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_objects(game," ") == ERROR);

}

void test2_game_management_load_objects() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_objects(game," ") == ERROR);

}

void test3_game_management_load_objects() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_objects(game,"data.dat") == ERROR);

}
void test4_game_management_load_objects() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_objects(game,"data.dat") == OK);
}

void test1_game_management_load_links() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_links(game," ") == ERROR);

}

void test2_game_management_load_links() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_links(game," ") == ERROR);

}

void test3_game_management_load_links() {
  Game *game;
  game = NULL;
  PRINT_TEST_RESULT(game_management_load_links(game,"data.dat") == ERROR);

}
void test4_game_management_load_links() {
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_management_load_links(game,"data.dat") == OK);
}
