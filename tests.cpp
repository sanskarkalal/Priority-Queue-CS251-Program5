/* -----------------------------------
Program 5: Priority Queue (Custom BST)

This program implements a priority queue using a custom BST. The BST is
implemented using a linked list of nodes. The nodes are linked together
when there are duplicate priorities.

Author: Sanskar Kalal
Course: CS 251, Spring 2023, UIC

----------------------------------- */


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

    SECTION("random strings queue"){
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

    SECTION("random float queue"){
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

    SECTION("random char queue"){
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

}

TEST_CASE("assignment operator"){
    SECTION("assigning empty queue to full queue"){
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        pq.enqueue(1, 1);
        pq.enqueue(2, 2);
        pq.enqueue(2, 8);
        pq = pq2;
        REQUIRE(pq.Size() ==  0);
        REQUIRE(pq2.Size() ==  0);

    }

    SECTION("assigning full queue to empty queue"){
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        pq2.enqueue(1, 1);
        pq2.enqueue(2, 2);
        pq2.enqueue(2, 8);
        pq = pq2;
        REQUIRE(pq.Size() ==  3);
        REQUIRE(pq2.Size() ==  3);
    }

    SECTION("assigning longer queue to shorter queue "){
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        map<int, vector<int> > map1;
        map<int, vector<int> > map2;
        vector<int> vals = {13,21,13,5,42,55,12,3,1,10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9,11};
        vector<int> vals2 = {13,21,13,5,42,55};
        vector<int> prs2 = {1,3,1,3,5,6};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map1[prs[i]].push_back(vals[i]);
        }
        for(int i = 0; i < vals2.size(); i++){
            pq2.enqueue(vals2[i], prs2[i]);
            map2[prs2[i]].push_back(vals2[i]);
        }
        REQUIRE(pq.Size() ==  10);
        REQUIRE(pq2.Size() ==  6);
        pq2 = pq;
        REQUIRE(pq.Size() ==  10);
        REQUIRE(pq2.Size() ==  10);
        for (auto e: map1) {
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() == pq2.dequeue());
            }
        }

    }
    SECTION("assigning shorter queue to longer queue"){
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        map<int, vector<int> > map1;
        map<int, vector<int> > map2;
        vector<int> vals = {13,21,13,5,42,55,12,3,1,10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9,11};
        vector<int> vals2 = {13,21,13,5,42,55};
        vector<int> prs2 = {1,3,1,3,5,6};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map1[prs[i]].push_back(vals[i]);
        }
        for(int i = 0; i < vals2.size(); i++){
            pq2.enqueue(vals2[i], prs2[i]);
            map2[prs2[i]].push_back(vals2[i]);
        }
        REQUIRE(pq.Size() ==  10);
        REQUIRE(pq2.Size() ==  6);
        pq = pq2;
        REQUIRE(pq.Size() ==  6);
        REQUIRE(pq2.Size() ==  6);
        for (auto e: map2) {
            vector <int> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() == pq2.dequeue());
            }
        }

    }
    SECTION("strings"){

        priorityqueue<string> pq;
        priorityqueue<string> pq2;
        map<int, vector<string> > map1;
        map<int, vector<string> > map2;
        vector<string> vals = {"hello", "world", "this", "is", "a", "test"};
        vector<int> prs = {2, 2, 3, 1, 1, 8};
        vector<string> vals2 = {"hello", "world", "this", "is", "a", "test", "of", "the", "emergency", "broadcast", "system"};
        vector<int> prs2 = {1,3,1,3,5,6, 7, 8, 9, 10, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map1[prs[i]].push_back(vals[i]);
        }
        for(int i = 0; i < vals2.size(); i++){
            pq2.enqueue(vals2[i], prs2[i]);
            map2[prs2[i]].push_back(vals2[i]);
        }
        REQUIRE(pq.Size() ==  6);
        REQUIRE(pq2.Size() ==  11);
        pq = pq2;
        REQUIRE(pq.Size() ==  11);
        REQUIRE(pq2.Size() ==  11);
        for (auto e: map2) {
            vector <string> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() == pq2.dequeue());
            }
        }
    }

    SECTION("floats"){
        priorityqueue<float> pq;
        priorityqueue<float> pq2;
        map<int, vector<float> > map1;
        map<int, vector<float> > map2;
        vector<float> vals = {13.2,21.3,13.4,5.5,42.6,55.7,12.8,3.9,1.10,10.11};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9,11};
        vector<float> vals2 = {13.2,21.3,13.4,5.5,42.6,55.7};
        vector<int> prs2 = {1,3,1,3,5,6};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map1[prs[i]].push_back(vals[i]);
        }
        for(int i = 0; i < vals2.size(); i++){
            pq2.enqueue(vals2[i], prs2[i]);
            map2[prs2[i]].push_back(vals2[i]);
        }
        REQUIRE(pq.Size() ==  10);
        REQUIRE(pq2.Size() ==  6);
        pq = pq2;
        REQUIRE(pq.Size() ==  6);
        REQUIRE(pq2.Size() ==  6);
        for (auto e: map2) {
            vector <float> values = e.second;
            for (size_t j = 0; j < values.size(); j++){
                REQUIRE(pq.dequeue() == pq2.dequeue());
            }
        }
    }
}

