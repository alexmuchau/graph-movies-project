#ifndef ADJ_M_H
#define ADJ_M_H

#include "methods.h"


Adjacency* adj_insert(Adjacency** adj, Movie * from, Movie * to) {
    if (!(*adj)) {
        (*adj) = malloc(sizeof(Adjacency));
        (*adj)->from = from;
        (*adj)->to = to;
        (*adj)->next = NULL;
        
        return (*adj);
    }
    
    (*adj)->next = adj_insert(&(*adj)->next, from, to);
    return (*adj);
}

void connect_and_create_adjacencies(Actor *** a_list, int size, Node ** movie_tree)
{
    int m_idx;
    int i;
    MovieNode ** movie_node;
    for (i =0; i < size; i++) {
        // Connecting movies_ids with movie_tree
        movie_node = &(*a_list)[i]->movies;
        for (m_idx = 0; m_idx < (*a_list)[i]->size_movies_ids; m_idx++) {
            (*movie_node) = malloc(sizeof(MovieNode));
            (*movie_node)->movie = search_movie((*movie_tree), (*a_list)[i]->movies_ids[m_idx]);
            (*movie_node)->next = NULL;

            if ((*movie_node)->movie) movie_node = &(*movie_node)->next;
        }
        
        // Adding adjacencies
        movie_node = &(*a_list)[i]->movies;
        MovieNode ** next_node;
        while ((*movie_node) && (*movie_node)->movie) {
            next_node = &(*movie_node)->next;
            while((*next_node) && (*next_node)->movie) {
                (*movie_node)->movie->neighbors = adj_insert(&(*movie_node)->movie->neighbors, (*movie_node)->movie, (*next_node)->movie);
                
                // Para grafos dirigidos, comentar essa linha
                (*next_node)->movie->neighbors = adj_insert(&(*next_node)->movie->neighbors, (*next_node)->movie, (*movie_node)->movie);
                
                next_node = &(*next_node)->next;
            }
            movie_node = &(*movie_node)->next;
        }
    }
}

#endif