/**
 * \file trace-set-test.cpp
 *
 * \Authors Jazmin Ortiz
 *
 * \brief Tests a TraceSet for correctness
 */

#include "TraceSet.hpp"
#include "gtest/gtest.h"

#include <memory>

using namespace std;

//--------------------------------------------------
//           TEST FUNCTIONS
//--------------------------------------------------

/// Test pushing back on an empty list (also tests default construction).

TEST(constructor, default_constructor)
{
    TraceSet test;
    vector<TraceSet::Line>& test_sequence = test.get_Sequence();
    vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
    vector<TraceSet::LBA_location>& test_locations = test.get_locations();
    assert(test_sequence.empty());

    assert(test_locations.size() == 1);
    assert(test_mapLBA.size() == 1);

}


/// Test insert when taking in only the same character
TEST(insert, all_same)
{
    TraceSet test;

    // insert 50 of the same character
    for(size_t i = 0; i < 50; ++i) {
        test.insert("1");
    }

    vector<TraceSet::Line>& testSequence = test.get_Sequence();
    vector<TraceSet::blockLBA>& testMapLBA = test.get_mapLBA();
    vector<TraceSet::LBA_location>& testlocation = test.get_locations();

    // checks that the mapLBA_ vector updates its data members corectly
    assert(testMapLBA[1].used == true);
    assert(testMapLBA[1].first == 0);
    assert(testMapLBA[1].last == 49);
    assert(testMapLBA[1].last == 49);

    // checks that the locations_ vector updates its data members correctly
    assert(testlocation[1].LBA == 1);
    assert(testlocation[1].used == true);
    assert(testlocation.size() >= 1);

    // checks that the Sequence_ vector updates correctly
    for (size_t i = 0; i < 49; ++i) {

        assert(testSequence[i].next == i+1);
        assert(testSequence[i].LBA == 1);
    }

    // Make sure that the vectors resize properly
    assert(testMapLBA.size() > 1);
    assert(testlocation.size() == testlocation.size());
}

/// Test insert when taking in many different characters
TEST(insert, different)
{
    TraceSet test;

    // insert 50 of the different characters
    string s;
    for(int i = 0; i < 50; ++i) {
        s = to_string(i);
        test.insert(s);
    }

    vector<TraceSet::Line>& testSequence = test.get_Sequence();
    vector<TraceSet::blockLBA>& testMapLBA = test.get_mapLBA();
    vector<TraceSet::LBA_location>& testlocation = test.get_locations();

    // checks that the mapLBA_, locations_ and Sequences_ vectors update sanely
     for (size_t i = 0; i < 49; ++i) {

         assert(testMapLBA[i].used == true);
         assert(testMapLBA[i].first == i);
         assert(testMapLBA[i].last == i);
         assert(testMapLBA[i].location == i);

         assert(testlocation[i].LBA == i);
         assert(testlocation[i].used == true);

         assert(testSequence[i].LBA == i);

    }
    assert(testMapLBA.size() > 48);
    assert(testlocation.size() == testMapLBA.size());
}

/// Test insert when taking in many different characters
TEST(insert, different_large)
{
    TraceSet test;

    // insert 1000 of the different characters
    string s;
    for(int i = 0; i < 1000; ++i) {
        s = to_string(i);
        test.insert(s);
    }

    // insert the same 1000 characters inserted above again
    for(int i = 0; i < 10000; ++i) {
        s = to_string(i);
        test.insert(s);
    }

    vector<TraceSet::Line>& testSequence = test.get_Sequence();
    vector<TraceSet::blockLBA>& testMapLBA = test.get_mapLBA();
    vector<TraceSet::LBA_location>& testlocation = test.get_locations();

    // checks that the mapLBA_, locations_ and Sequences_ vector update sanely
    for (size_t i = 0; i < 999; ++i) {

         assert(testMapLBA[i].used == true);
         assert(testMapLBA[i].first == i);
         assert(testMapLBA[i].last == i+1000);
         assert(testMapLBA[i].location == i);

         assert(testlocation[i].LBA == i);
         assert(testlocation[i].used == true);

         assert(testSequence[i].LBA == i);
         assert(testSequence[i+1000].LBA == i);

    }

    assert(testMapLBA.size() > 2000);
    assert(testlocation.size() == testMapLBA.size());
}



/// Test get_indices when taking in only the same character
TEST(get_indices, all_same)
{
    TraceSet test;

    // insert 50 of the same character
    for(size_t i = 0; i < 50; ++i) {
        test.insert("1");
    }

    vector<size_t> test_indices = test.get_indices(1);

    // checks that get_indices contains the correct values

    for (size_t i = 0; i < 50; ++i) {

        assert(test_indices[i] == i);
    }

    assert(test_indices.size() == 50);
}

