#ifndef __SHOOT__
#define __SHOOT__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"
#include "../include/Entity.h"

/*Shoot*/
/**
 * Calcul the direction with atan (need module math.h)
 * @param x_target The position x to target
 * @param y_target The position y to target
 * @param x The position x of the entity
 * @param y The position y of the entity
 * @return the direction to take for a shot
*/
float process_direction_shot(int x_target, int y_target, int x, int y);


/**
 * Manage shot for ship (player actions)
 * @param ship The ship entity
 * @param shot The list of shot
 * @param keysym The value of keyboard
 * @return 1 if the entity is not null (dont exist), 0 else
*/
int ship_shoot(Entities * ship, Entities * shot, MLV_Keyboard_button keysym);


/**
 * Manage shot for ennemy (ennemy difficulty conditions)
 * @param ennemy The list of ennemy
 * @param shot The list of shot
 * @param ship The ship entity
 * @return 1 if all shot creation happened well, 0 else
*/
int ennemy_shoot(Entities * ennemy, Entities * shot, Entities ship);


/**
 * Manage functions of all shots creation
 * @param ship The ship entity
 * @param ennemy The list of ennemy
 * @param shot The list of shot
 * @param keysym The value of keyboard
 * @return 1 if every call gone well, 0 else
*/
int manage_entities_shoot(Entities * ship, Entities * ennemy, Entities * shot, MLV_Keyboard_button keysym);

#endif
