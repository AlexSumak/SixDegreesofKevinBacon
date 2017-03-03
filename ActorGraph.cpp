/*
 * ActorGraph.cpp
 * Author: Blake McMurray Alex Sumak
 * Date: 3/2/17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include <queue>
using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now what?
        auto currActor = aMap.find(actor_name);
        string realMovie = movie_title + "#@" + to_string(movie_year);
        auto currMovie = mMap.find(realMovie);
        
        if(currActor == aMap.end()){

            aMap[actor_name] = new Node(actor_name);
            aMap.find(actor_name)->second->movies.push_back(realMovie);
        }
        else{
            int i = 0;
            for(;i < currActor->second->movies.size(); i++){
                if (realMovie == currActor->second->movies[i])
                    break;
            }
            if(i == currActor->second->movies.size()-1)
                currActor->second->movies.push_back(realMovie);
        }

        if(currMovie == mMap.end()){
            mMap[realMovie] = new Edge(realMovie);
            mMap.find(realMovie)->second->actors.push_back(actor_name);
        }
        else{
            int i = 0;
            for(;i < currMovie->second->actors.size(); i++){
                if (actor_name == currMovie->second->actors[i])
                    break;
            }
            if(i == currMovie->second->actors.size()-1)
                currMovie->second->actors.push_back(actor_name);
        }
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}




    Node* ActorGraph::BFS(Node* n1, Node* n2){
        queue<Node*> q;
        string find_actor = n1->name;
        auto actor_iterator = aMap.find(find_actor);
        if (actor_iterator == aMap.end()) return nullptr;
        actor_iterator->second->dist = 0;
        q.push(actor_iterator->second);  
        Node* curr;

        while(!q.empty()){

            curr = q.front();
            q.pop();

            if(curr == n2) 
                return curr;

            vector<string> movies = actor_iterator->second->movies;


            for(int i = 0; i < movies.size() ; i++) {
                auto movie_iterator = mMap.find(movies[i]);
                vector<string> actors = movie_iterator->second->actors;

                for (int j = 0; j < actors.size(); j++) {
                     auto actor_iterator2 = aMap.find(actors[j]);
                     if (actor_iterator2->second->dist == -1){
                     actor_iterator2 ->second->dist += curr->dist;
                     actor_iterator2->second->prev = curr;
                     q.push(actor_iterator2->second);
                     }
                }
            }
        }   
        return nullptr;

    
}


