#include "../include/Moove.h"

int move_entity(Entity * entity, float velocity_x, float velocity_y){
  if (entity == NULL) { return ERROR_RETURN;}
  entity->x += velocity_x;
  entity->y += velocity_y;
  return VALID_RETURN;
}


float path_process(float x, float y, float target_x, float target_y, float velocity){
  return (velocity / sqrt((x - target_x) * (x - target_x) + (y - target_y) * (y - target_y)));
}

int moove_shot(Entities * shot, Entities ship){
  Entities tmp_shot,save_shot;
  if (shot == NULL ) { return ERROR_RETURN; }

  if (*shot != NULL){
    tmp_shot = *shot;
    while (tmp_shot != NULL){
      save_shot = tmp_shot->next;
      switch (tmp_shot->type) {
        /* Ship_shot moove */
        case SHIP_SHOT :
          move_entity(tmp_shot,cos(tmp_shot->direction) * tmp_shot->velocity,sin(tmp_shot->direction) * tmp_shot->velocity); break;
        case SBIRE_SHOT :
          move_entity(tmp_shot,cos(tmp_shot->direction) * tmp_shot->velocity,sin(tmp_shot->direction)*tmp_shot->velocity); break;
        case SNIPER_SHOT :
          move_entity(tmp_shot,cos(tmp_shot->direction) * tmp_shot->velocity,sin(tmp_shot->direction) * tmp_shot->velocity); break;
        case SINUS_SHOT :
          if (tmp_shot->cooldown == 0) tmp_shot->hp = 0;
          tmp_shot->cooldown--;
          move_entity(tmp_shot,cos(tmp_shot->direction) * tmp_shot->velocity,sin(tmp_shot->direction) * tmp_shot->velocity); break;
        case GATLING_SHOT :
          move_entity(tmp_shot,cos(tmp_shot->direction) * tmp_shot->velocity,sin(tmp_shot->direction) * tmp_shot->velocity); break;

        /* Default */
        default : break;
      }
      tmp_shot = save_shot;
    }
  }
  return VALID_RETURN;
}

/* Deplacer la condition dans laquelle on détruit un ennemy dans le border collision */
int moove_ennemy(Entities * ennemy, Entities ship){
  /* OPTI */
  Entities tmp_ennemy;
  static int x_target, y_target;

  if (ennemy == NULL) { return ERROR_RETURN; }

  if (*ennemy != NULL){
    tmp_ennemy = *ennemy;
    while (tmp_ennemy != NULL){
      switch (tmp_ennemy->type) {
        /* Tank moove */
        case TANK: move_entity(tmp_ennemy,0,VELOCITY_TANK); break;
        /* Boss moove */
        case BOSS: move_entity(tmp_ennemy,0,VELOCITY_BOSS); break;
        /* Sbire moove */
        case SBIRE: move_entity(tmp_ennemy,0,VELOCITY_SBIRE); break;
        /* Sinus moove */
        case SINUS: move_entity(tmp_ennemy,sin(tmp_ennemy->y/50)*2,VELOCITY_SINUS); break;
        /* Sniper moove */
        case SNIPER: move_entity(tmp_ennemy,tmp_ennemy->velocity,0); break;
        /* Bomber moove */
        case BOMBER:
          if (in_range(tmp_ennemy->x,tmp_ennemy->y,ship->x,ship->y,RANGE_SIZE_BOMBER,HITBOX_BOMBER)){
            tmp_ennemy->direction = path_process(tmp_ennemy->x,tmp_ennemy->y,ship->x,ship->y,tmp_ennemy->velocity);
            move_entity(tmp_ennemy,(ship->x - tmp_ennemy->x) * tmp_ennemy->direction * 2, (ship->y - tmp_ennemy->y) * tmp_ennemy->direction * 2);
          }
          else move_entity(tmp_ennemy,0,VELOCITY_BOMBER);
          break;
        case GATLING: move_entity(tmp_ennemy,VELOCITY_GATLING,0); break;
        case COMET:
          if (tmp_ennemy->cooldown == 0) {
            x_target = rand()%W;
            y_target = rand()%H;
            tmp_ennemy->direction = path_process(tmp_ennemy->x,tmp_ennemy->y, x_target, y_target,tmp_ennemy->velocity);
            tmp_ennemy->cooldown = sqrt(pow(tmp_ennemy->x-x_target, 2) + pow(tmp_ennemy->y-y_target, 2)) / tmp_ennemy->velocity;
          }
          else {
            tmp_ennemy->cooldown--;
          }
          move_entity(tmp_ennemy,(x_target - tmp_ennemy->x) * tmp_ennemy->direction * 2, (y_target - tmp_ennemy->y) * tmp_ennemy->direction * 2);
        /* Default */
        default : break;
      }
      tmp_ennemy = tmp_ennemy->next;
    }
  }
  return VALID_RETURN;
}



int moove_ship(Entities * ship, float velocity_x, float velocity_y, int hitbox_size){
  if ((*ship)->bonus == NITRO) {
    (*ship)->x += velocity_x * NITRO_SPEED_FACTOR;
    (*ship)->y += velocity_y * NITRO_SPEED_FACTOR;
  }
  else {
    (*ship)->x += velocity_x;
    (*ship)->y += velocity_y;
  }
  return VALID_RETURN;
}

int manage_event_moove(Entities * ship, MLV_Keyboard_button keysym) {
  /* BUILD INERTIE */
  static float inertie_z = 1;
  static float inertie_s = 1;
  static float inertie_q = 1;
  static float inertie_d = 1;

  if (ship == NULL) { return ERROR_RETURN; }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED) {
    if (inertie_s < MAX_INERTIE_SHIP) inertie_s += INERTIE_SCALE_SHIP_S;
      moove_ship(ship,0,(*ship)->velocity + inertie_s,0);
    }
    else {
      if (inertie_s > 1) inertie_s -= INERTIE_SCALE_SHIP_S;
    moove_ship(ship,0,(*ship)->velocity + inertie_s/2,0);
  }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED) {
    if (inertie_z < MAX_INERTIE_SHIP) inertie_z += INERTIE_SCALE_SHIP_Z;
      moove_ship(ship,0,-(*ship)->velocity - inertie_z,0);
    }
    else {
      if (inertie_z > 1) inertie_z -= INERTIE_SCALE_SHIP_Z;
    moove_ship(ship,0,-(*ship)->velocity - inertie_z/2,0);
  }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED) {
    if (inertie_q < MAX_INERTIE_SHIP) inertie_q += INERTIE_SCALE_SHIP_Q;
    moove_ship(ship,-(*ship)->velocity - inertie_q,0,0);
  }
  else {
    if (inertie_q > 1) inertie_q -= INERTIE_SCALE_SHIP_Q;
    moove_ship(ship,-(*ship)->velocity - inertie_q/2,0,0);
  }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED) {
    if (inertie_d < MAX_INERTIE_SHIP) inertie_d += INERTIE_SCALE_SHIP_D;
    moove_ship(ship,(*ship)->velocity + inertie_d,0,0);
  }
  else {
    if (inertie_d > 1) inertie_d -= INERTIE_SCALE_SHIP_D;
    moove_ship(ship,(*ship)->velocity + inertie_d/2,0,0);
  }
  return VALID_RETURN;
}

int manage_moove(Entities * ship, Entities * ennemy, Entities * shot, MLV_Keyboard_button keysym){
  if (ship == NULL || ennemy == NULL || shot == NULL) {
    return ERROR_RETURN;
  }
  manage_event_moove(ship,keysym);
  moove_ennemy(ennemy,*ship);
  moove_shot(shot,*ship);
  return VALID_RETURN;
}
