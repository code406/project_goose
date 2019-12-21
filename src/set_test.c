/**
 * @brief Comprueba el funcionamiento de un set
 *
 * @file set_test.c
 * @author Ines Martin, Javier Mateos, Arturo Morcillo y David Palomo
 * @version 2.0.E
 * @date 11/03/2018
 * @copyright GNU Public License
 */

#include <stdio.h>

#include "set.h"

int main()
{
  Set* set = NULL;
  Id ele1=2, ele2=7, ele3=32, ele4=12;

  printf("Programa para comprobar el funcionamiento de un set.\n\n");

  printf("Estos son los id que se van a utilizar para la prueba:\n");
  printf("ele1: %ld \n", ele1);
  printf("ele2: %ld \n", ele2);
  printf("ele3: %ld \n", ele3);
  printf("ele4: %ld \n", ele4);


  printf("\nSe inicializa el set:\n");
  set = set_create();
  set_print(set);

  printf("\n\n");

  printf("Se añaden los elementos al set:\n");
  set_add_id(set, ele1);
  set_add_id(set, ele2);
  set_add_id(set, ele3);
  set_add_id(set, ele4);
  set_print(set);

  printf("\n\n");

  printf("Se elimina el set.\n");
  set_destroy(set);
  printf("Set destruido.\n");

  return 0;
}
