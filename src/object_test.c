/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author David Palomo
 * @version 2.0
 * @date 05-04-2018
 * @updated 06-05-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"
#include "types.h"

#define MAX_TESTS 39 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo object.
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
        printf("Running all test for module object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();
    if (all || test == 3) test1_object_set_name();
    if (all || test == 4) test2_object_set_name();
    if (all || test == 5) test3_object_set_name();
    if (all || test == 6) test1_object_get_name();
    if (all || test == 7) test2_object_get_name();
    if (all || test == 8) test1_object_set_description();
    if (all || test == 9) test2_object_set_description();
    if (all || test == 10) test3_object_set_description();
    if (all || test == 11) test1_object_get_description();
    if (all || test == 12) test2_object_get_description();
    if (all || test == 13) test1_object_set_movable();
    if (all || test == 14) test2_object_set_movable();
    if (all || test == 15) test1_object_get_movable();
    if (all || test == 16) test2_object_get_movable();
    if (all || test == 17) test1_object_set_moved();
    if (all || test == 18) test2_object_set_moved();
    if (all || test == 19) test1_object_get_moved();
    if (all || test == 20) test2_object_get_moved();
    if (all || test == 21) test1_object_set_hidden();
    if (all || test == 22) test2_object_set_hidden();
    if (all || test == 23) test1_object_get_hidden();
    if (all || test == 24) test2_object_get_hidden();
    if (all || test == 25) test1_object_set_open_link();
    if (all || test == 26) test2_object_set_open_link();
    if (all || test == 27) test1_object_get_open_link();
    if (all || test == 28) test2_object_get_open_link();
    if (all || test == 29) test1_object_set_light_space();
    if (all || test == 30) test2_object_set_light_space();
    if (all || test == 31) test1_object_get_light_space();
    if (all || test == 32) test2_object_get_light_space();
    if (all || test == 33) test1_object_set_on();
    if (all || test == 34) test2_object_set_on();
    if (all || test == 35) test1_object_get_on();
    if (all || test == 36) test2_object_get_on();
    if (all || test == 37) test1_object_get_id();
    if (all || test == 38) test2_object_get_id();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_object_create() {
  int result = object_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_object_create() {
    Object *s;
    s = object_create(4);
    PRINT_TEST_RESULT(object_get_id(s) == 4);
}

void test1_object_set_name() {
    Object *s;
    s = object_create(5);
    PRINT_TEST_RESULT(object_set_name(s, "hola") == OK);
}

void test2_object_set_name() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_name(s, "hola") == ERROR);
}

void test3_object_set_name() {
    Object *s;
    s = object_create(5);
    PRINT_TEST_RESULT(object_set_name(s, NULL) == ERROR);
}

void test1_object_get_name() {
    Object *s;
    s = object_create(1);
    object_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(object_get_name(s), "adios") == 0);

}

void test2_object_get_name() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_name(s) == NULL);
}

void test1_object_set_description() {
    Object *s;
    s = object_create(5);
    PRINT_TEST_RESULT(object_set_description(s, "hola") == OK);
}

void test2_object_set_description() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_description(s, "hola") == ERROR);
}

void test3_object_set_description() {
    Object *s;
    s = object_create(5);
    PRINT_TEST_RESULT(object_set_description(s, NULL) == ERROR);
}

void test1_object_get_description() {
    Object *s;
    s = object_create(1);
    object_set_description(s, "adios");
    PRINT_TEST_RESULT(strcmp(object_get_description(s), "adios") == 0);

}

void test2_object_get_description() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_description(s) == NULL);
}

void test1_object_set_movable() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_movable(s, TRUE) == OK);
}

void test2_object_set_movable() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_movable(s, TRUE) == ERROR);
}

void test1_object_get_movable() {
    Object *s;
    s = object_create(1);
    object_set_movable(s, TRUE);
    PRINT_TEST_RESULT(object_get_movable(s) == TRUE);
}

void test2_object_get_movable() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_movable(s) == BOOLEAN_ERROR);
}

void test1_object_set_moved() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_moved(s, TRUE) == OK);
}

void test2_object_set_moved() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_moved(s, TRUE) == ERROR);
}

void test1_object_get_moved() {
    Object *s;
    s = object_create(1);
    object_set_moved(s, TRUE);
    PRINT_TEST_RESULT(object_get_moved(s) == TRUE);
}

void test2_object_get_moved() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_moved(s) == BOOLEAN_ERROR);
}

void test1_object_set_hidden() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_hidden(s, TRUE) == OK);
}

void test2_object_set_hidden() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_hidden(s, TRUE) == ERROR);
}

void test1_object_get_hidden() {
    Object *s;
    s = object_create(1);
    object_set_hidden(s, TRUE);
    PRINT_TEST_RESULT(object_get_hidden(s) == TRUE);
}

void test2_object_get_hidden() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_hidden(s) == BOOLEAN_ERROR);
}

void test1_object_set_open_link() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_open_link(s, TRUE) == OK);
}

void test2_object_set_open_link() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_open_link(s, TRUE) == ERROR);
}

void test1_object_get_open_link() {
    Object *s;
    s = object_create(1);
    object_set_open_link(s, TRUE);
    PRINT_TEST_RESULT(object_get_open_link(s) == TRUE);
}

void test2_object_get_open_link() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_open_link(s) == NO_ID);
}

void test1_object_set_light_space() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_light_space(s, TRUE) == OK);
}

void test2_object_set_light_space() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_light_space(s, TRUE) == ERROR);
}

void test1_object_get_light_space() {
    Object *s;
    s = object_create(1);
    object_set_light_space(s, TRUE);
    PRINT_TEST_RESULT(object_get_light_space(s) == TRUE);
}

void test2_object_get_light_space() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_light_space(s) == BOOLEAN_ERROR);
}

void test1_object_set_on() {
    Object *s;
    s = object_create(1);
    PRINT_TEST_RESULT(object_set_on(s, TRUE) == OK);
}

void test2_object_set_on() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_set_on(s, TRUE) == ERROR);
}

void test1_object_get_on() {
    Object *s;
    s = object_create(1);
    object_set_on(s, TRUE);
    PRINT_TEST_RESULT(object_get_on(s) == TRUE);
}

void test2_object_get_on() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_on(s) == BOOLEAN_ERROR);
}

void test1_object_get_id() {
    Object *s;
    s = object_create(25);
    PRINT_TEST_RESULT(object_get_id(s) == 25);
}

void test2_object_get_id() {
    Object *s = NULL;
    PRINT_TEST_RESULT(object_get_id(s) == NO_ID);
}
