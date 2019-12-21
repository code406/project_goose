/**
 * @brief Pruebas del modulo inventory
 *
 * @file inventory_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"
#include "set.h"

#define MAX_TESTS 19 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo Inventory.
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
        printf("Running all test for module inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test1_inventory_add_id();
    if (all || test == 3) test2_inventory_add_id();
    if (all || test == 4) test3_inventory_add_id();
    if (all || test == 5) test1_inventory_get_ids();
    if (all || test == 6) test2_inventory_get_ids();
    if (all || test == 7) test3_inventory_get_ids();
    if (all || test == 8) test1_inventory_del_id();
    if (all || test == 9) test2_inventory_del_id();
    if (all || test == 10) test3_inventory_del_id();
    if (all || test == 11) test1_inventory_check_id();
    if (all || test == 12) test2_inventory_check_id();
    if (all || test == 13) test3_inventory_check_id();
    if (all || test == 14) test1_inventory_get_num_objects();
    if (all || test == 15) test2_inventory_get_num_objects();
    if (all || test == 16) test3_inventory_get_num_objects();
    if (all || test == 17) test1_inventory_set_ids();
    if (all || test == 18) test2_inventory_set_ids();
    if (all || test == 19) test3_inventory_set_ids();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_inventory_create() {
  int result = inventory_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test1_inventory_add_id() {
    Inventory *s;
    s = NULL;
    PRINT_TEST_RESULT(inventory_add_id(s,1) == ERROR);
}

void test2_inventory_add_id() {
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_add_id(s,1) == OK);
}
void test3_inventory_add_id() {
    int i;
    Inventory *s;
    s = inventory_create();
    for (i=1;i<inventory_get_num_objects(s)+1;i++)
      inventory_add_id(s,i);
    PRINT_TEST_RESULT(inventory_add_id(s,1) == ERROR);
}

void test1_inventory_get_ids() {
    Inventory *s;
    s = NULL;
    PRINT_TEST_RESULT(inventory_get_ids(s) == NULL);
}
void test2_inventory_get_ids() {
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_get_ids(s) != NULL);
}
void test3_inventory_get_ids() {
    Inventory *s;
    s=inventory_create();
    inventory_add_id(s, 2);
    PRINT_TEST_RESULT(inventory_get_ids(s) != NULL);
}
void test1_inventory_del_id() {
    Inventory *s;
    s = NULL;
    PRINT_TEST_RESULT(inventory_del_id(s,1) == ERROR);
}

void test2_inventory_del_id() {
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_del_id(s,1) == ERROR);
}

void test3_inventory_del_id() {
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s,1);
    PRINT_TEST_RESULT(inventory_del_id(s,1) == OK);
}

void test1_inventory_check_id() {
    Inventory *s;
    s = NULL;
    PRINT_TEST_RESULT(inventory_check_id(s,1) == FALSE);
}

void test2_inventory_check_id() {
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_check_id(s,1) == FALSE);
}

void test3_inventory_check_id() {
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s,1);
    PRINT_TEST_RESULT(inventory_check_id(s,1) == TRUE);
}


void test1_inventory_get_num_objects() {
    Inventory *s;
    s = NULL;
    PRINT_TEST_RESULT(inventory_get_num_objects(s) == 0);
}

void test2_inventory_get_num_objects() {
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_get_num_objects(s) == MAX_ID);
}

void test3_inventory_get_num_objects() {
    Inventory *s;
    s = inventory_create();
    inventory_set_num_objects(s,2);
    PRINT_TEST_RESULT(inventory_get_num_objects(s) == 2);
}

void test1_inventory_set_ids() {
    Inventory *s;
    Set *ps;
    s = NULL;
    ps = set_create();
    PRINT_TEST_RESULT(inventory_set_ids(s,ps) == ERROR);
}

void test2_inventory_set_ids() {
    Inventory *s;
    Set *ps;
    s = inventory_create();
    ps = NULL;
    PRINT_TEST_RESULT(inventory_set_ids(s,ps) == ERROR);
}

void test3_inventory_set_ids() {
    Inventory *s;
    Set *ps;
    s = inventory_create();
    ps = set_create();
    PRINT_TEST_RESULT(inventory_set_ids(s,ps) == OK);
}
