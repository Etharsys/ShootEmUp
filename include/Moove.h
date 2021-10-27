#ifndef __MOOVE__
#define __MOOVE__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"
#include "../include/Collision.h"
#include "../include/Entity.h"


/**
 * Move a entity in cartesian plan
 * @param entity The entity to move
 * @param velocity_x The deplacement in x
 * @param velocity_y The deplacement in x
 * @return 1 if the entity is not null (dont exist), 0 else
*/
int move_entity(Entity * entity, float velocity_x, float velocity_y);


/**
 * Move the ship in cartesian plan respecting ship movement conditions
 * @param ship The ship to move
 * @param velocity_x The deplacement in x
 * @param velocity_y The deplacement in x
 * @param hitbox_size The hitbox of the ship
 * @return 1 if the ship is not null, 0 else
*/
int moove_ship(Entities * ship, float velocity_x, float velocity_y, int hitbox_size);


/**
 * Calcul a movement to apply to a coordonate to go on an other coordonate
 * @param x The first position x
 * @param y The first position y
 * @param target_x The second position x
 * @param target_y The second position y
 * @param velocity The velocity for the movement
 * @return the direction to go for the coordonate x,y
*/
float path_process(float x, float y, float target_x, float target_y, float velocity);


/**
 * Move ennemys in cartesian plan respecting ship conditions
 * @param ship The ship to apply ship rules on ennemys
 * @param ennemy The list of ennemys
 * @return 1 if the list of ennemys is not null, 0 else
*/
int moove_ennemy(Entities * ennemy, Entities ship);


/**
 * Manage movement for all entity on map (ship, shot, ennemy)
 * @param ship The ship to move
 * @param ennemy The list of ennemys to move
 * @param shot The list of shots to move
 * @param keysym The value of keyboard
 * @return 1 if the ship, the list of ennemys and the list of shots are not null, 0 else
*/
int manage_moove(Entities * ship, Entities * ennemy, Entities * shot, MLV_Keyboard_button keysym);


/**
 * Manage movement with player actions
 * @param ship The ship to move
 * @param keysym The value of keyboard
 * @return 1 if the ship is not null, 0 else
*/
int manage_event_moove(Entities * ship, MLV_Keyboard_button keysym);


/**
 * Move shots in cartesian plan respecting ship conditions
 * @param ship The ship to apply ship rules on ennemys
 * @param shot The list of shots
 * @return 1 if the list of shots is not null, 0 else
*/
int moove_shot(Entities * shot, Entities ship);


#endif
