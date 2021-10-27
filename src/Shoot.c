#include "../include/Shoot.h"

float process_direction_shot(int x_target, int y_target, int x, int y){
  if (x_target - x != 0) {
    if (x_target < x) return PI + atan((float)(y_target - y) / (x_target - x));
    else return atan((float)(y_target - y) / (x_target - x));
  }
  if (y_target < y) return (-PI/2);
  else if (y_target > y) return (PI/2);
  return 0;
}

int ennemy_shoot(Entities * ennemy, Entities * shot, Entities ship){
  Entities tmp_ennemy;
  int nb_shot;

  if (ennemy == NULL || shot == NULL) { return ERROR_RETURN; }
  /* FAIRE LES PARTICULARITE DES TIRS ENNEMY */
  for (tmp_ennemy = *ennemy ; tmp_ennemy != NULL ; tmp_ennemy = tmp_ennemy->next){
    if (tmp_ennemy->cooldown <= 0) {
      switch (tmp_ennemy->type) {
        case SBIRE :
          tmp_ennemy->direction = process_direction_shot(ship->x,ship->y,tmp_ennemy->x,tmp_ennemy->y);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
          HP_SBIRE_SHOT,tmp_ennemy->direction,VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          tmp_ennemy->cooldown = COOLDOWN_SBIRE;
          break;
        case BOSS :
          tmp_ennemy->direction = process_direction_shot(ship->x,ship->y,tmp_ennemy->x,tmp_ennemy->y);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SBIRE_SHOT,tmp_ennemy->direction,VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          tmp_ennemy->cooldown = COOLDOWN_SBIRE;
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SBIRE_SHOT,tmp_ennemy->direction + (PI/6),VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SBIRE_SHOT,tmp_ennemy->direction - (PI/6),VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SBIRE_SHOT,tmp_ennemy->direction - (PI/3),VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SBIRE_SHOT,tmp_ennemy->direction + (PI/3),VELOCITY_SBIRE_SHOT,COOLDOWN_SBIRE_SHOT,DAMAGE_SBIRE_SHOT,SBIRE_SHOT,ENNEMY_CLAN,0,HITBOX_SBIRE_SHOT);
          break;
        case SINUS :
          tmp_ennemy->direction = process_direction_shot(ship->x,ship->y,tmp_ennemy->x,tmp_ennemy->y);
          for (nb_shot = 0 ; nb_shot < 6 ; nb_shot++) {
            add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
            HP_SINUS_SHOT,tmp_ennemy->direction + nb_shot,VELOCITY_SINUS_SHOT,COOLDOWN_SINUS_SHOT,DAMAGE_SINUS_SHOT,SINUS_SHOT,ENNEMY_CLAN,0,HITBOX_SINUS_SHOT);
          }
          tmp_ennemy->cooldown = COOLDOWN_SBIRE;
          break;
        case SNIPER :
          tmp_ennemy->direction = process_direction_shot(ship->x,ship->y,tmp_ennemy->x,tmp_ennemy->y);
          add_entity_to_list(shot,tmp_ennemy->x,tmp_ennemy->y,
          HP_SNIPER_SHOT,tmp_ennemy->direction,VELOCITY_SNIPER_SHOT,COOLDOWN_SNIPER_SHOT,DAMAGE_SNIPER_SHOT,SNIPER_SHOT,ENNEMY_CLAN,0,HITBOX_SNIPER_SHOT);
          tmp_ennemy->cooldown = COOLDOWN_SBIRE;
          break;
        case GATLING :
          if (tmp_ennemy->time < 5) {
            add_entity_to_list(shot,tmp_ennemy->x-16,tmp_ennemy->y + HITBOX_GATLING,
            HP_GATLING_SHOT,(PI/2),VELOCITY_GATLING_SHOT,COOLDOWN_GATLING_SHOT,DAMAGE_GATLING_SHOT,GATLING_SHOT,ENNEMY_CLAN,0,HITBOX_GATLING_SHOT);
            add_entity_to_list(shot,tmp_ennemy->x+16,tmp_ennemy->y + HITBOX_GATLING,
            HP_GATLING_SHOT,(PI/2),VELOCITY_GATLING_SHOT,COOLDOWN_GATLING_SHOT,DAMAGE_GATLING_SHOT,GATLING_SHOT,ENNEMY_CLAN,0,HITBOX_GATLING_SHOT);
            tmp_ennemy->time++;
            tmp_ennemy->cooldown = 2;
          }
          if (tmp_ennemy->time == 5){
            tmp_ennemy->cooldown = COOLDOWN_GATLING;
            tmp_ennemy->time = 0;
          }
          break;
        case BOMBER : break;
        default : break;
      }
    }
    else tmp_ennemy->cooldown--;
  }
  return VALID_RETURN;
}



int ship_shoot(Entities * ship, Entities * shot, MLV_Keyboard_button keysym){
  if (ship == NULL || shot == NULL) { return ERROR_RETURN; }
  if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
    if ((*ship)->cooldown == 0){
      if ((*ship)->bonus == TRIPLE_SHOT) {
        add_entity_to_list(shot,(*ship)->x,(*ship)->y,
          HP_SHIP_SHOT,(4*PI)/3,VELOCITY_SHIP_SHOT,COOLDOWN_SHIP_SHOT,
          DAMAGE_SHIP_SHOT,SHIP_SHOT,ALLY_CLAN,0,HITBOX_SHIP_SHOT);
        add_entity_to_list(shot,(*ship)->x,(*ship)->y,
          HP_SHIP_SHOT,(5*PI)/3,VELOCITY_SHIP_SHOT,COOLDOWN_SHIP_SHOT,
          DAMAGE_SHIP_SHOT,SHIP_SHOT,ALLY_CLAN,0,HITBOX_SHIP_SHOT);
      }
      add_entity_to_list(shot,(*ship)->x,(*ship)->y,
        HP_SHIP_SHOT,DIRECTION_SHIP_SHOT,VELOCITY_SHIP_SHOT,COOLDOWN_SHIP_SHOT,DAMAGE_SHIP_SHOT,SHIP_SHOT,ALLY_CLAN,0,HITBOX_SHIP_SHOT);
      (*ship)->cooldown = SHIP_COOLDOWN;
    }
    else (*ship)->cooldown-- ;
  }
  return VALID_RETURN;
}



int manage_entities_shoot(Entities * ship, Entities * ennemy, Entities * shot, MLV_Keyboard_button keysym){
  if (!ship_shoot(ship,shot,keysym) || !ennemy_shoot(ennemy,shot,*ship)) {
    return ERROR_RETURN;
  }
  return VALID_RETURN;
}
