/*
 *  traceloader.cpp
 *
 *  Author: Jazmin Ortiz
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

  // Reads the name of a trace file and puts it into string file_to_load
  string file_to_load;
  cin >> file_to_load;

  // Reads in the name of a list of hot LBAs and puts it into string
  // freqLBASeq.
  cout << "Please choose a list of frequent LBAs" << endl;
  string freqLBASeq;
  cin >> freqLBASeq;

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

    cout << "Total initial seek distance is: " ;
    cout << trace.total_seek_distance() << endl;

    trace.change_locations(trace.readLBAs(LBAFile), 0);

    cout << "Total final seek distance is:   " ;
    cout << trace.total_seek_distance() << endl;

  }

  return 0;

}

