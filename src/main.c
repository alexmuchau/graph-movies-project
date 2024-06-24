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
    int movie_size = -1;
    int actor_size = 200;
    
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
    
    Node * movies_tree = init_movie_tree(movies_fileptr, movie_size, separator);
    ActorList * actor_list = init_actor_list(actors_fileptr, actor_size, separator, movies_tree);
        
    connect_and_create_adjacencies(&actor_list, &movies_tree);
    
    FILE * dot_file = fopen("././input.dot", "w");
    draw_dot(movies_tree, dot_file);
    
    fclose(actors_fileptr);
    fclose(movies_fileptr);
    fclose(dot_file);
    return 0;
}