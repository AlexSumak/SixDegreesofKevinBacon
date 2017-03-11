#include "ActorGraph.h"

using namespace std;
int main(int argc, char* argv[])
{

    if(argc < 4)
    {
        cout << "Incorrect number of arguments" << endl;
        cout << "Usage: ./actorconnections inputfile pairs output" 
            << "[bfs,ufind(default)]" << endl;
        return -1;
    }

    string algor = "ufind";
    bool ufind = false;


    if(argc == 5)
    {
        algor = string(argv[4]);  
    }


    if(!algor.compare("ufind"))
    {
        ufind = true;
    }
    else if(!algor.compare("bfs"))
    {
        ufind = false;
    }
    else
    {
        cout << "Incorrect Fourth Input: [bfs,ufind(default)]" 
            << endl;
        return -1;
    }

    ActorGraph graph;


    bool success = graph.loadFromFile(argv[1]);
    if(!success)
    {
        return -1; 
    }

    success = graph.moviespan(argv[2], argv[3], ufind);
    if(!success)
    {
        return -1;
    }

    return 0;
}
