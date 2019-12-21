/**
 * @brief Pruebas del modulo player
 *
 * @file player_test.h
 * @author Arturo Morcillo
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H
/**
 * @test Prueba la función de creación de un jugador
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al jugador creado
 */
void test1_player_create();
/**
 * @test Prueba la función de creación de un jugador
 * @pre Un identificador como parámetro
 * @post El identificador del jugador es el introducido
 */
void test2_player_create();
/**
 * @test Prueba la función para establecer el nombre de un jugador
 * @pre Nombre que establecer al jugador
 * @post La salida debe ser OK
 */
void test1_player_set_name();
/**
 * @test Prueba la función para establecer el nombre de un jugador
 * @pre El jugador al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_player_set_name();
/**
 * @test Prueba la función para establecer el nombre de un jugadoor
 * @pre El jugador es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_player_set_name();
/**
 * @test Prueba la función para obtener el nombre de un jugador
 * @pre Jugador con el nombre "adios"
 * @post La salida debe ser una cadena de caracteres con el valor "adios"
 */
void test1_player_get_name();
/**
 * @test Prueba la función para obtener el nombre de un jugador
 * @pre jugador que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_player_get_name();
/**
 * @test Prueba la función para obtener el id de un jugador
 * @pre Jugador creado con el id 25
 * @post La salida debe ser 25 (un long (id))
 */
void test1_player_get_id();
/**
 * @test Prueba la función para obtener el id de un jugador
 * @pre jugador que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_player_get_id();
/**
 * @test Prueba la función para añadir un objeto a un jugador
 * @pre Jugador que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_player_add_object();
/**
 * @test Prueba la función para añadir un objeto a un jugador
 * @pre jugador con id 1
 * @post La salida debe ser OK
 */
void test2_player_add_object();
/**
 * @test Prueba la función para añadir un objeto a un jugador
 * @pre jugador con el maximo de objetos
 * @post La salida debe ser ERROR
 */
void test3_player_add_object();
/**
 * @test Prueba la función para obtener los objetos de un jugador
 * @pre Jugador sin objetos
 * @post La salida debe ser ERROR
 */
void test1_player_get_objects();
/**
 * @test Prueba la función para obtener los objetos de un espacio
 * @pre jugador sin objetos
 * @post La salida debe ser OK
 */

void test2_player_get_objects();
/**
 * @test Prueba la función para obtener los objetos de un jugador
 * @pre jugador con un objeto
 * @post La salida debe ser OK
 */
void test3_player_get_objects();
/**
 * @test Prueba la función para eliminar objetos de un jugador
 * @pre Jugador que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_player_del_object();
/**
 * @test Prueba la función para eliminar objetos de un jugador
 * @pre jugador sin objetos
 * @post La salida debe ser ERROR
 */
void test2_player_del_object();
/**
 * @test Prueba la función para eliminar objetos de un jugador
 * @pre jugador con el objeto que queremos borrar
 * @post La salida debe ser OK
 */
void test3_player_del_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un jugador
 * @pre jugador que apunta a NULL
 * @post La salida debe ser FALSE
 */
void test1_player_check_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un jugador
 * @pre jugador sin objetos
 * @post La salida debe ser FALSE
 */
void test2_player_check_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un jugador
 * @pre jugador con el objeto a comprobar
 * @post La salida debe ser TRUE
 */
void test3_player_check_object();
/**
 * @test Prueba la función para fijar la localizacion de un jugador
 * @pre jugador que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_player_set_location();
/**
 * @test Prueba la función para fijar la localizacion de un jugador
 * @pre jugador con id 1
 * @post La salida debe ser OK
 */

void test2_player_set_location();
/**
 * @test Prueba la función para obtener la localizacion de un jugador
 * @pre jugador que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test1_player_get_location();
/**
 * @test Prueba la función para obtener la localizacion de un jugador
 * @pre jugador sin localizacion
 * @post La salida debe ser NO_ID
 */
void test2_player_get_location();
/**
 * @test Prueba la función para obtener la localizacion de un jugador
 * @pre jugador en la localizacion 2
 * @post La salida debe ser 2
 */
void test3_player_get_location();

/**
 * @test Prueba la función para obtener el numero de objetos de un jugador
 * @pre jugador sin objetos
 * @post La salida debe ser 0
 */
void test1_player_get_num_objects();
/**
 * @test Prueba la función para obtener el numero de objetos de un jugador
 * @pre jugador con un objeto
 * @post La salida debe ser 1
 */
void test2_player_get_num_objects();
/**
 * @test Prueba la función para obtener el numero de objetos de un jugador
 * @pre jugador al que se le han añadido 3 objetos y quitado 1
 * @post La salida debe ser 2
 */
void test3_player_get_num_objects();




#endif