TEST_CASE("begin and next"){
    SECTION("empty queue"){
       priorityqueue<int> pq;
       pq.begin();
       int val =0 ;
       int pr = 0;
       REQUIRE(pq.next(val,pr) == false);
       REQUIRE(val == 0);
       REQUIRE(pr == 0);
    }
    SECTION("normal queue"){
        priorityqueue<int> pq;
        vector<int> vals = {13,21,13,5,42,55,12,3,1,10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9,11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
        }
        pq.begin();
        int val, pr;
        REQUIRE(pq.next(val,pr) == true);
        REQUIRE(val == 5);
        REQUIRE(pr == 1);
    }

    SECTION("normal queue random order"){
        priorityqueue<int> pq;
        map<int, vector<int> > map1;
        for(int i = 0; i < 100; i++){
            int val = rand() % 100;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        pq.begin();
        int val, pr;
        while(pq.next(val,pr)){
            REQUIRE(map1[pr].front() == val);
            map1[pr].erase(map1[pr].begin());
        }

    }

    SECTION("string queue random order"){
        priorityqueue<string> pq;
        map<int, vector<string> > map1;
        for(int i = 0; i < 100; i++){
            string val = "hello " + to_string(rand() % 100);
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        pq.begin();
        string val;
        int pr;
        while(pq.next(val,pr)){
            REQUIRE(map1[pr].front() == val);
            map1[pr].erase(map1[pr].begin());
        }

    }

    SECTION("floats queue random order"){
        priorityqueue<float> pq;
        map<int, vector<float> > map1;
        for(int i = 0; i < 100; i++){
            float val = (rand() % 100)/1000.0;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        pq.begin();
        float val;
        int pr;
        while(pq.next(val,pr)){
            REQUIRE(map1[pr].front() == val);
            map1[pr].erase(map1[pr].begin());
        }

    }


}

TEST_CASE("peek"){
    SECTION("peek empty"){
        priorityqueue<int> pq;
        REQUIRE(pq.peek() == 0);
    }

    SECTION("peek normal random order"){
        priorityqueue<int> pq;
        map<int, vector<int> > map1;
        for(int i = 0; i < 100; i++){
            int val = rand() % 100;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        for(auto e: map1){
            vector<int> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                REQUIRE(pq.peek() == values[i]);
                pq.dequeue();
            }
        }

    }

    SECTION("peek normal random order strings"){
        priorityqueue<string> pq;
        map<int, vector<string> > map1;
        for(int i = 0; i < 100; i++){
            string val = "hello " + to_string(rand() % 100);
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        for(auto e: map1){
            vector<string> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                REQUIRE(pq.peek() == values[i]);
                pq.dequeue();
            }
        }

    }

    SECTION("peek normal random order floats"){
        priorityqueue<float> pq;
        map<int, vector<float> > map1;
        for(int i = 0; i < 100; i++){
            float val = (rand() % 100)/1000.0;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map1[pr].push_back(val);
        }
        for(auto e: map1){
            vector<float> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                REQUIRE(pq.peek() == values[i]);
                pq.dequeue();
            }
        }

    }

}

TEST_CASE("equals operator overload") {
    SECTION("empty queue") {
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        REQUIRE(pq == pq2);
    }
    SECTION("normal queue") {
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        vector<int> vals = {13, 21, 13, 5, 42, 55, 12, 3, 1, 10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            pq2.enqueue(vals[i], prs[i]);
        }
        REQUIRE(pq == pq2);
    }
    SECTION("normal queue is not equal") {
        priorityqueue<int> pq;
        priorityqueue<int> pq2;
        vector<int> vals = {13, 21, 13, 5, 42, 55, 12, 3, 1, 10};
        vector<int> prs = {2, 2, 3, 1, 1, 8, 9, 5, 9, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            pq2.enqueue(vals[i], prs[i]);
        }
        pq2.dequeue();
        REQUIRE(pq != pq2);

    }
    SECTION("strings"){
        priorityqueue<string> pq;
        priorityqueue<string> pq2;
        vector<string> vals = {"hello", "world", "this", "is", "a", "test"};
        vector<int> prs = {2, 2, 3, 1, 1, 8};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            pq2.enqueue(vals[i], prs[i]);
        }
        REQUIRE(pq == pq2);
        pq.dequeue();
        REQUIRE(pq != pq2);
    }
    SECTION("floats"){
        priorityqueue<float> pq;
        priorityqueue<float> pq2;
        vector<float> vals = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
        vector<int> prs = {2, 2, 3, 1, 1, 8};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            pq2.enqueue(vals[i], prs[i]);
        }
        REQUIRE(pq == pq2);
        pq.dequeue();
        REQUIRE(pq != pq2);
    }

}

