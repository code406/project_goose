/**
 * @brief Pruebas del modulo game_rules
 *
 * @file game_rules_test.h
 * @author Arturo Morcillo
 * @copyright GNU Public License
 */

#ifndef game_rules_TEST_H
#define game_rules_TEST_H

/**
 * @test Prueba la función de crear las game_rules
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al inventario creado
 */
void test1_game_rules_create();

/**
 * @test Prueba la función para fijar el valor de next action en game_rules
 * @pre game_rules que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_game_rules_set_next_action_c();

/**
 * @test Prueba la función para fijar el valor de el contador de next action en game_rules
 * @pre game_rules creado anteriormente
 * @post La salida debe ser OK
 */
void test2_game_rules_set_next_action_c();

/**
 * @test Prueba la función para fijar el valor de el contador de days en game_rules
 * @pre game_rules que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_game_rules_set_days_c();

/**
 * @test Prueba la función para fijar el valor de el contador de days en game_rules
 * @pre game_rules creado anteriormente
 * @post La salida debe ser OK
 */
void test2_game_rules_set_days_c();

/**
 * @test Prueba la función para fijar el valor de el contador de n_cmd en game_rules
 * @pre game_rules que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_game_rules_set_n_cmd();

/**
 * @test Prueba la función para fijar el valor de el contador de n_cmd en game_rules
 * @pre game_rules creado anteriormente
 * @post La salida debe ser OK
 */
void test2_game_rules_set_n_cmd();

/**
 * @test Prueba la función para fijar el valor de el contador de notes en game_rules
 * @pre game_rules que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_game_rules_set_notes_c();

/**
 * @test Prueba la función para fijar el valor de el contador de notes en game_rules
 * @pre game_rules creado anteriormente
 * @post La salida debe ser OK
 */
void test2_game_rules_set_notes_c();

/**
 * @test Prueba la función para obtener el contador next_Action de game_rules
 * @pre puntero a game_rules que apunta a NULL
 * @post La salida debe ser -1
 */
void test1_game_rules_get_next_action_c();

/**
 * @test Prueba la función para obtener el contador next_Action de game_rules
 * @pre puntero a game_rules creado
 * @post La salida debe ser 0
 */
void test2_game_rules_get_next_action_c();

/**
 * @test Prueba la función para obtener el contador next_Action de game_rules
 * @pre puntero a game_rules con 5 en ese contador
 * @post La salida debe ser 5
 */
void test3_game_rules_get_next_action_c();

/**
 * @test Prueba la función para obtener el contador notes de game_rules
 * @pre puntero a game_rules que apunta a NULL
 * @post La salida debe ser -1
 */
void test1_game_rules_get_notes_c();

/**
 * @test Prueba la función para obtener el contador notes de game_rules
 * @pre puntero a game_rules recien creado
 * @post La salida debe ser -1
 */
void test2_game_rules_get_notes_c();

/**
 * @test Prueba la función para obtener el contador notes de game_rules
 * @pre puntero a game_rules recien creado con notes como 5
 * @post La salida debe ser 5
 */
void test3_game_rules_get_notes_c();

/**
 * @test Prueba la función para obtener el contador days de game_rules
 * @pre puntero a game_rules que apunta a NULL
 * @post La salida debe ser -1
 */
void test1_game_rules_get_days_c();

/**
 * @test Prueba la función para obtener el contador days de game_rules
 * @pre game_rules recien creadas
 * @post La salida debe ser 0
 */
void test2_game_rules_get_days_c();

/**
 * @test Prueba la función para obtener el contador days de game_rules
 * @pre game_rules con el contador days como 5
 * @post La salida debe ser 5
 */
void test3_game_rules_get_days_c();

/**
 * @test Prueba la función para obtener el contador n_cmd de game_rules
 * @pre puntero a game_rules que apunta a NULL
 * @post La salida debe ser -1
 */
void test1_game_rules_get_n_cmd();

/**
 * @test Prueba la función para obtener el contador n_cmd de game_rules
 * @pre game_rules recien creadas
 * @post La salida debe ser 0
 */
void test2_game_rules_get_n_cmd();

/**
 * @test Prueba la función para obtener el contador n_cmd de game_rules
 * @pre game_rules con el contador n_cmd como 5
 * @post La salida debe ser 5
 */
void test3_game_rules_get_n_cmd();

/**
 * @test Prueba la función para obtener actualizar las game_rules
 * @pre puntero a game_rules y a game como NULL
 * @post La salida debe ser ERROR
 */

void test1_game_rules_update();

/**
 * @test Prueba la función para obtener actualizar las game_rules
 * @pre game_rules creado y puntero game como NULL
 * @post La salida debe ser ERROR
 */
void test2_game_rules_update();

/**
 * @test Prueba la función para obtener actualizar las game_rules
 * @pre puntero a game_rules como NULL y game creado
 * @post La salida debe ser ERROR
 */
void test3_game_rules_update();

/**
 * @test Prueba la función para obtener actualizar las game_rules
 * @pre game_rules y game creados
 * @post La salida debe ser OK
 */
void test4_game_rules_update();


#endif
