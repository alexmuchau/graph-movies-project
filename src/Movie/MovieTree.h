//////////////////////////////////////////////////

//curitiba 2024
//universidade positivo
//escola de tecnologia da informação
//prof jean diogo

////// CODIGO DISPONIBILIZADO PELO PROFESSOR /////

#include <stdio.h>
#include <stdlib.h>
#include "Movie.h"

struct Node;
typedef struct Node Node;

struct Node
{
	Movie * movie;
	int     level;
	Node  * left;
	Node  * right; 
};

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
