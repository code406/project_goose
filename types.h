/**
 * @brief Define varios tipos
 *
 * @file types.h
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

 #ifndef TYPES_H
 #define TYPES_H

 #define WORD_SIZE 1000
 #define NO_ID -1
 #define MAX_ID 20


 /**
 * @brief Id (entero tipo long)
 * Define el tipo Id (identificador numérico de una casilla).
 */
 typedef long Id;


 /**
 *@brief Enumeracion BOOL 
 * Enumeración para crear un boolean
 */
 typedef enum
 {
   FALSE,  /* 0 */
   TRUE    /* 1 */
 } BOOL;


 /**
 * @brief Enumeracion STATUS
 *Enumeración que define para los estados ERROR y OK un valor numérico
 */
 typedef enum
 {
   ERROR, /* 0 */
   OK     /* 1 */
 } STATUS;


 /**
 * @brief enumeracion DIRECTION
 * Enumeración que define para cada dirección o coordenada un valor numérico
 */
 typedef enum
 {
   N, /* 0 */
   S, /* 1 */
   E, /* 2 */
   W  /* 3 */
 } DIRECTION;


 #endif
