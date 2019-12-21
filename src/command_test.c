/**
 * @brief It tests command module
 *
 * @file command_test.c
 * @author David Palomo
 * @version 3.0
 * @date 05-04-2018
 * @updated 08-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "command_test.h"
#include "test.h"

#define MAX_TESTS 29 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo command.
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
        printf("Running all test for module command:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1)  test1_command_create();
    if (all || test == 2)  test1_command_set_t_cmd();
    if (all || test == 3)  test2_command_set_t_cmd();
    if (all || test == 4)  test3_command_set_t_cmd();
    if (all || test == 5)  test4_command_set_t_cmd();
    if (all || test == 6)  test1_command_set_obj_name();
    if (all || test == 7)  test2_command_set_obj_name();
    if (all || test == 8)  test3_command_set_obj_name();
    if (all || test == 9)  test4_command_set_obj_name();
    if (all || test == 10) test1_command_set_direction();
    if (all || test == 11) test2_command_set_direction();
    if (all || test == 12) test3_command_set_direction();
    if (all || test == 13) test4_command_set_direction();
    if (all || test == 14) test1_command_set_status();
    if (all || test == 15) test2_command_set_status();
    if (all || test == 16) test3_command_set_status();
    if (all || test == 17) test4_command_set_status();
    if (all || test == 18) test1_command_get_t_cmd();
    if (all || test == 19) test2_command_get_t_cmd();
    if (all || test == 20) test1_command_get_obj_name();
    if (all || test == 21) test2_command_get_obj_name();
    if (all || test == 22) test1_command_get_direction();
    if (all || test == 23) test2_command_get_direction();
    if (all || test == 24) test1_command_get_status();
    if (all || test == 25) test2_command_get_status();
    if (all || test == 26) test3_command_get_status();
    if (all || test == 27) test1_command_write_log();
    if (all || test == 28) test2_command_write_log();
    if (all || test == 29) test3_command_write_log();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_command_create() {
  int result = command_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test1_command_set_t_cmd() {
    D_Command *s;
    int i;
    s = command_create();
    for (i=NO_CMD+1; i<=MOVE; i++)
    {
      PRINT_TEST_RESULT(command_set_t_cmd(s, i) == OK);
    }
}

void test2_command_set_t_cmd() {
    D_Command *s;
    int i;
    s = command_create();
    for (i=NO_CMD; i<=MOVE; i++)
    {
      command_set_t_cmd(s, i);
      PRINT_TEST_RESULT(command_get_t_cmd(s) == i);
    }
}

void test3_command_set_t_cmd() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_t_cmd(s, NO_CMD) == ERROR);
}

void test4_command_set_t_cmd() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_set_t_cmd(s, FOLLOWING) == ERROR);
}

void test1_command_set_obj_name() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_obj_name(s, "hola") == OK);
}

void test2_command_set_obj_name() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_set_obj_name(s, "hola") == ERROR);
}

void test3_command_set_obj_name() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_obj_name(s, NULL) == ERROR);
}

void test4_command_set_obj_name() {
    D_Command *s;
    s = command_create();
    command_set_obj_name(s, "hola");
    PRINT_TEST_RESULT(strcmp(command_get_obj_name(s),"hola")==0);
}

void test1_command_set_direction() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_direction(s, "hola") == OK);
}

void test2_command_set_direction() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_set_direction(s, "hola") == ERROR);
}

void test3_command_set_direction() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_direction(s, NULL) == ERROR);
}

void test4_command_set_direction() {
    D_Command *s;
    s = command_create();
    command_set_direction(s, "hola");
    PRINT_TEST_RESULT(strcmp(command_get_direction(s),"hola")==0);
}

void test1_command_set_status() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_status(s, "OK") == OK);
}

void test2_command_set_status() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_status(s, "ERROR") == OK);
}

void test3_command_set_status() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_set_status(s, "OK") == ERROR);
}

void test4_command_set_status() {
    D_Command *s;
    s = command_create();
    PRINT_TEST_RESULT(command_set_status(s, NULL) == ERROR);
}

void test1_command_get_t_cmd() {
    D_Command *s;
    int i;
    s = command_create();
    for (i=NO_CMD; i<=MOVE; i++)
    {
      command_set_t_cmd(s, i);
      PRINT_TEST_RESULT(command_get_t_cmd(s) == i);
    }
}

void test2_command_get_t_cmd() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_get_t_cmd(s) == NO_ID);
}

void test1_command_get_obj_name() {
    D_Command *s;
    s = command_create();
    command_set_obj_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(command_get_obj_name(s), "adios") == 0);

}

void test2_command_get_obj_name() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_get_obj_name(s) == NULL);

}

void test1_command_get_direction() {
    D_Command *s;
    s = command_create();
    command_set_direction(s, "adios");
    PRINT_TEST_RESULT(strcmp(command_get_direction(s), "adios") == 0);

}

void test2_command_get_direction() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_get_direction(s) == NULL);

}

void test1_command_get_status() {
    D_Command *s;
    s = command_create();
    command_set_status(s, "OK");
    PRINT_TEST_RESULT(strcmp(command_get_status(s), "OK") == 0);
}

void test2_command_get_status() {
    D_Command *s;
    s = command_create();
    command_set_status(s, "ERROR");
    PRINT_TEST_RESULT(strcmp(command_get_status(s), "ERROR") == 0);
}

void test3_command_get_status() {
    D_Command *s = NULL;
    PRINT_TEST_RESULT(command_get_status(s) == NULL);
}

void test1_command_write_log() {
    D_Command *s;
    FILE * pf = NULL;
    s = command_create();
    PRINT_TEST_RESULT(command_write_log(s, pf) == ERROR);
}

void test2_command_write_log() {
    D_Command *s = NULL;
    FILE * f = NULL;
    f = fopen("log.txt", "w");
    PRINT_TEST_RESULT(command_write_log(s, f) == ERROR);
    fclose(f);
}

void test3_command_write_log() {
    D_Command *s;
    FILE * f = NULL;
    f = fopen("log.txt", "w");
    s = command_create();
    PRINT_TEST_RESULT(command_write_log(s, f) == OK);
    fclose(f);
}
