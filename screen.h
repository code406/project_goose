/**
 * @brief Defines la pantalla en terminal
 *
 * @file screen.h
 * @author Pareja
 * @version 1.0.E
 * @date 17-02-2017
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80

/* Estructura que define una zona de pantalla */
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


/*******************************************************************************
Funcion: screen_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria reservada para __data
Argumentos:
  Ninguno
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_destroy();


/*******************************************************************************
Funcion: screen_paint
Autor: Arturo Morcillo
Descripcion: Se encarga de limpiar la terminal y volver a dibujar la pantalla.
  Si la terminal tiene el tamaño correcto da la sensacion de que se actualiza
Argumentos:
  Ninguno
Return:
  Ninguno (void)
*******************************************************************************/
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


/*******************************************************************************
Funcion: screen_area_init
Autor: Arturo Morcillo
Descripcion: Reserva memoria para un area y le asigna los valores argumento.
  area.cursor tendra tantos ceros como indique el valor de area.height
Argumentos:
  x     : Variable de tipo entero (int)
  y     : Variable de tipo entero (int)
  width : Variable de tipo entero (int)
  height: Variable de tipo entero (int)
Return:
  Puntero a estructura de tipo Area
*******************************************************************************/
Area* screen_area_init(int x, int y, int width, int height);


/*******************************************************************************
Funcion: screen_area_destroy
Autor: Arturo Morcillo
Descripcion: Libera la memoria del area introducida como argumento
Argumentos:
  area: Puntero a estructura de tipo Area
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_area_destroy(Area* area);


/*******************************************************************************
Funcion: screen_area_clear
Autor: Arturo Morcillo
Descripcion: Resetea el valor del area con screen_area_reset_cursor
  Tambien pone tantos ceros a area.cursor como indique area.height
Argumentos:
  area: Puntero a estructura de tipo Area
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_area_clear(Area* area);


/*******************************************************************************
Funcion: screen_area_reset_cursor
Autor: Arturo Morcillo
Descripcion: Resetea el valor del cursor al origen empleando la macro ACCESS
Argumentos:
  area: Puntero a estructura de tipo Area
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_area_reset_cursor(Area* area);


/*******************************************************************************
Funcion: screen_area_puts
Autor: Arturo Morcillo
Descripcion: Copia en el area pasada como argumento los datos pasados en str.
Argumentos:
  area: Puntero a estructura de tipo Area
  str : Cadena de caracteres
Return:
  Ninguno (void)
*******************************************************************************/
void  screen_area_puts(Area* area, char *str);

#endif
