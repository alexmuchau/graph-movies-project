//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

///////////// CORE

#ifndef ACT_M_H
#define ACT_M_H

#include "methods.h"


///////////// GET ACTOR COLS

int get_actor_cols(FILE ** fileptr, char separator, Column ** actors_cols_to_search)
{
    (*actors_cols_to_search)->name = malloc(sizeof(char)*6);
    strcpy((*actors_cols_to_search)->name, "nconst");
    (*actors_cols_to_search)->index = __INT32_MAX__;
    
    (*actors_cols_to_search)->next = malloc(sizeof(Column));
    
    Column * actor_col = (*actors_cols_to_search)->next;
    actor_col->name = malloc(sizeof(char)*11);
    strcpy(actor_col->name, "primaryName");
    actor_col->index = __INT32_MAX__;
    actor_col->next = malloc(sizeof(Column));
    
    actor_col = actor_col->next;
    actor_col->name = malloc(sizeof(char)*14);
    strcpy(actor_col->name, "knownForTitles");
    actor_col->index = __INT32_MAX__;
    actor_col->next = NULL;
    
    int cur_idx = get_col(fileptr, separator, actors_cols_to_search);
    return cur_idx;
}


///////////// GET ACTOR FILE INFO

void split_movies_ids(char * data, int size, char separator, Actor** actor, Node * movie_tree)
{
    // In cases that knownForTitles == \N
    if (strcmp(data, "\N") == 0) return;
    
    int start_idx = 0, i = 0, id_size, list_size = 5, size_movies_ids = 0;
    int * movies_ids = malloc(sizeof(int)*5);
    while (i < size) {
        while (data[i] != separator && i < size) {
            i++;
        }
        id_size = (i - start_idx);
        
        if (size_movies_ids > list_size) {
            list_size += 5;
            movies_ids = realloc(movies_ids, sizeof(int)*list_size);
        }
        
        char * id = malloc(sizeof(char)*id_size);
        strncpy(id, data + start_idx, id_size);
        
        movies_ids[size_movies_ids] = clear_id(id, id_size);
        
        size_movies_ids += 1;
        i += 1;
        start_idx = i;
        
        free(id);
    }
    
    if (size_movies_ids != list_size) {
        movies_ids = realloc(movies_ids, sizeof(int)*size_movies_ids);
    }
    
    (*actor)->movies = connect_movie_id(movies_ids, size_movies_ids, movie_tree);
    free(movies_ids);
}

void * actor_case(char* data, int size, Column* col, Actor** actor, Node * movie_tree)
{
    if (col->index == 0) {
        // printf("index -> %s\n", data);
        (*actor)->id = clear_id(data, size);
    } else if (strcmp(col->name, "primaryName") == 0) {
        // printf("name -> %s\n", data);
        (*actor)->name = data;
    } else if (strcmp(col->name, "knownForTitles") == 0) {
        // printf("movies_ids -> %s\n", data);
        if (strlen(data) < 5) {
            (*actor)->movies_ids = NULL;
        } else {
            split_movies_ids(data, size, ',', actor, movie_tree);
        }
        // for (int j = 0; j < (*actor)->size_movies_ids; j++) {
        //     printf("%d, ", (*actor)->movies_ids[j]);
        // }
        // printf("\n\n");
        
    } else {
        printf("Erro na comparacao -> %s -> %s\n", col->name,data);
    }
}

void fuel_actor_list(FILE ** actor_fileptr, char separator, ActorList ** a_list, int size, int list_size, Node * movie_tree)
{
    Column * actor_cols = malloc(sizeof(Column));
    int cur_idx = get_actor_cols(actor_fileptr, separator, &actor_cols);
    
    int i = 0;
    
    while (i < size) {        
        if (i > list_size)
        {
            list_size += 3000000;
            (*a_list)->a_list = realloc((*a_list)->a_list, sizeof(Actor) * list_size);
            (*a_list)->size = list_size;
        }
        (*a_list)->a_list[i] = malloc(sizeof(Actor));
        (*a_list)->a_list[i]->id = __INT32_MAX__;
        (*a_list)->a_list[i]->name = NULL;
        (*a_list)->a_list[i]->movies = NULL;
        
        cur_idx = get_row(
            &((*a_list)->a_list[i]), // Actor
            NULL, // Movie
            NULL, // Movie function,
            &actor_case, // Actor function
            actor_fileptr,
            separator,
            actor_cols,
            cur_idx,
            movie_tree
        );
        
        
        if (cur_idx == -1)
        {
            free((*a_list)->a_list[i]);
            break;
        }
        
        print_row_index(i, "Actors");

        i++;
    }
    
    if (i != list_size) {
        (*a_list)->a_list = realloc((*a_list)->a_list, sizeof(Actor)*i);
        (*a_list)->size = i;
        printf("Reallocating actor list -> list_size:%d -> i:%d\n", list_size, (*a_list)->size);
    }
    
    printf("----------> Read %d, FINISHED ACTOR ROWS\n\n", (*a_list)->size);
}

ActorList * init_actor_list(FILE * actor_fileptr, int init_size, char separator, Node * movie_tree)
{
    printf("----------> INIT ACTOR LIST\n");
    int list_size;

    if (init_size == -1)
    {
        init_size = __INT32_MAX__;
        list_size = 3000000;
    }
    else
    {
        list_size = init_size;
    }
    
    ActorList * actor_list = malloc(sizeof(ActorList));
    actor_list->a_list = malloc(sizeof(Actor*)*list_size);
    actor_list->size = list_size;
    
    fuel_actor_list(&actor_fileptr, separator, &actor_list, init_size, list_size, movie_tree);
    
    return actor_list;
}

#endif