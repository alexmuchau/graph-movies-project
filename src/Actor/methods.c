#ifndef ACT_M_H
#define ACT_M_H

#include "methods.h"

int * split_movies_ids(char * data, int size, char separator) {
    int start_idx = 0, i = 0, qty = 0, id_size, list_size = 5;
    int * result = malloc(sizeof(int)*5);
    // printf("%s\n", data);
    while (i < size) {
        while (data[i] != separator && i < size) {
            i++;
        }
        id_size = (i - start_idx);
        
        if (qty > list_size) {
            list_size += 5;
            result = realloc(result, sizeof(int)*list_size);
        }
        
        char * id = malloc(sizeof(char)*id_size);
        strncpy(id, data + start_idx, id_size);
        result[qty] = clear_id(id, id_size);
        // printf("%s -> %d,", id, result[qty]);
        
        qty += 1;
        i += 1;
        start_idx = i;
    }
    // printf("\n");
    
    if (qty != list_size) {
        result = realloc(result, sizeof(int)*qty);
    }
    
    return result;
}


void * actor_case (char* data, int size, Column* col, Actor** actor) {
    if (col->index == 0) {
        // printf("index -> %s\n", data);
        (*actor)->id = clear_id(data, size);
    } else if (strcmp(col->name, "primaryName") == 0) {
        // printf("name -> %s\n", data);
        (*actor)->name = data;
    } else if (strcmp(col->name, "knownForTitles") == 0) {
        // printf("movies_ids -> %s\n", data);
        (*actor)->movies_ids = split_movies_ids(data, size, ',');
    } else {
        printf("Erro na comparacao -> %s -> %s\n", col->name,data);
    }
}

int get_actor_cols(FILE ** fileptr, char separator, Column ** actors_cols_to_search) {
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

void fuel_actor_list(FILE ** actor_fileptr, char separator, Actor *** a_list, int size) {
    Column * actor_cols = malloc(sizeof(Column));
    int cur_idx = get_actor_cols(actor_fileptr, separator, &actor_cols);
    
    print_cols(actor_cols);
    
    for (int i = 0; i < size; i++) {
        (*a_list)[i] = malloc(sizeof(Actor));
        (*a_list)[i]->id = __INT32_MAX__;
        (*a_list)[i]->movies = NULL;
        (*a_list)[i]->movies_ids = NULL;
        (*a_list)[i]->name = NULL;
        
        cur_idx = get_row(
            &((*a_list)[i]), // Actor
            NULL, // Movie
            NULL, // Movie function,
            &actor_case, // Actor function
            actor_fileptr,
            separator,
            actor_cols,
            cur_idx
        );
        // break;
        // printf("\n\n");
    }
}

Actor ** init_actor_list(FILE * actor_fileptr, int init_size, char separator) {
    Actor ** a_list = malloc(sizeof(Actor*)*init_size);
    
    fuel_actor_list(&actor_fileptr, separator, &a_list, init_size);
    
    return a_list;
}

#endif