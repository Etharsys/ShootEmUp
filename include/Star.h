/* Star.h */
#ifndef __STAR__
#define __STAR__

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/Balancing.h"
#include "../include/Graphic_Values.h"
#include "../include/Error.h"

typedef struct stars{
  int x, y;
  int size;
  int speed;
  int active;
  int transparency; /* transparency factor 0,1,2 or 3*/
  int color; /* for now just white */
} Stars;


/**
 * Initiate the tab of stars
 * @param tab_stars The tab of stars
 * @return 1 if initiation gone well, 0 else
*/
int init_stars_tab(Stars tab_stars[]);


/**
 * Move every stars on the screen
 * @param tab_stars The tab of stars
 * @return 1 if every movements gone well, 0 else
*/
int move_stars_tab(Stars tab_stars[]);


/**
 * Create/Active a star on the tab of stars
 * @param tab_stars The tab of stars
 * @return 1 if the creation gone well, 0 else
*/
int create_star(Stars tab_stars[]);


/**
 * Delete every stars on the tab of stars
 * @param tab_stars The tab of stars
 * @return 1 if deletes gone well, 0 else
*/
int delete_stars_out_screen(Stars tab_stars[]);

#endif