/// Test get_indices when taking in different characters
TEST(get_indices, different)
{
    TraceSet test;

    // insert 50 different characters
    string s;
    for(int i = 0; i < 50; ++i) {
        s = to_string(i);
        test.insert(s);
    }


    vector<size_t> test_indices;
    for (size_t i = 0; i < 50; ++i) {

        test_indices = test.get_indices(i);
        size_t& index = test_indices.front();
        assert(test_indices.size() == 1);
        assert(index == i);
    }

}

/// Test that total_seek_distance works on 1 element
TEST(total_seek_distance, one)
{
    TraceSet test;
    test.insert("1");

    size_t total = test.total_seek_distance();
    assert(total == 0);
}

/// Test that total_seek_distance works for list of elements which are all the
/// the same
TEST(total_seek_distance, all_same)
{
    TraceSet test;

    // insert 50 of the same character
    for(size_t i = 0; i < 50; ++i) {
        test.insert("1");
    }

    size_t total = test.total_seek_distance();
    assert(total == 0);

}

/// Test that total_seek_distance works for elements that are not all the same
TEST(total_seek_distance, different)
{
    TraceSet test;

    // insert 50 different characters
    string s;
    size_t value;
    for(size_t i = 0; i < 50; ++i) {

        value = 2*i;
        s = to_string(value);

        test.insert(s);

    }

    size_t total = test.total_seek_distance();
    assert(total == 98);
}

/// Test to make sure that the helper function fix_locations() works on one
// element
TEST(fix_locations, one)
{

    TraceSet trace;
    TraceSet test;

    // Create and insert one element in tracesset objects
    string s;
    size_t value = 2;
    s = to_string(value);

    trace.insert(s);
    test.insert(s);

    // Get the private data members from both the traceset object
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();
    vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();

    vector<TraceSet::LBA_location>& trace_locations = trace.get_locations();
    vector<TraceSet::LBA_location>& test_locations = test.get_locations();

    test_mapLBA[2].location = 5;
    test.fix_locations();

    assert(trace_mapLBA[2].location == test_mapLBA[2].location);
    assert(trace_locations[2].LBA == test_locations[2].LBA);

    // Make sure that the Test data members sizes remain the same
    assert(test_mapLBA.size() == test_locations.size());
}

/// Test to make sure that the helper function fix_locations() works on small
// cases
TEST(fix_locations, small)
{

    TraceSet trace;
    TraceSet test;

    //loop through and insert elements in tracesset objects
    string s;
    size_t value;
    for(size_t i = 0; i < 50; ++i) {

        value = i;
        s = to_string(value);

        trace.insert(s);
        test.insert(s);

    }

    // Getting a reference to the mapLBA_ object test
    vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();

    // Looping through test's mapLBA_ data members and changing all of the
    // locations
    for (int i = 0; i < 50; ++i) {

        test_mapLBA[i].location = 100;

    }

    // Using fix_locations to fix the locations, which should set them back to
    // the original values
    test.fix_locations();

    // Get the provate data members from both the traceset and trace_set test
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();

    vector<TraceSet::LBA_location>& trace_location = trace.get_locations();
    vector<TraceSet::LBA_location>& test_location = test.get_locations();

    // Check that fix_PBAs reset the values properly
    for(int i = 0; i < 50; ++i) {

        assert(trace_mapLBA[i].location == test_mapLBA[i].location);
        assert(trace_location[i].LBA == test_location[i].LBA);
    }

    // Make sure that the trace_test data members sizes remain the same
    assert(test_mapLBA.size() == test_location.size());
}


/// Test to make sure that the helper function fix_locations() works on larger
// cases
TEST(fix_locations, large)
{

    TraceSet trace;
    TraceSet test;

    //loop through and insert elements in tracesset objects
    string s;
    size_t value;
    for(size_t i = 0; i < 1000; ++i) {

        value = i;
        s = to_string(value);

        trace.insert(s);
        test.insert(s);

    }

    // Getting a reference to the mapLBA_ object test
    vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();

    // Looping through test mapLBA_ and changing some of the locations
    int new_value;
    for (int i = 0; i < 50; ++i) {

        new_value = 20*i;
        test_mapLBA[new_value].location = 100;

    }

    // Using fix_locations to fix the locations which should set them back to
    // the original values
    test.fix_locations();

    // Get the private data members from both the trace and test
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();

    vector<TraceSet::LBA_location>& trace_location = trace.get_locations();
    vector<TraceSet::LBA_location>& test_location = test.get_locations();

    // Check that fix_PBAs reset the values properly
    for(int i = 0; i < 1000; ++i) {

        assert(trace_mapLBA[i].location == test_mapLBA[i].location);
        assert(trace_location[i].LBA == test_location[i].LBA);
    }

    // Make sure that the test data members sizes remain the same
    assert(test_mapLBA.size() == test_location.size());
}

