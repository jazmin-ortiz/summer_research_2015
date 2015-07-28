/*
 *  traceloader.cpp
 *
 *  Author: Jazmin Ortiz
 *  Last Modified: June 22, 2015
 *
 *  This file contains the main function that will be used to load traces
 *  and create a TraceSet object that will be used to compare different
 *  algorithms.
 *
 */

#include <string>
#include <iostream>
#include <fstream>

#include "TraceSet.hpp"

using namespace std;

int main()
{

  // Asks for a tracefile
  cout << "Please choose a trace file to load" << endl;

  // Reads the name of a trace file and puts it into string file_to_load
  string file_to_load;
  cin >> file_to_load;

  cout << "Please choose a list of frequent LBAs" << endl; 
  string freqLBASeq; 
  cin >> freqLBASeq; 

  // Creates a fstream object tracefile which holds the contents of the
  // trace file input by the user.
  ifstream tracefile(file_to_load);

  ifstream LBAFile(freqLBASeq); 

  // Returns an error message if the tracefile does not exist otherwise loads
  // the fstream tracefile into a TraceFile object.
  if(!tracefile) {
    cout << file_to_load << " does not seem to exist. " << endl;
  }
  if (!freqLBASeq){
    cout << freqLBASeq << " does not seem to exist." << endl; 
  }

  else {

    // Creates a TraceSet object
    TraceSet trace;

    // Reads in the user input file.
    trace.readIn(tracefile);

    std::cout << "total initial seek distance is: " << trace.total_seek_distance(); 

    size_t hotPartition = (trace.get_mapLBA()).size(); 

    trace.change_locations(trace.readLBAs(LBAFile), )
  }

  return 0;

}

