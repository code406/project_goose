/**
 * @brief Pruebas del modulo inventory
 *
 * @file inventory_test.h
 * @author Arturo Morcillo
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H
/**
 * @test Prueba la función de creación de un inventario
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al inventario creado
 */
void test1_inventory_create();

/**
 * @test Prueba la función para añadir un objeto a un inventario
 * @pre inventario que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_inventory_add_id();
/**
 * @test Prueba la función para añadir un objeto a un inventario
 * @pre inventario con id 1
 * @post La salida debe ser OK
 */
void test2_inventory_add_id();
/**
 * @test Prueba la función para añadir un objeto a un inventario
 * @pre inventario lleno
 * @post La salida debe ser ERROR
 */
void test3_inventory_add_id();
/**
 * @test Prueba la función para obtener los objetos de un inventario
 * @pre inventario sin objetos
 * @post La salida debe ser NULL
 */
void test1_inventory_get_ids();
/**
 * @test Prueba la función para obtener los objetos de un espacio
 * @pre Espacio sin objetos
 * @post La salida debe ser distinta de NULL ya que el set se ha creado
 */

void test2_inventory_get_ids();
/**
 * @test Prueba la función para obtener los objetos de un inventario
 * @pre inventario con un objeto
 * @post La salida debe ser distinta de NULL
 */
void test3_inventory_get_ids();
/**
 * @test Prueba la función para eliminar objetos de un inventario
 * @pre inventario que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test1_inventory_del_id();
/**
 * @test Prueba la función para eliminar objetos de un inventario
 * @pre inventario sin objetos
 * @post La salida debe ser ERROR
 */
void test2_inventory_del_id();
/**
 * @test Prueba la función para eliminar objetos de un inventario
 * @pre inventario con el objeto que queremos borrar
 * @post La salida debe ser OK
 */
void test3_inventory_del_id();
/**
 * @test Prueba la función para comprobar si esta el objeto en un inventario
 * @pre inventario que apunta a NULL
 * @post La salida debe ser FALSE
 */
void test1_inventory_check_id();
/**
 * @test Prueba la función para comprobar si esta el objeto en un inventario
 * @pre inventario sin objetos
 * @post La salida debe ser FALSE
 */
void test2_inventory_check_id();
/**
 * @test Prueba la función para comprobar si esta el objeto en un inventario
 * @pre inventario con el objeto a comprobar
 * @post La salida debe ser TRUE
 */
void test3_inventory_check_id();

/**
 * @test Prueba la función para obtener el numero de objetos de un inventario
 * @pre inventario que apunta a NULL
 * @post La salida debe ser 0
 */
void test1_inventory_get_num_objects();
/**
 * @test Prueba la función para obtener el numero de objetos de un inventario
 * @pre inventario sin objetos
 * @post La salida debe ser 0
 */
void test2_inventory_get_num_objects();
/**
 * @test Prueba la función para obtener el numero de objetos de un inventario
 * @pre inventario con un objeto
 * @post La salida debe ser MAX_ID, que so los objetos maximos que puede almacenar
 */
void test3_inventory_get_num_objects();

/**
 * @test Prueba la función para fijar el set de ids de un inventario
 * @pre inventario qeu apunta a NULL y un set
 * @post La salida debe ser ERROR
 */
void test1_inventory_set_ids();
/**
 * @test Prueba la función para fijar el set de ids de un inventario
 * @pre inventario y set que apunta a NULL
 * @post La salida debe ser ERROR
 */
void test2_inventory_set_ids();
/**
 * @test Prueba la función para fijar el set de ids de un inventario
 * @pre inventario y set
 * @post La salida debe ser OK
 */
void test3_inventory_set_ids();

#endif
