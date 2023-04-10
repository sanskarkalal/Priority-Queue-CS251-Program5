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
#include "map"

using namespace std;

TEST_CASE("enqueue and toString")
{
    SECTION("ints"){

        map<int, vector<int> > map;
        int n = 9;
        int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
        int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
        priorityqueue<int> pq;
        for (int i = 0; i < n; i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.Size() ==  9);
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                ss << priority << " value: " << values[j] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());

    }

    SECTION("strings"){

        map<int, vector<string> > map;
        int n = 9;
        int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
        int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
        priorityqueue<string> pq;
        for (int i = 0; i < n; i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.Size() ==  9);
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                ss << priority << " value: " << values[j] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());






    }
}

TEST_CASE("dequeue ()"){

    SECTION("ints"){

        map<int, vector<int> > map;
        int n = 10;
        int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1,12};
        int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3,4};
        priorityqueue<int> pq;
        for (int i = 0; i < n; i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.Size() ==  10);
        for (auto e: map) {
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() == values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);

    }



}