// Make sure that change_locations works when one element is inserted in front
// and previously resided in the middle of the trace object
TEST(change_locations, first_from_middle)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 5; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();

     // Switch values in test so that the instead of the LBA 0 being
     // at location 0 LBA 0 is now at location 2 and LBA 2 is at location 0
     test_mapLBA[2].location = 0;
     test_mapLBA[0].location = 2;

     test_locations[0].LBA = 2;
     test_locations[2].LBA = 0;

    // Create a vector of 1 element to insert
    vector<size_t> to_insert;

    // Set value of element in vector
    to_insert.push_back(0);

    // call change_locations, which should change the LBA 0 to be at location 0
    test.change_locations(to_insert, 0);

    // Check that change_locations reset the values properly
    assert(test_locations[0].LBA == 0);
    assert(test_mapLBA[0].location == 0);

    assert(test_locations[1].LBA == 2);
    assert(test_mapLBA[2].location == 1);

    assert(test_locations[2].LBA == 1);
    assert(test_mapLBA[1].location == 2);

    assert(test_locations[3].LBA == 3);
    assert(test_mapLBA[3].location == 3);

    assert(test_locations[4].LBA == 4);
    assert(test_mapLBA[4].location == 4);

    for(int i = 0; i < 5; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 5);
    assert(test_mapLBA.size() == test_locations.size());

    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 5; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
    }

}
// Make sure that change_locations works when one element is inserted in front
// and previously resided at the end of the trace object
TEST(change_locations, first_from_end)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 5; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();

     // Switch values in test so that the instead of the LBA 0 being
     // at location 0 LBA 0 it is now at location 4 and LBA 4 is at location 0
     test_mapLBA[4].location = 0;
     test_mapLBA[0].location = 4;

     test_locations[0].LBA = 4;
     test_locations[4].LBA = 0;

    // Create a vector of 1 element to insert
    vector<size_t> to_insert;

    // Set value of element in vector
    to_insert.push_back(0);

    // call change_locations, which should change the LBA 0 to be at location 0
    test.change_locations(to_insert, 0);

    // Check that change_locationss reset the values properly
    assert(test_locations[0].LBA == 0);
    assert(test_mapLBA[0].location == 0);;

    assert(test_locations[1].LBA == 4);
    assert(test_mapLBA[4].location == 1);

    assert(test_locations[2].LBA == 1);
    assert(test_mapLBA[1].location == 2);

    assert(test_locations[3].LBA == 2);
    assert(test_mapLBA[2].location == 3);

    assert(test_locations[4].LBA == 3);
    assert(test_mapLBA[3].location == 4);

    for(int i = 0; i < 5; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 5);
    assert(test_mapLBA.size() == test_locations.size());
    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 5; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
    }

}

// Make sure that change_locations works when one element is inserted at the end
// and previously resided at the begining of the trace object
TEST(change_locations, last_from_begining)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 5; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();


    // Create a vector of 1 element to insert
    vector<size_t> to_insert;

    // Set value of element in vector
    to_insert.push_back(0);

    // call change_locations, which should change the LBA 0 to be at location 0
    test.change_locations(to_insert, 4);

    // Check that change_locationss reset the values properly
    assert(test_locations[0].LBA == 1);
    assert(test_mapLBA[1].location == 0);;

    assert(test_locations[1].LBA == 2);
    assert(test_mapLBA[2].location == 1);

    assert(test_locations[2].LBA == 3);
    assert(test_mapLBA[3].location == 2);

    assert(test_locations[3].LBA == 4);
    assert(test_mapLBA[4].location == 3);

    assert(test_locations[4].LBA == 0);
    assert(test_mapLBA[0].location == 4);

    for(int i = 0; i < 5; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 5);
    assert(test_mapLBA.size() == test_locations.size());
    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 5; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
    }
}

// Make sure that change_locations works when one element is inserted at the end
// and previously resided in the middle of the trace object
TEST(change_locations, last_from_middle)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 5; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();


    // Create a vector of 1 element to insert
    vector<size_t> to_insert;

    // Set value of element in vector
    to_insert.push_back(3);

    // call change_locations, which should change the LBA 0 to be at location 0
    test.change_locations(to_insert, 4);

    // Check that change_locationss reset the values properly
    assert(test_locations[0].LBA == 0);
    assert(test_mapLBA[0].location == 0);;

    assert(test_locations[1].LBA == 1);
    assert(test_mapLBA[1].location ==1);

    assert(test_locations[2].LBA == 2);
    assert(test_mapLBA[2].location == 2);

    assert(test_locations[3].LBA == 4);
    assert(test_mapLBA[4].location == 3);

    assert(test_locations[4].LBA == 3);
    assert(test_mapLBA[3].location == 4);

    for(int i = 0; i < 5; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 5);
    assert(test_mapLBA.size() == test_locations.size());
    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 5; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
    }
}

