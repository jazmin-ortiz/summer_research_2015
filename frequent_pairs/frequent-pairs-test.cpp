/**
 * \file frequent-pairs-test.cpp
 *
 * \Authors Jazmin Ortiz
 *
 * \brief Tests a FrequentPairs for correctness
 */

#include "FrequentPairs.hpp"
#include "gtest/gtest.h"

#include <memory>

using namespace std;

//--------------------------------------------------
//           TEST FUNCTIONS
//--------------------------------------------------

TEST(constructor, default_constructor)
{
    FrequentPairs test;
    vector<size_t>& test_sequence = test.get_Sequence();
    unordered_map<size_t,size_t>& test_Table = test.get_FrequentLBAsTable();
    vector<size_t>& test_FreqLBAs = test.get_FrequentLBAs();

    // Make sure that all data members when default constructed contain no
    // elements.
    assert(test_sequence.empty());
    assert(test_FreqLBAs.empty());

    assert(test_Table.size() == 0);

}

TEST(empty, emptyone)
{
    //do nothing
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

