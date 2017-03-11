#ifndef NODE_H
#define NODE_H

#include <limits>
#include <string>
#include <vector>

#include "Edge.h"

using namespace std;

class Edge;
class Node {

    public:
        string name;
        int index;
        int dist;
        bool visit;
        Edge* path;
        Node* prev;
        vector<Edge*> edges;

            Node(string name)
            : name(name)
            {}

        ~Node()
        {

            for(vector<Edge*>::iterator it = edges.begin()
                    ; it != edges.end(); ++it)
            {
                delete(*it);
            }
        }

        bool operator<(const Node& other)
        {
            if(dist == other.dist)
            {
                return index > other.index;
            }
            return dist > other.dist;
        }
};
class ActorComp
{
    public:
        bool operator()(Node*& lhs, Node*& rhs) const
        {
            return (*lhs) < (*rhs);
        }
};


#endif // NODE_H
