#include "../include/Graphic.h"

int init_window() {
  MLV_create_window("Shoot'em Up", "Shoot'em Up", WIDTH, HEIGHT);
  return VALID_RETURN;
}

int close_window() {
  MLV_free_window();
  return VALID_RETURN;
}

static int calc_log(int value) {
  int i;
  for (i = 0 ; value != 0 ; i++) {
    value /= 10;
  }
  return i + 1;
}

int init_graphic_interface(Graphic interface[]){
  int type,width,height;
  MLV_Image * button;

  for (type = 0 ; type < 9 ; type++){
    switch (type) {
      case ARENA: button = MLV_load_image("../media/Arena.png"); width = WIDTH_ARENA; height = HEIGHT_ARENA;
      interface[type].x = X_ARENA;
      interface[type].y = Y_ARENA;
      break;
      case LEVELS: button = MLV_load_image("../media/Level.png"); width = WIDTH_LEVELS; height = HEIGHT_LEVELS;
      interface[type].x = X_LEVELS;
      interface[type].y = Y_LEVELS;
      break;
      case HOWTOPLAY: button = MLV_load_image("../media/HowToPlay.png"); width = WIDTH_HOWTOPLAY; height = HEIGHT_HOWTOPLAY;
      interface[type].x = X_HOWTOPLAY;
      interface[type].y = Y_HOWTOPLAY;
      break;
      case CLOSE: button = MLV_load_image("../media/Quit.png"); width = WIDTH_CLOSE; height = HEIGHT_CLOSE;
      interface[type].x = X_CLOSE;
      interface[type].y = Y_CLOSE;
      break;
      case ARENAGLOW: button = MLV_load_image("../media/ArenaGlow.png"); width = WIDTH_ARENA; height = HEIGHT_ARENA;
      interface[type].x = X_ARENA;
      interface[type].y = Y_ARENA;
      break;
      case LEVELSGLOW: button = MLV_load_image("../media/LevelGlow.png"); width = WIDTH_LEVELS; height = HEIGHT_LEVELS;
      interface[type].x = X_LEVELS;
      interface[type].y = Y_LEVELS;
      break;
      case HOWTOPLAYGLOW: button = MLV_load_image("../media/HowToPlayGlow.png"); width = WIDTH_HOWTOPLAY; height = HEIGHT_HOWTOPLAY;
      interface[type].x = X_HOWTOPLAY;
      interface[type].y = Y_HOWTOPLAY;
      break;
      case CLOSEGLOW: button = MLV_load_image("../media/QuitGlow.png"); width = WIDTH_CLOSE; height = HEIGHT_CLOSE;
      interface[type].x = X_CLOSE;
      interface[type].y = Y_CLOSE;
      break;
      case HOWTOPLAYINTERFACE: button = MLV_load_image("../media/HowToPlayMenu.png"); width = WIDTH_HOWTOPLAYINTERFACE; height = HEIGHT_HOWTOPLAYINTERFACE;
      interface[type].x = X_HOWTOPLAYINTERFACE;
      interface[type].y = Y_HOWTOPLAYINTERFACE;
      break;
      default : break;
    }
    if (button == NULL) return ERROR_RETURN;
    MLV_resize_image(button, width, height);
    interface[type].sprite = button;
    interface[type].width = width;
    interface[type].height = height;
  }

  button = NULL;
  return VALID_RETURN;
}

