#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include <string>
#include "Edge.h"

using namespace std;


class Edge;


class Movie
{
    public:

        string name;
        int year;
        vector<Edge*> edges;

        Movie(string name, int year)
            : name(name), year(year)
        {}

        ~Movie()
        {}
};
#endif
