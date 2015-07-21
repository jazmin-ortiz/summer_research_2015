/**
 * FrequentPairs.cpp
 *
 * Author: Jazmin Ortiz
 *
 * Implementation of the FrequentPairs class
 *
 */

#include <string>
#include <fstream>
#include <vector>

#include "FrequentPairs.hpp"

using namespace std;

// Default constructor for FrequentPairs
FrequentPairs::FrequentPairs()
{
  // Do nothing
}

// Destructor for FrequentPairs
FrequentPairs::~FrequentPairs()
{
  // Do nothing
}

/**
 * function: get_sequence()
 *
 * Returns a reference to the Sequence_ private data member
 */
vector<size_t>& FrequentPairs::get_Sequence()
{
  vector<size_t>& sequence = Sequence_;

  return sequence;

}

/**
 * function: readIn(ifstream& inputstream)
 *
 * Reads in from standard in and changes the Sequence_ data member
 * apropriately using the insert function.
 */
void FrequentPairs::readIn(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variable to hold the LBAs that are
  //read in as string from stdin
  char c;
  string current_LBA = "";
  while (inputstream.get(c)) {

    // Makes sure that stream closes if eof char is seen
    if (inputstream.eof()){

      return;

    }
    // Checks if a newline has been encountered which means that the
    // the current LBA has been completed and if so inserts it into the
    // Sequence_ vector.
    else if ( c == '\n' ) {

      insert(current_LBA);
      current_LBA = "";

    }

    // If a newline char has not been seen continues to push chars onto
    // current_LBA
    else {

      current_LBA.push_back(c);

    }

  }

  inputstream.close();
}

/**
 * function: insert(std::string LBA_to_add)insert
 *
 * Takes in a string and adds it to the end of the Sequence_data member.
 *
 */
void FrequentPairs::insert(string LBA_to_add)
 {
   // size_t version of the LBA
   size_t added_LBA = stoi(LBA_to_add);

   Sequence_.push_back(added_LBA);
 }

