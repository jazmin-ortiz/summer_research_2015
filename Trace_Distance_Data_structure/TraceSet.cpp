/*
* TraceSet.cpp
*
* Authors: Jazmin Ortiz and Elizabeth Krenkel
* Last Modified: July 13, 2015
*
* Takes in a trace file of LBAs (in decimal)  from stdin and creates a data
* structure to hold them.  Those two structures consist of a vector of all
* of the LBA as they come in (to preserve the sequence that they arrive in)
* and an array of the LBAs, indexed by the LBA divided by the block number,
* for ease of lookup.
*
* The ultimate purpose of this data structure is to help in looking at
* better ways to lay out the block on the disk drive
*
*/

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <unordered_map>

#include "TraceSet.hpp"

using namespace std;

// Default constructor for TraceSet
TraceSet::TraceSet():
  mapLBA_{1},
  mapPBA_{1}
{
  // Do nothing here`
}

// Destructor for the TraceSet
TraceSet::~TraceSet()
{
  // Do nothing here
}

/**
 * function: get_sequence()
 *
 * Returns a reference to the Sequence_ private data member
 */
vector<TraceSet::Line>& TraceSet::get_Sequence()
{
  vector<Line>& sequence = Sequence_;

  return sequence;

}

/**
 * function: get_mapLBA()
 *
 * Returns a reference to the mapLBA_ private data member
 */
vector<TraceSet::blockLBA>& TraceSet::get_mapLBA()
{
  vector<blockLBA>& blockLBAs = mapLBA_;

  return blockLBAs;
}

/**
 * function: get_mapPBA()
 *
 * Returns a reference to the mapPBA_ private data member
 */
vector<TraceSet::blockPBA>& TraceSet::get_mapPBA()
{
  vector<blockPBA>& blockPBAs = mapPBA_;

  return blockPBAs;
}

/**
 * function: insert(string LBA_to_add)
 *
 * Takes in a string which is a LBA and adds it to the end
 * of the Sequence vector and changes the mapLBA_ and mapPBA_ vectors
 * apropriately, meaning that if the LBA to insert is not currently in the
 * mapLBA_ vector that this LBA is added and sets the PBA of this LBA equal
 * to the LBA.
 *
 * NOTE This function initially sets the PBA equal to the LBA due
 * to the fact that before any algorithm is run the location of a given
 * LBA in the 1d representation of the disk should simply be the location
 * denoted by the LBA.
 *
 * NOTE: This function assumes that the trace is being read in for the first
 * time because it always sets the value of the PBA associated with a given
 * LBA equal to the PBA, which would lead to errors if that given PBA had
 * already been set.
 *
  */
void TraceSet::insert(string LBA_to_add)
{
  // size_t version of the LBA
  size_t added_LBA = stoi(LBA_to_add);

  // Initializes the traceLine object.
  Line Line_to_add;
  Line_to_add.LBA = added_LBA;

  // Adds object to Sequence_ vector
  Sequence_.push_back(Line_to_add);

  // Make sure that the LBA is in the mapLBA_vector and if it isnt
  // resizes the mapLBA_ vector apropriately. Since the mapPBA_ vector
  // contains the same information as the mapLBA vector but is instead
  // indexed by PBA, if the mapLBA_ vector needs to be resized then the
  // mapPBA_ vector will also need to be resized
  //
  // Since the last element pushed back onto Sequence_ is Line_to_add, this
  // is the index of Line_to_add
  size_t index_of_line = Sequence_.size() - 1;
  if (added_LBA >= mapLBA_.size()) {

    mapLBA_.resize(2*added_LBA);
    mapPBA_.resize(2*added_LBA);

  }

  // Variable representing the blockLBA which contains information
  // about LBA_to_add
  blockLBA& LBAs_blockLBA = mapLBA_[added_LBA];

  // Set of if statments to properly update the LBA's block map struct in the
  // mapLBA_ vector.

  // Deals with the cases where there is at least one instance of the given
  // LBA in the Sequence_ vector.
  if (LBAs_blockLBA.used) {

     // LBAs_blockLBA data members have not been updated, the data member
     // called last now is the index of the second to last
     size_t second_to_last = LBAs_blockLBA.last;

     // Update the previously last instance of LBA_to_add in Sequence_
     Sequence_[second_to_last].next = index_of_line;

  }

   // Deals with the case that LBA_to_add has not previously been in
   // Sequence_, which means that its PBA needs to be set in both the
   // mapLBA_ and mapPBA_ vector.
   else {

     // Sets the data members of LBAs_blockLBA apropriately.
     LBAs_blockLBA.first = index_of_line;
     LBAs_blockLBA.PBA = added_LBA;
     LBAs_blockLBA.used = true;

     // Sets the data members of the blockPBA which represents the given
     // LBA apropriately.
     mapPBA_[added_LBA].LBA = added_LBA;
     mapPBA_[added_LBA].used = true;

  }

  // update last data member of the LBAs_blockMap apropriately
  LBAs_blockLBA.last = index_of_line;

}

