/**
 * @brief It declares the tests for the dialogue module
 *
 * @file dialogue_test.h
 * @author Javier Mateos
 * @version 3.0
 * @date 06-05-2018
 * @updated 06-05-2018
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_TEST_H
#define DIALOGUE_TEST_H

/**
 * @test Prueba la función de creación de un dialogo
 * @pre Nada
 * @post Un puntero no nulo al comando creado
 */
void test1_dialogue_create();

/**
  * @test Prueba la función para establecer el tipo de un comando
  * @pre Tipo que establecer al comando (todos los posibles)
  * @post La salida debe ser OK
  */
void test1_dialogue_set_last_cmd();

/**
  * @test Prueba la función para establecer el tipo de un comando
  * @pre Tipo que establecer al comando NO_CMD
  * @post La salida debe ser ERROR
  */
void test2_dialogue_set_last_cmd();

/**
  * @test Prueba la función para establecer el tipo de un comando
  * @pre Tipo que establecer al comando NULL
  * @post La salida debe ser ERROR
  */
void test3_dialogue_set_last_cmd();
/**
 * @test Prueba la función para establecer el estado del comando del dialogo
 * @pre Estado a establecer ("OK")
 * @post La salida debe ser OK
 */
void test1_dialogue_set_last_cmd_status();

/**
 * @test Prueba la función para establecer el estado del comando del dialogo
 * @pre Estado a establecer ("ERROR")
 * @post La salida debe ser OK
 */
void test2_dialogue_set_last_cmd_status();

/**
 * @test Prueba la función para establecer el estado del comando del dialogo
 * @pre El comando al que establecer el parámetro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test3_dialogue_set_last_cmd_status();

/**
  * @test Prueba la funcion para establecer la plantilla del dialogo
  * @pre Archivo que se establece como plantilla
  * @post La salida debe ser OK
  */
void test1_dialogue_set_plantilla();

/**
  * @test Prueba la funcion para establecer la plantilla del dialogo
  * @pre Archivo que se establece como plantilla NULL
  * @post La salida debe ser ERROR
  */
void test2_dialogue_set_plantilla();

/**
  * @test Prueba la funcion para establecer la plantilla del dialogo
  * @pre Dialogo al que se establece la plantilla NULL
  * @post La salida debe ser ERROR
  */
void test3_dialogue_set_plantilla();

/**
  * @test Prueba la funcion para establecer la plantilla del dialogo
  * @pre Dialogo con plantilla asignada, se establece otra plantilla
  * @post La salida debe ser OK
  */
void test4_dialogue_set_plantilla();

/**
 * @test Prueba la función para establecer la primera parte del mensaje
 * @pre  Cadena con la primera parte del mensaje
 * @post La salida debe ser OK
 */
void test1_dialogue_set_part1();

/**
 * @test Prueba la función para establecer la primera parte del mensaje
 * @pre El dialogo al que establecer el mensaje es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_dialogue_set_part1();

/**
 * @test Prueba la función para establecer la primera parte del mensaje
 * @pre El dialogo es un puntero no NULL, pero el mensaje a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_dialogue_set_part1();

/**
 * @test Prueba la función para establecer la segunda parte del mensaje
 * @pre  Cadena con la segunda parte del mensaje
 * @post La salida debe ser OK
 */
void test1_dialogue_set_part2();

/**
 * @test Prueba la función para establecer la segunda parte del mensaje
 * @pre El dialogo al que establecer el mensaje es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_dialogue_set_part2();

/**
 * @test Prueba la función para establecer la segunda parte del mensaje
 * @pre El dialogo es un puntero no NULL, pero el mensaje a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_dialogue_set_part2();

/**
  * @test Prueba la funcion para establecer la tercera parte del mensaje
  * @pre Cadena con la tercera parte del mensaje,los comandos y las opciones válidas
  * @post La salida debe ser OK
  */
void test1_dialogue_set_part3();

/**
  * @test Prueba la funcion para establecer la tercera parte del mensaje
  * @pre Dialogo al que establecer el mensaje es un puntero a NULL
  * @post La salida debe ser ERROR
  */
void test2_dialogue_set_part3();

/**
  * @test Prueba la funcion para establecer la tercera parte del mensaje
  * @pre Dialogo con puntero no NULL, opciones y comandos validos, pero el mensaje a establecer es NULL
  * @post La salida debe ser ERROR
  */
void test3_dialogue_set_part3();

/**
  * @test Prueba la funcion para establecer la tercera parte del mensaje
  * @pre Dialogo y cadena con punteros no NULL, pero opciones y comandos no validos
  * @post La salida debe ser ERROR
  */
void test4_dialogue_set_part3();

/**
 * @test Prueba la función para obtener el tipo de un comando del dialogo
 * @pre Comando de cada tipo posible
 * @post La salida debe ser el tipo del comando
 */
void test1_dialogue_get_last_cmd();

/**
 * @test Prueba la función para obtener el tipo de un comando del dialogo
 * @pre El comando del que obtener el tipo es un puntero a NULL
 * @post La salida debe ser UNKNOWN
 */
void test2_dialogue_get_last_cmd();

/**
 * @test Prueba la función para obtener el estado de un comando del dialogo
 * @pre Comando con un estado ("OK")
 * @post La salida debe ser el estado del comando ("OK")
 */
void test1_dialogue_get_last_cmd_status();

/**
 * @test Prueba la función para obtener el estado de un comando del dialogo
 * @pre Comando con un estado ("ERROR")
 * @post La salida debe ser el estado del comando ("ERROR")
 */
void test2_dialogue_get_last_cmd_status();

/**
 * @test Prueba la función para obtener el estado de un comando del dialogo
 * @pre El comando del que obtener el parámetro es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test3_dialogue_get_last_cmd_status();

/**
 * @test Prueba la función para obtener la primera parte del mensaje
 * @pre  Cadena con el nombre prueba"
 * @post La salida debe ser una cadena de caracteres con el valor prueba
 */
void test1_dialogue_get_part1();

/**
 * @test Prueba la función para obtener la primera parte del mensaje
 * @pre Dialogo que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_dialogue_get_part1();

/**
 * @test Prueba la función para obtener la primera parte del mensaje
 * @pre  Cadena con el nombre prueba"
 * @post La salida debe ser una cadena de caracteres con el valor prueba
 */
void test3_dialogue_get_part1();

/**
 * @test Prueba la función para obtener la segunda parte del mensaje
 * @pre  Cadena con el nombre prueba
 * @post La salida debe ser una cadena de caracteres con el valor prueba
 */
void test1_dialogue_get_part2();

/**
 * @test Prueba la función para obtener la segunda parte del mensaje
 * @pre Dialogo que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_dialogue_get_part2();

/**
 * @test Prueba la función para obtener la segunda parte del mensaje
 * @pre Dialogo que apunta a NULL
 * @post La salida debe ser NULL
 */
void test3_dialogue_get_part2();



#endif
