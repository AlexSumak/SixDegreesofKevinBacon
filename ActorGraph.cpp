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
            
            Node* node  = new Node(actor_name);
            aMap.insert(make_pair<string, Node*> ((string)actor_name, (Node*)node));
            aMap.find(actor_name)->second->movies.push_back(realMovie);
            cout << node->name << " " << realMovie << endl;

        }
        else{
            currActor->second->movies.push_back(realMovie);
            cout << currActor->second->name << " " << realMovie << endl;
            /*cout<<actor_name+"yes"<<endl;
            int i = 0;
            for(;i < currActor->second->movies.size(); i++){
                if (realMovie == currActor->second->movies[i])
                    cout<<currActor->second->movies[i]+"rig"<<endl;
                    break;
            }
            if(i == currActor->second->movies.size()-1)
                cout<<"righteous"<<endl;
                currActor->second->movies.push_back(realMovie);*/
        }

        if(currMovie == mMap.end()){


            Edge* edge  = new Edge(realMovie);                                 
            mMap.insert(make_pair<string, Edge*> ((string)realMovie, (Edge*)edge));
            mMap.find(realMovie)->second->actors.push_back(actor_name);
            cout<<actor_name<<endl;
        }
        else{

            currMovie->second->actors.push_back(actor_name);
            cout<<actor_name<<endl;

            /*int i = 0;
            for(;i < currMovie->second->actors.size(); i++){
                if (actor_name == currMovie->second->actors[i])
                    break;
            }
            if(i == currMovie->second->actors.size()-1)
                currMovie->second->actors.push_back(actor_name);*/
        }
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}




    Node* ActorGraph::BFS(string a1, string a2){
        queue<Node*> q;
        auto actor_iterator = aMap.find(a1);
        if (actor_iterator == aMap.end()){
            return nullptr;
        }
        actor_iterator->second->dist = 0;
        
        cout<<actor_iterator->second<<endl;
        q.push(actor_iterator->second);  
        Node* curr;
        cout<<q.size()<<endl;
        while(!q.empty()){
            
            curr = q.front();
            q.pop();

            if(curr->name == a2) 
               return curr;

            vector<string> movies = actor_iterator->second->movies;

                cout << curr->name << " " << movies.size() << endl;

            for(int i = 0; i < movies.size() ; i++) {
                cout<<movies[i]<<endl;
                auto movie_iterator = mMap.find(movies[i]);
                vector<string> actors = movie_iterator->second->actors;

                for (int j = 0; j < actors.size(); j++) {
                     cout << actors[j] << endl;
                     auto actor_iterator2 = aMap.find(actors[j]);
                     if (actor_iterator2->second->dist == -1){
                     actor_iterator2 ->second->dist += curr->dist;
                     actor_iterator2->second->prev = curr;
                     actor_iterator2->second->movie_edge = movies[i];
                     q.push(actor_iterator2->second);
                     }
                }
            }
        }  
        return nullptr;

    
}

    vector<string> ActorGraph::shortestPath(string first, string second) {
        vector<string> returnString;
        Node* temp = BFS(first, second);
        while (temp != nullptr) {
            returnString.push_back(temp->name);
            if (temp->movie_edge != "") {
                returnString.push_back(temp->movie_edge);
            }
            temp = temp->prev;
        }
        return returnString; 
    }