int init_graphic_array(Graphic graphic[]){
  int type;
  int size_sprite;
  MLV_Image * entity;


  for (type = 0 ; type < MAX_GRAPHIC_ENTITY ; type++){
    switch (type) {
      case SHIP:        entity = MLV_load_image("../media/Ship.png"); size_sprite = SPRITE_SIZE_SHIP;break;
      case SBIRE:       entity = MLV_load_image("../media/Sbire.png"); size_sprite = SPRITE_SIZE_SBIRE;break;
      case SINUS:       entity = MLV_load_image("../media/Sinus.png"); size_sprite = SPRITE_SIZE_SINUS;break;
      case SNIPER:      entity = MLV_load_image("../media/Sniper.png"); size_sprite = SPRITE_SIZE_SNIPER;break;
      case BOMBER:      entity = MLV_load_image("../media/Bomber.png"); size_sprite = SPRITE_SIZE_BOMBER;break;
      case GATLING:     entity = MLV_load_image("../media/Gatling.png"); size_sprite = SPRITE_SIZE_GATLING;break;
      case COMET:       entity = MLV_load_image("../media/Comet.png"); size_sprite = SPRITE_SIZE_COMET;break;
      case SHIP_SHOT:   entity = MLV_load_image("../media/Ship_shot.png"); size_sprite = SPRITE_SIZE_SHIP_SHOT;break;
      case SBIRE_SHOT:  entity = MLV_load_image("../media/Sbire_shot.png"); size_sprite = SPRITE_SIZE_SBIRE_SHOT;break;
      case SNIPER_SHOT: entity = MLV_load_image("../media/Sniper_shot.png"); size_sprite = SPRITE_SIZE_SNIPER_SHOT;break;
      case SINUS_SHOT:  entity = MLV_load_image("../media/Sinus_shot.png"); size_sprite = SPRITE_SIZE_SINUS_SHOT;break;
      case GATLING_SHOT:entity = MLV_load_image("../media/Gatling_shot.png"); size_sprite = SPRITE_SIZE_GATLING_SHOT;break;
      case SHIELD:      entity = MLV_load_image("../media/Shield.png"); size_sprite = SPRITE_SIZE_SHIELD;break;
      case HEAL:        entity = MLV_load_image("../media/Heal.png"); size_sprite = SPRITE_SIZE_HEAL;break;
      case NITRO:       entity = MLV_load_image("../media/Nitro.png"); size_sprite = SPRITE_SIZE_NITRO;break;
      case TRIPLE_SHOT: entity = MLV_load_image("../media/TripleShot.png"); size_sprite = SPRITE_SIZE_TRIPLE_SHOT;break;
      case TANK:        entity = MLV_load_image("../media/Tank.png"); size_sprite = SPRITE_TANK;break;
      case BOSS:        entity = MLV_load_image("../media/Boss.png"); size_sprite = SPRITE_BOSS;break;
      default : break;
    }
    if (entity == NULL) return ERROR_RETURN;
    MLV_resize_image(entity, size_sprite, size_sprite);
    graphic[type].sprite = entity;
    graphic[type].sprite_size = size_sprite;
  }
  entity = NULL;
  return VALID_RETURN;
}



int print_lives(int hp) {
  MLV_Image * hp_sprite;

  switch (hp) {
    case 10 : hp_sprite = MLV_load_image("../media/life01.png"); break;
    case 9 : hp_sprite = MLV_load_image("../media/life02.png"); break;
    case 8 : hp_sprite = MLV_load_image("../media/life03.png"); break;
    case 7 : hp_sprite = MLV_load_image("../media/life04.png"); break;
    case 6 : hp_sprite = MLV_load_image("../media/life05.png"); break;
    case 5 : hp_sprite = MLV_load_image("../media/life06.png"); break;
    case 4 : hp_sprite = MLV_load_image("../media/life07.png"); break;
    case 3 : hp_sprite = MLV_load_image("../media/life08.png"); break;
    case 2 : hp_sprite = MLV_load_image("../media/life09.png"); break;
    case 1 : hp_sprite = MLV_load_image("../media/life10.png"); break;
    default :
      hp_sprite = MLV_load_image("../media/lifeno.png"); break;

  }
  MLV_resize_image(hp_sprite, 80, 80);
  MLV_draw_image(hp_sprite, 0, 0);
  MLV_free_image(hp_sprite);
  return VALID_RETURN;
}

int print_score(int score){
  char * score_str = NULL;
  MLV_Image * score_sprite;
  MLV_Font * font;

  font = MLV_load_font("../media/ka1.ttf",20);
  score_str = malloc(sizeof(char) * (calc_log(score)));
  score_sprite = MLV_load_image("../media/Score.png");

  sprintf(score_str, "%d",score);

  MLV_draw_image(score_sprite, WIDTH - 150, 0);
  MLV_draw_text_box_with_font(WIDTH - 80, 5, 100, 50, score_str, font, 1, MLV_rgba(0,0,0,0), MLV_COLOR_PURPLE, MLV_rgba(0,0,0,0), MLV_TEXT_RIGHT, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);

  free(score_str);
  MLV_free_image(score_sprite);
  MLV_free_font(font);
  return VALID_RETURN;
}

int print_interface(int hp, int score){
  print_lives(hp);
  print_score(score);
  return VALID_RETURN;
}

int print_stars(Stars tab_stars[]) {
  int i;
  for (i = 0 ; i < MAX_STAR ; i++) {
    if (tab_stars[i].active == 1) {
      MLV_draw_filled_circle(tab_stars[i].x, tab_stars[i].y, tab_stars[i].size, MLV_rgba(255, 255, 255, 255 - (tab_stars[i].transparency * TRANSPARENCY_STARS_FACTOR)));
    }
  }
  return VALID_RETURN;
}

int display_entity(Entities entity, Graphic graphic[]){
  while (entity != NULL){
    MLV_draw_image(graphic[entity->type].sprite,
      entity->x - graphic[entity->type].sprite_size / 2,entity->y - graphic[entity->type].sprite_size / 2);
      /*TO PRINT HITBOX*/
    /*MLV_draw_circle(entity->x,entity->y,entity->hitbox,MLV_COLOR_RED);*/
    entity = entity->next;
  }
  return VALID_RETURN;
}



