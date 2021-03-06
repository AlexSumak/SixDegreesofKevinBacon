/*
 ** ActorGraph.cpp
 ** Author: Blake McMurray Alex Sumak
 ** Date: 3/2/17
 **
 ** This file is meant to exist as a container for starter code that you can use to read the input file format
 ** defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 **/

#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}


ActorGraph::~ActorGraph()
{
    for(unordered_map<string,Node*>::iterator it = actors.begin()
            ; it != actors.end(); ++it)
    {
        delete (it->second);
    }

    for(unordered_map<string,Movie*>::iterator it = movies.begin()
            ; it != movies.end(); ++it)
    {
        delete (it->second);
    }

    for(vector<Disjoint*>::iterator it = set.begin()
            ; it != set.end(); ++it)
    {
        delete (*it);
    }
}

bool ActorGraph::loadFromFile(const char* in_filename)
{

    ifstream infile(in_filename);


    bool have_header = false;
    Node* node = 0;
    Movie* movie = 0;
    Edge* edge = 0;
    int index = 0;

    while (infile)
    {
        string s;

        if (!getline( infile, s )) break;

        if (!have_header)
        {

            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss)
        {
            string next;


            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 3)
        {

            continue;
        }


        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);


        if(movie_year < min_year)
        {
            min_year = movie_year;
        }


        string movie_key = record[1] + record[2];


        if(actors.find(actor_name) == actors.end())
        {

            node = new Node(actor_name);
            node->index = index++;
            actors.insert({actor_name, node});


            Disjoint* disjoint = new Disjoint(node);
            set.push_back(disjoint);
        }
        else
        {
            node = actors[actor_name];
        }


        if(movies.find(movie_key) == movies.end())
        {
            movie = new Movie(movie_title, movie_year);
            movies.insert({movie_key, movie});
        }
        else
        {
            movie = movies[movie_key];
        }

        Edge* edge = new Edge(node, movie, 1 + 2015 - movie->year);


        node->edges.push_back(edge);
        movie->edges.push_back(edge);
    }

    if (!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
/*
bool ActorGraph::findPath(const char* in_filename, const char* out_filename,
        bool use_weighted)
{

    ifstream infile(in_filename);
    ofstream outfile(out_filename);

    bool have_header = false;

    Node* start;
    Node* end;

    while(infile)
    {
        string s;


        if(!getline(infile,s)) break;

        if(!have_header)
        {
            have_header = true;
            outfile << "(actor)--[movie#@year]-->(actor)--...\n";
            continue;
        }


        istringstream ss(s);
        vector<string> record;

        while(ss)
        {
            string next;
            if(!getline(ss, next, '\t')) break;

            record.push_back(next);
        }


        if(record.size() != 2)
        {
            continue;
        }


        string source(record[0]);
        string dest(record[1]);
        bool find;


        unordered_map<string, Node*>::iterator it;
        it = actors.find(source);
        if(it == actors.end())
        {
            continue;
        }
        it = actors.find(dest);
        if(it == actors.end())
        {
            continue;
        }


        start = actors[source];
        end = actors[dest];


        if(use_weighted)
        {

            find = DijkTraverse(end,start);
            if(find)
            {

                Node* trav = start;
                while(1)
                {
                    outfile << "(" << trav->name << ")" << "--";
                    outfile << "[" << trav->path->movie->name << "#@" 
                        << trav->path->movie->year << "]" << "-->";
                    trav = trav->path->node;


                    if(trav == end)
                    {
                        outfile << "(" << trav->name << ")" << endl;
                        break;
                    }
                }
            }
        }


        else
        {

            find = BFSTraverse(end, start, 2016);
            if(find)
            {

                Node* trav = start;
                while(1)
                {
                    outfile << "(" << trav->name << ")" << "--";
                    outfile << "[" << trav->path->movie->name << "#@" 
                        << trav->path->movie->year << "]" << "-->";
                    trav = trav->path->node;

                    if(trav == end)
                    {
                        outfile << "(" << trav->name << ")" << endl;
                        break;
                    } 
                }
            }
        }
    }


    if(!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    outfile.close();

    return true;
}
*/

bool ActorGraph::moviespan(const char* in_filename, 
        const char* out_filename, bool ufind)
{

    ifstream infile(in_filename);
    ofstream outfile(out_filename);

    bool have_header = false;

    Node* start;
    Node* end;

    chrono::time_point<chrono::high_resolution_clock> begin
        = chrono::high_resolution_clock::now();

    while(infile)
    {

        start = 0;
        end = 0;
        string s;


        if(!getline(infile,s)) break;


        if(!have_header)
        {
            have_header = true;
            outfile << "Actor1\tActor2\tYear" << endl;
            continue;
        }

        istringstream ss(s);
        vector<string> record;


        while(ss)
        {
            string next;
            if(!getline(ss, next, '\t')) break;

            record.push_back(next);
        }

        if(record.size() != 2)
        {
            continue;
        }


        string source(record[0]);
        string dest(record[1]);

        unordered_map<string, Node*>::iterator it;
        it = actors.find(source);
        if(it != actors.end())
        {
            start = it->second;
        }
        it = actors.find(dest);
        if(it != actors.end())
        {
            end = it->second;
        }


        if(ufind)
        {

            int year = UnionFind(start,end);
            outfile << source << "\t" << dest << "\t" << year << endl;
        }
        else
        {

            int year = BFSSearch(start, end);
            outfile << source << "\t" << dest << "\t" << year << endl;
        }
    }


    chrono::time_point<chrono::high_resolution_clock> done 
        = chrono::high_resolution_clock::now();


    if(!infile.eof())
    {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    if(ufind)
    {
        cout << "Union Find took ";
    }
    else
    {
        cout << "BFS Search took ";
    }


    long int time = (long int)chrono::duration_cast<chrono::milliseconds>(done-begin).count();
    cout << time << " milliseconds" << endl;

    infile.close();
    outfile.close();
    return true;
}

bool ActorGraph::averageDist(const char* out_filename, 
        string actorName)
{

    ofstream outfile(out_filename);
    outfile << "Actor" << endl;


    unordered_map<string, Node*>::iterator it;
    it = actors.find(actorName);
    if(it == actors.end())
    {
        cout << "Actor, " << actorName << " does not exist in our"
            << " database, select another" << endl;
        return false;
    }

    Node* start = it->second; 


    int unweight_dist = 0;
    int numActors = 0;
    for(auto act_it = actors.begin(); act_it != actors.end(); ++act_it)
    {
        Node* end = act_it->second;

        bool find = BFSTraverse(end, start, 2016);
        if(!find)
        {
            continue;
        }

        outfile << end->name << endl;
        ++numActors;


        Node* trav = start;
        while(1)
        {
            trav = trav->path->node;
            ++unweight_dist;
            if(trav == end)
            {
                break;
            } 
        }
    }


    double unweight_average = (double)unweight_dist / numActors;


    outfile << numActors << " Actors are Connected to " 
        << actorName << endl;
    outfile << "The Average Shortest Unweighted Distance to "
        << actorName << " is " << unweight_average << endl;

    outfile.close();
    return true;
}

int ActorGraph::UnionFind(Node* start, Node* end)
{

    if(!start || !end)
    {
        return 9999;
    }


    vector<Disjoint*>::iterator joint_it = set.begin();
    for( ; joint_it != set.end(); ++joint_it)
    {
        Disjoint* disjoint = *joint_it;
        disjoint->sentinel = disjoint;
        disjoint->size = 1;
    }


    int year = min_year;
    while(year < 2016)
    {

        unordered_map<string,Movie*>::iterator it = movies.begin();
        for( ; it != movies.end(); ++it)
        {

            Movie* movie = it->second;
            if(movie->year == year)
            {
                Disjoint* disjoint = 0;


                vector<Edge*>::iterator act_it = movie->edges.begin();
                for( ; act_it != movie->edges.end(); ++act_it)
                {
                    Node* actor = (*act_it)->node;

                    if(disjoint)
                    {
                        disjoint->Union(set[actor->index]);
                    }

                    disjoint = set[actor->index];
                }
            }
        }


        Disjoint* first = set[start->index];
        Disjoint* second = set[end->index];
        if(first->Find()->node->index == second->Find()->node->index)
        {
            return year;
        }


        year++;
    }
    return 9999;
}

bool ActorGraph::BFSTraverse(Node* start, Node* end, int year)
{

    if(!start || !end)
    {
        return false;
    }


    if(start->index == end->index)
    {
        return false;
    }


    queue<Node*> explore;
    for(auto it = actors.begin(); it != actors.end(); ++it)
    {
        it->second->visit = false;
    }
    explore.push(start);
    start->visit = true;

    while(!explore.empty())
    {

        Node* next = explore.front();
        explore.pop();


        vector<Edge*>::iterator it = next->edges.begin();
        for( ; it != next->edges.end(); ++it)
        {
            Movie* movie = (*it)->movie;

            if(movie->year > year)
            {
                continue;
            }


            vector<Edge*>::iterator a_it = movie->edges.begin();
            for( ; a_it != movie->edges.end(); ++a_it)
            {
                Node* actor = (*a_it)->node;


                if(!actor->visit)
                {

                    if(actor->index == end->index)
                    {

                        end->path = *it;
                        end->prev = next;
                        return true;
                    }
                    else
                    {

                        actor->visit = true;
                        actor->path = *it;
                        actor->prev = next;
                        explore.push(actor);
                    }
                }
            }
        }
    }
    return false;
}
int ActorGraph::BFSSearch(Node* start, Node* end)
{
    if(!start || !end)
    {
        return 9999;
    }

    bool find = false;
    int year = min_year;
    while(year < 2016)
    {
        find = BFSTraverse(start, end, year);
        if(find)
        {
            return year;    
        }
        year++;
    }
    return 9999; 
}
bool ActorGraph::DijkTraverse(Node* start, Node* end)
{

    if(!start || !end)
    {
        return false;
    }


    for(auto it = actors.begin(); it != actors.end(); ++it)
    {
        it->second->visit = false;
        it->second->prev = 0;
        it->second->dist = numeric_limits<int>::max();
    }
    priority_queue<Node*, vector<Node*>, ActorComp> pq;
    start->dist = 0;
    pq.push(start);

    while(!pq.empty())
    {

        Node* next = pq.top();
        pq.pop();

        if(!next->visit)
        {
            next->visit = true;


            vector<Edge*>::iterator it = next->edges.begin();
            for( ; it != next->edges.end(); ++it)
            {
                Edge* edge = *it;
                Movie* movie = edge->movie;


                vector<Edge*>::iterator m_it = movie->edges.begin();      
                for( ; m_it != movie->edges.end(); ++m_it)
                {
                    Edge* inner_edge = *m_it;
                    Node* actor = inner_edge->node;


                    int distance = inner_edge->weight + next->dist;
                    if(distance < actor->dist)
                    {

                        actor->prev = next;
                        actor->path = edge;
                        actor->dist = distance;
                        pq.push(actor);
                    }
                }
            }
        }
    }
    return true; 
}

