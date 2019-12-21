/**
 * @brief Pruebas del modulo game_management
 *
 * @file game_management_test.h
 * @author Arturo Morcillo
 * @copyright GNU Public License
 */

#ifndef game_management_TEST_H
#define game_management_TEST_H
/**
 * @test Prueba la función de lectura de los espacios
 * @pre Un game y un FILE que apuntan a NULL
 * @post Un ERROR
 */
void test1_game_management_load_spaces();
/**
 * @test Prueba la función de lectura de los espacios
 * @pre Un game y un FILE que apunta a NULL
 * @post Un ERROR
 */
void test2_game_management_load_spaces();
/**
 * @test Prueba la función de lectura de los espacios
 * @pre Un game que apunta a NULL y un FILE
 * @post Un ERROR
 */
void test3_game_management_load_spaces();
/**
 * @test Prueba la función de lectura de los espacios
 * @pre Un game y un FILE (el data.dat)
 * @post Un OK
 */
void test4_game_management_load_spaces();
/**
 * @test Prueba la función de lectura de los objetos
 * @pre Un game y un FILE que apuntan a NULL
 * @post Un ERROR
 */
void test1_game_management_load_objects();
/**
 * @test Prueba la función de lectura de los objetos
 * @pre Un game y un FILE que apunta a NULL
 * @post Un ERROR
 */
void test2_game_management_load_objects();
/**
 * @test Prueba la función de lectura de los objetos
 * @pre Un game que apunta a NULL y un FILE
 * @post Un ERROR
 */
void test3_game_management_load_objects();
/**
 * @test Prueba la función de lectura de los objetos
 * @pre Un game y un FILE (el data.dat)
 * @post Un OK
 */
void test4_game_management_load_objects();
/**
 * @test Prueba la función de lectura de los links
 * @pre Un game y un FILE que apuntan a NULL
 * @post Un ERROR
 */
void test1_game_management_load_links();
/**
 * @test Prueba la función de lectura de los links
 * @pre Un game y un FILE que apunta a NULL
 * @post Un ERROR
 */
void test2_game_management_load_links();
/**
 * @test Prueba la función de lectura de los links
 * @pre Un game y un FILE (el data.dat)
 * @post Un OK
 */
void test3_game_management_load_links();
/**
 * @test Prueba la función de lectura de los links
 * @pre Un game y un FILE (el data.dat)
 * @post Un OK
 */
void test4_game_management_load_links();

#endif
