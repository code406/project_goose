/**
 * @brief Pruebas del modulo space
 *
 * @file space_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"
#include "set.h"

#define MAX_TESTS 63 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo Space.
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
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test1_space_set_name();
    if (all || test == 4) test2_space_set_name();
    if (all || test == 5) test3_space_set_name();
    if (all || test == 6) test1_space_set_description();
    if (all || test == 7) test2_space_set_description();
    if (all || test == 8) test1_space_set_north_link();
    if (all || test == 9) test2_space_set_north_link();
    if (all || test == 10) test1_space_set_south_link();
    if (all || test == 11) test2_space_set_south_link();
    if (all || test == 12) test1_space_set_east_link();
    if (all || test == 13) test2_space_set_east_link();
    if (all || test == 14) test1_space_set_west_link();
    if (all || test == 15) test2_space_set_west_link();
    if (all || test == 16) test1_space_set_up_link();
    if (all || test == 17) test2_space_set_up_link();
    if (all || test == 18) test1_space_set_down_link();
    if (all || test == 19) test1_space_set_down_link();
    if (all || test == 20) test1_space_set_lit();
    if (all || test == 21) test2_space_set_lit();
    if (all || test == 22) test1_space_set_ocupada();
    if (all || test == 23) test2_space_set_ocupada();
    if (all || test == 24) test1_space_get_name();
    if (all || test == 25) test2_space_get_name();
    if (all || test == 26) test1_space_get_description();
    if (all || test == 27) test2_space_get_description();
    if (all || test == 28) test1_space_get_gdesc();
    if (all || test == 29) test2_space_get_gdesc();
    if (all || test == 30) test3_space_get_gdesc();
    if (all || test == 31) test4_space_get_gdesc();
    if (all || test == 32) test5_space_get_gdesc();
    if (all || test == 33) test6_space_get_gdesc();
    if (all || test == 34) test1_space_get_north_link();
    if (all || test == 35) test2_space_get_north_link();
    if (all || test == 36) test1_space_get_south_link();
    if (all || test == 37) test2_space_get_south_link();
    if (all || test == 38) test1_space_get_east_link();
    if (all || test == 39) test2_space_get_east_link();
    if (all || test == 40) test1_space_get_west_link();
    if (all || test == 41) test2_space_get_west_link();
    if (all || test == 42) test1_space_get_up_link();
    if (all || test == 43) test2_space_get_up_link();
    if (all || test == 44) test1_space_get_down_link();
    if (all || test == 45) test2_space_get_down_link();
    if (all || test == 46) test1_space_get_lit();
    if (all || test == 47) test2_space_get_lit();
    if (all || test == 48) test1_space_get_ocupada();
    if (all || test == 49) test2_space_get_ocupada();
    if (all || test == 50) test1_space_get_id();
    if (all || test == 51) test2_space_get_id();
    if (all || test == 52) test1_space_add_object();
    if (all || test == 53) test2_space_add_object();
    if (all || test == 54) test3_space_add_object();
    if (all || test == 55) test1_space_get_ids_objects();
    if (all || test == 56) test2_space_get_ids_objects();
    if (all || test == 57) test1_space_del_object();
    if (all || test == 58) test2_space_del_object();
    if (all || test == 59) test3_space_del_object();
    if (all || test == 60) test1_space_check_object();
    if (all || test == 61) test2_space_check_object();
    if (all || test == 62) test3_space_check_object();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_space_create() {
  int result = space_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_space_create() {
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_id(s) == 4);
}

void test1_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
}

void test2_space_set_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
}

void test1_space_set_description() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_description(s, "prueba") == OK);
}

void test2_space_set_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_description(s, "hola") == ERROR);
}

void test3_space_set_description() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_description(s, NULL) == ERROR);
}

void test1_space_set_north_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_north_link(s, 4) == OK);
}

void test2_space_set_north_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_north_link(s, 4) == ERROR);
}

void test1_space_set_south_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_south_link(s, 4) == OK);
}

void test2_space_set_south_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_south_link(s, 4) == ERROR);
}

void test1_space_set_east_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_east_link(s, 4) == OK);
}

void test2_space_set_east_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_east_link(s, 4) == ERROR);
}

void test1_space_set_west_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_west_link(s, 4) == OK);
}

void test2_space_set_west_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_west_link(s, 4) == ERROR);
}

void test1_space_set_up_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_up_link(s, 4) == OK);
}

void test2_space_set_up_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_up_link(s, 4) == ERROR);
}

void test1_space_set_down_link() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_down_link(s, 4) == OK);
}

void test2_space_set_down_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_down_link(s, 4) == ERROR);
}

void test1_space_set_gdesc() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc(s,"hola",0) == OK);
}

void test2_space_set_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc(s,"Hola",0) == ERROR);
}
void test3_space_set_gdesc() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc(s,"hola",1) == OK);
}

void test4_space_set_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc(s,"Hola",1) == ERROR);
}
void test5_space_set_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc(s,"Hola",2) == ERROR);
}
void test6_space_set_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc(s,"Hola",2) == ERROR);
}

void test1_space_set_lit() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_lit(s, 1) == OK);
}
void test2_space_set_lit() {
  Space* s = NULL;
  PRINT_TEST_RESULT(space_set_lit(s, 1) == ERROR);
}

void test1_space_set_ocupada() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_lit(s, 1) == OK);
}
void test2_space_set_ocupada() {
  Space* s = NULL;
  PRINT_TEST_RESULT(space_set_lit(s, 1) == ERROR);
}

void test1_space_get_name() {
    Space *s;
    s = space_create(1);
    space_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);

}

void test2_space_get_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);

}

void test1_space_get_description() {
    Space *s;
    s = space_create(1);
    space_set_description(s, "adios");
    PRINT_TEST_RESULT(strcmp(space_get_description(s), "adios") == 0);

}

void test2_space_get_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_description(s) == NULL);

}

void test1_space_get_gdesc() {
    Space *s;
    s = space_create(1);
    space_set_gdesc(s,"hola",0);
    PRINT_TEST_RESULT(strcmp(space_get_gdesc(s,0), "hola")==0);

}

void test2_space_get_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc(s,0) == NULL);
}



void test3_space_get_gdesc() {
    Space *s;
    s = space_create(1);
    space_set_gdesc(s,"hola",1);
    PRINT_TEST_RESULT(strcmp(space_get_gdesc(s,1), "hola")==0);

}

void test4_space_get_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc(s,1) == NULL);
}


void test5_space_get_gdesc() {
    Space *s;
    s = space_create(1);
    space_set_gdesc(s,"hola",2);
    PRINT_TEST_RESULT(strcmp(space_get_gdesc(s,2),"hola")==0);

}

void test6_space_get_gdesc() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc(s,2) == NULL);
}

void test1_space_get_north_link() {
    Space *s;
    s = space_create(5);
    space_set_north_link(s, 4);
    PRINT_TEST_RESULT(space_get_north_link(s) == 4);
}

void test2_space_get_north_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_north_link(s) == NO_ID);
}

void test1_space_get_south_link() {
    Space *s;
    s = space_create(5);
    space_set_south_link(s, 2);
    PRINT_TEST_RESULT(space_get_south_link(s) == 2);
}

void test2_space_get_south_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_south_link(s) == NO_ID);
}

void test1_space_get_east_link() {
    Space *s;
    s = space_create(5);
    space_set_east_link(s, 1);
    PRINT_TEST_RESULT(space_get_east_link(s) == 1);
}

void test2_space_get_east_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_east_link(s) == NO_ID);
}

void test1_space_get_west_link() {
    Space *s;
    s = space_create(5);
    space_set_west_link(s, 6);
    PRINT_TEST_RESULT(space_get_west_link(s) == 6);
}

void test2_space_get_west_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_west_link(s) == NO_ID);
}

void test1_space_get_up_link() {
    Space *s;
    s = space_create(5);
    space_set_up_link(s, 6);
    PRINT_TEST_RESULT(space_get_up_link(s) == 6);
}

void test2_space_get_up_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_up_link(s) == NO_ID);
}

void test1_space_get_down_link() {
    Space *s;
    s = space_create(5);
    space_set_down_link(s, 6);
    PRINT_TEST_RESULT(space_get_down_link(s) == 6);
}

void test2_space_get_down_link() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_down_link(s) == NO_ID);
}

void test1_space_get_lit() {
  Space* s = space_create(5);
  space_set_lit(s, 1);
  PRINT_TEST_RESULT(space_get_lit(s) == TRUE);
}

void test2_space_get_lit() {
  Space* s = NULL;
  PRINT_TEST_RESULT(space_get_lit(s) == FALSE);
}

void test1_space_get_ocupada() {
  Space* s = space_create(5);
  space_set_ocupada(s, 1);
  PRINT_TEST_RESULT(space_get_ocupada(s) == TRUE);
}

void test2_space_get_ocupada() {
  Space* s = NULL;
  PRINT_TEST_RESULT(space_get_ocupada(s) == FALSE);
}

void test1_space_get_id() {
    Space *s;
    s = space_create(25);
    PRINT_TEST_RESULT(space_get_id(s) == 25);
}

void test2_space_get_id() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}



void test1_space_add_object() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_add_object(s,1) == ERROR);
}

void test2_space_add_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s,1) == OK);
}
void test3_space_add_object() {
    int i;
    Space *s;
    s = space_create(1);
    for (i=1;i<MAX_ID+1;i++)
      space_add_object(s,i);
    PRINT_TEST_RESULT(space_add_object(s,1) == OK);
}

void test1_space_get_ids_objects() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_get_ids_objects(s) == NULL);
}

void test2_space_get_ids_objects() {
    Space *s;
    s=space_create(1);
    space_add_object(s, 2);
    PRINT_TEST_RESULT(space_get_ids_objects(s) != NULL);
}




void test1_space_del_object() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_del_object(s,1) == ERROR);
}

void test2_space_del_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_del_object(s,1) == ERROR);
}

void test3_space_del_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s,1);
    PRINT_TEST_RESULT(space_del_object(s,1) == OK);
}

void test1_space_check_object() {
    Space *s;
    s = NULL;
    PRINT_TEST_RESULT(space_check_object(s,1) == FALSE);
}

void test2_space_check_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_check_object(s,1) == FALSE);
}

void test3_space_check_object() {
    Space *s;
    s = space_create(1);
    space_add_object(s,1);
    PRINT_TEST_RESULT(space_check_object(s,1) == TRUE);
}
