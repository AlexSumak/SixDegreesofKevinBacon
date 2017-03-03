
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
            vector <string> tempVector;//record

            while (ss) {
                string nextString;//next


               if (!getline( ss, nextString, '\t' )) break;

                tempVector.push_back( nextString );
            }

            if (tempVector.size() != 2) {

                continue;
            }

            //string first(record[0]); //first_actor
            //string second(record[1]);//second_actor
            //shorestPath(first, second, outfile);
        }

    }else{
        cerr << "Can't open file: " << endl;
    }

}
