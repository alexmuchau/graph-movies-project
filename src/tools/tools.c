//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

///////////// CORE

#ifndef TOOLS_H
#define TOOLS_H

#include "tools.h"


///////////// GET FILE INFO

int clear_id(char * data, int size) {
    return atoi(data + 2);
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
    if (feof((*fileptr))) {
        return -1;
    }
    
    if (actor && movie) {
        printf("Must get_row only for actor, or only for movie\n");
        return -1;
    }
    
    char sep_line = '\n';
    char c;
    int i = 0, j = 0, index = 0;
    fseek((*fileptr), cur_idx, SEEK_SET);
    
    while (c != sep_line && c != EOF) {
        while (c == separator) {
            c = fgetc((*fileptr));
        }
        
        while (c != separator && c != sep_line && c != EOF) {
            c = fgetc((*fileptr));
            j++;
        }
        
        if (index == col->index) {
            char * data = malloc(sizeof(char)*j);
            fseek((*fileptr), cur_idx + i, SEEK_SET);
            fgets(data, j, (*fileptr));
            // printf("found %s -> %s.\n", col->name, data);
            
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


///////////// DEBUG

void print_row_index(int index, char * title)
{
    if (index == 1000000)
    {
        printf("%s -> Passed first million rows", title);
        printf("\n------\n");
    } 
    else if (index == 3000000)
    {
        printf("%s -> Passed 3 million rows", title);
        printf("\n------\n");
    }
    else if (index == 5000000)
    {
        printf("%s -> Passed 5 million rows", title);
        printf("\n------\n");
    }
    else if (index == 10000000)
    {
        printf("%s -> Passed 10 million rows", title);
        printf("\n------\n");
    }
    else if (index == 12000000)
    {
        printf("%s -> Passed 12 million rows", title);
        printf("\n------\n");
    }    
}

void print_cols(Column * col) {
    if (col == NULL) {
        return;
    }
    
    printf("%d - %s\n", col->index, col->name);
    print_cols(col->next);
}

void print_actor_movies(MovieNode * m_node) {
    if (!m_node->next){
        printf("%s\n", m_node->movie->title);
        return;
    }
    
    printf("%s, ", m_node->movie->title);
    
    print_actor_movies(m_node->next);
    return;
}

void print_movies_ids(Actor * actor) {
    for (int i = 0; i < actor->size_movies_ids; i++) {
        printf("%d, ", actor->movies_ids[i]);
    }
}

void print_max_right(Node* node) {
    if (!node->right) {
    //     // printf("%d - %d, %s", node->level, node->movie->id, node->movie->title);
        printf("%d - %d, %s\n", node->level, node->movie->id, node->movie->title);
        return;
    }
    
    print_max_right(node->right);
}


#endif