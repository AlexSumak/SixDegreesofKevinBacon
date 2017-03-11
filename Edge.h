#ifndef EDGE_H 
#define EDGE_H

#include "Node.h"
#include "Movie.h"

class Node;
class Movie;

class Edge 
{

    public:
        Node* node;
        Movie* movie;
        int weight;


        Edge(Node* node, Movie* movie, int weight)
            :node(node), movie(movie), weight(weight)
        {}


        ~Edge()
        {}

};

#endif // EDGE_H
