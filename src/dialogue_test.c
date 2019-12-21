/**
 * @brief Pruebas del modulo dialogue
 *
 * @file dialogue_test.c
 * @author Arturo Morcillo
 * @version 1.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"
#include "dialogue_test.h"
#include "test.h"
#include "game.h"
#include "command.h"

#define MAX_TESTS 33 /*!<Numero maximo de test*/



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


    if (all || test == 1) test1_dialogue_create();
    if (all || test == 2) test1_dialogue_set_last_cmd();
    if (all || test == 3) test2_dialogue_set_last_cmd();
    if (all || test == 4) test3_dialogue_set_last_cmd();
    if (all || test == 5) test1_dialogue_set_last_cmd_status();
    if (all || test == 6) test2_dialogue_set_last_cmd_status();
    if (all || test == 7) test3_dialogue_set_last_cmd_status();
    if (all || test == 8) test1_dialogue_set_plantilla();
    if (all || test == 9) test2_dialogue_set_plantilla();
    if (all || test == 10) test3_dialogue_set_plantilla();
    if (all || test == 11) test4_dialogue_set_plantilla();
    if (all || test == 12) test1_dialogue_set_part1();
    if (all || test == 13) test2_dialogue_set_part1();
    if (all || test == 14) test3_dialogue_set_part1();
    if (all || test == 15) test1_dialogue_set_part2();
    if (all || test == 16) test2_dialogue_set_part2();
    if (all || test == 17) test3_dialogue_set_part2();
    if (all || test == 18) test1_dialogue_set_part3();
    if (all || test == 19) test2_dialogue_set_part3();
    if (all || test == 20) test3_dialogue_set_part3();
    if (all || test == 21) test4_dialogue_set_part3();
    if (all || test == 22) test1_dialogue_get_last_cmd();
    if (all || test == 23) test1_dialogue_get_last_cmd();
    if (all || test == 24) test1_dialogue_get_last_cmd_status();
    if (all || test == 25) test2_dialogue_get_last_cmd_status();
    if (all || test == 26) test3_dialogue_get_last_cmd_status();
    if (all || test == 27) test1_dialogue_get_part1();
    if (all || test == 28) test2_dialogue_get_part1();
    if (all || test == 29) test3_dialogue_get_part1();
    if (all || test == 30) test1_dialogue_get_part2();
    if (all || test == 31) test2_dialogue_get_part2();
    if (all || test == 32) test3_dialogue_get_part2();
    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_dialogue_create() {
  int result = dialogue_create("dialogue.dat")!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test1_dialogue_set_last_cmd(){
    T_Command cmd;
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    for(cmd = EXIT; cmd <= SHOWMAP; cmd++){
        game_set_last_t_cmd(game, cmd);
        PRINT_TEST_RESULT(dialogue_set_last_cmd(pd, game) == OK);
    }
}

void test2_dialogue_set_last_cmd(){
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    game_set_last_t_cmd(game, NO_CMD);
    PRINT_TEST_RESULT(dialogue_set_last_cmd(pd, game) == ERROR);
}

void test3_dialogue_set_last_cmd(){
    Dialogue *pd = NULL;
    Game *game = game_create();
    game_set_last_t_cmd(game, MOVE);
    PRINT_TEST_RESULT(dialogue_set_last_cmd(pd, game) == ERROR);
}

void test1_dialogue_set_last_cmd_status(){
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    game_set_last_cmd_status(game, "OK");
    PRINT_TEST_RESULT(dialogue_set_last_cmd_status(pd, game) == OK);
}

void test2_dialogue_set_last_cmd_status(){
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    game_set_last_cmd_status(game, "ERROR");
    PRINT_TEST_RESULT(dialogue_set_last_cmd_status(pd, game) == OK);
}

void test3_dialogue_set_last_cmd_status(){
    Dialogue *pd = NULL;
    Game *game = game_create();
    game_set_last_cmd_status(game, "OK");
    PRINT_TEST_RESULT(dialogue_set_last_cmd_status(pd, game) == ERROR);
}

void test1_dialogue_set_plantilla(){
    Dialogue *pd;
    FILE *file;
    pd = NULL;
    file = NULL;
    PRINT_TEST_RESULT(dialogue_set_plantilla(pd, file) == ERROR);
}

void test2_dialogue_set_plantilla(){
    Dialogue *pd;
    FILE *file;
    pd = dialogue_create("dialogue.dat");
    file = NULL;
    PRINT_TEST_RESULT(dialogue_set_plantilla(pd, file) == ERROR);
}

void test3_dialogue_set_plantilla(){
    Dialogue *pd;
    FILE *file;
    pd = NULL;
    file = fopen("dialogue.dat","r");
    PRINT_TEST_RESULT(dialogue_set_plantilla(pd, file) == ERROR);
}

void test4_dialogue_set_plantilla(){
    Dialogue *pd;
    FILE *file;
    pd = dialogue_create("dialogue.dat");
    file = fopen("dialogue.dat","r");
    PRINT_TEST_RESULT(dialogue_set_plantilla(pd, file) == OK);
}

void test1_dialogue_set_part1 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part1(pd, cadena) == ERROR);
    
}
void test2_dialogue_set_part1 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part1(pd, cadena) == ERROR);
}

