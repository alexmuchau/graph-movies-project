#include "../tools/libs.h"
#include "../tools/tools.h"
#include "../Column/Column.h"
#include "../Column/methods.h"
#include "Actor.h"

void split_movies_ids(char * data, int size, char separator, Actor** actor);

void * actor_case (char* data, int size, Column* col, Actor** actor);

int get_actor_cols(FILE ** fileptr, char separator, Column ** actors_cols_to_search);

void fuel_actor_list(FILE ** actor_fileptr, char separator, Actor *** a_list, int size);

Actor ** init_actor_list(FILE * actor_fileptr, int init_size, char separator);