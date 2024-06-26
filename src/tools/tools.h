//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#include "libs.h"
#include "../Column/Column.h"
#include "../Movie/Movie.h"
#include "../Movie/MovieTree.h"
#include "../Actor/Actor.h"

int clear_id(char * data, int size);

int get_row(
    Actor ** actor,
    Movie ** movie,
    void * (*movie_case)(char* data, int size, Column* col, Movie** movie),
    void * (*actor_case)(char* data, int size, Column* col, Actor** actor, Node * movie_tree),
    FILE ** fileptr,
    char separator,
    Column * col,
    int cur_idx,
    Node * movie_tree
);

void print_row_index(int index, char * title);
void print_cols(Column * col);
void print_actor_movies(MovieNode * m_node);
void print_max_right(Node* node);