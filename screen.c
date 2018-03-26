/**
 * @brief Implementa la pantalla en terminal
 *
 * @file screen.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 33
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS) + 1

/* Caracteres que se utilizan para pintar los colores de la interfaz */
#define BG_CHAR '~'
#define FG_CHAR ' '

#define PROMPT " prompt:> "


/**
* @brief area
*
* Estructura que define una zona de pantalla, con su posición u origen de
* coordenadas (x,y), su tamaño (width, height), y un puntero a su primera
* posicion en memoria.
*/
struct _Area
{
  int x,
      y,
      width,
      height;
  char *cursor;
};


/* __data es una cadena de caracteres que guarda memoria de forma contigua,
y la pantalla maneja coordenadas bidimensionales */
char *__data;

/*
La macro ACCESS sirve para, pasando los parámetros de coordenadas x e y,
acceder a la posicion de memoria que les corresponde.
"d" se utitilizará como origen de coordenadas.
El desplazamiento desde el origen es  "y * (número de columnas) + x".
*/
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))



/*************** Prototipo de funciones privadas ******************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);
/******************************************************************************/

/**
* @name screen_init
* @author David Palomo
* @brief Inicializa la zona de memoria de la pantalla y la rellena con
* color de fondo (rellena con un caracter que luego se detecta en screen_paint)
* @file screen.c
* @param Ninguno
* @return Ninguno (void)
*/

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

/**
* @name screen_destroy
* @author Arturo Morcillo
* @brief Libera la memoria reservada para __data
* @file screen.c
* @param ninguno
* @return Ninguno (void)
*/

void screen_destroy()
{
  if (__data)
    free(__data);
}

/**
* @name screen_paint
* @author Arturo Morcillo
* @brief Se encarga de limpiar la terminal y volver a dibujar la pantalla.
* Si la terminal tiene el tamaño correcto da la sensacion de que se actualiza
* @file player.c
* @param ninguno
* @return Ninguno (void)
*/

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

/**
* @name screen_gets
* @author David Palomo
* @brief Imprime "prompt:>" en terminal y escanea la introducción de comando.
* Por el momento, no se utiliza.* @file screen.c
* @param str cadena de caracteres
* @return Ninguno (void)
*/

void screen_gets(char *str)
{
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
  {
    /* Reemplaza el salto de línea introducido tras el comando por '\0' */
    *(str + strlen(str) - 1) = 0;
  }
}

/**
* @name screen_area_init
* @author Arturo Morcillo
* @brief Reserva memoria para un area y le asigna los valores argumento.
* area.cursor tendra tantos ceros como indique el valor de area.height
* @file screen.c
* @param x Variable de tipo entero (int)
* @param y Variable de tipo entero (int)
* @param width Variable de tipo entero (int)
* @param height Variable de tipo entero (int)
* @return Puntero a estructura de tipo Area
*/

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

/**
* @name screen_area_destroy
* @author Arturo Morcillo
* @brief Libera la memoria del area introducida como argumento
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/

void screen_area_destroy(Area* area)
{
  if(area)
    free(area);
}

/**
* @name screen_area_clear
* @author Arturo Morcillo
* @brief Resetea el valor del area con screen_area_reset_cursor
* Tambien pone tantos ceros a area.cursor como indique area.height
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/

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

/**
* @name screen_area_reset_cursor
* @author Arturo Morcillo
* @brief Resetea el valor del cursor al origen empleando la macro ACCESS
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/

void screen_area_reset_cursor(Area* area)
{
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/**
* @name screen_area_puts
* @author Arturo Morcillo
* @brief Copia en el area pasada como argumento los datos pasados en str.
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @param str Cadena de caracteres
* @return Ninguno (void)
*/

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

/**
* @name screen_area_cursor_is_out_of_bounds
* @author Arturo Morcillo
* @briefIndica si el cursor está fuera de limites
* @file screen.c
* @param area Puntero a estructura de tipo Area
* @return 1 si el cursor está fuera de límites, y 0 si no.
*/

int screen_area_cursor_is_out_of_bounds(Area* area)
{
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}

/**
* @name screen_area_scroll_up
* @author David Palomo
* @brief Hace scroll de un area una fila hacia arriba, sobreescribiendo
* cada fila con la siguiente
* @param area Puntero a estructura de tipo Area
* @return Ninguno (void)
*/

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

/**
* @name screen_utils_replaces_special_chars
* @author Arturo Morcillo
* @brief Reemplaza los caracteres especiales para que no haya problemas
* @file screen.c
* @param str Cadena de caracteres
* @return Ninguno (void)
*/

void screen_utils_replaces_special_chars(char* str)
{
  char *pch = NULL;

  /* Reemplaza caracteres especiales por '??' */
  /* strpbrk devuelve un puntero al primer caracter de str de la lista */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
