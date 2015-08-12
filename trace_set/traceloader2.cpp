/*
 *  traceloader2.cpp
 *
 *  Author:         Elizabeth Krenkel, modified code from Jazmin Ortiz. 
 *  Date Modified:  August 11, 2015
 *
 *  Description:    A modified traceloader function, which does the same thing 
 *                  as traceloader.cpp but takes in arguments from the 
 *                  command line.  
 */

#include <string>
#include <iostream>
#include <fstream>

#include "TraceSet.hpp"

using namespace std;

int main( int argc, char* argv[])
{
    string file_to_load;
    string freqLBASeq; 
    bool calcInitial; 
    for (int i = 1; i < argc; ++i){
        if (i + 1 != argc){
            cout << argv[i] << endl; 
            if (!strcmp(argv[i], "-t")){
                file_to_load = argv[i + 1];
                cout << "set file to load to: " << LBAmapping << endl; 
            }
            if (!strcmp(argv[i], "-l")){
                traceName = argv[i + 1]; 
                cout << "set LBA sequence file to: " << traceName << endl; 
            }
            if (!strcmp(argv[i], -s)){
                calcInitial = 1; 

            }
        }
    }

    // Creates fstream objects which hold the contents of the
    // files input by the user.
    ifstream tracefile(file_to_load);

    ifstream LBAFile(freqLBASeq);

    // Returns an error message if one of the files does not exist.
    if(!tracefile) {
        cout << file_to_load << " does not seem to exist. " << endl;
    }
    if (!LBAFile){
        cout << freqLBASeq << " does not seem to exist." << endl;
    }
    else {
        //Otherwise, loads the files into the traceset.

        // Creates a TraceSet object
        TraceSet trace;

        trace.readIn(tracefile);
        //If we only want the initial distance, then we just calculate
        //    the initial distance and do nothing else. 
        if (calcInitial){
            cout << "Initial: " << trace.total_seek_distance() << endl; 
        }

        else{
            trace.change_locations(trace.readLBAs(LBAFile), 0);
            cout << trace.total_seek_distance() << endl;
        }
    }
  return 0;
}

