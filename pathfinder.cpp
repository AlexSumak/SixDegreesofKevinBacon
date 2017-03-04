
#include "ActorGraph.h"
#include <fstream>                                                              
#include <iostream>                                                             
#include <sstream>                                                          
#include <string>                                                               
#include <vector>                                                               
//#include "ActorGraph.cpp"        
#include "Edge.h"

int main(int argc, char* argv[])
{


    if(argc < 5){
        cerr << "Incorrect number of args" << endl;
        return -1;
    }


    string filename =argv[1];//mov_cast_filename
    if(filename.length() < 1){
        return -1;
    }

    string weight = argv[2];//weightedString
    if(weight != "w" && weight != "u"){
        cerr << "it should be 'w' or 'u'" << endl;
        return -1;
    }

    bool isWeighted = (weight == "w");  //weighted 

    //    string testString = *(++argv);//test_pair_filename
    //   string outputString = *(++argv);//output_filename
    ActorGraph g;
    g.loadFromFile(argv[1], isWeighted);

    string actor1 = "BEN";
    string actor2 = "MATT";

    ifstream infile(argv[3]);//readPairFile
    ofstream outfile(argv[4]);//outputFile

    if(!outfile.is_open()){
        cerr << "Can't write to file: " << endl;
        return -1;
    }

    if(infile.is_open()){
        bool header = false;//have_header

        outfile << "(actor)--[movie#@year]-->(actor)--...:" << endl;

        while (infile) {
            string temp;//s


            if (!getline( infile, temp )) break;

            if (!header) {
                header = true;
                continue;
            }

            istringstream ss( temp );
            vector <string> record;//record

            while (ss) {
                string nextString;//next


                if (!getline( ss, nextString, '\t' )) break;

                record.push_back( nextString );
            }

            if (record.size() != 2) {

                continue;
            }

            string first(record[0]); //first_actor
            string second(record[1]);//second_actor

            ActorGraph a;

            vector<string> returnPath = a.shortestPath(first, second);


            if (returnPath.size() > 2) outfile << "(" << *returnPath.end() << ")--["; 
            cout<<record.empty()<<endl;
            cout<<"enything"<<endl; 
            returnPath.pop_back();
            cout<<"enything"<<endl;
            int index = 0;
            while (returnPath.size() != 0) {
                outfile << returnPath.back();
                if (index % 2 == 0) {
                    outfile << "]-->(";
                }
                else {
                    outfile << ")--[";
                }
                index++;

                returnPath.pop_back();
            }

            for (auto aMap_it = g.aMap.begin(); aMap_it != g.aMap.end(); ++aMap_it) {
                aMap_it->second->prev = nullptr;
                aMap_it->second->movie_edge = "";
            }
            for (auto mMap_it = g.mMap.begin(); mMap_it != g.mMap.end(); ++mMap_it) {
                mMap_it->second->prev = nullptr;
                mMap_it->second->movie_edge = "";
            }
            /*string output = "";
              bool succeed;
              succeed = BFS(first, second);

              if(succeed) {
              auto curr = findNode(dst);
              stack<string> path;
              while(true) {
              path.push("(" + curr->name + ")");

              if(curr->prevMovie != "")
              path.push("--[" + curr->prevMovie + "#@" + to_string(curr->prevYear) + "]-->");

              if(curr->prevNode)
              curr = curr->prevNode;
              else
              break;
              }

              }*/


            cerr << "Can't open file: " << endl;
        }
    }
}
