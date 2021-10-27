#include "../include/Game_loop.h"

int game_loose(Entities * ship, Entities * shot, Entities * ennemy, MLV_Keyboard_button keysym) {
  MLV_Font * font;
  if ((*ship)->hp <= 0) {
    font = MLV_load_font("../media/ka1.ttf",50);
    printf("YOU LOOSE\n");
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text_box_with_font(0, 0, WIDTH, HEIGHT, "GAME OVER", font,1, MLV_COLOR_PURPLE, MLV_COLOR_PURPLE, MLV_rgba(0,0,0,0), MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
    MLV_wait_seconds(1);
    MLV_wait_keyboard(&keysym, NULL, NULL);
    delete_all_entities(ship);
    delete_all_entities(shot);
    delete_all_entities(ennemy);
    initialize_ship(ship);
    MLV_free_font(font);
    return 1;
  }
  return 0;
}

int game_pause(MLV_Keyboard_button * keysym, MLV_Button_state state, int * pause){
  MLV_Font * font;
  if (*keysym == MLV_KEYBOARD_p && state == MLV_PRESSED) *pause = TRUE;
  if (*pause == TRUE){
    font = MLV_load_font("../media/ka1.ttf",50);
    MLV_draw_text_with_font(WIDTH/3,HEIGHT/3,"PAUSE",font,MLV_COLOR_PURPLE);
    MLV_actualise_window();
    do{
      MLV_draw_text_with_font(WIDTH/3,HEIGHT/3,"PAUSE",font,MLV_COLOR_PURPLE);
      MLV_wait_keyboard(keysym, NULL, NULL);
      /*end game*/
      if (*keysym == MLV_KEYBOARD_e) return ERROR_RETURN;
      MLV_actualise_window();
    }while(*keysym != MLV_KEYBOARD_p);
    *keysym = MLV_KEYBOARD_n;
    *pause = FALSE;
    MLV_free_font(font);
  }
  return VALID_RETURN;
}



int game_menu(Graphic interface[], Stars stars[]){
  int mouse_x, mouse_y,type_button;
  MLV_Mouse_button mousebutton;
  MLV_Button_state state = MLV_RELEASED;

  while (TRUE) {
    MLV_clear_window(MLV_COLOR_BLACK);
    move_stars_tab(stars);
    create_star(stars);
    delete_stars_out_screen(stars);
    print_stars(stars);
    MLV_get_mouse_position(&mouse_x, &mouse_y);
    MLV_get_event(NULL, NULL, NULL, NULL, NULL, NULL, NULL, &mousebutton, &state);
    if ((type_button = print_menu(interface,mouse_x,mouse_y,mousebutton,state)) != MENU) return type_button;
    MLV_actualise_window();
  }

  return ERROR_RETURN;
}



int launch_level(Entities * buffer_ennemy, int level){

  switch (level) {
    case 1 : manage_parse(buffer_ennemy, "../levels/level1.txt");
      print_level_n(level);
      return VALID_RETURN;
    case 2 : manage_parse(buffer_ennemy, "../levels/level2.txt");
      print_level_n(level);
      return VALID_RETURN;
    case 3 : manage_parse(buffer_ennemy, "../levels/level3.txt");
      print_level_n(level);
      return VALID_RETURN;
    case 4 : manage_parse(buffer_ennemy, "../levels/level4.txt");
      print_level_n(level);
      return VALID_RETURN;
    case 5 : manage_parse(buffer_ennemy, "../levels/level5.txt");
      print_level_n(level);
      return VALID_RETURN;
    default : printf("ERROR DEFAULT \n"); return VALID_RETURN;
  }
  printf("--- ERROR NO SWITCH ---\n");
  return ERROR_RETURN;
}


int main_loop(){
  /* A SPLIT ABSOLUMENT <----------------------------------------------------------------------------- */
  int choice_menu;
  MLV_Font * font;
  MLV_Button_state state = MLV_RELEASED;
  MLV_Keyboard_button keysym;

  Entities ship = NULL;
  Entities ennemy = NULL;
  Entities buffer_ennemy = NULL;
  Entities shot = NULL;
  Stars stars[MAX_STAR];
  Graphic graphic[MAX_GRAPHIC_ENTITY];
  Graphic interface[9];

  /*float chrono = 0;*/
  /*float save;*/

  int pause = FALSE;
  int level = 0;

  srand(time(NULL));

  initialize_ship(&ship);
  init_stars_tab(stars);

  init_graphic_array(graphic);
  init_graphic_interface(interface);

  MLV_change_frame_rate (FREQUENCY);

  choice_menu = game_menu(interface,stars);

  if (choice_menu != QUIT){
    while(keysym != MLV_KEYBOARD_e && ship->hp > 0) {
      MLV_get_event(&keysym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
      if (choice_menu == PLAY || choice_menu == LEVEL){

        if (choice_menu == PLAY){
          spawn_random_ennemy(&ennemy);
        }

        else if (choice_menu == LEVEL){
          if (buffer_ennemy == NULL && ennemy == NULL){
            if (level == MAX_LEVEL) {
              font = MLV_load_font("../media/ka1.ttf",50);
              MLV_clear_window(MLV_COLOR_BLACK);
              MLV_draw_text_with_font(W/4, H/3, "VICTORY !", font, MLV_COLOR_PURPLE);
              MLV_actualise_window();
              MLV_wait_seconds(2);
              return MENU;
            }
            level++;
            delete_all_entities(&shot);
            launch_level(&buffer_ennemy,level);
          }
          spawn_file_ennemy(&buffer_ennemy, &ennemy);
        }

        /*MLV_get_event(&keysym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);*/
        delete_die_entities(&ennemy,&(ship->score));
        delete_die_entities(&shot,&(ship->score));
        manage_moove(&ship,&ennemy,&shot,keysym);
        move_stars_tab(stars);
        manage_entities_shoot(&ship,&ennemy,&shot,keysym);
        manage_collision(&ship,&ennemy,&shot,choice_menu);
        manage_bonus(&ship);
        game_pause(&keysym,state,&pause);
        create_star(stars);
        delete_stars_out_screen(stars);

        if (game_loose(&ship, &shot, &ennemy, keysym)) {
          return PLAY;
        }

        display_manage(ship,ennemy,shot,stars,graphic);
        /*We wait for the next frame */
        MLV_delay_according_to_frame_rate();

      }
      else if (choice_menu == HOWTOPLAYMENU){
        display_how_to_play_menu(interface);
      }
    }
  }

  if (keysym == MLV_KEYBOARD_e) {
    keysym = MLV_KEYBOARD_n;
    delete_all_entities(&ship);
    delete_all_entities(&shot);
    delete_all_entities(&ennemy);
    return MENU;
  }

  delete_all_entities(&ship);
  delete_all_entities(&shot);
  delete_all_entities(&ennemy);
  return QUIT;
}



int main(){
  int menu;

  init_window();

  do {
    MLV_clear_window(MLV_COLOR_BLACK);
    menu = main_loop();
  } while (menu != QUIT);

  close_window();
  return 0;
}