// Make sure that change_locations works when a set of elements that were
// previously a contiguous set of elements is changed
TEST(change_locations, contiguous_set_large)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 500; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();


    // Create a vector size_ts to insert
    vector<size_t> to_insert;

    // Add size_ts to the vector to insert
    for (int i = 250; i < 276; ++i) {
        to_insert.push_back(i);
    }

    // call change_locations
    test.change_locations(to_insert, 0);

    // Check that change_locations reset the values inserted at the begining
    // properly
    size_t location;
    size_t locations_LBA;
    for (int i = 0; i < 26; ++i) {

        // the LBAs that were of the values 250-275 were inserted in front
        // so for the first 25 elements if the location is i then the LBA should
        // 250 + i
        location = i;
        locations_LBA = 250+i;

        assert(test_locations[location].LBA == locations_LBA);
        assert(test_mapLBA[locations_LBA].location == location);

    }

    for (int i = 26; i < 250; ++i) {
        // Since LBAs 250 - 275 were inserted in front the locations and
        // corresponding LBAS were shifted 26 positions "back".
        location = i;
        locations_LBA = i - 26;

        assert(test_locations[location].LBA == locations_LBA);
        assert(test_mapLBA[locations_LBA].location == location);
    }

    for (int i = 276; i < 500; ++i) {
        // Since LBAs 250 - 275 were inserted in front the locations then
        // the LBAs and corresponding locations for LBAS 276-500 will
        // remain in thier previous location.
        location = i;
        locations_LBA = i;

        assert(test_locations[location].LBA == locations_LBA);
        assert(test_mapLBA[locations_LBA].location == location);
    }

    for(int i = 0; i < 500; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 500);
    assert(test_mapLBA.size() == test_locations.size());
    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 500; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
    }
}

// Make sure that change_locations works when a set of elements that were
// previously a non contiguous set of elements is changed
TEST(change_locations, noncontiguous_set_large)
{

    TraceSet test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 500; ++i) {

        value = i;
        s = to_string(value);
        test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& test_mapLBA = test.get_mapLBA();
     vector<TraceSet::LBA_location>& test_locations = test.get_locations();


    // Create a vector size_ts to insert
    vector<size_t> to_insert;

    // Add size_ts to the vector to insert
    size_t element_to_insert;
    for (int i = 0; i < 25; ++i) {
        element_to_insert = i*20;
        to_insert.push_back(element_to_insert);
    }

    // call change_locations
    test.change_locations(to_insert, 0);

    // Check that change_locations reset the values properly for the previously
    // non-contiguous set which now inhabit the first 25 locations
    size_t location;
    size_t locations_LBA;
    for (int i = 0; i < 25; ++i) {

        // the LBA that were multiples of 25 were inserted in order at the front
        location = i;
        locations_LBA = 20*i;

        assert(test_locations[location].LBA == locations_LBA);
        assert(test_mapLBA[locations_LBA].location == location);

    }

    // Check that change_locations reset the values properly for the elements
    // which were not inserted at the front
    size_t positions_to_shift = 0;
    for (size_t LBA = 0; LBA < 500; ++LBA) {

        // Checks to see if the element is one that was inserted at the front,
        // if it is then it increments the positions_to_shift variable.
        //
        // This variable is is incremented because all LBAs after this will need
        // to be shifted back a position since that element was put at the front
        if (LBA % 20 == 0) {

            ++positions_to_shift;

        } else {

            location = LBA + 25 - positions_to_shift;
            locations_LBA = LBA;

            assert(test_locations[location].LBA == locations_LBA);
            assert(test_mapLBA[locations_LBA].location == location);

        }
    }

    for(int i = 0; i < 500; ++i) {
        assert(test_mapLBA[i].used == true);
        assert(test_locations[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(test_mapLBA.size() > 500);
    assert(test_mapLBA.size() == test_locations.size());
    // Check to make sure that indices within the vector that should have not
    // been used are not used.
    for(size_t i = 500; i < test_locations.size(); ++i) {

        assert(test_locations[i].used == false);
        assert(test_mapLBA[i].used == false);
        
    }
}

//--------------------------------------------------
//           RUNNING THE TESTS
//--------------------------------------------------

/// Run tests
int main(int argc, char** argv)
{
    // Initalize testing environment
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */

