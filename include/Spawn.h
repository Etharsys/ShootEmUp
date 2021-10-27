#ifndef __SPAWN__
#define __SPAWN__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"
#include "../include/Entity.h"

/*Spawn*/
/**
 * Spawn a random ennemy in the list of enemies
 * @param ennemy The list of enemies
 * @return 1 an ennemy is choose, 0 else
*/
int spawn_random_ennemy(Entities * ennemy);


/**
 * Calcul a random between 2 numbers
 * @param a The minimum (include)
 * @param b The maximum (not include)
 * @return the calculated random number
*/
int rand_a_b(int a, int b);


/**
 * Calcul a type for a ennemy with random values of balance
 * @param rand_100 A random number between 0 and 100
 * @return the type of ennemy, -1 if not found
*/
int type_of_ennemy(int rand_100);


/**
 * Check if a type is in the list of enemies
 * @param type The type to check
 * @param ennemy The list of ennemy
 * @return the type of ennemy, 0 else
*/
int type_in_ennemy(int type, Entities ennemy);


/**
 * Spawn a ennemy in the list of ennemy with sbire spawn rules
 * @param ennemy The list of enemies
 * @return 1 if spawn gone well, 0 else
*/
int spawn_sbire(Entities * ennemy);


/**
  * Spawn a ennemy in the list of ennemy with sinus spawn rules
  * @param ennemy The list of enemies
  * @return 1 if spawn gone well, 0 else
*/
int spawn_sinus(Entities * ennemy);


/**
  * Spawn a ennemy in the list of ennemy with sniper spawn rules
  * @param ennemy The list of enemies
  * @return 1 if spawn gone well, 0 else
*/
int spawn_sniper(Entities * ennemy);


/**
  * Spawn a ennemy in the list of ennemy with bomber spawn rules
  * @param ennemy The list of enemies
  * @return 1 if spawn gone well, 0 else
*/
int spawn_bomber(Entities * ennemy);


/**
  * Spawn a ennemy in the list of ennemy with gatling spawn rules
  * @param ennemy The list of enemies
  * @return 1 if spawn gone well, 0 else
*/
int spawn_gatling(Entities * ennemy);


/**
 * Spawn a ennemy from the ennemy on a file
 * @param buffer_ennemy The buffer of ennemy from the file
 * @param ennemy the current list of valid ennemy
 * @return 0 if the buffer is void
*/
int spawn_file_ennemy(Entities * buffer_ennemy, Entities * ennemy);

#endif
