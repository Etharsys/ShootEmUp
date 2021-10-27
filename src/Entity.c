#include "../include/Entity.h"

/*erroroverdose*/

/* SHIP */

int initialize_ship(Entities * ship){
  *ship = (Entity*) malloc(sizeof(Entity));
  if (*ship == NULL) return ERROR_RETURN;

  (*ship)->x = SHIP_X;
  (*ship)->y = SHIP_Y;
  (*ship)->hp = SHIP_HP;
  (*ship)->velocity = SHIP_VELOCITY;
  (*ship)->cooldown = SHIP_COOLDOWN;
  (*ship)->clan = ALLY_CLAN;
  (*ship)->type = SHIP;
  (*ship)->direction = NONE;
  (*ship)->damage = SHIP_DAMAGE;
  (*ship)->next = NULL;
  (*ship)->previous = NULL;
  (*ship)->score = 0;
  (*ship)->hitbox = HITBOX_SHIP;
  (*ship)->time = 0;
  (*ship)->bonus = NOT_A_BONUS;
  return VALID_RETURN;
}



int printf_ennemy(Entities ennemy){
  int i;
  i = 0;
  while (ennemy != NULL){
    /*printf("%d, ",ennemy->type);*/
    i++;
    ennemy = ennemy->next;
  }
  printf("CONTENU DE LA LISTE : %d \n",i);
  return VALID_RETURN;
}



int delete_entity(Entities * head, Entities * entity){
  Entity * delete;

  if (*head == NULL) {
    return VALID_RETURN;
  }

  if ((*head)->next == NULL && (*head)->previous == NULL) {
    delete = *entity;

    free(delete);
    *head = NULL;
    *entity = NULL;

    return VOID_EXCEPTION;
  }

  if ((*entity)->next != NULL && (*entity)->previous == NULL) {
    delete = *entity;

    *head = (*entity)->next;
    (*head)->previous = NULL;
    *entity = *head;

    free(delete);
    return VALID_RETURN;
  }

  if ((*entity)->next == NULL && (*entity)->previous != NULL) {
    delete = *entity;

    *entity = (*entity)->previous;
    (*entity)->next = NULL;
    free(delete);
    return VALID_RETURN;
  }

  if ((*entity)->next != NULL && (*entity)->previous != NULL) {
    delete = *entity;

    (*entity)->next->previous = (*entity)->previous;
    (*entity)->previous->next = (*entity)->next;
    (*entity) = (*entity)->next;

    free(delete);
    return VALID_RETURN;
  }
  return ERROR_RETURN;
}



Entity * initialize_entity(float x, float y, int hp, float direction, float velocity, int cooldown, int damage, int type, int clan, int score, int hitbox){
  Entity * entity = (Entity*) malloc(sizeof(Entity));
  if (entity == NULL) return NULL;

  entity->x = x;
  entity->y = y;
  entity->hp = hp;
  entity->velocity = velocity;
  entity->cooldown = cooldown;
  entity->clan = clan;
  entity->type = type;
  entity->direction = direction;
  entity->damage = damage;
  entity->next = NULL;
  entity->previous = NULL;
  entity->score = score;
  entity->hitbox = hitbox;
  entity->time = 0;
  entity->bonus = NOT_A_BONUS;
  entity->chrono = 0;

  return entity;
}



int add_entity_to_list(Entities * entity, float x, float y, int hp, float direction, float velocity, int cooldown, int damage, int type, int clan, int score, int hitbox){
  Entities new_entity;
  Entities tmp_entity;
  if (entity == NULL) { return ERROR_RETURN; }

  new_entity = initialize_entity(x,y,hp,direction,velocity,cooldown,damage,type,clan,score,hitbox);
  if (new_entity == NULL) return ERROR_RETURN;

  if (*entity == NULL){
    *entity = new_entity;
    return VALID_RETURN;
  }

  else{
    tmp_entity = *entity;
    *entity = new_entity;
    new_entity->next = tmp_entity;
    tmp_entity->previous = new_entity;
    return VALID_RETURN;
  }

  return VALID_RETURN;
}

int type_enity(int type){
  if (type == SBIRE || type == SNIPER || type == SINUS || type == BOMBER || type == GATLING || type == COMET) return ENNEMY;
  if (type == SHIP_SHOT || type == SBIRE_SHOT || type == SINUS_SHOT || type == SNIPER_SHOT || type == GATLING_SHOT) return SHOT;
  if (type == BONUS) return BONUS;
  return NONE;
}

int delete_die_entities(Entities * entity, int * score_ship){
  Entities tmp_entity,save_entity;

  if (entity == NULL || score_ship == NULL) { return ERROR_RETURN; }

  tmp_entity = *entity;
  while (tmp_entity != NULL){
    save_entity = tmp_entity->next;
    if (tmp_entity->hp <= 0){
      if (type_enity(tmp_entity->type) == ENNEMY) {
        if (tmp_entity->type == COMET) {
          become_bonus(&tmp_entity);
        }
        (*score_ship) += tmp_entity->score;
      }
      if (tmp_entity->hp <= 0) {
        delete_entity(entity,&tmp_entity);
      }
    }
    tmp_entity = save_entity;
  }
  return VALID_RETURN;
}

int delete_all_entities(Entities * entities) {
  Entities tmp, save;
  if (entities == NULL) { return ERROR_RETURN; }
  tmp = *entities;
  while (tmp != NULL) {
    save = tmp->next;
    delete_entity(entities, &tmp);
    tmp = save;
  }
  return VALID_RETURN;
}

int become_bonus(Entities * tmp_entity) {
  int rand_bonus = 12 + rand()%NB_BONUS;
  if (tmp_entity == NULL) { return ERROR_RETURN; }

  (*tmp_entity)->hp = 1;
  (*tmp_entity)->damage = 0;
  (*tmp_entity)->clan = ITEM_CLAN;

  switch(rand_bonus) {
    case HEAL :         (*tmp_entity)->time = TIME_HEAL; (*tmp_entity)->bonus = HEAL; break;
    case SHIELD :       (*tmp_entity)->time = TIME_SHIELD; (*tmp_entity)->bonus = SHIELD; break;
    case NITRO :        (*tmp_entity)->time = TIME_NITRO; (*tmp_entity)->bonus = NITRO; ;break;
    case TRIPLE_SHOT :  (*tmp_entity)->time = TIME_TRIPLE_SHOT; (*tmp_entity)->bonus = TRIPLE_SHOT; break;
    default :
      return 0;
  }
  (*tmp_entity)->type = (*tmp_entity)->bonus;

  return VALID_RETURN;
}

int manage_bonus(Entities * entity) {
  if (entity == NULL) { return ERROR_RETURN; }
  if ((*entity)->bonus == HEAL) {
    if ((*entity)->hp >= 8) {
      (*entity)->hp = 10;
    }
    else {
      (*entity)->hp += 2;
    }
  }
  (*entity)->time--;
  if ((*entity)->time <= 0) (*entity)->bonus = NOT_A_BONUS;

  return VALID_RETURN;
}
