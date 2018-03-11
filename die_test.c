/**
 * @brief Comprueba el funcionamiento de un dado
 *
 * @file die_test.c
 * @author Arturo Morcillo, David Palomo
 * @version 2.0.E
 * @date 11-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "die.h"
#include "types.h"

#define ID_D 1  /* Id que se asigna al dado */

int main()
{
  Die* die = NULL;

  printf("Programa para comprobar el funcionamiento de un dado.\n");

  printf("\nSe iniciliza el dado.\n");
  die = die_create(ID_D);
  die_print(die);

  printf("\nSe tira el dado.\n");
  die_roll(die);
  die_print(die);

  printf("\nSe destruye el dado.\n");
  if(die_destroy(die) == OK)
  {
    printf("Dado destruido\n");
  }
  else
  {
    printf("Dado no destruido:\n");
    die_print(die);
  }

  return 0;
}
