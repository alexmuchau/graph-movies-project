#include "tools/libs.h"
#include "Movie/methods.h"
#include "Actor/methods.h"
#include "Adjacency/methods.h"

int main() {
    FILE *actors_fileptr;
    FILE *movies_fileptr;
    char separator = '\t';
    int size = 100000;
    
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
    
    // for (int i = 0; i < size; i++) {
    //     printf("%d -> %s -> ", actor_list[i]->id, actor_list[i]->name);
    //     printf("%ld - ", sizeof(actor_list[i]->movies_ids)/sizeof(int));
        // for (int j = 0; j < sizeof(actor_list[i]->movies_ids)/sizeof(int); j++) {
        //     printf("%d, ", actor_list[i]->movies_ids[j]);
        // }
    //     printf("\n");
    // }
    int i = 0;
    while (1==1) {
        while (i < size - 1 && !actor_list[i]->movies->movie) {
            i++;
        }
        if (actor_list[i]->movies->movie) {
            if (actor_list[i]->movies->movie->neighbors) {
                printf(
                    "%d, %s -> %s -> %s\n",
                    i,
                    actor_list[i]->name,
                    actor_list[i]->movies->movie->neighbors->from->title,
                    actor_list[i]->movies->movie->neighbors->to->title
                );
                
                break;
            }
        }
        else {
            break;
        }
    }
    return 0;
}