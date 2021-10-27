#include "../include/Spawn.h"

int rand_a_b(int a, int b){
  return rand()%(b-a) + a;
}

int type_of_ennemy(int rand_100) {
  if (rand_100 >= 0 && rand_100 <= CHANCE_SBIRE) {
    return ENNEMY;
  }
  if (rand_100 > CHANCE_SBIRE && rand_100 <= CHANCE_SINUS) {
    return SINUS;
  }
  if (rand_100 > CHANCE_SINUS && rand_100 <= CHANCE_SNIPER) {
    return SNIPER;
  }
  if (rand_100 > CHANCE_SNIPER && rand_100 <= CHANCE_BOMBER) {
    return BOMBER;
  }
  if (rand_100 > CHANCE_BOMBER && rand_100 <= CHANCE_GATLING) {
    return GATLING;
  }
  if (rand_100 > CHANCE_GATLING && rand_100 <= CHANCE_COMET) {
    return COMET;
  }

  return -1;
}

int type_in_ennemy(int type, Entities ennemy) {
  while (ennemy != NULL) {
    if (ennemy->type == type) {
      return VALID_RETURN;
    }
    ennemy = ennemy->next;
  }
  return ERROR_RETURN;
}

int spawn_sbire(Entities * ennemy) {
  int x,y;
  x = rand_a_b(WIDTH / 10, WIDTH - WIDTH / 10);
  y = HITBOX_SBIRE;
  if (add_entity_to_list(ennemy,x,y,
    HP_SBIRE,NONE,VELOCITY_SBIRE,COOLDOWN_SBIRE,DAMAGE_SBIRE,SBIRE,ENNEMY_CLAN,1,HITBOX_SBIRE) == VALID_RETURN) {
    return VALID_RETURN;
  }
  return ERROR_RETURN;
}

int spawn_sinus(Entities * ennemy) {
  int x,y;
  x = rand_a_b(WIDTH/3,WIDTH - WIDTH/3);
  y = 1;
  if (add_entity_to_list(ennemy,x,y,
    HP_SINUS,NONE,VELOCITY_SINUS,COOLDOWN_SINUS,DAMAGE_SINUS,SINUS,ENNEMY_CLAN,2,HITBOX_SINUS) == VALID_RETURN) {
    return VALID_RETURN;
  }
  return ERROR_RETURN;
}

int spawn_sniper(Entities * ennemy) {
  int x,y;
  x = HITBOX_SNIPER;
  y = rand_a_b(50 + HITBOX_SNIPER, 50 + HEIGHT/4);
  if (add_entity_to_list(ennemy,x,y,
    HP_SNIPER,NONE,VELOCITY_SNIPER,COOLDOWN_SNIPER,DAMAGE_SNIPER,SNIPER,ENNEMY_CLAN,2,HITBOX_SNIPER) == VALID_RETURN) {
      return VALID_RETURN;
  }
  return ERROR_RETURN;
}

int spawn_bomber(Entities * ennemy) {
  int x,y;
  x = rand_a_b(WIDTH / 10, WIDTH - WIDTH / 10);
  y = HITBOX_BOMBER;
  if (add_entity_to_list(ennemy,x,y,
    HP_BOMBER,NONE,VELOCITY_BOMBER,COOLDOWN_BOMBER,DAMAGE_BOMBER,BOMBER,ENNEMY_CLAN,1,HITBOX_BOMBER) == VALID_RETURN
  && (add_entity_to_list(ennemy,x+HITBOX_BOMBER * 3,y+HITBOX_BOMBER * 3,
    HP_BOMBER,NONE,VELOCITY_BOMBER,COOLDOWN_BOMBER,DAMAGE_BOMBER,BOMBER,ENNEMY_CLAN,1,HITBOX_BOMBER) == VALID_RETURN)
  && (add_entity_to_list(ennemy,x+HITBOX_BOMBER * 3,y,
    HP_BOMBER,NONE,VELOCITY_BOMBER,COOLDOWN_BOMBER,DAMAGE_BOMBER,BOMBER,ENNEMY_CLAN,1,HITBOX_BOMBER) == VALID_RETURN)) {
      return VALID_RETURN;
  }
  else {
    return ERROR_RETURN;
  }
}

