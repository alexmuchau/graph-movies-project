//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#ifndef ADJ_H
#define ADJ_H

#include "../Movie/Movie.h"

struct Adjacency;
typedef struct Adjacency Adjacency;

struct Adjacency {
    struct Movie * from;
    struct Movie * to;
    Adjacency * next;
    // Actor ** by; // to-do
};

#endif