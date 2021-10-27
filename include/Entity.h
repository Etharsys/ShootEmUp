#ifndef __ENTITY__
#define __ENTITY__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"
#include "../include/Graphic_Values.h"

/* 60 byte */
/**
 * The structure entity representing a ship, an ennemy, a shot.
 * @param x The position x
 * @param y The position y
 * @param hp The health point of the entity
 * @param velocity The speed (acceleration)
 * @param cooldown The dps (shoot per seconds)
 * @param clan The clan (ally, ennemy, bonus)
 * @param type The type (ship, sbire, sinus...)
 * @param direction The actual direction for the entity
 * @param damage The body to body damage (if collision)
 * @param next The next entity
 * @param previous The previous entity
 * @param score The score of the entity (for ship)
 * @param hitbox The hitbox (px)
 * @param time The time before go on the next sequence of the entity
 * @param bonus The bonus value (enum bonus)
 * @param chrono The chrono for the spawn of a ennemy on parsing mode
*/
typedef struct entity {
  float x,y;
  int hp;
  float velocity;
  int cooldown;
  int clan;
  int type;
  float direction;
  int damage;
  struct entity *next;
  struct entity *previous;
  int score;
  int hitbox;
  /*for bonus*/
  int time;
  Bonus_type bonus;
  int chrono;
}*Entities,Entity;

/**
 * Initialize the ship following the initialisation plan
 * @param ship The ship entity
 * @return 1 if the entity ship created well, 0 else
*/
int initialize_ship(Entities * ship);


/**
 * Initialize a new entity following the initialisation plan
 * @param x The position x
 * @param y The position y
 * @param hp The entity health point
 * @param direction The direction of the entity
 * @param velocity The entity speed
 * @param cooldown The entity dps
 * @param damage The entity damage (body to body)
 * @param type The entity type (sniper, sbire, ...)
 * @param clan The entity clan (ennemy, ally, bonus)
 * @param score The initial score (for ship essentialy)
 * @param hitbox The entity hitbox
 * @return 1 if the entity created well, 0 else
*/
Entity * initialize_entity(float x, float y, int hp, float direction, float velocity, int cooldown, int damage, int type, int clan, int score, int hitbox);


/**
 * Add a new entity following the initialisation plan to a entity list
 * @param entity The list to append the new entity
 * @param x The position x
 * @param y The position y
 * @param hp The entity health point
 * @param direction The direction of the entity
 * @param velocity The entity speed
 * @param cooldown The entity dps
 * @param damage The entity damage (body to body)
 * @param type The entity type (sniper, sbire, ...)
 * @param clan The entity clan (ennemy, ally, bonus)
 * @param score The initial score (for ship essentialy)
 * @param hitbox The entity hitbox
 * @return 1 if the entity created well, 0 else
*/
int add_entity_to_list(Entities * entity, float x, float y, int hp, float direction, float velocity, int cooldown, int damage, int type, int clan, int score, int hitbox);


/**
 * Delete a entity of a list of entities
 * @param head The head of the list
 * @param entity A copy to the entity to delete
 * @return 1 if the entity is well delete, 0 else
*/
int delete_entity(Entities * head, Entities * entity);


/**
 * Delete every entities which have hp bellow 0
 * @param entity The entity list
 * @param score_ship The actual score of the ship
 * @return 1 if all entities deleted well, 0 else
*/
int delete_die_entities(Entities * entity, int * score_ship);


/**
 * Print the ennemy list
 * @param ennemy An entities list
 * @return 1 if the list printed well, 0 else
*/
int printf_ennemy(Entities ennemy);


/**
 * Check a type to have a clan
 * @param type The type to check
 * @return the clan of the type
*/
int type_enity(int type);


/**
 * Swap a entity to a bonus
 * @param tmp_entity The entity which need to become a bonus
 * @return 1 if the entity became a bonus, 0 else
*/
int become_bonus(Entities * tmp_entity);


/**
 * Manage actuals bonus on the ship with bonus rules
 * @param entity The bonus entity
 * @return 1 if the bonus is not null, 0 else
*/
int manage_bonus(Entities * entity);


/**
 * Delete every entities on the screen
 * @param entities A list of entities
 * @return 1 if every entities deleted well, 0 else
*/
int delete_all_entities(Entities * entities);


#endif
