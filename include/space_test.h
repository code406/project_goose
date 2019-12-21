/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @author Profesores Pprog
 * @version 2.0
 * @date 19-01-2016
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_space_create();

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post El identificador del espacio es el introducido
 */
void test2_space_create();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_name();
/**
 * @test Prueba la funcion para establecer la descripcion de un espacio
 * @pre Descripcion que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_description();
/**
 * @test Prueba la funcion para establecer la descripcion de un espacio
 * @pre El espacio al que establecer la descripcion es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_description();
/**
 * @test Prueba la funcion para establecer la descripcion de un espacio
 * @pre El espacio es un puntero no NULL, pero la descripcion a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_description();
/**
 * @test Prueba la función para establecer el link del norte de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_north_link();
/**
 * @test Prueba la función para establecer el link norte de un espacio
 * @pre Nombre que establecer al espacio, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_north_link();
/**
 * @test Prueba la función para establecer el link del sur de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_south_link();
/**
 * @test Prueba la función para establecer el link sur de un espacio
 * @pre Nombre que establecer al espacio, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_south_link();
/**
 * @test Prueba la función para establecer el link del este de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_east_link();
/**
 * @test Prueba la función para establecer el link este de un espacio
 * @pre Nombre que establecer al espacio, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_east_link();
/**
 * @test Prueba la función para establecer el link del oeste de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_west_link();
/**
 * @test Prueba la función para establecer el link oeste de un espacio
 * @pre Nombre que establecer al espacio, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_west_link();
/**
 * @test Prueba la funcion para establecer el link superior de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_up_link();
/**
 * @test Prueba la funcion para establecer el link superior de un espacio
 * @pre Link que se deberia establecer, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_up_link();
/**
 * @test Prueba la funcion para establecer el link inferior de un espacio
 * @pre Link que se deberia establecer
 * @post La salida debe ser OK
 */
void test1_space_set_down_link();
/**
 * @test Prueba la funcion para establecer el link inferior de un espacio
 * @pre Link que se deberia establecer, pero el espacio es NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_down_link();
/**
 * @test Prueba la función para obtener el id de un espacio
 * @pre Espacio creado con el id 25
 * @post La salida debe ser 25 (un long (id))
 */
void test1_space_get_id();
/**
 * @test Prueba la función para obtener el id de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_id();
/**
 * @test Prueba la función para fijar el primer gdesc de un espacio
 * @pre Espacio creado con el id 1
 * @post La salida debe ser OK
 */
void test1_space_set_gdesc();
/**
 * @test Prueba la función para fijar el primer gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_gdesc();
/**
 * @test Prueba la función para fijar el segundo gdesc de un espacio
 * @pre Espacio creado con el id 1
 * @post La salida debe ser OK
 */
void test3_space_set_gdesc();
/**
 * @test Prueba la función para fijar el segundo gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test4_space_set_gdesc();
/**
 * @test Prueba la función para fijar el tercer gdesc de un espacio
 * @pre Espacio creado con el id 1
 * @post La salida debe ser OK
 */
void test5_space_set_gdesc();
/**
 * @test Prueba la función para fijar el cuarto gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test6_space_set_gdesc();
/**
 * @test Prueba la funcion que ilumina un espacio
 * @pre Espacio no iluminado que se ilumina
 * @post La salida debe ser OK
 */
void test1_space_set_lit();
/**
 * @test Prueba la funcion que ilumina un espacio
 * @pre Espacio no iluminado con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_lit();
/**
 * @test Prueba la funcion que establece un espacio ocupado
 * @pre Espacio no ocupado que se ocupa
 * @post La salida debe ser OK
 */
void test1_space_set_ocupada();
/**
 * @test Prueba la funcion que estalece un espacio ocupado
 * @pre Espacio no ocupado con puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_ocupada();
/**
 * @test Prueba la función para obtener el nombre de un espacio
 * @pre Espacio con el nombre "adios"
 * @post La salida debe ser una cadena de caracteres con el valor "adios"
 */
void test1_space_get_name();
/**
 * @test Prueba la función para obtener el nombre de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_space_get_name();
/**
 * @test Prueba la función para obtener la descripcion de un espacio
 * @pre Espacio con la descripcion "prueba"
 * @post La salida debe ser una cadena de caracteres con el valor "prueba"
 */
void test1_space_get_description();
/**
 * @test Prueba la función para obtener la descripcion de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_space_get_description();
/**
 * @test Prueba la función para obtener el link norte de un espacio
 * @pre Espacio con el norte igual a 4
 * @post La salida debe ser 4
 */
