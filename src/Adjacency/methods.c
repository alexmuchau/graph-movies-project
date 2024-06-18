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

MovieNode * connect_movie_id(Node * movie_tree, int * movie_ids, int size) {
    if (!movie_ids) return NULL;
    
    MovieNode * m_node;
    for (int m_idx = 0; m_idx < size; m_idx++) {
        Movie * movie = search_movie(movie_tree, movie_ids[m_idx]);
        
        if (movie) {
            m_node = malloc(sizeof(MovieNode));
            m_node->movie = movie;
            if (m_idx + 1 < size) {
                m_node->next = connect_movie_id(movie_tree, movie_ids + m_idx + 1, size - (m_idx + 1));
            } else {
                m_node->next = NULL;
            }
            return m_node;
        }
    }
    
    return NULL;
}

void connect_and_create_adjacencies(Actor *** a_list, int size, Node ** movie_tree)
{
    int m_idx, i;
    MovieNode ** movie_node;
    for (i =0; i < size; i++) {
        // In cases that knownForTitles == \N
        if (!(*a_list)[i]->movies_ids) continue;
        
        // Connecting movies_ids with movie_tree
        (*a_list)[i]->movies = connect_movie_id(
            (*movie_tree),
            (*a_list)[i]->movies_ids,
            (*a_list)[i]->size_movies_ids
        );
        
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