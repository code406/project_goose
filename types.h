/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1



/* Define el tipo Id (identificador numérico de cada casilla). Es un entero long */
typedef long Id;



/* Enumeración para crear un boolean */
typedef enum {
  FALSE,  /* 0 */
  TRUE    /* 1 */
} BOOL;



/* Enumeración que define para los estados ERROR y OK un valor numérico */
typedef enum {
  ERROR, /* 0 */
  OK     /* 1 */
} STATUS;



/* Enumeración que define para cada dirección o coordenada un valor numérico */
typedef enum {
  N, /* 0 */
  S, /* 1 */
  E, /* 2 */
  W  /* 3 */
} DIRECTION;



#endif
