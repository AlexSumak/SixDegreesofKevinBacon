#ifndef EDGE_H
#define EDGE_H
#include <string>
#include <vector>
using namespace std;

class Edge {

public:
    string movie;
    vector <string> actors;
     Edge *prev;
         
             string movie_edge;
    Edge (string movie) : movie(movie){vector<string>actors;};
};

#endif // EDGE_H