int print_menu(Graphic interface[], int mouse_x, int mouse_y, MLV_Mouse_button mousebutton, MLV_Button_state state) {
  int type;

  for (type = 0 ; type < 4 ; type++){
    switch (type) {
      case ARENA:
        if ((mouse_x > X_ARENA && mouse_y > Y_ARENA) && (mouse_x < (X_ARENA + WIDTH_ARENA) && mouse_y < (Y_ARENA + HEIGHT_ARENA))){
          if (mousebutton == MLV_BUTTON_LEFT && state == MLV_PRESSED) { return PLAY;}
          MLV_draw_image(interface[ARENAGLOW].sprite,interface[ARENAGLOW].x,interface[ARENAGLOW].y);
        }
        else {
          MLV_draw_image(interface[ARENA].sprite,interface[ARENA].x,interface[ARENA].y);
        }
        break;
      case LEVELS:
        if ((mouse_x > X_LEVELS && mouse_y > Y_LEVELS) && (mouse_x < (X_LEVELS + WIDTH_LEVELS) && mouse_y < (Y_LEVELS + HEIGHT_LEVELS)) ){
          if (mousebutton == MLV_BUTTON_LEFT && state == MLV_PRESSED) { return LEVEL;}
          MLV_draw_image(interface[LEVELSGLOW].sprite,interface[LEVELSGLOW].x,interface[LEVELSGLOW].y);
        }
        else {
          MLV_draw_image(interface[LEVELS].sprite,interface[LEVELS].x,interface[LEVELS].y);
        }
        break;
      case HOWTOPLAY:
        if ((mouse_x > X_HOWTOPLAY && mouse_y > Y_HOWTOPLAY) && (mouse_x < (X_HOWTOPLAY + WIDTH_HOWTOPLAY) && mouse_y < (Y_HOWTOPLAY + HEIGHT_HOWTOPLAY)) ){
          if (mousebutton == MLV_BUTTON_LEFT && state == MLV_PRESSED) { return HOWTOPLAYMENU;}
          MLV_draw_image(interface[HOWTOPLAYGLOW].sprite,interface[HOWTOPLAYGLOW].x,interface[HOWTOPLAYGLOW].y);
        }
        else {
          MLV_draw_image(interface[HOWTOPLAY].sprite,interface[HOWTOPLAY].x,interface[HOWTOPLAY].y);
        }
        break;
      case CLOSE:
        if ((mouse_x > X_CLOSE && mouse_y > Y_CLOSE) && (mouse_x < (X_CLOSE + WIDTH_CLOSE) && mouse_y < (Y_CLOSE + HEIGHT_CLOSE)) ){
          if (mousebutton == MLV_BUTTON_LEFT && state == MLV_PRESSED) { return QUIT;}
          MLV_draw_image(interface[CLOSEGLOW].sprite,interface[CLOSEGLOW].x,interface[CLOSEGLOW].y);
        }
        else {
          MLV_draw_image(interface[CLOSE].sprite,interface[CLOSE].x,interface[CLOSE].y);
        }
        break;
      default : break;
    }
  }
  MLV_actualise_window();
  return MENU;
}



int print_level_n(int level){
  MLV_Font * font;

  font = MLV_load_font("../media/ka1.ttf",50);
  MLV_clear_window(MLV_COLOR_BLACK);
  switch (level) {
    case 1: MLV_draw_text_with_font(W/4, H/3, "LEVEL 1", font, MLV_COLOR_PURPLE); break;
    case 2: MLV_draw_text_with_font(W/4, H/3, "LEVEL 2", font, MLV_COLOR_PURPLE); break;
    case 3: MLV_draw_text_with_font(W/4, H/3, "LEVEL 3", font, MLV_COLOR_PURPLE); break;
    case 4: MLV_draw_text_with_font(W/4, H/3, "LEVEL 4", font, MLV_COLOR_PURPLE); break;
    case 5: MLV_draw_text_with_font(W/4, H/3, "LEVEL 5", font, MLV_COLOR_PURPLE); break;
    default : return ERROR_RETURN;
  }
  MLV_actualise_window();
  MLV_wait_seconds(2);
  return VALID_RETURN;
}

int display_how_to_play_menu(Graphic interface[]){
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_image(interface[HOWTOPLAYINTERFACE].sprite,interface[HOWTOPLAYINTERFACE].x,interface[HOWTOPLAYINTERFACE].y);
  MLV_actualise_window();
  return VALID_RETURN;
}

int display_manage(Entities ship, Entities ennemy, Entities shot, Stars stars[], Graphic graphic[]){
  MLV_clear_window(MLV_COLOR_BLACK);
  print_stars(stars);
  display_entity(ship,graphic);
  display_entity(ennemy,graphic);
  display_entity(shot,graphic);
  print_interface(ship->hp,ship->score);

  MLV_actualise_window();
  return VALID_RETURN;
}
