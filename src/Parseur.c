#include "../include/Parseur.h"

/*
TEXT FORMAT :
[ID ennemy] [TAMPON] [x] [y]
type = id ennemy
tampon = time
x = x
y = y
*/

void print_all_entity(Entities entity){
  if (entity == NULL){
    printf("ERROR VOID\n");
  }

  while (entity != NULL) {
    printf("%d : %d : %f %f\n",entity->type,entity->chrono,entity->x,entity->y);
    entity = entity->next;
  }
}

int manage_parse(Entities * test, char * level) {
  FILE * entry_ennemies = fopen(level, "r+"); /* the file of ennemies */

  if (entry_ennemies == NULL) {
    printf("<Error> No file to parse\n");
    return 0;
  }

  printf(">> Start parsing\n");
  file_parsing(entry_ennemies, test);
  printf(">> End parsing\n");
  print_all_entity(*test);

  fclose(entry_ennemies);
  return 1;
}



int compte_integer(char string[], int i){
  int cmpt;
  cmpt = 0;

  if (string == NULL) return 0;

  for( ; (string[i] >= '0' && string[i] <= '9') || ( string[i] == '-' ) ; i++){
    cmpt++;
  }

  return cmpt;
}



int file_parsing(FILE * file_to_parse, Entities * test){
  char line[50][MAXENNEMIES];
  char * buffer;
  int type;
  int i,j,k,size,nb_line;

  /* Save all line */
  i = 0;
  while (fgets(line[i],50,file_to_parse) != NULL){
    printf("%s\n",line[i]);
    i++;
  }
  nb_line = i;

  /* Print all line */
  for (i = 0 ; i < nb_line ; i++){
    printf("line %d : %s\n",i,line[i]);
  }

  /* Parse all line */
  for (i = 0 ; i < nb_line ; i++){ /* line */
    printf("line : %d\n",i);
    printf("line %d : %s\n",i,line[i]);
    type = 0;
    for (j = 0 ; type < 4 ; j++){ /* char */
      /* Add new void entity */
      if ((line[i][j] >= '0' && line[i][j] <= '9') || line[i][j] == '-' ){
        size = compte_integer(line[i],j);
        buffer = malloc(sizeof(char) * size);
        buffer[size] = '\n';

        for (k = 0 ; (line[i][j] >= '0' && line[i][j] <= '9') || line[i][j] == '-' ; k++ ){
          buffer[k] = line[i][j];
          j++;
        }

        /* Add values to neentity */
        switch (type) {
          case 0 : set_values_type(test,atoi(buffer)); break;
          case 1 : (*test)->chrono = (atoi(buffer) * FREQUENCY); break;
          case 2 : (*test)->x = (atoi(buffer) * COEFF_RESOLUTION); break;
          case 3 : (*test)->y = (atoi(buffer) * COEFF_RESOLUTION); break;
          default : return -1;
        }
        type++;
        free(buffer);
      }
    }
  }
  printf("nb_line = %d\n",nb_line);
  return nb_line;
}

int set_values_type(Entities * entity, int type){
  /* We add new type entity with her particularities */
  if (*entity == NULL){
    printf("ERROR VOID LIST IN set_values_type\n");
  }

  switch (type) {
    case SBIRE: add_entity_to_list(entity,NONE,NONE,
      HP_SBIRE,NONE,VELOCITY_SBIRE,COOLDOWN_SBIRE,DAMAGE_SBIRE,SBIRE,ENNEMY_CLAN,1,HITBOX_SBIRE); break;
    case SNIPER: add_entity_to_list(entity,NONE,NONE,
      HP_SNIPER,NONE,VELOCITY_SNIPER,COOLDOWN_SNIPER,DAMAGE_SNIPER,SNIPER,ENNEMY_CLAN,2,HITBOX_SNIPER); break;
    case BOMBER: add_entity_to_list(entity,NONE,NONE,
      HP_BOMBER,NONE,VELOCITY_BOMBER,COOLDOWN_BOMBER,DAMAGE_BOMBER,BOMBER,ENNEMY_CLAN,1,HITBOX_BOMBER); break;
    case SINUS: add_entity_to_list(entity,NONE,NONE,
      HP_SINUS,NONE,VELOCITY_SINUS,COOLDOWN_SINUS,DAMAGE_SINUS,SINUS,ENNEMY_CLAN,2,HITBOX_SINUS); break;
    case GATLING: add_entity_to_list(entity,NONE,NONE,
      HP_GATLING,NONE,VELOCITY_GATLING,COOLDOWN_GATLING,DAMAGE_GATLING,GATLING,ENNEMY_CLAN,1,HITBOX_GATLING); break;
    case TANK: add_entity_to_list(entity,NONE,NONE,
      HP_TANK,NONE,VELOCITY_TANK,COOLDOWN_TANK,DAMAGE_TANK,TANK,ENNEMY_CLAN,1,HITBOX_TANK); break;
    case BOSS: add_entity_to_list(entity,NONE,NONE,
      HP_BOSS,NONE,VELOCITY_BOSS,COOLDOWN_BOSS,DAMAGE_BOSS,BOSS,ENNEMY_CLAN,1,HITBOX_BOSS); break;
    default: printf("ERROR RETURN ALERT, ERROR TYPE : %d\n",type); return ERROR_RETURN;
  }

  if (*entity == NULL){
    printf("ERROR VOID LIST NEXT SWITCH\n");
  }
  else {
    printf("VALID LIST NEXT SWITCH\n");
  }

  return VALID_RETURN;
}
