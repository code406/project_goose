/**
 * @brief Defines la pantalla en terminal
 *
 * @file screen.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80

/**
^ @brief estructura Area
* Estructura que define una zona de pantalla
*/

typedef struct _Area Area;


/*******************************************************************************
Funcion: screen_init
Autor: David Palomo
Descripcion: Inicializa la zona de memoria de la pantalla y la rellena con
  color de fondo (rellena con un caracter que luego se detecta en screen_paint)
Argumentos:
  Ninguno
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_init();


/**
* @brief screen_destroy
* @author Arturo Morcillo
* Libera la memoria reservada para __data
* @file screen.c
* @return Ninguno (void)
*/

void  screen_destroy();


/**
* @brief screen_paint
* @author Arturo Morcillo
* Se encarga de limpiar la terminal y volver a dibujar la pantalla.
* Si la terminal tiene el tamaño correcto da la sensacion de que se actualiza
* @file player.c
* @return Ninguno (void)
*/
void  screen_paint();


/*******************************************************************************
Funcion: screen_gets
Autor: David Palomo
Descripcion: Imprime "prompt:>" en terminal y escanea la introducción de comando.
  Por el momento, no se utiliza.
Argumentos:
  str: Cadena de caracteres
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_gets(char *str);


/**
* @brief screen_area_init
* @author Arturo Morcillo
* Reserva memoria para un area y le asigna los valores argumento.
* area.cursor tendra tantos ceros como indique el valor de area.height
* @file screen.c
* @param x Variable de tipo entero (int)
* @param y Variable de tipo entero (int)
* @param width Variable de tipo entero (int)
* @param height Variable de tipo entero (int)
* @return Puntero a estructura de tipo Area
*/
Area* screen_area_init(int x, int y, int width, int height);


/**
* @brief screen_area_destroy
* @author Arturo Morcillo
* Libera la memoria del area introducida como argumento
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_destroy(Area* area);


/**
* @brief screen_area_clear
* @author Arturo Morcillo
* Resetea el valor del area con screen_area_reset_cursor
* Tambien pone tantos ceros a area.cursor como indique area.height
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_clear(Area* area);


/**
* @brief screen_area_reset_cursor
* @author Arturo Morcillo
* Resetea el valor del cursor al origen empleando la macro ACCESS
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/
void  screen_area_reset_cursor(Area* area);


/**
* @brief screen_area_puts
* @author Arturo Morcillo
* Copia en el area pasada como argumento los datos pasados en str.
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @param str Cadena de caracteres
* @return Ninguno (void)
*/
void  screen_area_puts(Area* area, char *str);

#endif
