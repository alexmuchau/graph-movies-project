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

MovieNode * connect_movie_id(Node * movie_tree, int * movie_ids, int size, int to_print) {
    MovieNode * m_node;
    for (int m_idx = 0; m_idx < size; m_idx++) {
        Movie * movie = search_movie(movie_tree, movie_ids[m_idx]);
        
        if (to_print == 0) {
            printf("Trying to find %d\n", movie_ids[m_idx]);    
        }
        
        if (movie) {
            if (to_print == 0) {
                printf("Found movie '%s' with id:%d\n", movie->title, movie->id);
            }
            m_node = malloc(sizeof(MovieNode));
            m_node->movie = movie;
            if (m_idx + 1 < size) {
                m_node->next = connect_movie_id(movie_tree, movie_ids + m_idx + 1, size - (m_idx + 1), to_print);
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
    int m_idx;
    int i;
    MovieNode ** movie_node;
    for (i =0; i < size; i++) {
        int to_print = strcmp((*a_list)[i]->name, "Robert Ellis");
        if (to_print == 0) {
            printf("--------------------%d- %s\n", (*a_list)[i]->id, (*a_list)[i]->name);
        }
        // Connecting movies_ids with movie_tree
        (*a_list)[i]->movies = connect_movie_id(
            (*movie_tree),
            (*a_list)[i]->movies_ids,
            (*a_list)[i]->size_movies_ids,
            to_print
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