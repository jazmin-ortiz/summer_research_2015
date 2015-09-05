/*
 * traceset-commandline.cpp
 *
 * Contains a main function which accepts 2 command line arguments.
 *
 * The first argument is the name of a .txt file that has a list of values
 * where each value is an LBA and the list is a list of accesses to those LBAs
 * take from some trace.
 *
 * The second argument is the name of a .txt file that has a list of values
 * which represent frequent LBAs, it is important to note that this list of
 * values cannot contain any repeated LBAs, since this could cause undefined
 * behavior in some of the TraceSet functions.
 */

#include <string>
#include <iostream>
#include <fstream>

#include "TraceSet.hpp"

using namespace std;

int main(int argc, const char** argv)
{

  // Process command-line options
  --argc;
  // Skip past 0th arg (program name)
  ++argv;

  string tracefile_to_load = *argv;

  // Move onto the next argument.
  ++argv;

  string frequentLBAs_to_load = *argv;

  // Creates fstream objects which hold the contents of the
  // files given in the commanline.
  ifstream tracefile(tracefile_to_load);
  ifstream frequentLBAs(frequentLBAs_to_load);

  // Returns an error message if one of the files does not exist.
  if(!tracefile) {
    cout << tracefile_to_load << " does not seem to exist. " << endl;
  }
  if (!frequentLBAs){
    cout << frequentLBAs_to_load << " does not seem to exist." << endl;
  }

  else {
    //Otherwise, loads the files into the traceset.

    // Creates a TraceSet object
    TraceSet trace;

    trace.readIn(tracefile);

    cout << trace.total_seek_distance() << " ";

    trace.change_locations(trace.readLBAs(frequentLBAs), 0);

    cout << trace.total_seek_distance() << endl;

  }

    return 0;
}
