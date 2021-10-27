#ifndef __GRAPHIC__
#define __GRAPHIC__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Entity.h"
#include "../include/Star.h"
#include "../include/Error.h"


/**
 * The structure which represent a entity to print
 * @param sprite The sprite (image)
 * @param sprite_size The size of the sprite to print (check values)
*/
typedef struct graphic{
  MLV_Image * sprite;
  int sprite_size;
  int width;
  int height;
  int x,y;
}Graphic;

/**
 * Initiate a MLV window
 * @return 1 if the window initiate well, 0 else
*/
int init_window();


/**
 * Close the MLV window
 * @return 1 if the window closed well, 0 else
*/
int close_window();

/**
 * Manage graphics needed display
 * @param ship The ship entity
 * @param ennemy The ennemy list
 * @param shot The shot list
 * @param star The star array
 * @param graphic The array of sprite for entities
 * @return 1 if every entities display well, 0 else
*/
int display_manage(Entities ship, Entities ennemy, Entities shot, Stars stars[], Graphic graphic[]);


/**
 * Manage the interface display : score and health point
 * @param hp The health point quantity
 * @param score The score count
 * @return 1 if the interface printed well, 0 else
*/
int print_interface(int hp, int score);


/**
 * Display the health point on the MLV window
 * @param score The score count
 * @return 1 if the score printed well, 0 else
*/
int print_score(int score);


/**
 * Display the health point on the MLV window
 * @param hp The health point quantity
 * @return 1 if the lives printed well, 0 else
*/
int print_lives(int hp);


/**
 * Print the stars on the MLV window
 * @param tab_stars The tab of stars
 * @return 1 if all stars printed well, 0 else
*/
int print_stars(Stars tab_stars[]);


/**
 * Charge all sprites for entities on a tab
 * @param graphic The array of sprite for entities
 * @return 1 if all sprites charged well, 0 else
*/
int init_graphic_array(Graphic graphic[]);


/**
 * Display every entities on the MLV window
 * @param hp The health point quantity
 * @param graphic The array of sprite for entities
 * @return 1 if the interface printed well, 0 else
*/
int display_entity(Entities entity, Graphic graphic[]);

/*---
int print_font_play_button(int mouse_x, int mouse_y, int x1, int y1, int x2, int y2, MLV_Color col1, MLV_Color col2);
---*/


/**
 * Display the menu on the MLV_window
 * @param interface The tab of saved sprites
 * @param mouse_x the x position of the ship
 * @param mouse_y the y position of the ship
 * @param mousebutton the keyvalue of the keyboard
 * @param state the status of the key
 * @return a global int for the main loop
*/
int print_menu(Graphic interface[], int mouse_x, int mouse_y, MLV_Mouse_button mousebutton, MLV_Button_state state);


/**
 * Init every sprite for the menu print
 * @param interface The tab of saved sprites
 * @return 1 if the interface initialized well, 0 else
*/
int init_graphic_interface(Graphic interface[]);


/**
 * Display a level number on level game mode on the MLV window
 * @param level The current level number
 * @return 0 if not a valid level number
*/
int print_level_n(int level);


/**
 * Display the how to play button on the MLV_window
 * @param interface The tab of saved sprites
 * @return 1 if the button printed well, 0 else
*/
int display_how_to_play_menu(Graphic interface[]);

#endif
