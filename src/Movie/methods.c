//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

///////////// CORE

#ifndef MOV_M_H
#define MOV_M_H

#include "methods.h"


///////////// MOVIE NODE

void insert_movie_node(MovieNode * m_node, Movie * movie)
{
    if (!m_node->next)
    {
        m_node->next = malloc(sizeof(MovieNode));
        m_node->next->movie = movie;
        m_node->next->next = NULL;
    }
    
    insert_movie_node(m_node->next, movie);
}


///////////// GET MOVIE COLS

int get_movies_cols(FILE ** fileptr, char separator, Column ** movie_col_to_search_list)
{
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


///////////// GET MOVIE FILE INFO

void * movie_case(char* data, int size, Column* col, Movie** movie)
{
    if (col->index == 0)
    {
        (*movie)->id = clear_id(data, size);
    }
    else
    {
        (*movie)->title = data;
    }
}

void fuel_movie_tree(FILE ** movie_file_ptr, char separator, Node ** tree_head, int size)
{
    Column * movie_cols = malloc(sizeof(Column));
    int cur_idx = get_movies_cols(movie_file_ptr, separator, &movie_cols);
    int i = 0;
    
    while (i < size)
    {
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
        
        if (cur_idx == -1)
        {
            free(movie);
            break;
        }
        
        print_row_index(i, "Movies");

        insert(tree_head, movie);

        i++;
    }
    
    printf("----------> Read %d, FINISHED MOVIES ROWS\n\n", i);
}

Node * init_movie_tree(FILE * movie_file_ptr, int init_size, char separator)
{
    Node * tree_head = NULL;
    
    if (init_size < 0) init_size = __INT32_MAX__;
    
    fuel_movie_tree(&movie_file_ptr, separator, &tree_head, init_size);
    
    return tree_head;
}

#endif