void test1_space_get_north_link();
/**
 * @test Prueba la función para obtener el link norte de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_north_link();
/**
 * @test Prueba la función para obtener el link sur de un espacio
 * @pre Espacio con el sur igual a 2
 * @post La salida debe ser 2
 */
void test1_space_get_south_link();
/**
 * @test Prueba la función para obtener el link sur de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_south_link();
/**
 * @test Prueba la función para obtener el link este de un espacio
 * @pre Espacio con el este igual a 1
 * @post La salida debe ser 1
 */
void test1_space_get_east_link();
/**
 * @test Prueba la función para obtener el link este de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_east_link();
/**
 * @test Prueba la función para obtener el link oeste de un espacio
 * @pre Espacio con el oeste igual a 6
 * @post La salida debe ser 6
 */
void test1_space_get_west_link();/**
 * @test Prueba la función para obtener el link oeste de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_west_link();
/**
 * @test Prueba la función para obtener el link superior de un espacio
 * @pre Espacio con el superior igual a 6
 * @post La salida debe ser 6
 */
void test1_space_get_up_link();/**
 * @test Prueba la función para obtener el link superior de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_up_link();
/**
 * @test Prueba la función para obtener el link inferior de un espacio
 * @pre Espacio con el inferior igual a 6
 * @post La salida debe ser 6
 */
void test1_space_get_down_link();/**
 * @test Prueba la función para obtener el link inferior de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NO_ID
 */
void test2_space_get_down_link();
/**
 * @test Prueba la función para saber si una casilla esta iluminada
 * @pre Espacio iluminado
 * @post La salida debe ser TRUE
 */
void test1_space_get_lit();/**
 * @test Prueba la función para saber si una casilla esta iluminada
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser FALSE
 */
void test2_space_get_lit();
/**
 * @test Prueba la función para saber si una casilla esta ocupada
 * @pre Espacio ocupado
 * @post La salida debe ser TRUE
 */
void test1_space_get_ocupada();/**
 * @test Prueba la función para saber si una casilla esta ocupada
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser FALSE
 */
void test2_space_get_ocupada();
/**
 * @test Prueba la función para obtener el primer gdesc de un espacio
 * @pre Espacio cuyo primer gdesc es "Hola"
 * @post La salida debe ser "hola"
 */
void test1_space_get_gdesc();
/**
 * @test Prueba la función para obtener el primer gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NULL
 */
void test2_space_get_gdesc();

/**
 * @test Prueba la función para obtener el segundo gdesc de un espacio
 * @pre Espacio cuyo segundo gdesc es "Hola"
 * @post La salida debe ser "hola"
 */
void test3_space_get_gdesc();
/**
 * @test Prueba la función para obtener el tercer gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NULL
 */
void test4_space_get_gdesc();

/**
 * @test Prueba la función para obtener el tercer gdesc de un espacio
 * @pre Espacio cuyo tercer gdesc es "Hola"
 * @post La salida debe ser "hola"
 */
void test5_space_get_gdesc();
/**
 * @test Prueba la función para obtener el tercer gdesc de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser NULL
 */
void test6_space_get_gdesc();
/**
 * @test Prueba la función para añadir un objeto a un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_space_add_object();
/**
 * @test Prueba la función para añadir un objeto a un espacio
 * @pre Espacio con id 1
 * @post La salida debe ser OK
 */
void test2_space_add_object();
/**
 * @test Prueba la función para añadir un objeto a un espacio
 * @pre Espacio con varios objetos añadidos
 * @post La salida debe ser OK
 */
void test3_space_add_object();
/**
 * @test Prueba la función para obtener los objetos de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_space_get_ids_objects();

/**
 * @test Prueba la función para obtener los objetos de un espacio
 * @pre Espacio con un objeto
 * @post La salida debe ser OK
 */
void test2_space_get_ids_objects();
/**
 * @test Prueba la función para eliminar objetos de un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_space_del_object();
/**
 * @test Prueba la función para eliminar objetos de un espacio
 * @pre Espacio sin objetos
 * @post La salida debe ser ERROR
 */
void test2_space_del_object();
/**
 * @test Prueba la función para eliminar objetos de un espacio
 * @pre Espacio con el objeto que queremos borrar
 * @post La salida debe ser OK
 */
void test3_space_del_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un espacio
 * @pre Espacio que apunta a NULL
 * @post La salida debe ser FALSE
 */
void test1_space_check_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un espacio
 * @pre Espacio sin objetos
 * @post La salida debe ser FALSE
 */
void test2_space_check_object();
/**
 * @test Prueba la función para comprobar si esta el objeto en un espacio
 * @pre Espacio con el objeto a comprobar
 * @post La salida debe ser TRUE
 */
void test3_space_check_object();
#endif
