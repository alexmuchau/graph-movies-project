#include "tools/libs.h"
#include "Movie/methods.h"
#include "Actor/methods.h"
#include "Adjacency/methods.h"

void print_actor_movies(MovieNode * m_node) {
    if (!m_node->next){
        printf("%s\n", m_node->movie->title);
        return;
    }
    
    printf("%s, ", m_node->movie->title);
    
    print_actor_movies(m_node->next);
    return;
}

void print_movies_ids(Actor * actor) {
    for (int i = 0; i < actor->size_movies_ids; i++) {
        printf("%d, ", actor->movies_ids[i]);
    }
}

void print_max_right(Node* node) {
    if (!node->right) {
    //     // printf("%d - %d, %s", node->level, node->movie->id, node->movie->title);
        printf("%d - %d, %s\n", node->level, node->movie->id, node->movie->title);
        return;
    }
    
    print_max_right(node->right);
}

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
    printf("\n\n");
    Actor ** actor_list = init_actor_list(actors_fileptr, size, separator);
    
    // ride_in_tree(movies_tree);
    
    // printf("right -> %d", movies_tree->right->right->level);
    print_max_right(movies_tree);
    // printf("%d---\n", movies_tree->level);
    // Movie * m = search_movie(movies_tree, 9999);
    // if (m) {
    //     printf("%d, %s\n", m->id, m->title);
    // } else {
    //     printf("Dont found\n");
    // }
        
    // connect_and_create_adjacencies(&actor_list, size, &movies_tree);
    
    // for (int i = 0; i < size; i++) {
    //     printf("%d -> %s -> ", actor_list[i]->id, actor_list[i]->name);
    //     printf("%ld - ", sizeof(actor_list[i]->movies_ids)/sizeof(int));
        // for (int j = 0; j < sizeof(actor_list[i]->movies_ids)/sizeof(int); j++) {
        //     printf("%d, ", actor_list[i]->movies_ids[j]);
        // }
    //     printf("\n");
    // }
    // int i = 0;
    // while (1==1) {
    //     while (i < size - 1 && !actor_list[i]->movies) {
    //         i++;
    //     }
    //     if (actor_list[i]->movies) {
    //         if (actor_list[i]->movies->movie->neighbors) {
    //             printf("%d, Actor -> %s\n", i, actor_list[i+1]->name);
    //             printf("Actor Movies -> ");
    //             print_actor_movies(actor_list[i+1]->movies);
    //             print_movies_ids(actor_list[i+1]);
    //             printf("\n");
    //             // printf(
    //             //     "%d, %s -> %s -> %s\n",
    //             //     i,
    //             //     actor_list[i]->name,
    //             //     actor_list[i]->movies->movie->neighbors->from->title,
    //             //     actor_list[i]->movies->movie->neighbors->to->title
    //             // );
                
    //             break;
    //         }
    //     }
    //     else {
    //         break;
    //     }
    // }
    return 0;
}