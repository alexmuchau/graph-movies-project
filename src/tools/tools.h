#include "libs.h"
#include "../Column/Column.h"
#include "../Movie/Movie.h"
#include "../Actor/Actor.h"

int clear_id(char * data, int size);

int get_row(
    Actor ** actor,
    Movie ** movie,
    void * (*movie_case)(char* data, int size, Column* col, Movie** movie),
    void * (*actor_case)(char* data, int size, Column* col, Actor** actor),
    FILE ** fileptr,
    char separator,
    Column * col,
    int cur_idx
);

void print_cols(Column * col);