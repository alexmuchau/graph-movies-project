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



void get_col(FILE ** fileptr, char separator, Column ** col_to_search) {
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
        }
        while (c != separator && c != sep_line) {
            c = fgetc((*fileptr));
            j++;
        }
        char * text = malloc(sizeof(char)*(j));
        fseek((*fileptr), i, SEEK_SET);
        fgets(text, j, (*fileptr));
        
        if (strcmp(text, (*col_to_search)->name) == 0) {
            (*col_to_search)->index = index;
            
            if ((*col_to_search)->next) {
                get_col(fileptr, separator, &((*col_to_search)->next));
            }
            
            break;
        }
        
        i += j;
        j = 1;
        
        index += 1;
    }
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

Column * get_movies_cols(FILE ** fileptr, char separator) {
    Column *movie_col_to_search_list = malloc(sizeof(Column));
    
    movie_col_to_search_list->name = malloc(sizeof(char)*6);
    strcpy(movie_col_to_search_list->name, "tconst");
    movie_col_to_search_list->index = __INT32_MAX__;
    
    movie_col_to_search_list->next = malloc(sizeof(Column));
    
    Column * movie_col_to_search = movie_col_to_search_list->next;
    movie_col_to_search->name = malloc(sizeof(char)*11);
    strcpy(movie_col_to_search->name, "primaryTitle");
    movie_col_to_search->index = __INT32_MAX__;
    movie_col_to_search->next = NULL;
    
    get_col(fileptr, separator, &movie_col_to_search_list);
    return movie_col_to_search_list;
}

int clear_id(char * data, int size) {
    char *id = malloc(sizeof(char)*(size-2));
    for (int i = 2; i< size; i++) {
        id[i] = data[i];
    }
    
    return atoi(id);
}

void get_movie(Movie ** movie, FILE ** movie_file_ptr, char separator, Column * col) {
    int i = 0, j = 0;
    
    int index = 0;
    char sep_line = '\n';
    char c = fgetc((*movie_file_ptr));
    
    // Adjust to start read by a char
    while (c == sep_line) {
        c = fgetc((*movie_file_ptr));
    }
    
    while (c != sep_line) {
        while (c == separator) {
            c = fgetc((*movie_file_ptr));
        }
        while (c != separator && c != sep_line) {
            c = fgetc((*movie_file_ptr));
            j++;
        }
        if (index == col->index) {
            char * data = malloc(sizeof(char)*(j));
            fseek((*movie_file_ptr), i, SEEK_SET);
            fgets(data, j, (*movie_file_ptr));
            
            if (strcmp(col->name, "tconst") == 0) {
                (*movie)->id = clear_id(data, j);
            } else {
                (*movie)->title = data;
            }
            
            if (col->next) {
                get_movie(movie, movie_file_ptr, separator, col->next);
            }
            break;
        }
        
        index += 1;
        
        i += j;
        j = 1;
        
        index += 1;
    }
}

void fuel_movie_list(FILE ** movie_file_ptr, char separator, Movie *** m_list, int size) {
    Column * movie_cols = get_movies_cols(movie_file_ptr, separator);
    
    for (int i = 0; i < size; i++) {
        (*m_list)[i] = malloc(sizeof(Movie));
        (*m_list)[i]->id = __INT32_MAX__;
        (*m_list)[i]->title = NULL;
        (*m_list)[i]->neighbors = NULL;
        (*m_list)[i]->list_index = i;
        
        get_movie(&((*m_list)[i]), movie_file_ptr, separator, movie_cols);
    }
}

Movie ** init_movie_list(FILE * movie_file_ptr, int init_size, char separator) {
    Movie ** m_list = malloc(sizeof(Movie*)*init_size);
    
    fuel_movie_list(&movie_file_ptr, separator, &m_list, init_size);
    
    return m_list;
}

int main() {
    FILE *artists_fileptr;
    FILE *movies_fileptr;
    char separator = '\t';
    
    artists_fileptr = fopen("../data/name.basics.tsv", "r");
    movies_fileptr = fopen("../data/title.basics.tsv", "r");
    
    if (artists_fileptr == NULL || movies_fileptr == NULL) {
        printf("File not found");
        return -1;
    }
    
    // Column ** artists_cols = get_artists_cols(&artists_fileptr, separator);
    Movie ** movies_list = init_movie_list(movies_fileptr, 100, separator);
    
    
    printf("%d\n", movies_list[0]->id);
    return 0;
}