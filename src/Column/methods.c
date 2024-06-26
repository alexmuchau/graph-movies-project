//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

///////////// CORE

#ifndef COL_M_H
#define COL_M_H

#include "methods.h"


///////////// GET COLUMN IN A ROW

int get_col(FILE ** fileptr, char separator, Column ** col_to_search)
{
    int i = 0, j = 0, index = 0;
    char sep_line = '\n';

    char c;
    while (c != sep_line)
    {
        while (c == separator)
        {
            c = fgetc((*fileptr));
        }
        while (c != separator && c != sep_line)
        {
            c = fgetc((*fileptr));
            j++;
        }
        char * text = malloc(sizeof(char)*(j));
        fseek((*fileptr), i, SEEK_SET);
        fgets(text, j, (*fileptr));
        
        if (strcmp(text, (*col_to_search)->name) == 0)
        {
            (*col_to_search)->index = index;
            
            if (!(*col_to_search)->next)
            {
                break;
            }
            
            col_to_search = &((*col_to_search)->next);
        }
        
        i += j;
        j = 1;
        
        index += 1;
    }
    
    while (c != sep_line)
    {
        c = fgetc((*fileptr));
    }
    
    // c = fgetc((*fileptr));
    // search_index += 1;
    return ftell(*fileptr) + 1;
}

#endif