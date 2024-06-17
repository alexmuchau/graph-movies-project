#ifndef ACT_H
#define ACT_H

struct Actor;
typedef struct Actor Actor;

struct Actor {
    int id;
    char * name;
    MovieNode * movies;
    int * movies_ids;
    int size_movies_ids;
};

#endif