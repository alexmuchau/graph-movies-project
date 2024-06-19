//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#ifndef MOV_M_H
#define MOV_M_H

#include "methods.h"

void insert_movie_node(MovieNode * m_node, Movie * movie) {
    if (!m_node->next) {
        m_node->next = malloc(sizeof(MovieNode));
        m_node->next->movie = movie;
        m_node->next->next = NULL;
    }
    
    insert_movie_node(m_node->next, movie);
}

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

void * movie_case(char* data, int size, Column* col, Movie** movie) {
    if (col->index == 0) {
        (*movie)->id = clear_id(data, size);
    } else {
        (*movie)->title = data;
    }
}

void fuel_movie_tree(FILE ** movie_file_ptr, char separator, Node ** tree_head, int size) {
    Column * movie_cols = malloc(sizeof(Column));
    int cur_idx = get_movies_cols(movie_file_ptr, separator, &movie_cols);
    
    for (int i = 0; i < size; i++) {
        Movie * movie = malloc(sizeof(Movie));
        movie->id = __INT32_MAX__;
        movie->title = NULL;
        movie->neighbors = NULL;
        movie->is_drawn = 0;
        
        cur_idx = get_row(
            NULL, // Actor
            &(movie), // Movie
            movie_case, // Movie function,
            NULL, // Actor function
            movie_file_ptr,
            separator,
            movie_cols,
            cur_idx
        );
        
        if (movie->id != __INT32_MAX__) insert(tree_head, movie);
        // printf("\n\n");
    }
}

Node * init_movie_tree(FILE * movie_file_ptr, int init_size, char separator) {
    Node * tree_head = NULL;
    
    fuel_movie_tree(&movie_file_ptr, separator, &tree_head, init_size);
    
    return tree_head;
}

#endif