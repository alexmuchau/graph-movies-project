//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#ifndef DOT_T_H
#define DOT_T_H

#include "dot_tool.h"

void _write_dot(char * from, char * to, FILE * dot_file) {
    // 10 por conta das: aspas, dos --, dos espacos e dos \n
    int length = strlen(from) + strlen(to) + 13;
    char * text = malloc(sizeof(char)*length);
    
    snprintf(text, length, "\n\"%s\" -- \"%s\"\n", from, to);
    printf("Writing edge -> %s\n", text);
    fwrite(text, 1, strlen(text)-1, dot_file);
    free(text);
}

void _draw_dot_adj(Adjacency * adj, FILE * dot_file) {
    if (!adj) return;
    
    if (adj->to->is_drawn == 0) {
        _write_dot(adj->from->title, adj->to->title, dot_file);
        adj->from->is_drawn = 1;
    }
    
    _draw_dot_adj(adj->next, dot_file);
}

void _draw_dot_node(Node *movie_tree, FILE * dot_file) {
    if (!movie_tree) return;
    if (movie_tree->movie->neighbors) _draw_dot_adj(movie_tree->movie->neighbors, dot_file);
    
    _draw_dot_node(movie_tree->left, dot_file);
    _draw_dot_node(movie_tree->right, dot_file);
}

void draw_dot(Node *movie_tree, FILE * dot_file) {
    int length = strlen("graph { concentrate=true\n");
    char header[] = "graph { concentrate=true\n";
    
    fwrite(header, 1, sizeof(header) - 1, dot_file);
    
    _draw_dot_node(movie_tree, dot_file);
    
    length = strlen("}");
    char footer[] = "}";
    
    fwrite(footer, 1, sizeof(footer) - 1, dot_file);
}

#endif