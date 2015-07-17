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
    vector<TraceSet::blockPBA>& test_mapPBA = test.get_mapPBA();
    assert(test_sequence.empty());

    assert(test_mapPBA.size() == 1);
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
    vector<TraceSet::blockPBA>& testMapPBA = test.get_mapPBA();

    // checks that the mapLBA vector updates its data members corectly
    assert(testMapLBA[1].used == true);
    assert(testMapLBA[1].first == 0);
    assert(testMapLBA[1].last == 49);
    assert(testMapLBA[1].last == 49);

    // checks that the mapPBA vector updates its data members correctly
    assert(testMapPBA[1].LBA == 1);
    assert(testMapPBA[1].used == true);
    assert(testMapPBA.size() >= 1);

    // checks that the Sequence_ vector updates correctly
    for (size_t i = 0; i < 49; ++i) {

        assert(testSequence[i].next == i+1);
        assert(testSequence[i].LBA == 1);
    }

    // Make sure that the vectors resize properly
    assert(testMapLBA.size() > 1);
    assert(testMapPBA.size() == testMapPBA.size());
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
    vector<TraceSet::blockPBA>& testMapPBA = test.get_mapPBA();

    // checks that the mapLBA_, mapPBA_ and Sequnces_ vector update sanely

     for (size_t i = 0; i < 49; ++i) {

         assert(testMapLBA[i].used == true);
         assert(testMapLBA[i].first == i);
         assert(testMapLBA[i].last == i);

         assert(testMapPBA[i].LBA == i);
         assert(testMapPBA[i].used == true);

         assert(testSequence[i].LBA == i);

    }
    assert(testMapLBA.size() > 48);
    assert(testMapPBA.size() == testMapLBA.size());
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
    vector<TraceSet::blockPBA>& testMapPBA = test.get_mapPBA();

    // checks that the mapLBA_, mapPBA_ and Sequnces_ vector update sanely
    for (size_t i = 0; i < 999; ++i) {

         assert(testMapLBA[i].used == true);
         assert(testMapLBA[i].first == i);
         assert(testMapLBA[i].last == i+1000);

         assert(testMapPBA[i].LBA == i);
         assert(testMapPBA[i].used == true);

         assert(testSequence[i].LBA == i);
         assert(testSequence[i+1000].LBA == i);

    }

    assert(testMapLBA.size() > 2000);
    assert(testMapPBA.size() == testMapLBA.size());
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

/// Test that find_total_distance works on 1 element
TEST(find_distance, one)
{
    TraceSet test;
    test.insert("1");

    size_t total = test.find_total_distance();
    assert(total == 0);
}

/// Test that find_total_distance works for list of elements which are all the
/// the same
TEST(find_distance, all_same)
{
    TraceSet test;

    // insert 50 of the same character
    for(size_t i = 0; i < 50; ++i) {
        test.insert("1");
    }

    size_t total = test.find_total_distance();
    assert(total == 0);

}

/// Test that find_total_distance works for elements that are not all the same
TEST(find_distance, different)
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

    size_t total = test.find_total_distance();
    assert(total == 98);
}

/// Test to make sure that the helper function fix_PBAs() works on one element
TEST(fix_PBAS, one)
{

    TraceSet trace;
    TraceSet trace_test;

    // Create and insert one element in tracesset objects
    string s;
    size_t value = 2;
    s = to_string(value);

    trace.insert(s);
    trace_test.insert(s);

    // Get the private data members from both the traceset object
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();
    vector<TraceSet::blockLBA>& trace_test_mapLBA = trace_test.get_mapLBA();

    vector<TraceSet::blockPBA>& trace_mapPBA = trace.get_mapPBA();
    vector<TraceSet::blockPBA>& trace_test_mapPBA = trace_test.get_mapPBA();

    trace_test_mapLBA[0].PBA = 5;
    trace_test.fix_PBAs();

    assert(trace_mapLBA[0].PBA == trace_test_mapLBA[0].PBA);
    assert(trace_mapPBA[0].LBA == trace_test_mapPBA[0].LBA);

    // Make sure that the trace_test data members sizes remain the same
    assert(trace_test_mapLBA.size() == trace_test_mapPBA.size());
}

/// Test to make sure that the helper function fix_PBAs() works on small cases
TEST(fix_PBAS, small)
{

    TraceSet trace;
    TraceSet trace_test;

    //loop through and insert elements in tracesset objects
    string s;
    size_t value;
    for(size_t i = 0; i < 50; ++i) {

        value = i;
        s = to_string(value);

        trace.insert(s);
        trace_test.insert(s);

    }

    // Getting a reference to the mapLBA_ object traceset_test
    vector<TraceSet::blockLBA>& test_mapLBA = trace_test.get_mapLBA();

    // Looping through traceset_test mapLBA and changing all of the PBAs
    for (int i = 0; i < 50; ++i) {

        test_mapLBA[i].PBA = 100;

    }

    // Using fix_PBAS to fix the PBAs which should set them back to the
    // original values
    trace_test.fix_PBAs();

    // Get the provate data members from both the traceset and trace_set test
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();
    vector<TraceSet::blockLBA>& trace_test_mapLBA = trace_test.get_mapLBA();

    vector<TraceSet::blockPBA>& trace_mapPBA = trace.get_mapPBA();
    vector<TraceSet::blockPBA>& trace_test_mapPBA = trace_test.get_mapPBA();

    // Check that fix_PBAs reset the values properly
    for(int i = 0; i < 50; ++i) {

        assert(trace_mapLBA[i].PBA == trace_test_mapLBA[i].PBA);
        assert(trace_mapPBA[i].LBA == trace_test_mapPBA[i].LBA);
    }

    // Make sure that the trace_test data members sizes remain the same
    assert(trace_test_mapLBA.size() == trace_test_mapPBA.size());
}

