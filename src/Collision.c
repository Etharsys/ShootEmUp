#include "../include/Collision.h"


/* BUILD */
int in_range(int x, int y, int target_x, int target_y, int range, int hitbox_size){
  return sqrt(((target_x - x) * (target_x - x)) + ((target_y - y) * (target_y - y))) <= range + hitbox_size;
}

int in_collision(int xa, int ya, int xb, int yb, int hitbox_size_a, int hitbox_size_b){
  if (xb == xa && ya == yb) return FALSE;
  return sqrt(((xb - xa) * (xb - xa)) + ((yb - ya) * (yb - ya))) <= hitbox_size_a + hitbox_size_b;
}



int collision_entities(Entities * entity_a, Entities * entity_b){
  /*attention : this function is good for not many Entities, to divide if we have a lot*/
  /* AMELIORER CECI */
  Entities tmp_a,tmp_b;
  int i = 0, j = 0;

  if (*entity_a == NULL || *entity_b == NULL) {
    return ERROR_RETURN;
  }

  for (tmp_a = *entity_a ; tmp_a != NULL ; tmp_a = tmp_a->next){
    for (tmp_b = *entity_b ; tmp_b != NULL ; tmp_b = tmp_b->next){
      if ((tmp_a->clan == ALLY_CLAN && tmp_b->clan == ENNEMY_CLAN) || (tmp_a->clan == ENNEMY_CLAN && tmp_b->clan == ALLY_CLAN)){
        if (in_collision(tmp_a->x,tmp_a->y,tmp_b->x,tmp_b->y,tmp_a->hitbox,tmp_b->hitbox) == TRUE){
          if (tmp_a->bonus == SHIELD) {
            tmp_a->hp += tmp_b->damage;
          }
          if (tmp_b->bonus == SHIELD) {
            tmp_b->hp += tmp_a->damage;
          }
          tmp_a->hp -= tmp_b->damage;
          tmp_b->hp -= tmp_a->damage;
        }
      }
      if (type_enity(tmp_a->type) == ENNEMY && type_enity(tmp_b->type) == ENNEMY && i < j) {
        if (in_collision(tmp_a->x,tmp_a->y,tmp_b->x,tmp_b->y,tmp_a->hitbox - 1,tmp_b->hitbox - 1) == TRUE){
          /*tmp_a->hp -= tmp_b->damage;
          tmp_b->hp -= tmp_a->damage;*/
        }
      }
      if (tmp_a->clan == ALLY_CLAN && tmp_b->clan == ITEM_CLAN) {
        if (in_collision(tmp_a->x,tmp_a->y,tmp_b->x,tmp_b->y,tmp_a->hitbox,tmp_b->hitbox) == TRUE){
          tmp_b->hp = 0;
          tmp_a->bonus = tmp_b->bonus;
          tmp_a->time = tmp_b->time;
        }
      }
      j++;
    }
    i++;
  }
  return VALID_RETURN;
}



int border_collision(int hitbox_size, int new_x, int new_y){
  if ((new_x - hitbox_size) < 0 )       return TRUE;
  if ((new_y - hitbox_size) < 0 )       return TRUE;
  if ((new_x + hitbox_size) > WIDTH )   return TRUE;
  if ((new_y + hitbox_size) > HEIGHT )  return TRUE;
  return FALSE;
}

int border_collision_difference(int hitbox_size, float * x, float * y, float velocity){
  if ((*x - hitbox_size) < 0 )       {*x += hitbox_size + velocity; return 1;}
  if ((*y - hitbox_size) < 0 )       {*y += hitbox_size + velocity; return 1;}
  if ((*x + hitbox_size) > WIDTH )   {*x -= hitbox_size + velocity;  return 1;}
  if ((*y + hitbox_size) > HEIGHT )  {*y -= hitbox_size + velocity;  return 1;}
  return 0;
}

int border_collision_entities(Entities * entity, Entities * ship){
  /*OPTI*/
  Entities tmp_entity;

  if (entity == NULL || ship == NULL) { return ERROR_RETURN; }

  for (tmp_entity = *entity ; tmp_entity != NULL ; tmp_entity = tmp_entity->next){
    switch (tmp_entity->type) {
      case TANK:
        if(border_collision(0,tmp_entity->x,tmp_entity->y)){
          tmp_entity->hp = 0;
          tmp_entity->score = 0;
        }
        break;
      case SHIP:
        if (border_collision(tmp_entity->hitbox,tmp_entity->x + tmp_entity->velocity,tmp_entity->y + tmp_entity->velocity)){
          border_collision_difference(tmp_entity->hitbox, &tmp_entity->x, &tmp_entity->y, tmp_entity->velocity);
        }
      case SBIRE:
        if(border_collision(0,tmp_entity->x,tmp_entity->y)){
          tmp_entity->hp = 0;
          tmp_entity->score = 0;
          (*ship)->hp--;
        }
        break;
      case SINUS:
        if(border_collision(0,tmp_entity->x,tmp_entity->y)){
          tmp_entity->hp = 0;
          tmp_entity->score = 0;
          (*ship)->hp--;
        }
        break;
      case SNIPER:
        if(border_collision(0,tmp_entity->x,tmp_entity->y)){
          tmp_entity->velocity *= -1;
        }
        break;
      case BOMBER:
        if(border_collision(0,tmp_entity->x,tmp_entity->y)){
          tmp_entity->hp = 0;
          tmp_entity->score = 0;
          (*ship)->hp--;
        }
        break;
      case GATLING: if(tmp_entity->x > WIDTH) tmp_entity->hp = 0; break;
      case SBIRE_SHOT: if(border_collision(0,tmp_entity->x,tmp_entity->y)) tmp_entity->hp = 0; break;
      case SHIP_SHOT: if(border_collision(0,tmp_entity->x,tmp_entity->y)) tmp_entity->hp = 0; break;
      case SNIPER_SHOT: if(border_collision(0,tmp_entity->x,tmp_entity->y)) tmp_entity->hp = 0; break;
      case SINUS_SHOT: if(border_collision(0,tmp_entity->x,tmp_entity->y)) tmp_entity->hp = 0; break;
      case GATLING_SHOT: if(border_collision(0,tmp_entity->x,tmp_entity->y)) tmp_entity->hp = 0; break;
      default : break;
    }
  }
  return VALID_RETURN;
}


int manage_collision(Entities * ship, Entities * ennemy, Entities * shot, int type_game){
  if (ship == NULL || ennemy == NULL || shot == NULL) { return ERROR_RETURN; }
  border_collision_entities(ennemy,ship);
  border_collision_entities(shot,ship);
  border_collision_entities(ship,ship);
  collision_entities(ship,ennemy);
  collision_entities(ship,shot);
  collision_entities(ennemy,shot);
  if (type_game == PLAY) {
    collision_entities(ennemy,ennemy);
  }
  return VALID_RETURN;
}
