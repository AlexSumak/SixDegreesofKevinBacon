/*
 * ActorGraph.h
 * Author: Blake McMurray; Alex Sumak
 * Date: 3/1/17
 * PA4
 *
 * This file is meant to exist as a container for starter
 * code that you can use to read the input file format defined in 
 * movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include <unordered_map>
#include <iostream>
#include "Edge.h"
#include "Node.h"
#include <string>


// Maybe include some data structures here


using namespace std;
class Node;
class Edge;
class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here

public:

    unordered_map<string, Edge*> mMap;
    unordered_map<string, Node*> aMap;

    ActorGraph(void);
    
    // Maybe add some more methods here
    
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    vector<string> shortestPath(string, string);
    Node* BFS(string, string);
};


#endif // ACTORGRAPH_H
