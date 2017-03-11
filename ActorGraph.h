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

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include "Node.h"
#include "Edge.h"
#include "Movie.h"
#include "Disjoint.h"


// Maybe include some data structures here


using namespace std;
class ActorGraph {
    protected:
        std::unordered_map<string, Node*> actors;
        std::unordered_map<string, Movie*> movies;
        std::vector<Disjoint*> set;
        int min_year = 9999;
        
        bool BFSTraverse(Node* start, Node* end, int year);

        bool DijkTraverse(Node* start, Node* end);

        int BFSSearch(Node* start, Node* end);

        int UnionFind(Node*, Node* end);

public:


        ActorGraph(void);

        ~ActorGraph();

        bool loadFromFile(const char* in_filename);
        
        bool findPath(const char* in_filename, const char* out_filename, 
                        bool use_weighted);

        bool moviespan(const char* in_filename, const char* out_filename,
                         bool ufind);

        bool averageDist(const char* out_filename, std::string actorName);
};


#endif // ACTORGRAPH_H
