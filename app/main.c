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
    char ** movies_ids;
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

void * movie_case (char* data, int size, Column* col, Movie** movie) {
    if (col->index == 0) {
        (*movie)->id = clear_id(data, size);
    } else {
        (*movie)->title = data;
    }
}

char ** split_movies_ids(char * data, int size, char separator) {
    int start_idx = 0, i = 0, qty = 0, id_size, list_size = 5;
    char ** result = malloc(sizeof(char*)*5);
    while (i < size) {
        while (data[i] != separator && i < size) {
            i++;
        }
        qty += 1;
        id_size = (i - start_idx);
        
        if (qty > list_size) {
            list_size += 5;
            result = realloc(result, list_size);
        }
        
        result[qty] = malloc(sizeof(char)*id_size);
        strncpy(result[qty], data + start_idx, id_size);
        
        i += 1;
        start_idx = i;
    }
    
    if (qty != list_size) {
        result = realloc(result, qty);
    }
    
    return result;
}

void * actor_case (char* data, int size, Column* col, Actor** actor) {
    if (col->index == 0) {
        (*actor)->id = clear_id(data, size);
    } else if (strcmp(col->name, "primaryName")) {
        (*actor)->name = data;
    } else {
        (*actor)->movies_ids = split_movies_ids(data, size, ',');
    }
}

int get_row(
    Actor ** actor,
    Movie ** movie,
    void * (*movie_case)(char* data, int size, Column* col, Movie** movie),
    void * (*actor_case)(char* data, int size, Column* col, Actor** actor),
    FILE ** fileptr,
    char separator,
    Column * col,
    int cur_idx
)
{
    if (actor && movie) {
        printf("Must get_row only for actor, or only for movie\n");
        return;
    }
    
    char sep_line = '\n';
    char c = fgetc((*fileptr));
    int i = 0, j = 0, index = 0;
    int search_index = 0;
    
    fseek((*fileptr), cur_idx, SEEK_SET);
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
        
        if (index == col->index) {
            char * data = malloc(sizeof(char)*j);
            fseek((*fileptr), cur_idx + i, SEEK_SET);
            fgets(data, j, (*fileptr));
            
            if (movie) {
                movie_case(data, j + 1, col, movie);
            } else {
                actor_case(data, j + 1, col, actor);
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
        c = fgetc((*fileptr));
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
        
        cur_idx = get_row(
            NULL, // Actor
            &((*m_list)[i]), // Movie
            movie_case, // Movie function,
            NULL, // Actor function
            movie_file_ptr,
            separator,
            movie_cols,
            cur_idx
        );
        // printf("\n\n");
    }
}

Movie ** init_movie_list(FILE * movie_file_ptr, int init_size, char separator) {
    Movie ** m_list = malloc(sizeof(Movie*)*init_size);
    
    fuel_movie_list(&movie_file_ptr, separator, &m_list, init_size);
    
    return m_list;
}

int get_actor_cols(FILE ** fileptr, char separator, Column ** actors_cols_to_search) {
    (*actors_cols_to_search)->name = malloc(sizeof(char)*6);
    strcpy((*actors_cols_to_search)->name, "nconst");
    (*actors_cols_to_search)->index = __INT32_MAX__;
    
    (*actors_cols_to_search)->next = malloc(sizeof(Column));
    
    Column * actor_col = (*actors_cols_to_search)->next;
    actor_col->name = malloc(sizeof(char)*11);
    strcpy(actor_col->name, "primaryName");
    actor_col->index = __INT32_MAX__;
    actor_col->next = malloc(sizeof(Column));
    
    actor_col = actor_col->next;
    actor_col->name = malloc(sizeof(char)*14);
    strcpy(actor_col->name, "knownForTitles");
    actor_col->index = __INT32_MAX__;
    actor_col->next = NULL;
    
    int cur_idx = get_col(fileptr, separator, actors_cols_to_search);
    return cur_idx;
}

void fuel_actor_list(FILE ** actor_fileptr, char separator, Actor *** a_list, int size) {
    Column * actor_cols = malloc(sizeof(Column));
    int cur_idx = get_actor_cols(actor_fileptr, separator, &actor_cols);
    
    printf("%d\n\n", actor_cols->index);
    
    for (int i = 0; i < size; i++) {
        (*a_list)[i] = malloc(sizeof(Movie));
        (*a_list)[i]->id = __INT32_MAX__;
        (*a_list)[i]->movies = NULL;
        (*a_list)[i]->movies_ids = NULL;
        (*a_list)[i]->name = NULL;
        
        cur_idx = get_row(
            &((*a_list)[i]), // Actor
            NULL, // Movie
            NULL, // Movie function,
            &actor_case, // Actor function
            actor_fileptr,
            separator,
            actor_cols,
            cur_idx
        );
        // printf("\n\n");
    }
}

Actor ** init_actor_list(FILE * actor_fileptr, int init_size, char separator) {
    Actor ** a_list = malloc(sizeof(Actor*)*init_size);
    
    fuel_actor_list(&actor_fileptr, separator, &a_list, init_size);
    
    return a_list;
}

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
        printf("%d -> %s\n", actor_list[i]->id, actor_list[i]->name);
    }
    return 0;
}