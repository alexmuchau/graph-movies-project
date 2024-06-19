//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

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

void print_cols(Column * col) {
    if (col == NULL) {
        return;
    }
    
    printf("%d - %s\n", col->index, col->name);
    print_cols(col->next);
}

void write_dot(char * from, char * to, FILE * dot_file) {
    // 10 por conta das: aspas, dos --, dos espacos e dos \n
    int length = strlen(from) + strlen(to) + 13;
    char * text = malloc(sizeof(char)*length);
    
    snprintf(text, length, "\n\"%s\" -- \"%s\"\n", from, to);
    
    fwrite(text, 1, strlen(text)-1, dot_file);
    free(text);
}

void draw_dot_adj(Adjacency * adj, FILE * dot_file) {
    if (!adj) return;
    
    if (adj->to->is_drawn == 0) {
        write_dot(adj->from->title, adj->to->title, dot_file);
        adj->from->is_drawn = 1;
    }
    
    draw_dot_adj(adj->next, dot_file);
}

void draw_dot_node(Node *movie_tree, FILE * dot_file) {
    if (!movie_tree) return;
    if (movie_tree->movie->neighbors) draw_dot_adj(movie_tree->movie->neighbors, dot_file);
    
    draw_dot_node(movie_tree->left, dot_file);
    draw_dot_node(movie_tree->right, dot_file);
}

void draw_dot(Node *movie_tree, FILE * dot_file) {
    int length = strlen("graph { concentrate=true\n");
    char header[] = "graph { concentrate=true\n";
    
    fwrite(header, 1, sizeof(header) - 1, dot_file);
    
    draw_dot_node(movie_tree, dot_file);
    
    length = strlen("}");
    char footer[] = "}";
    
    fwrite(footer, 1, sizeof(footer) - 1, dot_file);
}

#endif