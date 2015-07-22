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
 * Reads in a .txt where each line contains a single unique element
 * which represents a frequent LBA, and inserts that value into the
 * FrequentLBAsTable_ data member and the FrequentLBAs_ data member, where
 * FrequentLBAs_ is a vector of the frequent LBAs and FrequentLBAsTable_ is a
 * hashtable where the keys are frequent LBAs and the values are the index of
 * that LBA in FrequentLBAs_.
 */
void FrequentPairs::ReadInFrequentLBAs(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variables to hold and insert the LBAs
  // that are read in as a string from stdin
  char c;
  string current_LBA = "";
  size_t LBA_to_add;
  size_t LBAs_index = 0;
  while (inputstream.get(c)) {

    // Makes sure that stream closes if eof char is seen
    if (inputstream.eof()){

      return;

    }

    // Checks if a newline has been encountered which means that the
    // the current LBA has been completed and if so properly inserts it into
    // FrequentLBAs_ and FrequentLBAsTable_. Please note that here there is an
    // assumption that every LBA that is read in is unique, if this is not the
    // there will be more than one element in the FrequentLBAs_ vector that will
    // contain the same LBA and the FrequentLBAsTable will only have the index
    // of the first element.
    else if ( c == '\n' ) {

      LBA_to_add = stoi(crrent_LBA);

      // push_back LBA_to_add onto the FrequentLBAs_ data member. Before pushing
      // back LBA_to_add the length of FrequentLBAs_ is equal to LBAs_index
      // meaning that LBA_to_add will be at index LBAs_index since when it is
      // pushed back.
      FrequentLBAs_.push_back(LBA_to_add);

      // Insert LBA_to_add and LBAs_index as a key value pair into the hash
      // table FrequentLBAsTable_. Please note that every LBA that is read in is
      // unique so there will never be the case where there are two element
      FrequentLBAsTable_.emplace(LBA_to_add, LBAs_index);



      // Resets the current_LBA, since the LBA has already been added
      current_LBA = "";

      // Update LBAS_index since the LBA has been pushed back
      ++LBAs_index;

    }

    // If a newline char has not been seen continues to push chars onto
    // current_LBA
    else {

      current_LBA.push_back(c);

    }

  }

  inputstream.close();


}
  
