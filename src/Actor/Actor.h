//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#ifndef ACT_H
#define ACT_H

struct Actor;
typedef struct Actor Actor;

struct MovieNode;

struct Actor
{
    int id;
    char * name;
    struct MovieNode * movies;
    int * movies_ids;
};

struct ActorList;
typedef struct ActorList ActorList;

struct ActorList
{
    Actor ** a_list;
    int size;
};

#endif