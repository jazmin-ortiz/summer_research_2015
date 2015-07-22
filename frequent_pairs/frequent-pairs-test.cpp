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

// Empty test that is a place holder currently
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

