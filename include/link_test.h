/**
 * @brief It declares the tests for the link module
 *
 * @file link_test.h
 * @author David Palomo
 * @version 2.0
 * @date 05-04-2018
 * @updated 05-04-2018
 * @copyright GNU Public License
 */

#ifndef link_TEST_H
#define link_TEST_H

/**
 * @test Prueba la función de creación de un enlace
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al enlace creado
 */
void test1_link_create();

/**
 * @test Prueba la función de creación de un enlace
 * @pre Un identificador como parámetro
 * @post El identificador del enlace es el introducido
 */
void test2_link_create();

/**
 * @test Prueba la función para establecer el nombre de un enlace
 * @pre Nombre que establecer al enlace
 * @post La salida debe ser OK
 */
void test1_link_set_name();

/**
 * @test Prueba la función para establecer el nombre de un enlace
 * @pre El enlace al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_name();

/**
 * @test Prueba la función para establecer el nombre de un enlace
 * @pre El enlace es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_link_set_name();

/**
 * @test Prueba la función para establecer el primer espacio de los dos enlazados
 * @pre Primer espacio que establecer para el enlace
 * @post La salida debe ser OK
 */
void test1_link_set_espacio_1();

/**
* @test Prueba la función para establecer el primer espacio de los dos enlazados
 * @pre El enlace al que establecer el espacio es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_espacio_1();

/**
 * @test Prueba la función para establecer el primer espacio de los dos enlazados
 * @pre El enlace es un puntero no NULL, pero el id del espacio a establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_espacio_1();

/**
 * @test Prueba la función para establecer el primer espacio de los dos enlazados
 * @pre Un identificador como parámetro
 * @post El identificador de la casilla enlazada es el introducido
 */
void test4_link_set_espacio_1();

/**
 * @test Prueba la función para establecer el segundo espacio de los dos enlazados
 * @pre Segundo espacio que establecer para el enlace
 * @post La salida debe ser OK
 */
void test1_link_set_espacio_2();

/**
 * @test Prueba la función para establecer el segundo espacio de los dos enlazados
 * @pre El enlace al que establecer el espacio es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_set_espacio_2();

/**
 * @test Prueba la función para establecer el segundo espacio de los dos enlazados
 * @pre El enlace es un puntero no NULL, pero el id del espacio a establecer es NO_ID
 * @post La salida debe ser ERROR
 */
void test3_link_set_espacio_2();

/**
 * @test Prueba la función para establecer el segundo espacio de los dos enlazados
 * @pre Un identificador como parámetro
 * @post El identificador de la casilla enlazada es el introducido
 */
void test4_link_set_espacio_2();

/**
 * @test Prueba la función para establecer si un enlace está abierto o cerrado
 * @pre Valor TRUE que establecer al enlace (abierto)
 * @post La salida debe ser OK
 */
void test1_link_set_linked();

/**
 * @test Prueba la función para establecer si un enlace está abierto o cerrado
 * @pre Valor FALSE que establecer al enlace (cerrado)
 * @post La salida debe ser OK
 */
void test2_link_set_linked();

/**
 * @test Prueba la función para establecer si un enlace está abierto o cerrado
 * @pre El enlace al que establecer el parametro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test3_link_set_linked();

/**
 * @test Prueba la función para establecer si un enlace está abierto o cerrado
 * @pre Valor distinto de TRUE o FALSE que establecer al enlace
 * @post La salida debe ser ERROR
 */
void test4_link_set_linked();

/**
 * @test Prueba la función para obtener el identificador de un enlace
 * @pre Enlace creado con el id 5
 * @post La salida debe ser el id del enlace (5)
 */
void test1_link_get_id();

/**
 * @test Prueba la función para obtener el identificador de un enlace
 * @pre El enlace del que obtener el identificador es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_get_id();

/**
 * @test Prueba la función para obtener el nombre de un enlace
 * @pre Enlace creado con un nombre
 * @post La salida debe ser el nombre del enlace
 */
void test1_link_get_name();

/**
 * @test Prueba la función para obtener el nombre de un enlace
 * @pre El enlace del que obtener el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_get_name();

/**
 * @test Prueba la función para obtener el id del primer espacio de los dos enlazados
 * @pre El espacio a obtener tiene un id
 * @post La salida debe ser el id del espacio
 */
void test1_link_get_espacio_1();

/**
 * @test Prueba la función para obtener el id del primer espacio de los dos enlazados
 * @pre El enlace del que obtener el id del primer espacio es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_get_espacio_1();

/**
 * @test Prueba la función para obtener el id del segundo espacio de los dos enlazados
 * @pre El espacio a obtener tiene un id
 * @post La salida debe ser el id del espacio
 */
void test1_link_get_espacio_2();

/**
 * @test Prueba la función para obtener el id del segundo espacio de los dos enlazados
 * @pre El enlace del que obtener el id del segundo espacio es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_link_get_espacio_2();

/**
 * @test Prueba la función para obtener si un enlace está abierto o cerrado
 * @pre El enlace está abierto (TRUE)
 * @post La salida debe ser TRUE
 */
void test1_link_get_linked();

/**
 * @test Prueba la función para obtener si un enlace está abierto o cerrado
 * @pre El enlace está cerrado (FALSE)
 * @post La salida debe ser FALSE
 */
void test2_link_get_linked();

/**
 * @test Prueba la función para obtener si un enlace está abierto o cerrado
 * @pre El enlace del que obtener el parámetro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test3_link_get_linked();


#endif