TEST_CASE("clear"){
    SECTION("empty queue"){
        priorityqueue<int> pq;
        pq.clear();
        REQUIRE(pq.Size() == 0);
    }
    SECTION("normal queue without duplicates"){
        priorityqueue<int> pq;
        vector<int> vals = {13, 21, 13, 5, 42, 55, 12, 3, 1, 10};
        vector<int> prs = {2, 13, 3, 1, 12, 8, 9, 5, 10, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
        }
        pq.clear();
        REQUIRE(pq.Size() == 0);
    }
    SECTION("normal queue with duplicates"){
        priorityqueue<int> pq;
        vector<int> vals = {13, 21, 13, 5, 42, 55, 12, 3, 1, 10};
        vector<int> prs = {2, 1, 3, 1, 2, 8, 9, 5, 11, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
        }
        pq.clear();
        REQUIRE(pq.Size() == 0);
    }
}


TEST_CASE("toString function"){
    SECTION("empty queue"){
        priorityqueue<int> pq;
        REQUIRE(pq.toString() == "");
    }
    SECTION("normal queue with duplicates"){
        map<int, vector<int> > map;
        priorityqueue<int>pq;
        for(int i = 0; i < 100; i++){
            int val = rand() % 100;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
        }
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            vector<int> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                ss << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());

    }
    SECTION("normal queue without duplicates"){
        priorityqueue<int> pq;
        map<int, int> map;
        vector<int> vals = {13, 21, 13, 5, 42, 55, 12, 3, 1, 10};
        vector<int> prs = {2, 13, 3, 1, 12, 8, 9, 5, 10, 11};
        for (int i = 0; i < vals.size(); i++) {
            pq.enqueue(vals[i], prs[i]);
            map[prs[i]] = vals[i];
        }
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            int value = e.second;
            ss << priority << " value: " << value << endl;
        }
        REQUIRE(pq.toString() == ss.str());

    }

    SECTION("string"){
        priorityqueue<string> pq;
        map<int, vector<string> > map;
        for(int i = 0; i < 100; i++){
            string val = "hello " + to_string(rand() % 100);
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
        }
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            vector<string> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                ss << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
    }

    SECTION("floats"){
        priorityqueue<float> pq;
        map<int, vector<float> > map;
        for(int i = 0; i < 100; i++){
            float val = (rand() % 100)/100.0;
            int pr = rand() % 100;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
        }
        stringstream ss;
        for (auto e: map) {
            int priority = e.first;
            vector<float> values = e.second;
            for(size_t i = 0; i < values.size(); i++){
                ss << priority << " value: " << values[i] << endl;
            }
        }
        REQUIRE(pq.toString() == ss.str());
    }


}

TEST_CASE("getRoot"){
    SECTION("empty queue"){
        priorityqueue<int> pq;
        REQUIRE(pq.getRoot() == nullptr);
    }
}






