#include "../tools/libs.h"
#include "../tools/tools.h"
#include "../Movie/Movie.h"
#include "../Column/Column.h"
#include "../Column/methods.h"

int get_movies_cols(FILE ** fileptr, char separator, Column ** movie_col_to_search_list);

void * movie_case (char* data, int size, Column* col, Movie** movie);

void fuel_movie_list(FILE ** movie_file_ptr, char separator, Movie *** m_list, int size);

Movie ** init_movie_list(FILE * movie_file_ptr, int init_size, char separator);