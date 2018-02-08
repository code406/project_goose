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

typedef struct _Area Area;

/*
Funcion tipo void sin argumentos
libera la memoria de data por si ya esta reservada, luego
la reserva y pone todos sus caracteres como BG_CHAR
*/
void  screen_init();
/*
Funcion tipo void que libera la memoria
de __data (variable)
*/
void  screen_destroy();
/*
Funcion del tipo void sin argumentos
Se encarga de limpiar la terminal y volver a dibujar la pantalla
Si la terminal tiene el tamaño correcto da la sensacion de que
se actualiza
*/
void  screen_paint();
/*
Funcion tipo void cuyo argumento es un puntero a char
escribe lo de la macro PROMPT.
Le da al argumento el valor de COLUMNS.
Reemplaza el caracter de la nueva linea con 0
*/
void  screen_gets(char *str);
/*
Funcion que devuelve un puntero a area y cuyos argumentos
son 4 enteros: x, y width, height.
Hace reserva dinamica de memoria para un Area y luego
le asigna los valores introducidos como argumento.
Tambien area.cursor tendrá tantos ceros como indique el valor de
area.height
*/
Area* screen_area_init(int x, int y, int width, int height);
/*
Funcion tipo void que libera la memoria del Area
introducida como argumento
*/
void  screen_area_destroy(Area* area);
/*
Funcion tipo void cuyo argumento es un puntero a area.
resetea el valor del area la funcion screen_area_reset_cursor
Tambien pone tantos ceros a area.cursor como indique area.height
*/
void  screen_area_clear(Area* area);
/*
Funcion tipo void que devuelve el valor del area.cursor
empleando la macro ACCESS
*/
void  screen_area_reset_cursor(Area* area);
void  screen_area_puts(Area* area, char *str);

#endif
