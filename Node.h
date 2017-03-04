#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
using namespace std;

class Node {

public:
    string name;
    vector<string> movies;
    Node *prev;
    int dist;
    string movie_edge;
    Node (string name): name(name), prev(nullptr), dist(-1) {
        vector<string> movies;
        movie_edge = "";
        };
};
#endif // NODE_H
