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
#include "vector"
#include "random"

using namespace std;

TEST_CASE("enqueue and toString")
{
    SECTION("ints"){
        srand(1);
        priorityqueue<int> pq;
        map<int, vector<int> > map;
        for(int i=0; i< 25 ;i++){
            int val = rand() % 100;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
            REQUIRE(pq.Size() ==  i+1);
        }

    }

    SECTION("strings"){
        srand(1);
        priorityqueue<string> pq;

        for(int i=0; i< 25 ;i++){
            string val = "a" + to_string(rand() % 100);
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            REQUIRE(pq.Size() ==  i+1);
        }

    }

    SECTION("chars"){
        srand(1);
        priorityqueue<char> pq;
        for(int i=0; i< 25 ;i++){
            char val = 'a' + rand() % 26;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            REQUIRE(pq.Size() ==  i+1);
        }

    }

    SECTION("floats"){
        srand(1);
        priorityqueue<float> pq;
        for(int i=0; i< 25 ;i++){
            float val = (rand() % 100)/100.0;
            int pr = (rand() % 100);
            pq.enqueue(val, pr);
            REQUIRE(pq.Size() ==  i+1);
        }

    }



}

TEST_CASE("dequeue ()"){

    SECTION("empty"){
        priorityqueue<int> pq;
        REQUIRE(pq.dequeue() == 0);
    }

    SECTION("tree without duplicates"){
        map<int, vector<int> > map;
        vector<int> vals = {13,21,13,5,42,55,12,3,1,10};
        vector<int> prs = {2, 4, 3, 1, 10, 8, 9, 5, 6,11};
        priorityqueue<int> pq;
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.Size() ==  10);

        for (auto e: map) {
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() ==  values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);

    }

    SECTION("trees with duplicates"){
        map <int, vector<int> > map;
        vector<int> vals = {13,21,13,5,42,55,12,3,1,10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9,11};
        priorityqueue<int> pq;
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]].push_back(vals[i]);
        }
        REQUIRE(pq.Size() ==  10);
        for (auto e: map) {
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() ==  values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);
    }

    SECTION("random strings tree"){
        srand(1);
        priorityqueue<string> pq;
        map<int, vector<string> > map;
        for(int i=0; i< 25 ;i++){
            string val = "a" + to_string(rand() % 100);
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
            REQUIRE(pq.Size() ==  i+1);
        }
        for (auto e: map) {
            vector <string> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() ==  values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);

    }

    SECTION("random float tree"){
        srand(1);
        priorityqueue<float> pq;
        map<int, vector<float> > map;
        for(int i=0; i< 25 ;i++){
            float val = (rand() % 100)/100.0;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
            REQUIRE(pq.Size() ==  i+1);
        }
        for (auto e: map) {
            vector <float> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() ==  values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);

    }

    SECTION("random char tree"){
        srand(1);
        priorityqueue<char> pq;
        map<int, vector<char> > map;
        for(int i=0; i< 25 ;i++){
            char val = 'a' + rand() % 26;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
            REQUIRE(pq.Size() ==  i+1);
        }
        for (auto e: map) {
            vector <char> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() ==  values[j]);
            }
        }
        REQUIRE(pq.Size() ==  0);

    }



}

TEST_CASE("default constructor"){
    priorityqueue<int> pq;
    REQUIRE(pq.Size() ==  0);
    REQUIRE(getRoot(pq) ==  nullptr);
}

TEST_CASE("")



