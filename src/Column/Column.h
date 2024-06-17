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