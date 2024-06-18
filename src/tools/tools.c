#ifndef TOOLS_H
#define TOOLS_H

#include "tools.h"

int clear_id(char * data, int size) {
    char *id = malloc(sizeof(char)*(size - 2));
    strcpy(id, data + 2);
    
    return atoi(id);
}

int get_row(
    Actor ** actor,
    Movie ** movie,
    void * (*movie_case)(char* data, int size, Column* col, Movie** movie),
    void * (*actor_case)(char* data, int size, Column* col, Actor** actor),
    FILE ** fileptr,
    char separator,
    Column * col,
    int cur_idx
)
{
    if (actor && movie) {
        printf("Must get_row only for actor, or only for movie\n");
        return -1;
    }
    
    char sep_line = '\n';
    char c;
    int i = 0, j = 0, index = 0;
    fseek((*fileptr), cur_idx, SEEK_SET);
    
    while (c != sep_line) {
        while (c == separator) {
            c = fgetc((*fileptr));
        }
        
        while (c != separator && c != sep_line) {
            c = fgetc((*fileptr));
            j++;
        }
        
        if (index == col->index) {
            char * data = malloc(sizeof(char)*j);
            fseek((*fileptr), cur_idx + i, SEEK_SET);
            fgets(data, j, (*fileptr));
            printf("found %s -> %s.\n", col->name, data);
            
            if (movie) {
                movie_case(data, j + 1, col, movie);
            } else {
                actor_case(data, j + 1, col, actor);
            }
            
            if (!col->next) {
                break;
            }
            
            col = col->next;
        }
        
        i += j;
        j = 1;
        
        index += 1;
    }
    
    while (c != sep_line) {
        c = fgetc((*fileptr));
    }
    
    while (c == sep_line) {
        c = fgetc((*fileptr));
    }
    
    // c = fgetc((*fileptr));
    // search_index += 1;
    // printf("\n");
    
    return ftell((*fileptr));
}

void print_cols(Column * col) {
    if (col == NULL) {
        return;
    }
    
    printf("%d - %s\n", col->index, col->name);
    print_cols(col->next);
}

#endif