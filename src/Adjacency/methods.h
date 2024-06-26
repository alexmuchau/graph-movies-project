//////////////////////////////////////////////////

// Curitiba 2024
// Universidade Positivo
// Escola de Tecnologia da Informação
// Alex Muchau

//////////////////////////////////////////////////

#include "../tools/libs.h"
#include "../tools/tools.h"
#include "../Actor/Actor.h"
#include "../Movie/Movie.h"
#include "../Movie/MovieTree.h"

void connect_and_create_adjacencies(ActorList ** a_list, Node ** movie_tree);

MovieNode * connect_movie_id(int * movie_ids, int size, Node * movie_tree);