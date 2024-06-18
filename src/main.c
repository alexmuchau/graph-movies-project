#include "tools/libs.h"
#include "Movie/methods.h"
#include "Actor/methods.h"

int main() {
    FILE *actors_fileptr;
    FILE *movies_fileptr;
    char separator = '\t';
    int size = 100;
    
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
    
    // for (int i = 0; i < size; i++) {
    //     printf("%d -> %s -> ", actor_list[i]->id, actor_list[i]->name);
    //     printf("%ld - ", sizeof(actor_list[i]->movies_ids)/sizeof(int));
        // for (int j = 0; j < sizeof(actor_list[i]->movies_ids)/sizeof(int); j++) {
        //     printf("%d, ", actor_list[i]->movies_ids[j]);
        // }
    //     printf("\n");
    // }
    printf("%s -> %d", movies_tree->movie->title, movies_tree->movie->id);
    return 0;
}