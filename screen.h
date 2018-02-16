/**
 * @brief It defines a screen
 *
 * @file screen.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 11-01-2017
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80
/*Estructura con 4 enteros y un puntero a char*/
typedef struct _Area Area;


/*******************************************************************************
Funcion: screen_init
Descripcion: libera la memoria de data por si ya esta reservada, luego
la reserva y pone todos sus caracteres como BG_CHAR
Argumentos:
  ninguno
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_init();

/*******************************************************************************
Funcion: screen_destroy
Descripcion: funcion tipo coid que libera la memoria de __data (variable)
Argumentos:
  ninguno
Return:
  nada (tipo void)
*******************************************************************************/


void  screen_destroy();

/*******************************************************************************
Funcion: screen_paint
Descripcion: Se encarga de limpiar la terminal y volver a dibujar la pantalla.
Si la terminal tiene el tamaño correcto da la sensacion de que se actualiza
Argumentos:
  ninguno
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_paint();

/*******************************************************************************
Funcion: screen_gets
Descripcion: Escribe lo de la macro PROMPT y le da al argumento el valor de COLUMNS
Argumentos:
  puntero a chat (str)
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_gets(char *str);

/*******************************************************************************
Funcion: screen_area_init
Descripcion: Hace reserva dinamica de memoria para un area y luego le asigna los
valores introducidos como argumenro.
area.cursor tendra tantos ceros como indique el valor de area.height
Argumentos:
  cuatro enteros (x, y, width, height)
Return:
  un puntero a Area
*******************************************************************************/

Area* screen_area_init(int x, int y, int width, int height);

/*******************************************************************************
Funcion: screen_area_destroy
Descripcion: Libera la memoria del area introducida como argumento
Argumentos:
  un puntero a area
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_area_destroy(Area* area);

/*******************************************************************************
Funcion: screen_area_clear
Descripcion: resetea el valor del area la funcion screen_area_reset_cursor
Tambien pone tantos ceros a area.cursor como indique area.height
Argumentos:
  un puntero a Area (area)
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_area_clear(Area* area);

/*******************************************************************************
Funcion: screen_area_reset_cursor
Descripcion: Funcion tipo void que devuelve el valor del area.cursor
empleando la macro ACCESS
Argumentos:
  un puntero a Area (area)
Return:
  nada (tipo void)
*******************************************************************************/

void  screen_area_reset_cursor(Area* area);

/*******************************************************************************
Funcion: screen_area_puts
Descripcion: Realiza llamadas a la macro y a otras funciones
de esta forma termina de fijar el area
Argumentos:
  un puntero a Area (area) y un puntero a char (str)
Return:
  nada (tipo void)
*******************************************************************************/
void  screen_area_puts(Area* area, char *str);

#endif
