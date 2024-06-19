#ifndef MOV_H
#define MOV_H

#include "../Adjacency/Adjacency.h"

struct Movie;
typedef struct Movie Movie;

struct Movie {
    int id;
    char * title;
    struct Adjacency * neighbors;
    
    // Nao escrito no .dot, entao = 0, se nao 1
    int is_drawn;
};

struct MovieNode;
typedef struct MovieNode MovieNode;

struct MovieNode {
    Movie * movie;
    MovieNode *next;
};

#endif