/**
 * function: readIn(ifstream& inputstream)
 *
 * Reads in from standard in and changes the Sequence_, mapLBA_ and
 * mapPBA_ private data members apropriately using the insert function.
 */
void TraceSet::readIn(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variable to hold the LBAs that are
  //read in as string from stdin in the
  char c;
  string current_LBA = "";
  while (inputstream.get(c)) {

    // Makes sure that
    if (inputstream.eof()){

      return;

    }
    // Checks if a newline has been encountered which means that the end of
    // the current LBA has been encountered and if so inserts it into the
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
 * function: get_indices(size_t LBA_to_find)
 *
 * Takes in a size_t that represents an LBA
 * and returns a vector of size_ts that are the indices of all ocurrences
 * of the given LBA in the Sequences_ vector.
 */
vector<size_t> TraceSet::get_indices(size_t LBA_to_find)
{

  // Vector which will hold the size_ts which represent the indices in
  vector<size_t> instances;


  // BlockMap that contains information pertaining to LBA_to_find
  struct blockLBA LBAs_BlockLBA = mapLBA_[LBA_to_find];

  // Checks if there are instances of the LBA by checking the LBAs_BlockMap
  // to see if that LBA has been used. If it has not been used returns the
  // vector of instances.
  if (LBAs_BlockLBA.used) {

    // Finds index of first instance then pushes index onto instances vector
    instances.push_back(LBAs_BlockLBA.first);

    // Loops through Sequence_ and finds the indices of all occurences of
    // the LBA in the Sequence_.
    //
    // Variables that will be used to loop through instances of the
    // LBA in Sequence_.
    size_t index = LBAs_BlockLBA.first;
    Line next_line = Sequence_[index];
    while (index != LBAs_BlockLBA.last) {

      // Adds the index of the next occurence of the LBA to the vector
      instances.push_back(next_line.next);

      // update loop variable
      index = next_line.next;
      next_line = Sequence_[index];

    }
}

  else {

    // Do nothing

  }

  return instances;
}

/**
 * function: find_total_distance()
 *
 * This is a function that returns the sum of the distance between two
 * consecutive access in the Sequences vector.
 *
 * The distance is said to be the absolute value of the difference of the PBAs
 * associated with the onsecutive LBAs that represent accesses in the Sequences
 * data member.
 */
size_t TraceSet::find_total_distance()
{

  // Iterators that will be used to iterate through Sequences_.
  vector<Line>::iterator current_it = Sequence_.begin();
  vector<Line>::iterator next_it = Sequence_.begin();
  ++next_it;

  // Size_ts that will be used to hold PBAs in the while looop
  size_t current_PBA;
  size_t next_PBA;
  size_t total_distance = 0;
  while (next_it != Sequence_.end()) {

    // Finds the blockLBA associated with current_it and next_it and then
    // assigns its PBA data member to respectivly to current_PBA and next_PBA
    current_PBA = mapLBA_[current_it->LBA].PBA;
    next_PBA = mapLBA_[next_it->LBA].PBA;

    // Finds the absolute values of the difference of current_PBA and next_PBA.
    // Since current_PBA and next_PBA are size_ts the smaller PBA must be
    // subtracted from the larger.
    if (current_PBA < next_PBA) {

      total_distance += next_PBA - current_PBA;

    }

    else {

      total_distance += current_PBA - next_PBA;

    }

    ++current_it;
    ++next_it;

  }

  return total_distance;
}

/**
 * function: change_PBAs(vector<size_t> LBA_vector, size_t start)
 *
 * This is a function that takes in a vector of size_ts that represent LBAs and
 * the order in which to insert them and a size_t which represents the PBA that
 * should be the PBA of the first LBA in the LBA_vector, the other LBAs in
 * LBA_vector will then be assigned a contiguous set of PBAs following start.
 * The PBAs of the LBAs will be moved so that the no new PBAs will be used but
 * spaces that existed between LBAs that are not in LBA_vector will be
 * preserved.
 *
 */
void TraceSet::change_PBAs(vector<size_t> LBA_vector, size_t start)
{

  // loops through LBA_vector, finds the PBA associated with each LBA and then
  // inserts the LBA and its associated PBA as a key-value pair into
  // PBA_hashtable, where the LBA is used as the key.
  unordered_map<size_t, size_t> PBA_hashtable;
  size_t current_LBA;
  size_t LBAs_PBA;
  for (size_t i = 0; i < LBA_vector.size(); ++i) {

    current_LBA = LBA_vector[i];

    // Sets LBAs_PBA equal to the PBA that is assigned to current_LBA in the
    // mapLBA_ data member.
    LBAs_PBA = mapLBA_[current_LBA].PBA;

    PBA_hashtable.emplace(current_LBA, LBAs_PBA);
  }

  // Loops through the mapPBA_ data member and checks the LBA associated with
  // each PBA to see if thier LBA is in the hash table. If so the PBA of that
  // LBA will be changed, and that blockPBA will be reinserted later. Therefore
  // the num_positions counter is incremented by 1 and all blocks after that
  // are moved up by num_positions and overwrites that block since it will be
  // inserted in mapPBA_ again and be reassigned a PBA
  size_t num_positions = 0;
  size_t associated_LBA;
  blockPBA current_blockPBA;
  for (size_t i = 0; i < mapPBA_.size(); ++i) {

    associated_LBA = mapPBA_[i].LBA;

    // checks to see if the LBA associated with the PBA is in PBA_hashtable, if
    // so increments the counter. Otherwise simply moves the current block up
    // mum_positions places in mapPBA_
    if (PBA_hashtable.count(associated_LBA)) {

      ++num_positions;

    } else {

      // assigns the block to move to the temp variable
      current_blockPBA = mapPBA_[i];

      // moves the block to the correct position
      mapPBA_[i - num_positions] = current_blockPBA;

    }
  }

  vector<blockPBA> LBAs;
  blockPBA LBA_to_add;

  // Iterates through and creates a blockPBA for each LBA in the LBA_vector,
  // ordering of the LBAs is the same both the LBA_vector and PBAs.
  for(size_t i = 0; i < LBA_vector.size(); ++i) {

    LBA_to_add.LBA = LBA_vector[i];
    LBA_to_add.used = true;

    LBAs.push_back(LBA_to_add);
  }

  // Initializes an iterator for the mapLBA_ vector and then moves it so that it
  // is pointing at the object at index start.
  vector<blockPBA>::iterator start_location = mapPBA_.begin();
  advance(start_location, start);

  // Inserts the vector LBAs in the mapPBA_ data member right before
  // the iterator start_location
  mapPBA_.insert(start_location, LBAs.begin(), LBAs.end());

  // The ordering of the LBAs and the associated PBAs is now correct in
  // mapPBA_, the helper function fix_PBAs() is now run to fix any discrepancies
  // that may have occured in the LBA-PBA pairs in the mapLBA_ data structure
  // due to the movement of blocks need to place the LBAs in LBA_vector in the
  // correct position in the mapPBA_ vector.
  fix_PBAs();

}

/**
 * function: fix_PBAs()
 *
 * This is a helper function that was created to fix descrepancies in the PBAs
 * and LBAs in the data members of the TraceSet object.
 *
 * This function fixes descrepancies by iterating through the mapPBA_ data
 * member and at each index i, since mapPBA_ is indexed by PBA i represents the
 * PBA that is associated with the LBA l, whic is in the struct at that
 * position. It will then go to the index l in the mapLBA_ data member since
 * this vector is indexed by LBA, it will then access the PBA data member of the 
 * struct at this location and check if it is equal to i, if it is not equal to
 * i, then there is a descrepancy between the assignements of the LBA-PBA pair,
 * this is fixed by then setting the PBA data member in that struct equal to i.
 *
 */
void TraceSet::fix_PBAs()
{

  size_t current_LBA;
  for(size_t current_PBA = 0; current_PBA < mapPBA_.size(); ++current_PBA) {

    current_LBA = mapPBA_[current_PBA].LBA;

    // check to make sure the PBA is the same for any given LBA in both
    // mapPBA_ and mapLBA_ and change the PBA in mapLBA_ if it is not.
    if(current_PBA != mapLBA_[current_LBA].PBA) {

      mapLBA_[current_PBA].PBA = current_PBA;

    } else {

      // do nothing

    }
  }
}
