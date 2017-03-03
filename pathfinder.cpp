#include "ActorGraph.h"


int main(int argc, char* argv[])
{
    if(argc < 5)
    {
        std::cout << "Incorrect number of arguments." << std::endl;
        return -1;
    }

    ActorGraph actorGraph;
    bool weighted;

    if(*argv[2] == 'w')
    {
        weighted = true;
    }
    else if(*argv[2] == 'u')
    {
        weighted = false;
    }
    else
    {
        std::cout << "wrong input" << std::endl;
        return -1;
    }

    if(!actorGraph.loadFromFile(argv[1], weighted))
    {
        return -1;
    }

    /*if(!actorGraph.find(argv[3], argv[4], weighted))
    {
        return -1;
    }*/

    return 0;
}
