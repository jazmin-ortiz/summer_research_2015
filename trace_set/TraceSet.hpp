
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
* contains the location of  that LBA and the index of the first
* instance of  that LBA in Sequence_. This data member allows for
* quick look up of the location that is associated with a given LBA
*
* (3) The third vector mapLocation_, is indexed by location on disc and holds a
* struct which contains the LBA associated with that location. This data member
* allows for quick look up of the location  that is associated with a given LBA
*
* NOTE: For this Data Structure the disk is represented as a
* 1d array. In order to test algorithms each LBA is assigned a location which is 
* an index in the 1d arry, however this is not the actual location since the
* actual location is known only by the disk manufacturers. The variable called
* location, represents the index in the 1d array representation of the disk that 
* contains our approxmition of a given LBAs location.
*
* The quality of the algorithms are tested against one another using the metric
* of "total seek distance" which is calculated by the total_seek_distance()
* function which finds the "total distance" which is said to be the sum of the
* absolute value of differences of locations associated with consecutive LBAs in
* the Sequence_ vector.
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
   * struct: Line
   *
   *  A struct used to describe a single access for some LBA
   *  and the next access in sequence that has the same LBA.
   */
  struct Line {

    size_t next;                  // index to the next occurence of the LBA in
                                  // the vector.

    size_t LBA;                   // int representation of the LBA

  };

  /*
   *  struct: blockLBA
   *
   *  A struct to keep track of the logical blocks used in the trace
   *  and the locations that those blocks are mapped to which we refer
   *  to as location.
   */
  struct blockLBA{

    size_t first;             // Index to the first time that LBA
                              // occurs in the Sequence_ vector

    size_t last;              // Index of the last time the LBA occurs in
                              // the Sequence_ vector

    size_t location;          // Please note that this is not the actual
                              // physical block address since this is not known
                              // to anyone but the disk manufacturers. This
                              // variable actually represents our approximation
                              // of that location

    bool used = false;        // A boolean to indicate whether this LBA is
                              // used in the trace
  };

  /*
   *  struct: location
   *
   *   A struct to keep track of our approximation of the locations  associated
   *   with the LBAs used in the trace. This struct contains a size_t which
   *   represents an LBA.
   */
  struct LBA_location{

    size_t LBA;               // A size_t which represents a LBA

    bool used = false;        // A bool which represents if the given
                              // location has been used.

  };

  /// Returns a reference to the Sequence_ private data member
  std::vector<Line>& get_Sequence();

  /// Returns a reference to the mapLBA_ private data member
  std::vector<blockLBA>& get_mapLBA();

  /// Returns a reference to the mapPBA_ private data member
  std::vector<LBA_location>& get_locations();

  /// Adds a string which defines a LBA address and and adds it to the end
  /// of the Sequence_ vector and updates data members apropriately.
  void insert(std::string LBA_to_add);

  /// Reads in a text file where each line in the text file contains a LBA
  /// and adds each LBA in the text file to the TraceSet data members
  /// apropriately.
  void readIn(std::ifstream& inputstream);

  /// Reads in a text file where each line in the text file contains
  /// a frequent LBA, which will be part of the "hot" partition in our
  /// final disk arrangment.
  std::vector<std::size_t> readLBAs(std::ifstream& inputstream);


  /// This function takes in a size_t which is an LBA and returns
  /// a vector of size_ts which represent the indices of all
  /// occurences of the given LBA in the TraceSet private data member
  /// Sequence_.
  std::vector<std::size_t> get_indices(std::size_t LBA_to_find);

  /// This finds and returns the sum of the distances between two adjacent
  /// LBAs in the Sequences vector.
  ///
  /// The distance between two LBAS is the absolute value
  /// of the difference of thier respective location values.
  std::size_t total_seek_distance();

  /// This function takes in a vector of size_ts that are LBAs in the
  /// mapLBA_ vector and a size_t start, where the ordeor of the LBAs in
  /// the vector represents a reordering of the locations that are associated
  /// with these LBAs.
  ///
  /// This function alters the LBA_locations structs and location associated
  /// with the LBAs in the mapLBA_ and locations_ vectors, so that the locations
  /// of the LBAs in the input vector are consecutive and in the order that they
  /// appear in the input vector, and also begin at the size_t called start.
  ///
  /// The locations of the LBAs that are not in the input vector will then be
  /// shifted so that no LBAs have the same location.
  void change_locations(std::vector<std::size_t> LBA_vector, std::size_t start);

  /// This is a helper function for change_location, the function takes in a
  /// a vector of size_ts, LBA_vector, and removes the LBA_locations struct
  /// associated with these LBAs from the locations_ vector while still
  /// preserving the structure and spacing of the other locations with respect
  /// to one another
  void remove_LBA_locations(std::vector<std::size_t> LBA_vector);

  /// This is a helper function for change_locations, when run it goes through
  /// the TraceSet object and makes sure that for any given LBA that it is
  /// a single and unique location across both the mapLBA_ and location_
  /// vectors. If a discrepancy is seen, meaning that for some LBA, the LBA is
  /// assigned different locations_ in the mapLBA_ and locations_ data members
  /// then it will change the location assigned to the LBA in mapLBA_ to match
  /// the LBA in locations_.
  void fix_locations();

private:

  // Sequence_ is an vector of TraceSet structs, which together contain
  // the entirety of the trace. The indices of Sequence_ correspond to the order
  // access.
  //
  // The struct at index i contains information concerning the i LBA accessed,
  // this struct contains:
  // (1) The LBA which is accessed
  // (2) The index of the next instance of that LBA in the trace.
  // (3) A bool which represents if this is the last occurence of that LBA
  // in the trace.
  std::vector<Line> Sequence_;

  // mapLBA_ is a vector of structs, each struct contains information pertaining
  // to a specfic LBA in the trace and the mapLBA_ vector contains a struct for
  // every LBA contained within the trace. The indices of mapLBA_ correspond to
  // LBAS so the struct at index i has information about the LBA whose value is
  // i.
  //
  // The struct at index i contains;
  // (1) A size_t called location which represents our approxmiation of
  // the location LBA i  maps to.
  // (2) The index of the first and las instance of LBA i within the trace.
  //
  // This data member allows for quick look up and access of locations when
  //given a LBA.
  std::vector<blockLBA> mapLBA_;

  // locations_ is a vector of LBA_location structs, indexed by location,
  // The struct at index i contains:
  // (1) The LBA which is currently mapped to this location.
  // (2) A bool which corresponds to if there is an LBA currently mapped to this
  // location.
  //
  // This data member allows for quick look up of LBAs when given a location.
  std::vector<LBA_location> locations_;

};

#endif // TRACESET_HPP_INCLUDED

