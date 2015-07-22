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
#include <unordered_map>

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
      Sequence_.push_back(LBA_to_add);

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
void FrequentPairs::readInFrequentLBAs(ifstream& inputstream)
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

      LBA_to_add = stoi(current_LBA);

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

/**
 * function: fillInFrequentMatrix()
 *
 * This function creates an adjacency matrix from the LBAs in FrequentLBAs_.
 * This is an n by n matrix where each row/column corresponds to a frequent LBA
 * that was mapped to that index in the FrequentLBAs_ vector, the value at
 * index (i,j) is the number of times that the LBAS mapped to i and j are
 * consecutive in the Sequences_ data member.
 */
std::vector<std::vector<std::size_t>> FrequentPairs::fillInFrequentMatrix()
{

  // The matrix will be an n by n matrix where n is the number of LBAs in
  // FrequentLBAs_, so here we create a varaiable which is the number of LBAs.
  size_t num_LBAs = FrequentLBAs_.size();

  // Initialize a vector of vectors of size_ts of the correct size
  vector<vector<size_t>> adjacency_matrix(num_LBAs, vector<size_t>(num_LBAs));

  // Loop through and set all size_ts to 0 in adjacency matrix to 0 so that we
  // can later increment these values to reflect the number of times frequent
  // LBAs are adjacent accurately.
  for (size_t j = 0; j < num_LBAs; ++j) {
    for (size_t i = 0; i < num_LBAs; ++i) {

      adjacency_matrix[j][i] = 0;

    }
  }

  // Now that all values in the adjacency matrix have been set to 0, the
  // adjacency matrix will now be filled by looping through the Sequence_
  // matrix and for each value checking if it and the following LBA are frequent
  // by checking if they are in the hash table FrequentLBAsTable_.
  //
  // If they are both frequent then thier values, i and j in the in the
  // FrequentLBAsTable_ will be thier indices in the FrequentLBAs_ vector and
  // therefore also be thier row/column in adjacency_matrix, so we will use
  // thier values to properly increment the elements at indices (i,j) and (j,i)
  // in the adjacency matrix by 1.
  //
  // If they are not both frequent then nothing will happen and the next LBA
  // in Sequences_ will be considered.

  // Temp variables for the following loop
  unordered_map<size_t, size_t>::iterator LBA_it;
  unordered_map<size_t, size_t>::iterator next_LBA_it;
  size_t LBA;
  size_t next_LBA;
  size_t LBAs_index;
  size_t next_LBAs_index;
  size_t new_value;

  // Since we are comparing an LBA and the following LBA if we loop all the way
  // until the last element and try to check the last element against the
  // following LBA that will cause undefined behavior, so we will set our
  // loop upper bound as the Sequence_ size minus 1.
  size_t LBAs_ = Sequence_.size() - 1;

  // We will be check if iterators are pointing at
  // FrequentLBAsTable_.end() and FrequentLBASTable_ will not be
  // altered in this function so an iterator pointing at end() will be
  // initialized so that FrequentLBAsTable_.end() will be called only once.
  unordered_map<size_t, size_t>::iterator end_it = FrequentLBAsTable_.end();

  for (size_t i = 0; i < LBAs_; ++i) {

    // Set LBA and next_LBA to thier values in Sequences_
    LBA = Sequence_[i];
    next_LBA = Sequence_[i+1];

    // Set iterators LBA_it and next_LBA_it to be equal to iterators that
    // are returned when find is called on thier corresponding LBAs, LBA and
    // next_LBA
    LBA_it = FrequentLBAsTable_.find(LBA);
    next_LBA_it = FrequentLBAsTable_.find(next_LBA);

    // The iterators will be be pointing at FrequentLBAsTable_.end() if the
    // value is not in the table. If both LBA_it and next_LBA_it are not
    // pointing at the end then they are both frequent and thier corresponding
    // elements in adjacency_matrix should be incremented by 1.
    if (LBA_it != end_it && next_LBA_it != end_it) {

      // Assign LBAs_index and next_LBAs_index to the values in the hash table
      // gotten by derefrencing the values of LBAs_it and next_LBAs_it, since
      // their values in the hashtable will be thier index in FrequentLBAs_
      // and thier row/column in adjacency_matrix
      LBAs_index = LBA_it->second;
      next_LBAs_index = next_LBA_it->second;

      // These values are the indices of these LBAS in adjacency_matrix, so
      // the values held at  positions (LBAs_value, next_LBAs_value) and
      // (next_LBAs_value, LBAs_value) will both be incremented by 1 since these
      // appear consecutively in Sequences_. Increment the value held at these
      // indices by 1 since because we have seen them consecutively in Sequence_
      new_value = adjacency_matrix[LBAs_index][next_LBAs_index] + 1;

      adjacency_matrix[LBAs_index][next_LBAs_index] = new_value;
      adjacency_matrix[next_LBAs_index][LBAs_index] = new_value;

    } else {

      // Do nothing, this is the case where one of the LBAs being considered is
      // not frequent

    }

  }

  return adjacency_matrix;

}
  
