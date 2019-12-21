/**
 * @brief Implementa la pantalla en terminal
 *
 * @file screen.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 36
#define COLUMNS 152
#define TOTAL_DATA (ROWS * COLUMNS) + 1


#define BG_CHAR '~'/*!<Caracter que se utiliza para pintar los colores de la interfaz*/
#define FG_CHAR ' '/*!<Caracter que se utiliza para pintar los colores de la interfaz*/

#define PROMPT " prompt:> " /*!<Caracter que se utiliza para pintar el prompt de la interfaz*/


/**
* @brief area
*
* Estructura que define una zona de pantalla, con su posición u origen de
* coordenadas (x,y), su tamaño (width, height), y un puntero a su primera
* posicion en memoria.
*/
/**
* @struct _Area
* @brief Implementacion de la definicion de la estructura Area
*/
struct _Area
{
  int x, /*!<Coordenada origen x*/
      y, /*!<Coordenada origen y*/
      width, /*!<Ancho desde el origen*/
      height;/*!<Altura desde el origen*/
  char *cursor; /*!<Puntero a su primera posicion en memoria*/
};



char *__data;/*!< __data es una cadena de caracteres que guarda memoria de forma contigua, y la pantalla maneja coordenadas bidimensionales */


#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))/*!< La macro ACCESS sirve para, pasando los parámetros de coordenadas x e y,
                                                    * acceder a la posicion de memoria que les corresponde.
                                                    * "d" se utitilizará como origen de coordenadas.
                                                    * El desplazamiento desde el origen es  "y * (número de columnas) + x".
                                                    */



/*************** Prototipo de funciones privadas ******************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);
/******************************************************************************/


void screen_init()
{
  /*libera la memoria de __data*/
  screen_destroy();
  /*Reserva memoria para __data*/
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);
  /*copia BG_CHAR en los todos los caracteres de __data*/
  if (__data)
  {
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /* Rellena con color de fondo */
    *(__data + TOTAL_DATA - 1) = '\0';         /* Termina __data en '\0'     */
  }
}

void screen_destroy()
{
  if (__data)
    free(__data);
}



void screen_paint()
{
  char *src = NULL;
  char dest[COLUMNS + 1];
  int i=0;

  /* Rellena con 0 los caracteres de dest */
  memset(dest, 0, COLUMNS + 1);

  if (__data)
  {
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/

    puts("\033[2J"); /* Limpia la terminal (clear) */
    for (src=__data; src < (__data + TOTAL_DATA - 1); src+=COLUMNS)
    {
      /* Parece que funcionaría usando src sin copiar a dest (no lo modifica) */
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i=0; i<COLUMNS; i++)
      {
      	if (dest[i] == BG_CHAR)
        {
      	  printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:blue(34);bg:blue(44) */
      	}
        else
        {
      	  printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
      	}
      }
      printf("\n");
    }
  }
}



void screen_gets(char *str)
{
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
  {
    /* Reemplaza el salto de línea introducido tras el comando por '\0' */
    *(str + strlen(str) - 1) = 0;
  }
}



Area* screen_area_init(int x, int y, int width, int height)
{
  int i = 0;
  Area* area = NULL;

  if ( (area  = (Area*) malloc (sizeof(struct _Area))) )
  {
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};
    /*copia en los i primeros caracteres de area.cursor el numero 0*/
    for (i=0; i < area->height; i++)
    {
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }
  }

  return area;
}



void screen_area_destroy(Area* area)
{
  if(area)
    free(area);
}



void screen_area_clear(Area* area)
{
  int i = 0;

  if (area)
  {
    screen_area_reset_cursor(area);

    for (i=0; i < area->height; i++)
    {
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
    }
  }
}



void screen_area_reset_cursor(Area* area)
{
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}


void screen_area_puts(Area* area, char *str)
{
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  screen_utils_replaces_special_chars(str);

  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width)
  {
    memset(area->cursor, FG_CHAR, area->width);
    /* resul = (condicion)? resultrue : resulfalse
    Asigna strlen(ptr) si (strlen(ptr) < area->width). Si no, asigna area->width
    Sirve para copiar solo lo necesario */
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}


int screen_area_cursor_is_out_of_bounds(Area* area)
{
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}



void screen_area_scroll_up(Area* area)
{
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS)
  {
    /* Copia de origen (puntero) a destino (puntero) tantos bytes como indica tamaño */
    /* memcpy(destino, origen, tamaño) */
    /* Copia cada fila siguiente del area en la fila anterior */
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}


void screen_utils_replaces_special_chars(char* str)
{
  char *pch = NULL;

  /* Reemplaza caracteres especiales por '??' */
  /* strpbrk devuelve un puntero al primer caracter de str de la lista */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
