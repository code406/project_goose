/**
 * @brief It declares the tests for the command module
 *
 * @file command_test.h
 * @author David Palomo
 * @version 3.0
 * @date 05-04-2018
 * @updated 08-04-2018
 * @copyright GNU Public License
 */

#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

/**
 * @test Prueba la función de creación de un comando
 * @pre Nada
 * @post Un puntero no nulo al comando creado
 */
void test1_command_create();

/**
 * @test Prueba la función para establecer el tipo de un comando
 * @pre Tipo que establecer al comando (todos los posibles)
 * @post La salida debe ser OK
 */
void test1_command_set_t_cmd();

/**
 * @test Prueba la función para establecer el tipo de un comando
 * @pre Comando al que se le asigna un tipo (todos los posibles)
 * @post El tipo del comando debe ser el que se le ha asignado
 */
void test2_command_set_t_cmd();

/**
 * @test Prueba la función para establecer el tipo de un comando
 * @pre El tipo a asignar al comando es NO_CMD
 * @post La salida debe ser ERROR
 */
void test3_command_set_t_cmd();

/**
 * @test Prueba la función para establecer el tipo de un comando
 * @pre El comando al que establecer el tipo es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test4_command_set_t_cmd();

/**
 * @test Prueba la función para establecer el nombre del objeto con el que
 * interacciona un comando
 * @pre Nombre de objeto a establecer
 * @post La salida debe ser OK
 */
void test1_command_set_obj_name();

/**
 * @test Prueba la función para establecer el nombre del objeto con el que
 * interacciona un comando
 * @pre El comando al que establecer el parámetro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_command_set_obj_name();

/**
 * @test Prueba la función para establecer el nombre del objeto con el que
 * interacciona un comando
 * @pre El comando es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_command_set_obj_name();

/**
 * @test Prueba la función para establecer el nombre del objeto con el que
 * interacciona un comando
 * @pre Se asigna un nombre de objeto
 * @post El nombre debe ser el que se ha asignado
 */
void test4_command_set_obj_name();

/**
 * @test Prueba la función para establecer la direccion para el comando move
 * @pre Direccion a establecer
 * @post La salida debe ser OK
 */
void test1_command_set_direction();

/**
 * @test Prueba la función para establecer la direccion para el comando move
 * @pre El comando al que establecer el parámetro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_command_set_direction();

/**
 * @test Prueba la función para establecer la direccion para el comando move
 * @pre El comando es un puntero no NULL, pero la direccion a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_command_set_direction();

/**
 * @test Prueba la función para establecer la direccion para el comando move
 * @pre Se asigna una direccion
 * @post La direccion debe ser la que se ha asignado
 */
void test4_command_set_direction();

/**
 * @test Prueba la función para establecer el estado del comando para el log
 * @pre Estado a establecer ("OK")
 * @post La salida debe ser OK
 */
void test1_command_set_status();

/**
 * @test Prueba la función para establecer el estado del comando para el log
 * @pre Estado a establecer ("ERROR")
 * @post La salida debe ser OK
 */
void test2_command_set_status();

/**
 * @test Prueba la función para establecer el estado del comando para el log
 * @pre El comando al que establecer el parámetro es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test3_command_set_status();

/**
 * @test Prueba la función para establecer el estado del comando para el log
 * @pre El comando es un puntero no NULL, pero la direccion a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test4_command_set_status();

/**
 * @test Prueba la función para obtener el tipo de un comando
 * @pre Comando de cada tipo posible
 * @post La salida debe ser el tipo del comando
 */
void test1_command_get_t_cmd();

/**
 * @test Prueba la función para obtener el tipo de un comando
 * @pre El comando del que obtener el tipo es un puntero a NULL
 * @post La salida debe ser NO_ID
 */
void test2_command_get_t_cmd();

/**
 * @test Prueba la función para obtener el nombre del objeto con el que
 * interacciona un comando
 * @pre Comando con un nombre
 * @post La salida debe ser el nombre
 */
void test1_command_get_obj_name();

/**
 * @test Prueba la función para obtener el nombre del objeto con el que
 * interacciona un comando
 * @pre El comando del que obtener el parámetro es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_command_get_obj_name();

/**
 * @test Prueba la función para obtener la direccion que utiliza el comando move
 * @pre Comando con una direccion
 * @post La salida debe ser la direccion
 */
void test1_command_get_direction();

/**
 * @test Prueba la función para obtener la direccion que utiliza el comando move
 * @pre El comando del que obtener el parámetro es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test2_command_get_direction();

/**
 * @test Prueba la función para obtener el estado de un comando
 * @pre Comando con un estado ("OK")
 * @post La salida debe ser el estado del comando ("OK")
 */
void test1_command_get_status();

/**
 * @test Prueba la función para obtener el estado de un comando
 * @pre Comando con un estado ("ERROR")
 * @post La salida debe ser el estado del comando ("ERROR")
 */
void test2_command_get_status();

/**
 * @test Prueba la función para obtener el estado de un comando
 * @pre El comando del que obtener el parámetro es un puntero a NULL
 * @post La salida debe ser NULL
 */
void test3_command_get_status();

/**
 * @test Prueba la función de escritura en el archivo log
 * @pre El comando es un puntero no NULL, pero el archivo donde escribir es NULL
 * @post La salida debe ser ERROR
 */
void test1_command_write_log();

/**
 * @test Prueba la función de escritura en el archivo log
 * @pre El comando a escribir en el log es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_command_write_log();

/**
 * @test Prueba la función de escritura en el archivo log
 * @pre Un comando a escribir en el log, y un archivo correcto
 * @post La salida debe ser OK
 */
void test3_command_write_log();


#endif
