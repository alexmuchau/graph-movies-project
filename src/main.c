//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#include "tools/libs.h"
#include "Movie/methods.h"
#include "Actor/methods.h"
#include "Adjacency/methods.h"
#include "tools/dot_tool.h"

int main() {
    FILE *actors_fileptr;
    FILE *movies_fileptr;
    char separator = '\t';
    int size = 10000;
    
    actors_fileptr = fopen("././data/name.basics.tsv", "r");
    movies_fileptr = fopen("././data/title.basics.tsv", "r");
    
    if (actors_fileptr == NULL) {
        printf("Actors file not found\n");
        return -1;
    }
    
    if (movies_fileptr == NULL) {
        printf("Movies file not found\n");
        return -1;
    }
    
    Node * movies_tree = init_movie_tree(movies_fileptr, size, separator);
    Actor ** actor_list = init_actor_list(actors_fileptr, size, separator);
        
    connect_and_create_adjacencies(&actor_list, size, &movies_tree);
    
    FILE * dot_file = fopen("././input.dot", "w");
    draw_dot(movies_tree, dot_file);
    
    return 0;
}