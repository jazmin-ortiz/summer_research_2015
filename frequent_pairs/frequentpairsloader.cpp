/**
 * frequentpairsloader.cpp
 *
 * Author: Jazmin Ortiz
 *
 * This is the main function for FrequentPairs.cpp
 */

#include <fstream>
#include <iostream>
#include <string>


#include "FrequentPairs.hpp"

using namespace std;

int main()
{

  // Asks for a trace file to load
  cout << "Please choose a trace file to load" << endl;

  // Reads the name of a trace file and puts it into string file_to_load
  string file_to_load;
  cin >> file_to_load;

  // Creates a fstream object tracefile which holds the contents of the
  // trace file input by the user.
  fstream tracefile(file_to_load);

 // Asks for a frequent LBAs file to load
  cout<< "Please choose a frequent LBA file to load" << endl;

  // Reads the name of the frequent LBAs file and puts it into string
  // freq_LBAs_to_load
  string freq_LBAs_to_load;
  cin >> freq_LBAs_to_load;

  // Creates a fstream object frequentLBAs which holds the contents of the
  // trace file input by the user.
  fstream frequentLBAs(freq_LBAs_to_load);

   // Asks for an empty  file in which to put the adjacency matrix that will be
  // created
  cout<< "Please choose an empty file to put the adjacency matrix in" << endl;

  // Reads the name of the frequent LBAs file and puts it into string
  // freq_LBAs_to_load
  string adjacency_matrix_file;
  cin >> adjacency_matrix_file;

  // Creates a fstream object matrix  which holds the contents of the
  // empty adjacency matrix file input by the user.
  fstream matrix(adjacency_matrix_file);


  // Returns an error message if the tracefile, frequent LBA or adjacency matrix
  // file does not exist otherwise loads the files into a FrequentPairs object.
  if (!tracefile) {

    cout << file_to_load << " does not seem to exist. " << endl;

  }

  else if (!frequentLBAs) {

    cout << freq_LBAs_to_load << " does not seem to exist. " << endl;

  }

  else if (!matrix) {

    cout << adjacency_matrix_file << " does not seem to exist." << endl;

  } else {

    FrequentPairs frequentpairs;

    frequentpairs.readInSequence(tracefile);
    frequentpairs.readInFrequentLBAs(frequentLBAs);

    frequentpairs.createAsciiMatrix(adjacency_matrix_file);

  }

  return 0;

}
