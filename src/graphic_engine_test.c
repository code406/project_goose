/**
 * @brief It tests graphic_engine module
 *
 * @file graphic_engine_test.c
 * @author David Palomo
 * @version 2.0
 * @date 07-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "graphic_engine_test.h"
#include "test.h"

#define MAX_TESTS 1 /*!<Numero maximo de test*/

/**
 * @brief Funcion principal de pruebas para el modulo graphic_engine.
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
        printf("Running all test for module graphic_engine:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_graphic_engine_create();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_graphic_engine_create() {
  int result = graphic_engine_create()!=NULL ;
  PRINT_TEST_RESULT(result);
}
