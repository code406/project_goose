#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 23
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS) + 1

#define BG_CHAR '~'
#define FG_CHAR ' '
#define PROMPT " prompt:> "

/*
define tipo funcion.
(d,x,y) son argumentos
lo otro es valor
*/
#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))

/*
Estructura con 4 enteros y un puntero a char
*/
struct _Area{
  int x,
      y,
      width,
      height;
  char *cursor;
};

char *__data;

/****************************/
/*     Private functions    */
/****************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);

/****************************/
/* Functions implementation */
/****************************/

/*
Funcion tipo void sin argumentos
libera la memoria de data por si ya esta reservada, luego
la reserva y pone todos sus caracteres como BG_CHAR
*/
void screen_init(){
  /*libera la memoria de __data*/
  screen_destroy(); /* Dispose if previously initialized */
  /*Reserva memoria para __data*/
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);
  /*copia BG_CHAR en los todos los caracteres de __data*/
  if (__data){
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';         /*NULL-terminated string*/
  }
}
/*
Funcion tipo void que libera la memoria
de __data (variable)
*/
void screen_destroy(){
  if (__data)
    free(__data);
}
/*
Funcion del tipo void sin argumentos
Se encarga de limpiar la terminal y volver a dibujar la pantalla
Si la terminal tiene el tamaño correcto da la sensacion de que
se actualiza
*/
void screen_paint(){
  /*Crea un puntero a char*/
  char *src = NULL;
  /*crea una cadena de caracteres*/
  char dest[COLUMNS + 1];
  int i=0;
  /*Todos los caracteres de dest son 0*/
  memset(dest, 0, COLUMNS + 1);

  if (__data){
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/

    puts("\033[2J"); /*Clear the terminal*/
    for (src=__data; src < (__data + TOTAL_DATA - 1); src+=COLUMNS){
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i=0; i<COLUMNS; i++){
	if (dest[i] == BG_CHAR){
	  printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:blue(34);bg:blue(44) */
	}else{
	  printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
	}
      }
      printf("\n");
    }
  }
}
/*
Funcion tipo boid cuyo argumento es un puntero a char
escribe lo de la macro PROMPT.
Le da al argumento el valor de COLUMNS.
Reemplaza el caracter de la nueva linea con 0
*/
void screen_gets(char *str){
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
    *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

/*
Funcion que devuelve un puntero a area y cuyos argumentos
son 4 enteros: x, y width, height.
Hace reserva dinamica de memoria para un Area y luego
le asigna los valores introducidos como argumento.
Tambien area.cursor tendrá tantos ceros como indique el valor de
area.height
*/

Area* screen_area_init(int x, int y, int width, int height){
  int i = 0;
  Area* area = NULL;
  if ( (area  = (Area*) malloc (sizeof(struct _Area))) ){
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};
    /*copia en los i primeros caracteres de area.cursor el numero 0*/
    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }

  return area;
}

/*
Funcion tipo void que libera la memoria del Area
introducida como argumento si no es NULL.
*/
void screen_area_destroy(Area* area){
  if(area)
    free(area);
}
/*
Funcion tipo void cuyo argumento es un puntero a area.
resetea el valor del area la funcion screen_area_reset_cursor
Tambien pone tantos ceros a area.cursor como indique area.height
*/
void screen_area_clear(Area* area){
  int i = 0;

  if (area){
    screen_area_reset_cursor(area);

    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
}

/*
Funcion tipo void que fija el valor del area.cursor
empleando la macro ACCESS
Su argumento es un puntero a area
*/
void screen_area_reset_cursor(Area* area){
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/*
*******************************
*******************************
*******************************
Mi capacidad se ha visto sobrepasada por esto.
 Mañana le preguntamos a partir de aqui
*******************************
*******************************
*******************************
*/
void screen_area_puts(Area* area, char *str){
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  screen_utils_replaces_special_chars(str);

  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width){
    memset(area->cursor, FG_CHAR, area->width);
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}

/*
Funcion que devuelve un int y cuyo argumento es puntero a Area
devuelve 1 si la area.cursor es mayor que la funcion ACCESS(__data, area->x + area->width, area->y + area->height - 1)
*/

int screen_area_cursor_is_out_of_bounds(Area* area){
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}

/*
Funcion tipo void cuyo argumento es un puntero a Area
¿¿¿¿¿¿¿¿¿¿¿¿???????????????
*/
void screen_area_scroll_up(Area* area){
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS){
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}
/*Revisa caracteres como tildes para que no haya problemas*/
void screen_utils_replaces_special_chars(char* str){
  char *pch = NULL;

  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
