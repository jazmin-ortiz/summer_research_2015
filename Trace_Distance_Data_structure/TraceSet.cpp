/*
* TraceSet.cpp
*
* Authors: Jazmin Ortiz
*
* A class that takes in a trace file of LBAs (in decimal)  from stdin and
* creates a data structure to hold them and easily change and keep track of the
* locations of the LBAs.
*
* The ultimate purpose of this data structure is to help in looking at
* better ways to lay out the blocks on the disk drive, where the metric which
* defines a more optimal layout of the blocks is a layout that minimizes the
* total seek distance. The total seek distance is said to be the sum of the
* absolute value of differences of locations associated with consecutive LBAs in
* the Sequence_ vector.
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
  locations_{1}
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
  vector<blockLBA>& mapLBA = mapLBA_;

  return mapLBA;
}

/**
 * function: get_locations()
 *
 * Returns a reference to the locations_ private data member
 */
vector<TraceSet::LBA_location>& TraceSet::get_locations()
{
  vector<LBA_location>& locations = locations_;

  return locations;
}

/**
 * function: insert(string LBA_to_add)
 *
 * Takes in a string which is a LBA and adds it to the end
 * of the Sequence vector and changes the mapLBA_ and locations_ vectors
 * apropriately, meaning that if the LBA to insert is not currently in the
 * mapLBA_ vector that this LBA is added and sets the location of this LBA equal
 * to the LBA.
 *
 * NOTE This function initially sets the location equal to the LBA due
 * to the fact that before any algorithm is run the location of a given
 * LBA in the 1d representation of the disk should simply be the location
 * denoted by the LBA.
 *
 * NOTE: This function assumes that the trace is being read in for the first
 * time and LBAs have not been moved to locations that correspond to values
 * of LBAs that have not yet been used. It makes this assumption because the
 * function always sets the value of the location associated with a given
 * LBA equal to that LBA if the LBA has not been seen before. This could lead to 
 * errors if that given location had already been set in to a different LBA.
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
  // resizes the mapLBA_ vector apropriately. Since the locations_ vector
  // contains the same information as the mapLBA vector but is instead
  // indexed by location, if the mapLBA_ vector needs to be resized then the
  // locations_ vector will also need to be resized
  //
  // Since the last element pushed back onto Sequence_ is Line_to_add, this
  // is the index of Line_to_add
  size_t index_of_line = Sequence_.size() - 1;
  if (added_LBA >= mapLBA_.size()) {

    mapLBA_.resize(2*added_LBA); 
    locations_.resize(2*added_LBA);

  }

  // Variable representing the blockLBA which contains information
  // about LBA_to_add
  blockLBA& LBAs_blockLBA = mapLBA_[added_LBA];

  // Set of if statments to properly update the LBA's block map struct in the
  // mapLBA_ vector.

  // Deals with the cases where there is at least one instance of the given
  // LBA in the Sequence_ vector.
  if (LBAs_blockLBA.used) {

     // LBAs_blockLBA data members have not been updated yet, the data member
     // called last now is the index of the second to last
     size_t second_to_last = LBAs_blockLBA.last;

     // Update the previously last instance of LBA_to_add in Sequence_
     Sequence_[second_to_last].next = index_of_line;

  }

   // Deals with the case that LBA_to_add has not previously been in
   // Sequence_, which means that its location needs to be set in both the
   // mapLBA_ and locations_ vector.
   else {

     // Sets the data members of LBAs_blockLBA apropriately.
     LBAs_blockLBA.first = index_of_line;
     LBAs_blockLBA.location = added_LBA;
     LBAs_blockLBA.used = true;

     // Sets the data members of the LBA_location struct which represents the
     // given LBA apropriately.
     locations_[added_LBA].LBA = added_LBA;
     locations_[added_LBA].used = true;

  }

  // update last data member of the LBAs_blockLBA apropriately
  LBAs_blockLBA.last = index_of_line;

}

/**
 * function: readIn(ifstream& inputstream)
 *
 * Reads in from standard in and changes the Sequence_, mapLBA_ and
 * location_ private data members apropriately using the insert function.
 */
