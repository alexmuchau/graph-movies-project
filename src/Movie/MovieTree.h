//////////////////////////////////////////////////

//curitiba 2024
//universidade positivo
//escola de tecnologia da informação
//prof jean diogo

////// CODIGO DISPONIBILIZADO PELO PROFESSOR /////

#include "../tools/libs.h"
#include "Movie.h"

#ifndef MOV_T_C_H
#define MOV_T_C_H

struct Node;
typedef struct Node Node;

struct Node
{
	Movie * movie;
	int     level;
	Node  * left;
	Node  * right; 
};

#endif

void visit(Node * n);
void destruct(Node * n);

//////////////////////////////////////////////////

int get_weight(Node * n);
void update_level(Node * n);

Node * rotate_left(Node * n, int weight);
Node * rotate_right(Node * n, int weight);

void balance(Node ** n);

//////////////////////////////////////////////////

void insert_node(Node ** n, Node * m);

void insert(Node ** n, Movie* movie);

void erase(Node ** n, int id);

Movie * search_movie(Node *n, int id);
