#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct column;
typedef struct column column;

struct column {
    int index;
    char * name;
};

int main() {
    FILE *fileptr;
    
    fileptr = fopen("../data/name.basics.tsv", "r");
    
    if (fileptr == NULL) {
        printf("File not found");
        return -1;
    }
    
    char c = fgetc(fileptr);
    char separator = '\t';
    char sep_line = '\n';
    
    int i = 0;
    int j = 1;
    int index = 0;
    column ** cols = malloc(sizeof(column)*3);
    printf("%d\n", cols[0]->index);
    while (c != sep_line) {
        while (c == separator) {
            c = fgetc(fileptr);
        }
        while (c != separator && c != sep_line) {
            c = fgetc(fileptr);
            j++;
        }
        char * text = malloc(sizeof(char)*(j));
        fseek(fileptr, i, SEEK_SET);
        fgets(text, j, fileptr);
        
        if (text == "nconst") {
            cols[0]->name[j+1] = "primaryName";
            cols[0]->index = index;
        } else if (text == "primaryName") {
            char col
            cols[1]->name[j+1] = ;
            cols[1]->index = index;
        } else if (text == "knownForTitles") {
            char col_name[15] = "knownForTitles";
            cols[2]->name = col_name;
            cols[2]->index = index;
        }
        
        printf("%i, %i - ", i, j);
        printf("%s\n", text);
        
        i += j;
        j = 1;
        
        index += 1;
        // cols = realloc(cols, sizeof(cols) + sizeof(char)*j-i);
        // strcpy(cols[j-i], text);
    }
    
    for (int i = 0; i<3;i++) {
        printf("%s - %d\n", cols[i]->name, cols[i]->index);
    }
    
    return 0;
}