/// @file tests.cpp
/// @date March 17, 2023

/// 
/// TODO

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// TODO:
// Choose which framework to keep and delete the other.
//


// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"

using namespace std;

TEST_CASE("(0) no tests") 
{
    priorityqueue<int> Q;
    Q.enqueue(1,3);
    Q.enqueue(2,2);
    Q.enqueue(3,4);
    Q.enqueue(4,1);
    REQUIRE(Q.Size() == 4);

}



