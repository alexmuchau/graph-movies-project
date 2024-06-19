//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#ifndef COL_H
#define COL_H

struct Column;
typedef struct Column Column;

struct Column {
    int index;
    char * name;
    Column * next;
};

#endif