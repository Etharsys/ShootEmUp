#ifndef __MAIN_LOOP__
#define __MAIN_LOOP__

#include <time.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Balancing.h"
#include "../include/Error.h"

#include "../include/Graphic.h"
#include "../include/Entity.h"
#include "../include/Collision.h"
#include "../include/Moove.h"
#include "../include/Star.h"
#include "../include/Spawn.h"
#include "../include/Shoot.h"
#include "../include/Parseur.h"

/**
 * Manage the pause and unpause button
 * @param keysym A symbol of keyboard
 * @param state The state of the button on keysym
 * @param pause A boolean value : 1 pause, 0 unpause
 * @return 1 if the pause is called, 0 if the exit button is pressed
*/
int game_pause(MLV_Keyboard_button * keysym, MLV_Button_state state, int * pause);


/**
 * Manage the end game (loose), by deleting entities
 * @param ship The ship entity
 * @param shot The list of shots
 * @param ennemy The ennemy list
 * @return 1 if the loose condition are complete, 0 else
*/
int game_loose(Entities * ship, Entities * shot, Entities * ennemy, MLV_Keyboard_button keysym);


/**
 * The main loop for the game
 * @return 1 if the game end propely, 0 else
*/
int game_loop();


/**
 * Manage the menus, import sprite for entities, and create the tab of stars
 * @param interface The tab of sprite for entities
 * @param stars The tab of stars
 * @return 1 if stars,interface has been well created and the menu well initialize, 0 else
*/
int game_menu(Graphic interface[], Stars stars[]);


#endif
