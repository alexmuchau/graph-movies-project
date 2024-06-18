//////////////////////////////////////////////////

//curitiba 2024
//universidade positivo
//escola de tecnologia da informação
//prof jean diogo

////// CODIGO DISPONIBILIZADO PELO PROFESSOR /////

#ifndef MOV_T_H
#define MOV_T_H

#include "MovieTree.h"

void visit(Node * n)
{
	if(n)
	{
		printf("[");
		visit(n->left);
		printf("%d", n->movie->id);
		visit(n->right);
		printf("]");
	}
}

void destruct(Node * n)
{
	if(n)
	{
		destruct(n->left);
		destruct(n->right);
		free(n);
	}
}

//////////////////////////////////////////////////

int get_weight(Node * n)
{
	if(!n)
	{
		return 0;
	}
	int const left_level  = n->left  ? n->left->level  : -1;
	int const right_level = n->right ? n->right->level : -1;
	return right_level - left_level;
}

void update_level(Node * n)
{
	if(n)
	{
		int const left_level  = n->left  ? n->left->level  : -1;
		int const right_level = n->right ? n->right->level : -1;
		int const max_level = left_level > right_level ? left_level : right_level;
		n->level = max_level + 1;
	}
}

Node * rotate_left(Node *, int);
Node * rotate_right(Node *, int);

Node * rotate_left(Node * n, int weight)
{
	if(!n)
	{
		return NULL;
	}
	
	int const right_weight = get_weight(n->right);
	
	if((weight < 0 && right_weight > 0) || (weight > 0 && right_weight < 0))
	{
		n->right = rotate_right(n->right, right_weight);
	}
	
	Node * temp = n->right;
	n->right = temp->left;
	temp->left = n; 
	
	update_level(temp->left);
	update_level(temp);
	
	return temp;
}

Node * rotate_right(Node * n, int weight)
{
	if(!n)
	{
		return NULL;
	}
	
	int const left_weight = get_weight(n->left);
	
	if((weight < 0 && left_weight > 0) || (weight > 0 && left_weight < 0))
	{
		n->left = rotate_left(n->left, left_weight);
	}
	
	Node * temp = n->left;
	n->left = temp->right;
	temp->right = n;
	
	update_level(temp->right);
	update_level(temp);
	
	return temp;
}

void balance(Node ** n)
{
	if(*n)
	{
		int const weight = get_weight(*n);
		if(weight > 1)
		{
			*n = rotate_left(*n, weight);
		}
		else if(weight < -1)
		{
			*n = rotate_right(*n, weight);
		}
		else
		{
			update_level(*n);
		}
	}
}

//////////////////////////////////////////////////

void insert_node(Node ** n, Node * m)
{
	if(!m)
	{
		return;
	}
	
	if(!*n)
	{
		*n = m;
		return;
	}
	
	if(m->movie->id < (*n)->movie->id)
	{
		insert_node(&(*n)->left, m);
	}
	else
	{
		insert_node(&(*n)->right, m);
	}
	
	balance(n);
}

void insert(Node ** n, Movie* movie)
{
	Node * m = (Node *) malloc(sizeof(Node));
	if(m)
	{
		m->movie = movie;
		m->level = 0;
		m->left  = NULL;
		m->right = NULL;
	}
	insert_node(n, m);
}

void erase(Node ** n, int id)
{
	if(!(*n))
	{
		return;
	}
	
	if(id < (*n)->movie->id)
	{
		erase(&(*n)->left, id);
	}
	else if(id > (*n)->movie->id)
	{
		erase(&(*n)->right, id);
	}
	else
	{
		insert_node(&((*n)->left), (*n)->right);
		Node * temp = (*n)->left;
		free(*n);
		(*n) = temp;
	}
	
	balance(n);
}

Movie * search_movie(Node *n, int id)
{
	if (id == n->movie->id) {
		return n->movie;
	}
	
	if (id >= n->movie->id) {
		return search_movie(n->right, id);
	} else {
		return search_movie(n->left, id);
	}
}


#endif