void test3_dialogue_set_part1 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part1(pd, cadena) == ERROR);
}

void test4_dialogue_set_part1 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part1(pd, cadena) == OK);
}

void test1_dialogue_set_part2 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part2(pd, cadena) == ERROR);
    
}
void test2_dialogue_set_part2 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part2(pd, cadena) == ERROR);
}

void test3_dialogue_set_part2 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part2(pd, cadena) == ERROR);
}

void test4_dialogue_set_part2 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part2(pd, cadena) == OK);
}

void test1_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,1) == ERROR);
    
}
void test2_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = NULL;
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,1) == ERROR);
}

void test3_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = NULL;
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,1) == ERROR);
}

void test4_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,-10,2) == ERROR);
}

void test5_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,-2) == ERROR);
}

void test6_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1000,2) == ERROR);
}

void test7_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,2000) == ERROR);
}

void test8_dialogue_set_part3 (){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    PRINT_TEST_RESULT(dialogue_set_part3(pd, cadena,1,2) == OK);
}

void test1_dialogue_get_last_cmd(){
    T_Command cmd;
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    for(cmd = EXIT; cmd <= SHOWMAP; cmd++){
        game_set_last_t_cmd(game, cmd);
        dialogue_set_last_cmd(pd, game);
        PRINT_TEST_RESULT(dialogue_get_last_cmd(pd) == cmd);
    };
}

void test2_dialogue_get_last_cmd(){
    Dialogue *pd = NULL;
    Game *game = game_create();
    game_set_last_t_cmd(game, MOVE);
    PRINT_TEST_RESULT(dialogue_set_last_cmd(pd, game) == ERROR);
}

void test1_dialogue_get_last_cmd_status(){
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    game_set_last_cmd_status(game, "OK");
    dialogue_set_last_cmd_status(pd, game);
    PRINT_TEST_RESULT(strcmp(dialogue_get_last_cmd_status(pd), "OK") == 0);
}

void test2_dialogue_get_last_cmd_status(){
    Dialogue *pd = dialogue_create("dialogue.dat");
    Game *game = game_create();
    game_set_last_cmd_status(game, "ERROR");
    dialogue_set_last_cmd_status(pd, game);
    PRINT_TEST_RESULT(strcmp(dialogue_get_last_cmd_status(pd), "ERROR") == 0);
}

void test3_dialogue_get_last_cmd_status(){
    Dialogue *pd = NULL;
    Game *game = game_create();
    game_set_last_cmd_status(game, "OK");
    dialogue_set_last_cmd_status(pd, game);
    PRINT_TEST_RESULT(strcmp(dialogue_get_last_cmd_status(pd), "ERROR") == 0);
}

void test1_dialogue_get_part1(){
    Dialogue *pd;
    pd = NULL;
    PRINT_TEST_RESULT(dialogue_get_part1(pd) == ERROR);
}

void test2_dialogue_get_part1(){
    Dialogue *pd;
    pd = dialogue_create("dialogue.dat");
    PRINT_TEST_RESULT(dialogue_get_part1(pd) == NULL);
}

void test3_dialogue_get_part1(){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    dialogue_set_part1(pd,cadena);
    PRINT_TEST_RESULT(strcmp(dialogue_get_part1(pd), "Hola") == 0);
}

void test1_dialogue_get_part2(){
    Dialogue *pd;
    pd = NULL;
    PRINT_TEST_RESULT(dialogue_get_part2(pd) == ERROR);
}

void test2_dialogue_get_part2(){
    Dialogue *pd;
    pd = dialogue_create("dialogue.dat");
    dialogue_set_part2(pd, NULL);
    PRINT_TEST_RESULT(dialogue_get_part2(pd) == NULL);
}

void test3_dialogue_get_part2(){
    Dialogue *pd;
    char *cadena;
    pd = dialogue_create("dialogue.dat");
    cadena = "Hola";
    dialogue_set_part2(pd,cadena);
    PRINT_TEST_RESULT(strcmp(dialogue_get_part2(pd), "Hola") == 0);
}
