#ifndef __PARSEUR__
#define __PARSEUR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Entity.h"
#include "Balancing.h"
#include "Error.h"


/**
 * Manage the parsing actions
 * @param test A entities test lisr
 * @param level The level to parse (txt file)
 * @return if the parsing action gone well
*/
int manage_parse(Entities * test, char * level);


/**
 * Count the number of integer on a line (on the buffer)
 * @param string the buffer
 * @param i the position
 * @return the count
*/
int compte_integer(char string[], int i);


/**
 * Parse a file
 * @param file_to_parse The file to parse
 * @param test the list of entity
 * @return 1 if the parsing gone well
*/
int file_parsing(FILE * file_to_parse, Entities * test);


/**
 * Apply all type to list
 * @param entity the entity list to modify
 * @param type The type to add
 * @return 1 if every setter gone well, 0 else
*/
int set_values_type(Entities * entity, int type);

#endif
