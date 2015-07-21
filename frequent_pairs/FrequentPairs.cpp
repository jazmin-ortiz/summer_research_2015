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
 * function: readInSequence(ifstream& inputstream)
 *
 * Reads in LBAs from standard in and inserts LBAs into the
 * Sequences_ data member.
 */
void FrequentPairs::readInSequence(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variables to hold and insert the LBAs
  // that are read in as a string from stdin
  char c;
  string current_LBA = "";
  size_t LBA_to_add;
  while (inputstream.get(c)) {

    // Makes sure that stream closes if eof char is seen
    if (inputstream.eof()){

      return;

    }
    
    // Checks if a newline has been encountered which means that the
    // the current LBA has been completed and if so inserts it into the
    // Sequence_ vector.
    else if ( c == '\n' ) {

      // Creates a size_t that represents the current_LBA and pushes it onto
      // the Sequence_ data member
      LBA_to_add = stoi(current_LBA);
      Sequence_.push_back(LBA_to_add);insert(current_LBA);

      // Resets the current_LBA, since the LBA has already been added
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
 * function: ReadInFrequentLBAs(std::ifstream& inputstream)
 *
 * Reads in a .txt where each line contains a single element which represents a
 * frequent LBA, and inserts that value into the FrequentLBAs_ data member which
 * is a hashtable.
 */
void FrequentPairs::ReadInFrequentLBAs(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variables to hold and insert the LBAs
  // that are read in as a string from stdin
  char c;
  string current_LBA = "";
  size_t LBA_to_add;;
  while (inputstream.get(c)) {

    // Makes sure that stream closes if eof char is seen
    if (inputstream.eof()){

      return;

    }

    // Checks if a newline has been encountered which means that the
    // the current LBA has been completed and if so inserts it into the
    // FrequentLBAs_ hashtable where both the key and the value are the
    // current_LBA.
    else if ( c == '\n' ) {

      LBA_to_add = stoi(current_LBA);
      FrequentLBAs_.emplace(LBA_to_add, LBA_to_add);

       // Resets the current_LBA, since the LBA has already been added
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
  