/// Test to make sure that the helper function fix_PBAs() works on larger cases
TEST(fix_PBAS, large)
{

    TraceSet trace;
    TraceSet trace_test;

    //loop through and insert elements in tracesset objects
    string s;
    size_t value;
    for(size_t i = 0; i < 1000; ++i) {

        value = 1000 - i;
        s = to_string(value);

        trace.insert(s);
        trace_test.insert(s);

    }

    // Getting a reference to the mapLBA_ object traceset_test
    vector<TraceSet::blockLBA>& test_mapLBA = trace_test.get_mapLBA();

    // Looping through traceset_test mapLBA and changing some of the PBAs
    int new_value;
    for (int i = 0; i < 50; ++i) {

        new_value = 20*i;
        test_mapLBA[new_value].PBA = 100;

    }

    // Using fix_PBAS to fix the PBAs which should set them back to the
    // original values
    trace_test.fix_PBAs();

    // Get the provate data members from both the traceset and trace_set test
    vector<TraceSet::blockLBA>& trace_mapLBA = trace.get_mapLBA();
    vector<TraceSet::blockLBA>& trace_test_mapLBA = trace_test.get_mapLBA();

    vector<TraceSet::blockPBA>& trace_mapPBA = trace.get_mapPBA();
    vector<TraceSet::blockPBA>& trace_test_mapPBA = trace_test.get_mapPBA();

    // Check that fix_PBAs reset the values properly
    for(int i = 0; i < 1000; ++i) {

        assert(trace_mapLBA[i].PBA == trace_test_mapLBA[i].PBA);
        assert(trace_mapPBA[i].LBA == trace_test_mapPBA[i].LBA);
    }

    // Make sure that the trace_test data members sizes remain the same
    assert(trace_test_mapLBA.size() == trace_test_mapPBA.size());
}

// Make sure that change_PBAs when changing one element in front is inserted and
// element previously resided in the middle of the trace object
TEST(change_PBAs, first_from_middle)
{

    TraceSet trace_test;

    // Insert elements into the traceset objects
    string s;
    size_t value;

    for(size_t i = 0; i < 5; ++i) {

        value = i;
        s = to_string(value);
        trace_test.insert(s);

    }

     // Access data members of trace_test and trace
     vector<TraceSet::blockLBA>& trace_test_mapLBA = trace_test.get_mapLBA();
     vector<TraceSet::blockPBA>& trace_test_mapPBA = trace_test.get_mapPBA();

     // Switch values in trace_test so that the instead of the LBA 0 being
     // at PBA 0 LBA 0 is now at PBA 4 and LBA 4 is at PBA 0
     trace_test_mapLBA[2].PBA = 0;
     trace_test_mapLBA[0].PBA = 2;

     trace_test_mapPBA[0].LBA = 2;
     trace_test_mapPBA[2].LBA = 0;

    // Create a vector of 1 element to insert
    vector<size_t> to_insert;

    // Set value of element in vector
    to_insert.push_back(0);

      cout << "LBAs before chang_order" << endl;
    for (size_t i = 0; i < trace_test_mapPBA.size(); ++i) {
        cout << trace_test_mapPBA[i].LBA <<endl;
    }

    // call change_PBA, which should change the LBA 0 to be at location 0, which
    // if it operates it properly will cause the data members of trace_test to
    // t be equivalent to that of trace
    trace_test.change_order_PBA(to_insert, 0);

    cout << "LBAs after chang_order" << endl;
    for (size_t i = 0; i < trace_test_mapPBA.size(); ++i) {
        cout << trace_test_mapPBA[i].LBA <<endl;
    }

    cout << "PBAs after chang_order" << endl;
    for (size_t i = 0; i < trace_test_mapPBA.size(); ++i) {
        cout << trace_test_mapLBA[i].PBA <<endl;
    }

    // Check that fix_PBAs reset the values properly
    assert(trace_test_mapPBA[0].LBA == 0);
    assert(trace_test_mapLBA[0].PBA == 0);

    cout << trace_test_mapLBA[2].PBA <<endl;

    assert(trace_test_mapPBA[1].LBA == 2);
    assert(trace_test_mapLBA[2].PBA == 1);

    assert(trace_test_mapPBA[2].LBA == 1);
    assert(trace_test_mapLBA[1].PBA == 2);

    assert(trace_test_mapPBA[3].LBA == 3);
    assert(trace_test_mapLBA[3].PBA == 3);

    assert(trace_test_mapPBA[4].LBA == 4);
    assert(trace_test_mapLBA[4].PBA == 4);

    for(int i = 0; i < 5; ++i) {
        assert(trace_test_mapLBA[i].used == true);
        assert(trace_test_mapPBA[i].used == true);
    }

    // Make sure that the sizes of the traceset objects vectors are equal and
    // have a valid size
    assert(trace_test_mapLBA.size() > 5);
    assert(trace_test_mapLBA.size() == trace_test_mapPBA.size());

    // Check to make sure that indices within the array that should have not
    // been used are not used.
    for(size_t i = 5; i < trace_test_mapPBA.size(); ++i) {

        assert(trace_test_mapPBA[i].used == false);
        assert(trace_test_mapLBA[i].used == false);
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
