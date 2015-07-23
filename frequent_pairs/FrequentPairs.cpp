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
 * function: get_Sequence()
 *
 * Returns a reference to the Sequence_ private data member
 */
vector<size_t>& FrequentPairs::get_Sequence()
{
  vector<size_t>& sequence = Sequence_;

  return sequence;

}

/**
 * function: get_FrequentLBAsTable()
 *
 * Returns a reference to the FrequentLBAsTable_ private data member
 */
unordered_map<size_t, size_t>& FrequentPairs::get_FrequentLBAsTable()
{
  unordered_map<size_t, size_t>& table = FrequentLBAsTable_;

  return table;

}

/**
 * function: get_FrequentLBAs()
 *
 * Returns a reference to the FrequentLBAs_ private data member
 */
vector<size_t>& FrequentPairs::get_FrequentLBAs()
{
  vector<size_t>& frequentLBAs = FrequentLBAs_;

  return frequentLBAs;

}

/**
 * function: readInSequence(ifstream& inputstream)
 *
 * Reads in LBAs from standard in and inserts LBAs into the
 * Sequences_ data member.
 */
void FrequentPairs::readInSequence(ifstream& inputstream)
{

  char c;
  string current_LBA = "";
  while (inputstream.get(c)) {

    if (inputstream.eof()){

      return;

    }

    // If current LBA has been completed, inserts it into the
    // Sequence_ vector.
    else if ( c == '\n' ) {

      insert_LBA_into_Sequence(current_LBA);

      current_LBA = "";

    }

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

  char c;
  string current_LBA = "";
  while (inputstream.get(c)) {

    if (inputstream.eof()){

      return;

    }

    // Please note that here, there is an assumption that every LBA that is read
    // in is unique, if this is not the case there will be more than one element
    // in the FrequentLBAs_ vector that will contain the same LBA and the
    // FrequentLBAsTable will only have the index of the first element, which is
    // inaccurate.
    else if ( c == '\n' ) {


      insert_Frequent_LBA(current_LBA);

      current_LBA = "";

    }

    else {

      current_LBA.push_back(c);

    }

  }

  inputstream.close();


}

/**
 * function: insert_LBA_into_Sequence(string LBA)
 *
 * Helper function for readInSequence(). Takes in a string s which is a LBA
 * and inserts it at the end of the the Sequence_ data member
 */
void FrequentPairs::insert_LBA_into_Sequence(string LBA)
{

  size_t LBA_to_add = stoi(LBA);

  Sequence_.push_back(LBA_to_add);

}

/**
 * function: insert_LBA_into_Sequence(string LBA)
 *
 * Helper function for readInFrequentLBAs(). Takes in a string s which is a
 * LBA and inserts into the FrequentLBAsTable_ and FrequentLBAs_ data member
 * and updates them properly.
 *
 * NOTE: There is an implicit assumption that every frequent LBA that is read
 * in is unique, so if the LBA to insert has already occured in
 * FrequentLBAsTable_ and FrequentLBAs_ then this function will not update the
 * these data member properly.
 */
void FrequentPairs::insert_Frequent_LBA(string LBA)
{

  size_t LBA_to_add = stoi(LBA);

  FrequentLBAs_.push_back(LBA_to_add);

  // The index of the LBA in FrequentLBAs_ will its value in FrequentLBAsTable_
  // since the LBA was just pushed back onto FrequentLBAs_ it will be the last
  // element in the vector meaning that its index is FrequentLBAs_.size()-1.
  size_t LBA_index = FrequentLBAs_.size() - 1;

  FrequentLBAsTable_.emplace(LBA_to_add, LBA_index);

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
  // FrequentLBAsTable_.end() so iterator pointing at end is intialized.
  unordered_map<size_t, size_t>::iterator end_it = FrequentLBAsTable_.end();

  for (size_t i = 0; i < LBAs_; ++i) {

    LBA = Sequence_[i];
    next_LBA = Sequence_[i+1];

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
      // the values held at indices (LBAs_value, next_LBAs_value) and
      // (next_LBAs_value, LBAs_value) will both be incremented by 1 since these
      // appear consecutively in Sequences_.
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
  
