#ifndef __COLLISION__
#define __COLLISION__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"
#include "../include/Entity.h"

/**
 * Check if a future position of a entity is out of the screen
 * @param hitbox_size The actual hitbox of the entity
 * @param new_x The future position x of the entity
 * @param new_y The future position y of the entity
 * @return 1 if the entity is in collision, 0 else
*/
int border_collision(int hitbox_size, int new_x, int new_y);


/**
 * Check if a position of a entity (target) is in range of an other entity position (checked).
 * @param x The position x of the checked position
 * @param y The position y of the checked position
 * @param target_x The position x of the target position
 * @param target_y The position y of the target position
 * @param range The distance max to check between the both position
 * @param target_x hitbox_size the size of the target
 * @return 1 if the target position is in range of the checked position, 0 else
*/
int in_range(int x, int y, int target_x, int target_y, int range, int hitbox_size);


/**
 * Apply effects on ship with rules of borders collisions
 * @param entity The list of ennemies and shots entity
 * @param ship The ship
 * @return 1 if all collision gone well, 0 else
*/
int border_collision_entities(Entities * entity, Entities * ship);


/**
 * Apply effect on all entities with collision rules
 * @param entity_a The first list of entities
 * @param entity_b The second list of entities
 * @return 1 if every collision gone well, 0 else
*/
int collision_entities(Entities * entity_a, Entities * entity_b);


/**
 * Check if two entity position are in collision
 * @param xa The position x of the first entity
 * @param ya The position y of the first entity
 * @param xb The position x of the second entity
 * @param yb The position y of the second entity
 * @return 1 if the entity is in collision, 0 else
*/
int in_collision(int xa, int ya, int xb, int yb, int hitbox_size_a, int hitbox_size_b);


/**
 * Call every happenable collision
 * @param ship The ship
 * @param ennemy The list of ennemies
 * @param shot The list of shot
 * @return 1 if every collision call gone well, 0 else
*/
int manage_collision(Entities * ship, Entities * ennemy, Entities * shot,  int type_game);


/**
 * Check for all entity if there are a collision with the ship
 * @param entity The entity to check
 * @param ship The ship entity
 * @return 1 if every collision call gone well, 0 else
*/
int border_collision_entities(Entities * entity, Entities * ship);

#endif
