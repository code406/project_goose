/**
 * @brief Pruebas del modulo player
 *
 * @file player_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"
#include "set.h"
#include "inventory.h"

#define MAX_TESTS 29 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo Player.
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
        printf("Running all test for module player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_player_create();
    if (all || test == 2) test2_player_create();
    if (all || test == 3) test1_player_set_name();
    if (all || test == 4) test2_player_set_name();
    if (all || test == 5) test3_player_set_name();
    if (all || test == 6) test1_player_get_name();
    if (all || test == 7) test2_player_get_name();
    if (all || test == 8) test1_player_get_id();
    if (all || test == 9) test2_player_get_id();
    if (all || test == 10) test1_player_add_object();
    if (all || test == 11) test2_player_add_object();
    if (all || test == 12) test3_player_add_object();
    if (all || test == 13) test1_player_get_objects();
    if (all || test == 14) test2_player_get_objects();
    if (all || test == 15) test3_player_get_objects();
    if (all || test == 16) test1_player_del_object();
    if (all || test == 17) test2_player_del_object();
    if (all || test == 18) test3_player_del_object();
    if (all || test == 19) test1_player_check_object();
    if (all || test == 20) test2_player_check_object();
    if (all || test == 21) test3_player_check_object();
    if (all || test == 22) test1_player_set_location();
    if (all || test == 23) test2_player_set_location();
    if (all || test == 24) test1_player_get_location();
    if (all || test == 25) test2_player_get_location();
    if (all || test == 26) test3_player_get_location();
    if (all || test == 27) test1_player_get_num_objects();
    if (all || test == 28) test2_player_get_num_objects();
    if (all || test == 29) test3_player_get_num_objects();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_player_create() {
  int result = player_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_player_create() {
    Player *s;
    s = player_create(4);
    PRINT_TEST_RESULT(player_get_id(s) == 4);
}

void test1_player_set_name() {
    Player *s;
    s = player_create(5);
    PRINT_TEST_RESULT(player_set_name(s, "hola") == OK);
}

void test2_player_set_name() {
    Player *s = NULL;
    PRINT_TEST_RESULT(player_set_name(s, "hola") == ERROR);
}

void test3_player_set_name() {
    Player *s;
    s = player_create(5);
    PRINT_TEST_RESULT(player_set_name(s, NULL) == ERROR);
}


void test1_player_get_name() {
    Player *s;
    s = player_create(1);
    player_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(player_get_name(s), "adios") == 0);

}

void test2_player_get_name() {
    Player *s = NULL;
    PRINT_TEST_RESULT(player_get_name(s) == NULL);

}


void test1_player_get_id() {
    Player *s;
    s = player_create(25);
    PRINT_TEST_RESULT(player_get_id(s) == 25);
}

void test2_player_get_id() {
    Player *s = NULL;
    PRINT_TEST_RESULT(player_get_id(s) == NO_ID);
}

void test1_player_add_object() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_add_object(s,1) == ERROR);
}

void test2_player_add_object() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_add_object(s,1) == OK);
}
void test3_player_add_object() {
    int i;
    Player *s;
    s = player_create(1);
    for (i=1;i<MAX_ID+1;i++)
      player_add_object(s,i);
    PRINT_TEST_RESULT(player_add_object(s,1) == ERROR);
}

void test1_player_get_objects() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_get_objects(s) == NULL);
}
void test2_player_get_objects() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_get_objects(s) != NULL);
}
void test3_player_get_objects() {
    Player *s;
    s=player_create(1);
    player_add_object(s, 2);
    PRINT_TEST_RESULT(player_get_objects(s) != NULL);
}
void test1_player_del_object() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_del_object(s,1) == ERROR);
}

void test2_player_del_object() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_del_object(s,1) == ERROR);
}

void test3_player_del_object() {
    Player *s;
    s = player_create(1);
    player_add_object(s,1);
    PRINT_TEST_RESULT(player_del_object(s,1) == OK);
}

void test1_player_check_object() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_check_object(s,1) == FALSE);
}

void test2_player_check_object() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_check_object(s,1) == FALSE);
}

void test3_player_check_object() {
    Player *s;
    s = player_create(1);
    player_add_object(s,1);
    PRINT_TEST_RESULT(player_check_object(s,1) == TRUE);
}



void test1_player_set_location() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_set_location(s,1) == ERROR);
}

void test2_player_set_location() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_set_location(s,1) == OK);
}

void test1_player_get_location() {
    Player *s;
    s = NULL;
    PRINT_TEST_RESULT(player_get_location(s) == NO_ID);
}

void test2_player_get_location() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_get_location(s) == NO_ID);
}

void test3_player_get_location() {
    Player *s;
    s = player_create(1);
    player_set_location(s,2);
    PRINT_TEST_RESULT(player_get_location(s) == 2);
}


void test1_player_get_num_objects() {
    Player *s;
    s = player_create(1);
    PRINT_TEST_RESULT(player_get_num_objects(s) == 0);
}

void test2_player_get_num_objects() {
    Player *s;
    s = player_create(1);
    player_add_object(s,2);
    PRINT_TEST_RESULT(player_get_num_objects(s) == 1);
}

void test3_player_get_num_objects() {
    Player *s;
    s = player_create(1);
    player_add_object(s,2);
    player_add_object(s,1);
    player_add_object(s,4);
    player_del_object(s,1);
    PRINT_TEST_RESULT(player_get_num_objects(s) == 2);
}
