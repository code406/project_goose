/**
 * @brief Define varios tipos
 *
 * @file types.h
 * @author Pareja
 * @version 1.0.E
 * @date 18/02/2018
 * @copyright GNU Public License
 */

 #ifndef TYPES_H
 #define TYPES_H

 #define WORD_SIZE 1000
 #define NO_ID -1


 /* Define el tipo Id (identificador numérico de una casilla). Es entero long */
 typedef long Id;


 /* Enumeración para crear un boolean */
 typedef enum
 {
   FALSE,  /* 0 */
   TRUE    /* 1 */
 } BOOL;


 /* Enumeración que define para los estados ERROR y OK un valor numérico */
 typedef enum
 {
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
