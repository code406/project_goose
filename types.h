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

typedef long Id;


/*
Crea una enumeracion (modo de hacer una variable BOOL)
False = 0; True = 1;
*/

/*
Para STATUS ERROR = 0; OK = 1;
*/

typedef enum {
  ERROR, OK
} STATUS;

/*
Para DIRECTION
N = 0; S = 1; E = 2; W = 3

*/

typedef enum {
  N, S, E, W
} DIRECTION;

#endif
