//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

///////////// CORE

#ifndef ADJ_M_H
#define ADJ_M_H

#include "methods.h"


///////////// ADD ADJACENCY

Adjacency* adj_insert(Adjacency** adj, Movie * from, Movie * to)
{
    if (!(*adj))
    {
        (*adj) = malloc(sizeof(Adjacency));
        (*adj)->from = from;
        (*adj)->to = to;
        (*adj)->next = NULL;
        
        return (*adj);
    }
    
    (*adj)->next = adj_insert(&(*adj)->next, from, to);
    return (*adj);
}


///////////// CREATE ADJACENCIES

MovieNode * _connect_movie_id(int * movie_ids, int size, int m_idx, Node * movie_tree) {
    while (m_idx < size)
    {
        Movie * movie = search_movie(movie_tree, movie_ids[m_idx]);
        if (movie)
        {
            MovieNode * node = malloc(sizeof(MovieNode));
            node->movie = movie;
            node->next = _connect_movie_id(movie_ids, size, m_idx + 1, movie_tree);
            
            return node;
        }
        m_idx += 1;
    }
    
    return NULL;
}

MovieNode * connect_movie_id(int * movie_ids, int size, Node * movie_tree)
{
    if (!movie_ids) return NULL;
    
    MovieNode * head_node = _connect_movie_id(movie_ids, size, 0, movie_tree);
    return head_node;
}

void connect_and_create_adjacencies(ActorList ** a_list, Node ** movie_tree)
{
    printf("----------> CREATING ADJACENCIES\n");
    int m_idx, i;
    MovieNode * movie_node;
    MovieNode * next_node;
    for (i = 0; i < (*a_list)->size; i++)
    {   
        if (!(*a_list)->a_list[i]->movies) continue;
        movie_node = (*a_list)->a_list[i]->movies;
        
        // printf("Actor %s| Movie node -> %s\n",(*a_list)->a_list[i]->name,  movie_node->movie->title);

        // Adding adjacencies
        while (movie_node)
        {
            next_node = movie_node->next;
            while(next_node)
            {
                movie_node->movie->neighbors = adj_insert(&movie_node->movie->neighbors, movie_node->movie, next_node->movie);
                
                // Para grafos dirigidos, comentar essa linha
                next_node->movie->neighbors = adj_insert(&next_node->movie->neighbors, next_node->movie, movie_node->movie);
                
                next_node = next_node->next;
            }
            movie_node = movie_node->next;
        }
        
        print_row_index(i, "ADJACENCIES | ACTORS");
    }
    
    printf("\n-----> CONNECTED AND CREATED ADJACENCIES\n");
}

#endif