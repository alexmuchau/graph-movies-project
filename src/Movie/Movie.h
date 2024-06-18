#ifndef MOV_H
#define MOV_H

#include "../Adjacency/Adjacency.h"

struct Movie;
typedef struct Movie Movie;

struct Movie {
    int id;
    char * title;
    struct Adjacency * neighbors;
    int list_index;
};

struct MovieNode;
typedef struct MovieNode MovieNode;

struct MovieNode {
    Movie * movie;
    MovieNode *next;
};

#endif
