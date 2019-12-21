/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @author David Palomo
 * @version 2.0
 * @date 05-04-2018
 * @updated 05-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 28 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo link.
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
        printf("Running all test for module link:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1)  test1_link_create();
    if (all || test == 2)  test2_link_create();
    if (all || test == 3)  test1_link_set_name();
    if (all || test == 4)  test2_link_set_name();
    if (all || test == 5)  test3_link_set_name();
    if (all || test == 6)  test1_link_set_espacio_1();
    if (all || test == 7)  test2_link_set_espacio_1();
    if (all || test == 8)  test3_link_set_espacio_1();
    if (all || test == 9)  test4_link_set_espacio_1();
    if (all || test == 10) test1_link_set_espacio_2();
    if (all || test == 11) test2_link_set_espacio_2();
    if (all || test == 12) test3_link_set_espacio_2();
    if (all || test == 13) test4_link_set_espacio_2();
    if (all || test == 14) test1_link_set_linked();
    if (all || test == 15) test2_link_set_linked();
    if (all || test == 16) test3_link_set_linked();
    if (all || test == 17) test4_link_set_linked();
    if (all || test == 18) test1_link_get_id();
    if (all || test == 19) test2_link_get_id();
    if (all || test == 20) test1_link_get_name();
    if (all || test == 21) test2_link_get_name();
    if (all || test == 22) test1_link_get_espacio_1();
    if (all || test == 23) test2_link_get_espacio_1();
    if (all || test == 24) test1_link_get_espacio_2();
    if (all || test == 25) test2_link_get_espacio_2();
    if (all || test == 26) test1_link_get_linked();
    if (all || test == 27) test2_link_get_linked();
    if (all || test == 28) test3_link_get_linked();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_link_create() {
  int result = link_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_link_create() {
    Link *s;
    s = link_create(4);
    PRINT_TEST_RESULT(link_get_id(s) == 4);
}

void test1_link_set_name() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_name(s, "hola") == OK);
}

void test2_link_set_name() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_name(s, "hola") == ERROR);
}

void test3_link_set_name() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_name(s, NULL) == ERROR);
}

void test1_link_set_espacio_1() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_espacio_1(s, 4) == OK);
}

void test2_link_set_espacio_1() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_espacio_1(s, 4) == ERROR);
}

void test3_link_set_espacio_1() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_espacio_1(s, NO_ID) == ERROR);
}

void test4_link_set_espacio_1() {
    Link *s;
    s = link_create(5);
    link_set_espacio_1(s, 4);
    PRINT_TEST_RESULT(link_get_espacio_1(s) == 4);
}

void test1_link_set_espacio_2() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_espacio_2(s, 4) == OK);
}

void test2_link_set_espacio_2() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_espacio_2(s, 4) == ERROR);
}

void test3_link_set_espacio_2() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_espacio_2(s, NO_ID) == ERROR);
}

void test4_link_set_espacio_2() {
    Link *s;
    s = link_create(5);
    link_set_espacio_2(s, 4);
    PRINT_TEST_RESULT(link_get_espacio_2(s) == 4);
}

void test1_link_set_linked() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_linked(s, TRUE) == OK);
}

void test2_link_set_linked() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_linked(s, FALSE) == OK);
}

void test3_link_set_linked() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_set_linked(s, TRUE) == ERROR);
}

void test4_link_set_linked() {
    Link *s;
    s = link_create(5);
    PRINT_TEST_RESULT(link_set_linked(s, 5) == ERROR);
}

void test1_link_get_id() {
    Link *s;
    s = link_create(25);
    PRINT_TEST_RESULT(link_get_id(s) == 25);
}

void test2_link_get_id() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_id(s) == NO_ID);
}

void test1_link_get_name() {
    Link *s;
    s = link_create(1);
    link_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(link_get_name(s), "adios") == 0);

}

void test2_link_get_name() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_name(s) == NULL);

}

void test1_link_get_espacio_1() {
    Link *s;
    s = link_create(5);
    link_set_espacio_1(s, 4);
    PRINT_TEST_RESULT(link_get_espacio_1(s) == 4);
}

void test2_link_get_espacio_1() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_espacio_1(s) == NO_ID);
}

void test1_link_get_espacio_2() {
    Link *s;
    s = link_create(5);
    link_set_espacio_2(s, 4);
    PRINT_TEST_RESULT(link_get_espacio_2(s) == 4);
}

void test2_link_get_espacio_2() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_espacio_2(s) == NO_ID);
}

void test1_link_get_linked() {
    Link *s;
    s = link_create(5);
    link_set_linked(s, TRUE);
    PRINT_TEST_RESULT(link_get_linked(s) == TRUE);
}

void test2_link_get_linked() {
    Link *s;
    s = link_create(5);
    link_set_linked(s, FALSE);
    PRINT_TEST_RESULT(link_get_linked(s) == FALSE);
}

void test3_link_get_linked() {
    Link *s = NULL;
    PRINT_TEST_RESULT(link_get_linked(s) == FALSE);
}
