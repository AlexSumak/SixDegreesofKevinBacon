#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <string>
#include "Edge.h"

class Edge;

class Movie
{
    public:

        std::string name;
        int year;
        std::vector<Edge*> edges;

        Movie(std::string name, int year)
            : name(name), year(year)
        {}

        ~Movie()
        {}
};
#endif