int spawn_gatling(Entities * ennemy) {
  int x,y;
  x = HITBOX_GATLING;
  y = HITBOX_GATLING * 2;
  if (add_entity_to_list(ennemy,x,y,
    HP_GATLING,NONE,VELOCITY_GATLING,COOLDOWN_GATLING,DAMAGE_GATLING,GATLING,ENNEMY_CLAN,1,HITBOX_GATLING) == VALID_RETURN) {
      return VALID_RETURN;
  }
  return ERROR_RETURN;
}

int spawn_comet(Entities * ennemy, int can_spawn) {
  int x,y;
  if (!type_in_ennemy(COMET, *ennemy) && !type_in_ennemy(HEAL, *ennemy) && !type_in_ennemy(SHIELD, *ennemy) &&
          !type_in_ennemy(NITRO, *ennemy) && !type_in_ennemy(TRIPLE_SHOT, *ennemy)) {
    if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
      x = rand_a_b(1,WIDTH);
      y = HITBOX_COMET;
      if (add_entity_to_list(ennemy,x,y,
        HP_COMET,NONE,VELOCITY_COMET,COOLDOWN_COMET,DAMAGE_COMET,COMET,ENNEMY_CLAN,1,HITBOX_COMET) == VALID_RETURN) {
          return VALID_RETURN;
        }
      return ERROR_RETURN;
    }
    else {
      return VALID_RETURN;
    }
  }
  else {
    return VALID_RETURN;
  }
}


int spawn_random_ennemy(Entities * ennemy){
  /* AMELIORER CECI */
  int random_type = type_of_ennemy(rand_a_b(0,CHANCE_ENNEMY));
  int can_spawn = rand_a_b(0,100);

  switch (random_type) {
    case SBIRE:
      if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
        if (spawn_sbire(ennemy)) { return VALID_RETURN; }
        break;
      }
      return VALID_RETURN;
    case SINUS:
      if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
        if (spawn_sinus(ennemy)) { return VALID_RETURN; }
        break;
      }
      return VALID_RETURN;
    case SNIPER:
      if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
        if (spawn_sniper(ennemy)) { return VALID_RETURN; }
        break;
      }
      return VALID_RETURN;
    case BOMBER:
      if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
        if (spawn_bomber(ennemy)) { return VALID_RETURN; }
        break;
      }
    case GATLING:
      if (can_spawn >= 0 && can_spawn < SPAWN_CHANCE_ENNEMY){
        if (spawn_gatling(ennemy)) { return VALID_RETURN; }
        break;
      }
    case COMET:
      if (spawn_comet(ennemy, can_spawn)) { return VALID_RETURN; }
      break;
    default : break;
  }
  printf("ERROR spawn_random_ennemy()\n");
  return ERROR_RETURN;
}


int spawn_file_ennemy(Entities * buffer_ennemy, Entities * ennemy) {
  if (*buffer_ennemy == NULL){
    return END_PARSING;
  }
  if ((*buffer_ennemy)->chrono == 0) {
    add_entity_to_list(ennemy, (*buffer_ennemy)->x, (*buffer_ennemy)->y, (*buffer_ennemy)->hp,
      (*buffer_ennemy)->direction, (*buffer_ennemy)->velocity, (*buffer_ennemy)->cooldown,
        (*buffer_ennemy)->damage, (*buffer_ennemy)->type, (*buffer_ennemy)->clan,
           (*buffer_ennemy)->score, (*buffer_ennemy)->hitbox);
    delete_entity(buffer_ennemy,buffer_ennemy);
  }
  else {
    (*buffer_ennemy)->chrono--;
  }
  return VALID_RETURN;
}
