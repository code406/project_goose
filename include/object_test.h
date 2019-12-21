/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author David Palomo
 * @version 2.0
 * @date 05-04-2018
 * @updated 05-04-2018
 * @copyright GNU Public License
 */

#ifndef object_TEST_H
#define object_TEST_H

/**
 * @test Prueba la función de creación de un objeto
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al objeto creado
 */
void test1_object_create();

/**
 * @test Prueba la función de creación de un objeto
 * @pre Un identificador como parámetro
 * @post El identificador del objeto es el introducido
 */
void test2_object_create();

/**
 * @test Prueba la función para establecer el nombre de un objeto
 * @pre Nombre que establecer al objeto
 * @post La salida debe ser OK
 */
void test1_object_set_name();

/**
 * @test Prueba la función para establecer el nombre de un objeto
 * @pre El objeto al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_name();

/**
 * @test Prueba la función para establecer el nombre de un objeto
 * @pre El objeto es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_object_set_name();

/**
 * @test Prueba la función para obtener el nombre de un objeto
 * @pre Objeto con un nombre
 * @post La salida debe ser el nombre del objeto
 */
void test1_object_get_name();

/**
 * @test Prueba la función para obtener el nombre de un objeto
 * @pre El objeto del que obtener el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_name();

/**
 * @test Prueba la función para establecer la descripcion de un objeto
 * @pre Descripcion que establecer al objeto
 * @post La salida debe ser OK
 */
void test1_object_set_description();

/**
 * @test Prueba la función para establecer la descripcion de un objeto
 * @pre El objeto al que establecer la descripcion es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_description();

/**
 * @test Prueba la función para establecer la descripcion de un objeto
 * @pre El objeto es un puntero no NULL, pero la descripcion a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_object_set_description();

/**
 * @test Prueba la función para obtener la descripcion de un objeto
 * @pre Objeto con una descripcion
 * @post La salida debe ser el nombre del objeto
 */
void test1_object_get_description();

/**
 * @test Prueba la función para obtener la descripcion de un objeto
 * @pre El objeto del que obtener la descripcion es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_description();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser OK
 */
void test1_object_set_movable();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_movable();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser TRUE
 */
void test1_object_get_movable();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_movable();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser OK
 */
void test1_object_set_moved();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_moved();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser OK
 */
void test1_object_get_moved();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_moved();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser OK
 */
void test1_object_set_hidden();

/**
 * @test Prueba la funcion para asignar si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_hidden();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto no movible a movible
 * @post La salida debe ser OK
 */
void test1_object_get_hidden();

/**
 * @test Prueba la funcion para obtener si un objeto se puede mover
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_hidden();

/**
 * @test Prueba la funcion que establece el link que abre el objeto
 * @pre Objeto no NULL y un identificador valido
 * @post La salida debe ser OK
 */
void test1_object_set_open_link();

/**
 * @test Prueba la funcion que establece el link que abre el objeto
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_open_link();

/**
 * @test Prueba la funcion que obtiene el link que abre el objeto
 * @pre Objeto no NULL con un identificador de un link
 * @post La salida debe ser un identificador
 */
void test1_object_get_open_link();

/**
 * @test Prueba la funcion que obtiene el link que abre el objeto
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser un identificador
 */
void test2_object_get_open_link();

/**
 * @test Prueba la funcion para asignar si un objeto puede iluminar un espacio
 * @pre Objeto que no ilumina a iluminar un espacio
 * @post La salida debe ser OK
 */
void test1_object_set_light_space();

/**
 * @test Prueba la funcion para asignar si un objeto puede iluminar un espacio
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_light_space();

/**
 * @test Prueba la funcion para obtener si un objeto iluminar un espacio
 * @pre Objeto con puntero no nulo y que ilumina
 * @post La salida debe ser TRUE
 */
void test1_object_get_light_space();

/**
 * @test Prueba la funcion para obtener si un objeto iluminar un espacio
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser BOOLEAN_ERROR
 */
void test2_object_get_light_space();

/**
 * @test Prueba la funcion para asignar si un objeto esta encendido o no
 * @pre Objeto no encendido a encendido
 * @post La salida debe ser OK
 */
void test1_object_set_on();

/**
 * @test Prueba la funcion para asignar si un objeto esta encendido o no
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_set_on();

/**
 * @test Prueba la funcion para obtener si un objeto esta encendido o no
 * @pre Objeto con puntero no nulo y que esta encendido
 * @post La salida debe ser TRUE
 */
void test1_object_get_on();

/**
 * @test Prueba la funcion para obtener si un objeto esta encendido o no
 * @pre Objeto con puntero a NULL
 * @post La salida debe ser BOOLEAN_ERROR
 */
void test2_object_get_on();

/**
 * @test Prueba la función para obtener el identificador de un objeto
 * @pre Objeto con un identificador
 * @post La salida debe ser el identificador del objeto
 */
void test1_object_get_id();

/**
 * @test Prueba la función para obtener el identificador de un objeto
 * @pre El objeto del que obtener el identificador es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_object_get_id();

#endif
