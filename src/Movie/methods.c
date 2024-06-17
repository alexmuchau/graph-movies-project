#ifndef MOV_M_H
#define MOV_M_H

#include "methods.h"

int get_movies_cols(FILE ** fileptr, char separator, Column ** movie_col_to_search_list) {
    (*movie_col_to_search_list)->name = malloc(sizeof(char)*6);
    strcpy((*movie_col_to_search_list)->name, "tconst");
    (*movie_col_to_search_list)->index = __INT32_MAX__;
    
    (*movie_col_to_search_list)->next = malloc(sizeof(Column));
    
    Column * movie_col_to_search = (*movie_col_to_search_list)->next;
    movie_col_to_search->name = malloc(sizeof(char)*11);
    strcpy(movie_col_to_search->name, "primaryTitle");
    movie_col_to_search->index = __INT32_MAX__;
    movie_col_to_search->next = NULL;
    
    int cur_idx = get_col(fileptr, separator, movie_col_to_search_list);
    return cur_idx;
}

void * movie_case (char* data, int size, Column* col, Movie** movie) {
    if (col->index == 0) {
        (*movie)->id = clear_id(data, size);
    } else {
        (*movie)->title = data;
    }
}

void fuel_movie_list(FILE ** movie_file_ptr, char separator, Movie *** m_list, int size) {
    Column * movie_cols = malloc(sizeof(Column));
    int cur_idx = get_movies_cols(movie_file_ptr, separator, &movie_cols);
    
    printf("%d\n\n", movie_cols->index);
    
    for (int i = 0; i < size; i++) {
        (*m_list)[i] = malloc(sizeof(Movie));
        (*m_list)[i]->id = __INT32_MAX__;
        (*m_list)[i]->title = NULL;
        (*m_list)[i]->neighbors = NULL;
        (*m_list)[i]->list_index = i;
        
        cur_idx = get_row(
            NULL, // Actor
            &((*m_list)[i]), // Movie
            movie_case, // Movie function,
            NULL, // Actor function
            movie_file_ptr,
            separator,
            movie_cols,
            cur_idx
        );
        // printf("\n\n");
    }
}

Movie ** init_movie_list(FILE * movie_file_ptr, int init_size, char separator) {
    Movie ** m_list = malloc(sizeof(Movie*)*init_size);
    
    fuel_movie_list(&movie_file_ptr, separator, &m_list, init_size);
    
    return m_list;
}

#endif