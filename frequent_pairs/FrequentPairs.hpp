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
#include <unordered_map>


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
   * function:  get_FrequentLBAsTable()
   *
   * Returns a reference to the FrequentLBAsTable_ private data member
   */
  std::unordered_map<size_t, size_t>& get_FrequentLBAsTable();

  /**
   * function:  get_FrequentLBAs()
   *
   * Returns a reference to the FrequentLBAs_ private data member
   */
  std::vector<size_t>& get_FrequentLBAs();

  /**
   * function: readInSequence(std::ifstream& inputstream)
   *
   * Reads in a text file where each line in the text file contains a LBA
   * and adds each LBA in the text file to the FrequentPairs data members
   * apropriately.
   */
  void readInSequence(std::ifstream& inputstream);

  /**
   * function: ReadInFrequentLBAs(ifstream& inputstream)
   *
   * This function reads in a .txt file which contains frequent LBAS and inserts
   * the LBAs into the FrequentLBAsTable_ data member and the FrequentLBAs_ data
   * member. FrequentLBAs_ is a vector of the frequent LBAs and
   * FrequentLBAsTable_ is a hashtable where the keys are frequent LBAs and the
   * values are the index of that LBA in FrequentLBAs_.
   *
   * NOTE: There is an implicit assumption that every LBA that is read in is
   * unique, if an LBA occurs more than once in the .txt file this function is
   * not guaranteed to insert LBAs properly.
   */
  void readInFrequentLBAs(std::ifstream& inputstream);

  /**
   * function: fillInFrequentMatrix()
   *
   * This is a function that creates a vector of vectors of size_ts that is an
   * adjacency matrix from all the LBAs in FrequentLBAs_. This is an n by n
   * matrix where each row/column i, corresponds to a frequent LBA that was
   * mapped to the index i in the FrequentLBAs_ vector, the value at index
   * (i,j) is the number of times that the LBAS mapped to i and j
   * are consecutive in the Sequence_ data member.
   */
  std::vector<std::vector<std::size_t>> fillInFrequentMatrix();

  /**
   * function: insert_LBA_into_Sequence(string LBA)
   *
   * Helper function for readInSequence(). Takes in a string s which is a LBA
   * and inserts it at the end of the the Sequence_ data member
   */
  void insert_LBA_into_Sequence(std::string LBA);

  /**
   * function: insert_LBA_into_Sequence(string LBA)
   *
   * Helper function for readInFrequentLBAs(). Takes in a string s which is a
   * LBA and pushes back the LBA onto FrequentLBAs_ and then inserts the LBA
   * into FrequentLBAsTable_ with the LBA as the key and the LBAs index in
   * FrequentLBAs_ as its value.
   *
   * NOTE: There is an implicit assumption that every frequent LBA that is read
   * in is unique, so if the LBA to insert has already occured in
   * FrequentLBAsTable_ and FrequentLBAs_ then this function will not update the
   * these data member properly.
   */
  void insert_Frequent_LBA(std::string LBA);

private:

  /**
   * Sequence_ is a vector of size_ts that represents the original ordering of
   * LBAs in the .txt that is read in.
   */
  std::vector<size_t> Sequence_;

  /**
   * FrequentLBAsTable_ is a hashtable of size_ts which are frequent LBAs in
   * Sequence_ and where the key is a frequent LBA and the value is the LBAs
   * index in the FrequentLBAs_ vector. This data member
   * allows for quick lookup of the frequent LBAs in Sequence_.
   */
  std::unordered_map<size_t, size_t> FrequentLBAsTable_;

  /**
   * FrequentLBAs_ is a vector of size_ts that represent frequent LBAs in the
   * Seuqence_ data member where each postion contains a size_t which is an LBA
   * and the index of that LBA is the size_t that the LBA is mapped to.
   */
  std::vector<size_t> FrequentLBAs_;
};

#endif // FREQUENTPAIRS_HPP_INCLUDED

