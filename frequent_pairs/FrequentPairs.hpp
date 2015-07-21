/**
 * FrequentPairs.hpp
 *
 * Author: Jazmin Ortiz
 *
 * A small data structure that reads in a .txt file and finds and can returns
 * different information about the frequency of LBAs, pairs of succesive LBAS
 * and different information concerning the top most frequent LBAs.
 *
 */

#ifndef FREQUENTPAIRS_HPP_INCLUDED
#define FREQUENTPAIRS_HPP_INCLUDED 1

#include <vector>


class FrequentPairs{

public:

  /**
   * Constructor creates an empty frequentpairs object.
   */
  FrequentPairs();

  /**
   * Destructor.
   */
  ~FrequentPairs();

  /**
   * function:  get_Sequence()
   *
   * Returns a reference to the Sequence_ private data member
   */
  std::vector<size_t>& get_Sequence();

  /**
   * function: readIn(std::ifstream& inputstream
   *
   * Reads in a text file where each line in the text file contains a LBA
   * and adds each LBA in the text file to the FrequentPairs data members
   * apropriately.
   */
  void readIn(std::ifstream& inputstream);

  /**
   * function: insert(std::string LBA_to_add)
   *
   * Adds a string which defines a LBA address and and adds it to the end
   * of the traceSequence vector and updates data members apropriately.
   */
  void insert(std::string LBA_to_add);

  /**
   * function: most_frequent(size_t top_most_frequent)
   *
   * This function returns a vector of size_ts which represent the most frequent
   * LBAS in the sequence_ data member from most to least frequent. The length
   * of the vector returned is specified by the input value top_most_frequent.
   *
   */
  std::vector<std::size_t> most_frequent(size_t top_most_frequent)

private:

  /**
   * Sequence_ is a vector of size_ts that represents the original ordering of
   * LBAs in the .txt that is read in.
   */
  std::vector<size_t> Sequence_;
};

#endif // FREQUENTPAIRS_HPP_INCLUDED

