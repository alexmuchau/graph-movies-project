#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Column;
typedef struct Column Column;

struct Adjacency;
typedef struct Adjacency Adjacency;

struct Movie;
typedef struct Movie Movie;

struct Actor;
typedef struct Actor Actor;

struct MovieNode;
typedef struct MovieNode MovieNode;

struct Column {
    int index;
    char * name;
    Column * next;
};

struct MovieNode {
    Movie * Movie;
    MovieNode *next;
};

struct Actor {
    int id;
    char * name;
    MovieNode * movies;  
};

struct Movie {
    int id;
    char * title;
    Adjacency * neighbors;
    int list_index;
};

struct Adjacency {
    Movie * from;
    Movie * to;
    Adjacency * next;
    // Actor ** by; // to-do
};



int get_col(FILE ** fileptr, char separator, Column ** col_to_search) {
    int i = 0;
    int j = 1;
    int index = 0;
    int search_index = 0;
    char sep_line = '\n';

    fseek((*fileptr), i, SEEK_SET);
    char c = fgetc((*fileptr));
    while (c != sep_line) {
        while (c == separator) {
            c = fgetc((*fileptr));
            search_index += 1;
        }
        while (c != separator && c != sep_line) {
            c = fgetc((*fileptr));
            j++;
            search_index += 1;
        }
        char * text = malloc(sizeof(char)*(j));
        fseek((*fileptr), i, SEEK_SET);
        fgets(text, j, (*fileptr));
        
        if (strcmp(text, (*col_to_search)->name) == 0) {
            (*col_to_search)->index = index;
            
            if (!(*col_to_search)->next) {
                break;
            }
            
            col_to_search = &((*col_to_search)->next);
        }
        
        i += j;
        j = 1;
        
        index += 1;
    }
    
    while (c != sep_line) {
        c = fgetc((*fileptr));
        search_index += 1;
    }
    
    return search_index;
}

int get_movies_cols(FILE ** fileptr, char separator, Column ** movie_col_to_search_list) {
    (*movie_col_to_search_list)->name = malloc(sizeof(char)*6);
    strcpy((*movie_col_to_search_list)->name, "tconst");
    (*movie_col_to_search_list)->index = __INT32_MAX__;
    
    (*movie_col_to_search_list)->next = malloc(sizeof(Column));
    
    Column * movie_col_to_search = (*movie_col_to_search_list)->next;
    movie_col_to_search->name = malloc(sizeof(char)*11);
    strcpy(movie_col_to_search->name, "primaryTitle");
    movie_col_to_search->index = __INT32_MAX__;
    movie_col_to_search->next = NULL;
    
    int cur_idx = get_col(fileptr, separator, movie_col_to_search_list);
    return cur_idx;
}

int clear_id(char * data, int size) {
    char *id = malloc(sizeof(char)*(size-2));
    strcpy(id, data + 2);
    
    return atoi(id);
}

int get_movie(Movie ** movie, FILE ** movie_file_ptr, char separator, Column * col, int cur_idx) {
    char sep_line = '\n';
    char c = fgetc((*movie_file_ptr));
    int i = 0, j = 0, index = 0;
    int search_index = 0;
    
    fseek((*movie_file_ptr), cur_idx, SEEK_SET);
    while (c != sep_line) {
        while (c == separator) {
            c = fgetc((*movie_file_ptr));
            search_index += 1;
        }
        
        while (c != separator && c != sep_line) {
            c = fgetc((*movie_file_ptr));
            j++;
            search_index += 1;
        }
        
        if (index == col->index) {
            char * data = malloc(sizeof(char)*j);
            fseek((*movie_file_ptr), cur_idx + i, SEEK_SET);
            fgets(data, j, (*movie_file_ptr));
            // printf("%s\n", data);
            
            if (strcmp(col->name, "tconst") == 0) {
                (*movie)->id = clear_id(data, j + 1);
            } else {
                (*movie)->title = data;
            }
            
            if (!col->next) {
                break;
            }
            
            col = col->next;
        }
        
        i += j;
        j = 1;
        
        index += 1;
    }
    
    while (c != sep_line) {
        c = fgetc((*movie_file_ptr));
        search_index += 1;
    }
    
    return cur_idx + search_index;
}

void fuel_movie_list(FILE ** movie_file_ptr, char separator, Movie *** m_list, int size) {
    Column * movie_cols = malloc(sizeof(Column));
    int cur_idx = get_movies_cols(movie_file_ptr, separator, &movie_cols);
    
    printf("%d\n\n", movie_cols->index);
    
    for (int i = 0; i < size; i++) {
        (*m_list)[i] = malloc(sizeof(Movie));
        (*m_list)[i]->id = __INT32_MAX__;
        (*m_list)[i]->title = NULL;
        (*m_list)[i]->neighbors = NULL;
        (*m_list)[i]->list_index = i;
        
        cur_idx = get_movie(&((*m_list)[i]), movie_file_ptr, separator, movie_cols, cur_idx);
        // printf("\n\n");
    }
}

Movie ** init_movie_list(FILE * movie_file_ptr, int init_size, char separator) {
    Movie ** m_list = malloc(sizeof(Movie*)*init_size);
    
    fuel_movie_list(&movie_file_ptr, separator, &m_list, init_size);
    
    return m_list;
}

// Column ** get_artists_cols(FILE ** fileptr, char separator) {
//     int size = 3;
//     char **artists_cols_to_search = malloc(sizeof(char*)*size);
    
//     artists_cols_to_search[0] = malloc(sizeof(char)*6);
//     strcpy(artists_cols_to_search[0], "nconst");
    
//     artists_cols_to_search[1] = malloc(sizeof(char)*11);
//     strcpy(artists_cols_to_search[1], "primaryName");
    
//     artists_cols_to_search[2] = malloc(sizeof(char)*14);
//     strcpy(artists_cols_to_search[2], "knownForTitles");
    
//     return get_cols(fileptr, separator, artists_cols_to_search, size);
// }

int main() {
    FILE *actors_fileptr;
    FILE *movies_fileptr;
    char separator = '\t';
    
    actors_fileptr = fopen("../data/name.basics.tsv", "r");
    movies_fileptr = fopen("../data/title.basics.tsv", "r");
    
    if (actors_fileptr == NULL || movies_fileptr == NULL) {
        printf("File not found");
        return -1;
    }
    
    Movie ** movies_list = init_movie_list(movies_fileptr, 100, separator);
    Actor ** actor_list = init_actor_list(actors_fileptr, 100, separator);
    
    for (int i = 0; i < 100; i++) {
        printf("%d -> %s\n", movies_list[i]->id, movies_list[i]->title);
    }
    return 0;
}