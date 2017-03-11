#include "ActorGraph.h"
using namespace std;
int main(int argc, char* argv[])
{

    if(argc < 4)
    {
        cout << "Incorrect number of arguments" << endl;
        cout << "Usage: ./extension inputfile output actorName" 
            << endl;
        return -1;
    }

    ActorGraph graph;


    bool success = graph.loadFromFile(argv[1]);
    if(!success)
    {
        return -1;
    }


    string name(argv[3]);
    for(int index = 4; index < argc; ++index)
    {
        name += " ";
        name += argv[index];
    }


    success = graph.averageDist(argv[2], name);
    if(!success)
    {
        return -1;
    }

    return 0;
}


