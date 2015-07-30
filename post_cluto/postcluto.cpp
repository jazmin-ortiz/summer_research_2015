/*
 *  postCluto.cpp
 *
 *  Author: Elizabeth Krenkel
 *  Last Modified: June 22, 2015
 *
 */

#include <string>
#include <iostream>
#include <fstream>

#include "cluster_parse/ClusterParse.hpp"
#include "trace_set/TraceSet.hpp"

using namespace std;

int main( int argc, char *argv[]){
    string LBAmapping; 
    string clutoName; 
    string traceName; 
    bool initialDistance = false; 
    for (int i = 1; i < argc; ++i){
        if (i + 1 != argc){
            cout << argv[i] << endl; 
            if (!strcmp(argv[i], "-m")){
                LBAmapping = argv[i + 1];
                cout << "set LBAMappint to " << LBAmapping << endl; 
            }
            if (!strcmp(argv[i], "-t")){
                traceName = argv[i + 1]; 
                cout << "set tracename to " << traceName << endl; 
            }
            if (!strcmp(argv[i], "-c")){
                clutoName = argv[i + 1]; 
                cout << "set ClutoName to " << clutoName << endl; 
            }
            if (!strcmp(argv[i], "-i")){
                initialDistance = true; 
                cout << "set initialDistance to " << endl; 
            }
        }
    }
    ifstream clutoFile(clutoName);
    ifstream mapping(LBAmapping);
    ifstream traceFile(traceName); 
    /* If there's a problem with one of the files, throw an error. */ 
    if((!clutoFile) || (!mapping)  || (!traceFile)){
        cout << "One of the input files does not exist." << endl; 
    } 
    else{
        /*The body of the function.  Make a clusterParse object and
         *    read the cluto file into it. */  
        ClusterParse cluster; 
        cluster.readIn(clutoFile, false);
        /* Read in the mapping of objects in the cluto file. */ 
        vector<size_t> remap = cluster.readRemap(mapping); 
        /* Correct that mapping when we format the output of cluto. */ 
        vector<size_t> LBAList = cluster.formatOutput(remap);  

        /* Having obtained our list of frequent LBAs in the order 
         *      that we request/require/desire, we move on and create
         *     a TraceSet. */ 
        TraceSet trace; 
        /* We read in our trace file. */ 
        trace.readIn(traceFile); 
        if(initialDistance){
            cout << "total initial seek distance is: " << 
                         trace.total_seek_distance() << endl; 
        }
        //We change the locations within the tracefile. 
        trace.change_locations(LBAList, 0);
        cout << "total seek distance is: " << trace.total_seek_distance() << endl;
    }
    return 0; 
}