void TraceSet::readIn(ifstream& inputstream)
{

  // While loop to read in a text file from stdin.
  //
  // The most recently read character and variable to hold the LBAs that are
  //read in as string from stdin
  char c;
  string current_LBA = "";

  while (inputstream.get(c)) {

    // Makes sure that streamn closes if eof char is seen
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

}

/**
 * function: readLBAs(ifstream& inputstream)
 *
 * Reads in from standard in a list of numbers (one per line)
 * and returns a vector of those size_ts in the order that
 * that they were seen.
 */

std::vector<size_t> TraceSet::readLBAs(ifstream& inputstream)
{


    char c;
    string current_LBA = "";
    std::vector<size_t> freqLBAs;

    while (inputstream.get(c)) {
    // Makes sure that streamn closes if eof char is seen
        if (inputstream.eof()){
            inputstream.close();
            return freqLBAs;
        }
        // Checks if a newline has been encountered which means that the
        // the current LBA has been completed and if so inserts it into the
        // Sequence_ vector.
        else if ( c == '\n' ) {
            freqLBAs.push_back(stoi(current_LBA));
            current_LBA = "";
        }
        // If a newline char has not been seen continues to push chars onto
        // current_LBA
        else {
            current_LBA.push_back(c);
        }
    }

    return freqLBAs;

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


  // blockLBA that contains information pertaining to LBA_to_find
  struct blockLBA LBAs_BlockLBA = mapLBA_[LBA_to_find];

  // Checks if there are instances of the LBA by checking the LBAs_BlockLBA
  // to see if that LBA has been used, if it has been used loops through and
  // adds indices of all instance of LBA_to_find in Sequences_ to the instances
  // vector. If it has not been used returns the vector of instances.
  if (LBAs_BlockLBA.used) {

    // Finds index of first instance then pushes index onto instances vector
    instances.push_back(LBAs_BlockLBA.first);

    // Loops through Sequence_ and finds the indices of all occurences of
    // the LBA in the Sequence_.
    //
    // Variables that will be used to loop through instances of the
    // LBA in Sequeence_.
    size_t index = LBAs_BlockLBA.first;
    Line next_line = Sequence_[index];
    while (index != LBAs_BlockLBA.last) {

      // Adds the index of the next occurence of the LBA to the vector
      instances.push_back(next_line.next);

      // update loop variable
      index = next_line.next;
      next_line = Sequence_[index];

    }

  } else {

    // Do nothing

  }

  return instances;
}

/**
 * function: total_seek_distance()
 *
 * This is a function that returns the sum of the distance between two
 * consecutive access in the Sequences vector.
 *
 * The distance is said to be the absolute value of the difference of the
 * locations associated with the consecutive LBAs that represent accesses in the 
 * Sequence_ data member.
 */
size_t TraceSet::total_seek_distance()
{

  // Iterators that will be used to iterate through Sequences_.
  vector<Line>::iterator current_it = Sequence_.begin();
  vector<Line>::iterator next_it = Sequence_.begin();
  ++next_it;

  // Size_ts that will be used to hold locations in the while looop
  size_t current_location;
  size_t next_location;
  size_t total_distance = 0;
  while (next_it != Sequence_.end()) {

    // Finds the blockLBA associated with current_it and next_it and then
    // assigns its location data member to respectivly to current_location
    // and next_location
    current_location = mapLBA_[current_it->LBA].location;
    next_location = mapLBA_[next_it->LBA].location;

    // Finds the absolute values of the difference of current_location and
    // next_location.Since current_location and next_location are size_ts the
    // smaller location must be subtracted from the larger.
    if (current_location < next_location) {

      total_distance += next_location - current_location;

    }

    else {

        total_distance += current_location - next_location;

    }

  }

  ++current_it;
  ++next_it;

  return total_distance;

}

/**
 * function: change_locations(vector<size_t> LBA_vector, size_t start)
 *
 * This is a function that takes in a vector of size_ts that represent LBAs and
 * the order in which to insert them and a size_t start, which represents the
 * location that should be the location of the first LBA in the LBA_vector, the
 * other LBAs in LBA_vector will then be assigned a contiguous set of locations
 * following start. The locations of the LBAs will be moved so that the no new
 * locations will be used but spaces that existed between LBAs that are not in
 * LBA_vector will be preserved.
 *
 */
void TraceSet::change_locations(vector<size_t> LBA_vector, size_t start)
{

  // Call to a helper function that will remove the LBA_locations structs
  // associated with the LBAs in LBA_vector from the locations_ data member
  remove_LBA_locations(LBA_vector);

  vector<LBA_location> LBAs;
  LBA_location LBA_to_add;

  // Iterates through and creates a LBA_location struct for each LBA in the
  // LBA_vector, ordering of the LBAs is the same both the LBA_vector and LBAs.
  for(size_t i = 0; i < LBA_vector.size(); ++i) {

    LBA_to_add.LBA = LBA_vector[i];
    LBA_to_add.used = true;

    LBAs.push_back(LBA_to_add);
  }

  // Initializes an iterator for the mapLBA_ vector and then moves it so that it
  // is pointing at the object at index start.
  vector<LBA_location>::iterator start_location = locations_.begin();
  advance(start_location, start);

  // Inserts the vector LBAs in the locations_ data member right before
  // the iterator start_location.
  locations_.insert(start_location, LBAs.begin(), LBAs.end());

  // The ordering of the LBAs and the associated LBA_locationss is now correct
  // in locations_, the helper function fix_locationss() is now run to fix any
  // discrepancies that may have occured in the LBA-location pairs in the
  // mapLBA_ data structure due to the movement of LBA_location structs which
  // was cause by the need to place the LBAs in LBA_vector in the
  // correct locations in the locations_ vector.

  fix_locations();

}

/**
 * function: remove_LBA_locations
 *
 * This is a helper function for change_locations that takes in a vector of
 * size_ts that represent LBAs whose LBA_location structs should be removed from
 * the locations_ data member and removes the LBA_location structs from
 * locations.
 *
 */
void TraceSet::remove_LBA_locations(vector<size_t> LBA_vector)
{

  // loops through LBA_vector, finds the location associated with each LBA and
  // then inserts the LBA and its associated location as a key-value pair into
  // location_hashtable, where the LBA is used as the key.
  unordered_map<size_t, size_t> location_hashtable;
  size_t current_LBA;
  size_t LBAs_location;
  for (size_t i = 0; i < LBA_vector.size(); ++i) {

    current_LBA = LBA_vector[i];

    // Sets LBAs_location equal to the location that is assigned to current_LBA
    // in the  mapLBA_ data member.
    LBAs_location = mapLBA_[current_LBA].location;

    location_hashtable.emplace(current_LBA, LBAs_location);
  }

  // Loops through the locations_ data member and checks the LBA associated with
  // each location to see if it is in the hash table. If the LBA is in the hash
  // table it should be removed. Therefore the num_positions counter is
  // incremented by 1 and all LBA_location structs after that struct are moved
  // up by num_positions which overwrites that LBA_location struct.
  size_t num_positions = 0;
  size_t associated_LBA;
  LBA_location current_location;
  for (size_t i = 0; i < locations_.size(); ++i) {

    associated_LBA = locations_[i].LBA;

    // checks to see if the LBA associated with the location is in
    // location_hashtable and if that location has been used, if both of these
    // are true then the counter is incremented by one. Otherwise this simply
    // moves the current LBA_location block num_positions places in locations_
    if (location_hashtable.count(associated_LBA) && locations_[i].used) {

      ++num_positions;

    } else {

      // assigns the LBA_location to move to a temp variable
      current_location = locations_[i];

      // moves the LBA_location to the correct location
      locations_[i - num_positions] = current_location;

    }

  }

  // Now that LBA_location in locations_ have been shifted up apropriately, we
  // know that all LBA_location structs associated with the elements in
  // LBA_vector have been overwritten, therefore the last LBA_vector.size()
  // elements in the locations_ vector do not contain anything since that is the
  // number of position all currently existing LBA_location structs have been
  // moved up, those elements will now be removed.
  for(size_t i = 0; i < LBA_vector.size(); ++i) {

    locations_.pop_back();

  }

}

/**
 * function: fix_locations()
 *
 * This is a helper function that was created to fix descrepancies in the
 * locations and LBAs in the data members of the TraceSet object.
 *
 * This function fixes descrepancies by iterating through the locations_ data
 * member, since locations_ is indexed by location index i represents the
 * location that is associated with the LBA l, which is in the LBA_location
 * struct at that position. The function will then go to the index l in the
 * mapLBA_ data member since this vector is indexed by LBA, it will then access
 * the location data member of the struct at this location and check if it is
 * equal to i, if it is not equal to i, there is a descrepancy between the
 * assignements of the LBA-location pair across the mapLBA and locations data
 * members,this is fixed by then setting the location data member in that struct
 * equal to i.
 *
 */
void TraceSet::fix_locations()
{

  size_t current_LBA;
  for(size_t location = 0; location < locations_.size(); ++location) {

    current_LBA = locations_[location].LBA;

    // check to make sure that used locatins are the same for any given LBA in
    // both locations_ and mapLBA_ and change the location in mapLBA_ if it
    // is not
    if(location != mapLBA_[current_LBA].location && locations_[location].used) {

      mapLBA_[current_LBA].location = location;

    } else {

      // do nothing

    }
  }
}

