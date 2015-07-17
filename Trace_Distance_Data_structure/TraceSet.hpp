/**
* TraceSet.hpp
*
* Authors: Jazmin Ortiz
*
* This is a class callled TraceSet, this class was made to test algorithms that
* try to optimize the location of memory on the disk. This class is made up of
* three private data members which are vectors:
*
* (1) The first vector Sequence_, is a vector of structs where each struct
* contains a size_t which is an LBA and another size_t which represents the
* next occurence of that LBA in the vector. This vector is used to represent
* a trace.
*
* (2) The second vector mapLBA_, is indexed by LBA and holds a struct which
* contains the PBA associated with that LBA and a pointer to the first
* instance of  that LBA in the first vector. This data member allows for
* quick look up of a PBA that is associated with a given LBA
*
* (3) The third vector mapPBA__, is indexed by PBA and holds a struct which
* contains the LBA associated with that PBA. This data member allows for quick
* look up of a PBA that is associated with a given LBA
*
* NOTE: For this Data Structure the disk is represented as a
* 1d array. In order to test algorithms each LBA is assigned a variable
* called PBA which is not the actual PBA since the actual PBA is known only
* by the disk manufacturers. The variable called PBA, represents the
* index in the 1d array representation of the disk that a given LBA is located.
* The quality of the algorithms are tested against one another using the metric
* of "total distance" which is calculated by the find_total_distance() function
*  which finds the "total distance" which is said to be the sum of the
* absolute value of differences of PBAs associated with consecutive LBAs in the
* Sequence_ vector.
*
*
*/

#ifndef TRACESET_HPP_INCLUDED
#define TRACESET_HPP_INCLUDED 1

#include <string>
#include <vector>



class TraceSet{

public:

  ///<Constructor creates an empty traceset.
  TraceSet();

  ///<Destructor.
  ~TraceSet();

  /*
   *    A struct used to describe a single access for some LBA
   *    and the next access in sequence that has the same LBA.
   */
  struct Line {

    size_t next;                  // Index to the next occurence of the LBA in
                                  // the vector.

    size_t LBA;                   // Int representation of the LBA

  };

  /*
   *   A struct to keep track of the logical blocks used in the trace
   *       and the locations that those blocks are mapped to which we refer
   *       to as PBA.
   */
  struct blockLBA{

    size_t first;             // Index to the first time that LBA
                              // occurs in the traceSequence_ vector

    size_t last;              // Index of the last time the LBA occurs in
                              // the traceSequence_ vector

    size_t PBA;               // Please note that this is not the actual
                              // physical block address since this is not known
                              // to anyone but the disk manufacturers. This
                              // variable actually represents the location that
                              // the LBAs are mapped which may be changed.

    bool used = false;        // A boolean to indicate whether this LBA is
                              // used in the trace
  };

    /*
   *   A struct to keep track of the physical blocks associated with the
   *       LBAs used in the trace. This struct contains a size_t which
   *       represents an LBA.
   */
  struct blockPBA{

    size_t LBA;               // A size_t which represents a LBA

    bool used = false;        // A bool which represents if the given
                              // PBA has been used.

  };

  /// Returns a reference to the Sequence_ private data member
  std::vector<Line>& get_Sequence();

  /// Returns a reference to the mapLBA_ private data member
  std::vector<blockLBA>& get_mapLBA();

  /// Returns a reference to the mapPBA_ private data member
  std::vector<blockPBA>& get_mapPBA();

  /// Adds a string which defines a LBA address and and adds it to the end
  /// of the traceSequence vector and updates data members apropriately.
  void insert(std::string LBA_to_add);

  /// Reads in a text file where each line in the text file contains a LBA
  /// and adds each LBA in the text file to the TraceSet data members
  /// apropriately.
  void readIn(std::ifstream& inputstream);


  /// This function takes in a size_t which is an LBA and returns
  /// a vector of ints which represent the indices of all
  /// occurences of the given LBA in the TraceSet private data member
  /// traceSequence_.
  std::vector<size_t> get_indices(size_t LBA_to_find);

  /// This finds and returns the sum of the distances between two adjacent
  /// LBAs in the Sequences vector.
  ///
  /// This distance between two LBAS is the absolute value
  /// of the difference of thier respective PBA values.
  size_t find_total_distance();

  /// This function takes in a vector of size_ts that are LBAs in the
  /// mapLBA_ vector and a size_t start, where the order of the LBAs in
  /// the vector represents a reordering of the PBAs that are associated
  /// with these LBAs.
  ///
  /// This function alters the PBAs associated
  /// with the LBAs in the mapLBA_ and mapPBA_ vectors, so that the PBAs of
  /// the LBAs in the input vector are consecutive and in the order that they
  /// appear in the input vector and begin at the size_t start,
  ///
  /// The PBAs of the LBAs that are not in the input vector will then be
  /// shifted so that no LBAs have the same PBA.
  void change_order_PBA(std::vector<std::size_t> LBA_vector, std::size_t start);

  /// This is a helper function for change_PBAS, the function takes in a
  /// a vector of size_ts, LBA_vector, and removes the blockPBA struct
  /// associated these LBAs from the mapPBA vector while still preserving the
  /// structure and spacing of the other PBAs
  ///
  /// The function takes the vector of size_ts which represent LBAS and finds
  /// the PBA associated with each LBA in the vector LBAs and removes it from
  /// the mapPBA_ data member of trace_to_consider.
  void shift_PBAs_up(std::vector<std::size_t> LBA_vector);

  /// This is a helper function for change_PBAs when this is run it goes through
  /// TraceSet object and makes sure that each for any given LBA that it is
  /// a single and unique PBA across both the mapLBA_ and mapPBA_ vectors.
  /// If a discrepancy is seen, meaning that for some LBA, the LBA is assigned
  /// different PBAs in the mapLBA_ and mapPBA_ data members then it will change
  /// the PBA assigned to the LBA in mapLBA_ to match the LBA in mapPBA_.
  void fix_PBAs();

private:

  // Sequence_ is an array of traceLine structs.  Together it contains
  // the entirety of the trace, and the index of the next instance of that
  // LBA in the trace.
  std::vector<Line> Sequence_;
  
  // mapLBA_ is a vector of structs that contain (1) the LBA of everything
  // in the trace, (2) the physical block address that each LBA maps to, and
  // (3) the index of the first and last instance of that address within the
  // trace. This data member allows for quick look up and access for PBAs
  // when given a LBA.
  std::vector<blockLBA> mapLBA_;

  // mapPBA_ is a vector of blockPBA_ structs which is indexed by PBA, this
  // data member allows for quick look up of LBAs when given a PBA.
  std::vector<blockPBA> mapPBA_;

};

#endif // TRACESET_HPP_INCLUDED
