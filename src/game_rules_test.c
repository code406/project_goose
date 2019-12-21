/**
 * @brief Pruebas del modulo game_rules
 *
 * @file game_rules_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_rules.h"
#include "game_rules_test.h"
#include "test.h"
#include "game.h"


#define MAX_TESTS 25 /*!<Numero maximo de test*/



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

    if (all || test == 1) test1_game_rules_create();
    if (all || test == 2) test1_game_rules_set_next_action_c();
    if (all || test == 3) test2_game_rules_set_next_action_c();
    if (all || test == 4) test1_game_rules_set_days_c();
    if (all || test == 5) test2_game_rules_set_days_c();
    if (all || test == 6) test1_game_rules_set_n_cmd();
    if (all || test == 7) test2_game_rules_set_n_cmd();
    if (all || test == 8) test1_game_rules_set_notes_c();
    if (all || test == 9) test2_game_rules_set_notes_c();
    if (all || test == 10) test1_game_rules_get_next_action_c();
    if (all || test == 11) test2_game_rules_get_next_action_c();
    if (all || test == 12) test3_game_rules_get_next_action_c();
    if (all || test == 13) test1_game_rules_get_notes_c();
    if (all || test == 14) test2_game_rules_get_notes_c();
    if (all || test == 15) test3_game_rules_get_notes_c();
    if (all || test == 16) test1_game_rules_get_days_c();
    if (all || test == 17) test2_game_rules_get_days_c();
    if (all || test == 18) test3_game_rules_get_days_c();
    if (all || test == 19) test1_game_rules_get_n_cmd();
    if (all || test == 20) test2_game_rules_get_n_cmd();
    if (all || test == 21) test3_game_rules_get_n_cmd();
    if (all || test == 22) test1_game_rules_update();
    if (all || test == 23) test2_game_rules_update();
    if (all || test == 24) test3_game_rules_update();
    if (all || test == 25) test4_game_rules_update();
  
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_game_rules_create() {
  int result = game_rules_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test1_game_rules_set_next_action_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_set_next_action_c(pgr,5) == ERROR);
}

void test2_game_rules_set_next_action_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_set_next_action_c(pgr,5) == OK);
}

void test1_game_rules_set_days_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_set_days_c(pgr,5) == ERROR);
}

void test2_game_rules_set_days_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_set_days_c(pgr,5) == OK);
}

void test1_game_rules_set_n_cmd() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_set_n_cmd(pgr,5) == ERROR);
}

void test2_game_rules_set_n_cmd() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_set_n_cmd(pgr,5) == OK);
}

void test1_game_rules_set_notes_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_set_notes_c(pgr,5) == ERROR);
}

void test2_game_rules_set_notes_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_set_notes_c(pgr,5) == OK);
}

void test1_game_rules_get_next_action_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_get_next_action_c(pgr) == -1);
}

void test2_game_rules_get_next_action_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_get_next_action_c(pgr) == 0);
}

void test3_game_rules_get_next_action_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  game_rules_set_next_action_c(pgr,5);
  PRINT_TEST_RESULT(game_rules_get_next_action_c(pgr) == 5);
}

void test1_game_rules_get_notes_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_get_notes_c(pgr) == -1);
}

void test2_game_rules_get_notes_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_get_notes_c(pgr) == 0);
}

void test3_game_rules_get_notes_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  game_rules_set_notes_c(pgr,5);
  PRINT_TEST_RESULT(game_rules_get_notes_c(pgr) == 5);
}

void test1_game_rules_get_days_c() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_get_days_c(pgr) == -1);
}

void test2_game_rules_get_days_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_get_days_c(pgr) == 0);
}

void test3_game_rules_get_days_c() {
  Game_rules *pgr;
  pgr = game_rules_create();
  game_rules_set_days_c(pgr,5);
  PRINT_TEST_RESULT(game_rules_get_days_c(pgr) == 5);
}

void test1_game_rules_get_n_cmd() {
  Game_rules *pgr;
  pgr = NULL;
  PRINT_TEST_RESULT(game_rules_get_n_cmd(pgr) == -1);
}

void test2_game_rules_get_n_cmd() {
  Game_rules *pgr;
  pgr = game_rules_create();
  PRINT_TEST_RESULT(game_rules_get_n_cmd(pgr) == 0);
}

void test3_game_rules_get_n_cmd() {
  Game_rules *pgr;
  pgr = game_rules_create();
  game_rules_set_n_cmd(pgr,5);
  PRINT_TEST_RESULT(game_rules_get_n_cmd(pgr) == 5);
}

void test1_game_rules_update() {
  Game_rules *pgr;
  Game *pg;
  pgr = NULL;
  pg = NULL;
  PRINT_TEST_RESULT(game_rules_update (pg, pgr) == ERROR);
}

void test2_game_rules_update() {
  Game_rules *pgr;
  Game *pg;
  pgr = game_rules_create();
  pg = NULL;
  PRINT_TEST_RESULT(game_rules_update (pg, pgr) == ERROR);
}

void test3_game_rules_update() {
  Game_rules *pgr;
  Game *pg;
  pgr = NULL;
  pg = game_create();
  PRINT_TEST_RESULT(game_rules_update (pg, pgr) == ERROR);
}

void test4_game_rules_update() {
  Game_rules *pgr;
  Game *pg;
  pgr = game_rules_create();
  pg = game_create();
  PRINT_TEST_RESULT(game_rules_update (pg, pgr) == OK);
}

