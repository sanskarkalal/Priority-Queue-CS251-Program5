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

TEST_CASE("(0) no tests") 
{
    priorityqueue<string> pq;
    pq.enqueue("ten",10);
    pq.enqueue("two",2);
    pq.enqueue("two 1",2);
    pq.enqueue("one",1);
    pq.enqueue("one 1",1);
    pq.enqueue("one 2",1);
    pq.enqueue("thirteen",13);
    pq.enqueue("fourteen",14);
    pq.enqueue("twelve",12);
    pq.enqueue("six",6);
    pq.enqueue("six 1",6);
    pq.enqueue("eleven",11);
    pq.begin();
    string value = "";
    int priority = 0;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;
    pq.next(value,priority);
    cout << value << " " << priority << endl;









}



