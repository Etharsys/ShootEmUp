#include "../include/Star.h"
/* Au lieu d'appeler la fonction create_star, tp la star en haut de l'écran */
int init_stars_tab(Stars tab_stars[]) {
  int i;

  for(i = 0 ; i < MAX_STAR ; i++) {
    tab_stars[i].x = rand()%W;
    tab_stars[i].y = 0;
    tab_stars[i].size = rand()%MAX_SIZE_STARS - MIN_SIZE_STARS;
    tab_stars[i].speed = rand()%MAX_SPEED_STARS + 1;
    tab_stars[i].active = 0;
    tab_stars[i].transparency = rand()%TRANSPARENCY_STARS;
    tab_stars[i].color = 0;
  }
  return VALID_RETURN;
}

int move_stars_tab(Stars tab_stars[]) {
  int i;
  for (i = 0 ; i < MAX_STAR ; i++) {
    if (tab_stars[i].active == 1) {
      tab_stars[i].y += tab_stars[i].speed;
    }
  }
  return VALID_RETURN;
}

int create_star(Stars tab_stars[]) {
  int alea = rand()%MAX_STAR;
  if (alea % STAR_RAND == 0 && tab_stars[alea].active == 0) {
    tab_stars[alea].active = 1;
  }
  return VALID_RETURN;
}

int delete_stars_out_screen(Stars tab_stars[]) {
  int i;
  for (i = 0 ; i < MAX_STAR ; i++) {
    if (tab_stars[i].active == 1) {
      if (tab_stars[i].y > HEIGHT + MAX_SIZE_STARS) {
        tab_stars[i].y = 0;
        tab_stars[i].active = 0;
      }
    }
  }
  return VALID_RETURN;
}
