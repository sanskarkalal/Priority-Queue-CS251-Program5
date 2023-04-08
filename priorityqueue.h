
/// @file priorityqueue.h
///
///
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    void inorder (NODE * root, ostream &ss){
        if(root == nullptr){
            return;
        }

        inorder(root->left, ss);
        //ss <<root->priority <<" value: "<< root->value << endl;
        if(root->dup){
            NODE * temp = root;
            while(temp != nullptr){
                ss <<temp->priority <<" value: "<< temp->value << endl;
                temp = temp->link;
            }
        }
        else{
            ss <<root->priority <<" value: "<< root->value << endl;
        }

        inorder(root->right,ss);
    }

    void postorder(NODE * root){
        if(root == nullptr){
            return;
        }
        postorder(root->left);
        postorder(root->right);
        postorder(root->link);

        delete root;
    }

    void preorder(NODE* node){

        if(node == NULL){
            return;
        }else{
            NODE * temp = node;
            enqueue(temp->value,temp->priority);

            if(temp->link != NULL){
                while(temp->link != NULL){
                    temp = temp->link;
                    enqueue(temp->value,temp->priority);
                }
            }

            preorder(node->left);
            preorder(node->right);
        }


    }


    NODE* getNewNode(T value, int priority){
        NODE * newNode = new NODE();
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->link = nullptr;
        newNode->dup = false;
        newNode->value = value;
        newNode->priority = priority;
        return newNode;
    }

    bool compare(NODE * one,NODE* two) const{
        if(one  == NULL && two == NULL){
            return true;
        }
        if(one == NULL && two != NULL){
            return false;
        }
        if(one->value != two->value){
            return false;
        }
        if(!compare(one->left,two->left)){
            return false;
        }
        if(!compare(one->right,two->right)){
            return false;
        }
        if(!compare(one->link,two->link)){
            return false;
        }
        return true;
    }
public:



    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = root;
    }



    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        this->clear();
        preorder(other.root);
        this->size = other.size;
        //this->root = other.root;


        // TO DO: write this function.
        return *this;


    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        postorder(root);
        size = 0;
        root = NULL;

        // TO DO: write this function.


    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {

        this->clear();
        // TO DO: write this function.


    }







    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE * current = root;
        NODE * prev = nullptr;
        bool dup = false;
        while(current != nullptr){
            if(current->priority>priority){
                prev = current;
                current = current->left;
            }
            else if(current->priority<priority){
                prev = current;
                current = current->right;
            }
            else{
                dup = true;
                current->dup = true;
                break;
            }
        }

        NODE * newNode = getNewNode(value, priority);
        newNode->parent = prev;
        if(dup){
            // duplicate priority

            while(current->link != nullptr){
                prev = current;
                current = current->link;
            }
            newNode->parent = current;
            current->link = newNode;
        }
        else{
            if(prev == nullptr){

                root = newNode;
            }
            else if(prev->priority>priority){


                prev->left = newNode;
            }
            else{

                prev->right = newNode;
            }
        }
        size++;
    }




    // TO DO: write this function.


    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    T dequeue() {
        NODE *temp = root;
        NODE *prev = nullptr;
        T valueOut;
        if (temp == nullptr) {
            cout << "empty" << endl;
            return T();
        }
        while (temp->left != nullptr) {
            prev = temp;
            temp = temp->left;
        }

        if (temp->dup == false) {
            if (temp == root) {
                root = temp->right;
                temp->parent = nullptr;
                valueOut = temp->value;

                delete temp;
                size--;
                return valueOut;
            } else {
                if (temp->right != nullptr) {
                    temp->right->parent = prev;
                }
                prev->left = temp->right;
                valueOut = temp->value;

                delete temp;
                size--;
                return valueOut;
            }

        } else {
            if (temp == root) {
                valueOut = temp->value;
                if(temp->link->link != nullptr){
                    temp->link->dup = true;
                }else{
                    temp->link->dup = false;
                }
                if(temp->right != nullptr) {
                    temp->link->right = temp->right;
                    temp->right->parent = temp->link;
                }

                temp->link->parent = nullptr;
                root = temp->link;
                delete temp;
                size--;
                return valueOut;
            } else {
                valueOut = temp->value;
                if(temp->link->link != nullptr){
                    temp->link->dup = true;
                }else{
                    temp->link->dup = false;
                }
                if (temp->right != nullptr) {
                    temp->link->right = temp->right;
                    temp->right->parent = temp->link;
                }
                prev->left = temp->link;
                temp->link->parent = prev;
                delete temp;
                size--;
                return valueOut;


            }
        }
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {

        return size; // TO DO: update this return

    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        curr = root;
        while(curr->left != nullptr){
            curr = curr->left;
        }
        // TO DO: write this function.


    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        if (curr == nullptr) {
            return false;
        }

        value = curr->value;
        priority = curr->priority;

        if(curr->right != NULL){
            curr = curr->right;
            while(curr->left != NULL){
                curr = curr->left;
            }
            return true;
        }else{
            while(curr->parent->priority < curr->priority && curr->parent != nullptr){
                curr = curr->parent;
            }
            if(curr->parent!= NULL){
                curr = curr->parent;
            }

            return true;
        }

    }









    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString()
    {
        stringstream ss;
        inorder(root,ss);
        return ss.str();

    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    T peek() {


        // TO DO: write this function.
        T valueOut;
        NODE * temp = root;
        while(temp->left != NULL){
            temp = temp->left;
        }
        valueOut = temp->value;
        return valueOut; // TO DO: update this return


    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        if(size != other.size){
            return false;
        }

        return compare(root,other.root);


        // TO DO: write this function.
        // TO DO: update this return


    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};