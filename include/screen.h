/**
 * @brief Define la pantalla en terminal
 *
 * @file screen.h
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 3.0
 * @date   08-04-2018
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80 /*!<Longitud maxima de la cadena STR*/

/**
* @typedef Area
* @brief  Definicion de la estructura de datos Area
*/
typedef struct _Area Area;


/**
* @name screen_init
* @author David Palomo
* @brief Inicializa la zona de memoria de la pantalla y la rellena con
* color de fondo (rellena con un caracter que luego se detecta en screen_paint)
* @file screen.h
* @param
* @return Ninguno (void)
*/
void  screen_init();


/**
* @name screen_destroy
* @author Arturo Morcillo
* @brief Libera la memoria reservada para __data
* @file screen.h
* @param
* @return Ninguno (void)
*/

void  screen_destroy();


/**
* @name screen_paint
* @author Arturo Morcillo
* @brief Se encarga de limpiar la terminal y volver a dibujar la pantalla.
* Si la terminal tiene el tamaño correcto da la sensacion de que se actualiza
* @file player.h
* @param
* @return Ninguno (void)
*/
void  screen_paint();


/**
* @name screen_gets
* @author David Palomo
* @brief Imprime "prompt:>" en terminal y escanea la introducción de comando.
* Por el momento, no se utiliza.* @file screen.h
* @param str cadena de caracteres
* @return Ninguno (void)
*/
void  screen_gets(char *str);


/**
* @name screen_area_init
* @author Arturo Morcillo
* @brief Reserva memoria para un area y le asigna los valores argumento.
* area.hursor tendra tantos ceros como indique el valor de area.height
* @file screen.h
* @param x Variable de tipo entero (int)
* @param y Variable de tipo entero (int)
* @param width Variable de tipo entero (int)
* @param height Variable de tipo entero (int)
* @return Puntero a estructura de tipo Area
*/
Area* screen_area_init(int x, int y, int width, int height);


/**
* @name screen_area_destroy
* @author Arturo Morcillo
* @brief Libera la memoria del area introducida como argumento
* @file screen.h
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_destroy(Area* area);


/**
* @name screen_area_clear
* @author Arturo Morcillo
* @brief Resetea el valor del area con screen_area_reset_cursor
* Tambien pone tantos ceros a area.hursor como indique area.height
* @file screen.h
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_clear(Area* area);


/**
* @name screen_area_reset_cursor
* @author Arturo Morcillo
* @brief Resetea el valor del cursor al origen empleando la macro ACCESS
* @file screen.h
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_reset_cursor(Area* area);


/**
* @name screen_area_puts
* @author Arturo Morcillo
* @brief Copia en el area pasada como argumento los datos pasados en str.
* @file screen.h
* @param area Puntero a estructura de tipo Area
* @param str Cadena de caracteres
* @return Ninguno (void)
*/
void  screen_area_puts(Area* area, char *str);

#endif
