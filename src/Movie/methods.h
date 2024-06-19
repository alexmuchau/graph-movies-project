//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#include "../tools/libs.h"
#include "../tools/tools.h"
#include "../Movie/Movie.h"
#include "../Column/Column.h"
#include "../Column/methods.h"
#include "MovieTree.h"

int get_movies_cols(FILE ** fileptr, char separator, Column ** movie_col_to_search_list);

void * movie_case (char* data, int size, Column* col, Movie** movie);

void fuel_movie_tree(FILE ** movie_file_ptr, char separator, Node ** tree_head, int size);

Node * init_movie_tree(FILE * movie_file_ptr, int init_size, char separator);