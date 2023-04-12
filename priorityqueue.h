
/* -----------------------------------
Program 5: Priority Queue (Custom BST)

This program implements a priority queue using a custom BST. The BST is
implemented using a linked list of nodes. The nodes are linked together
when there are duplicate priorities.

Author: Sanskar Kalal
Course: CS 251, Spring 2023, UIC

----------------------------------- */

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

    void inorder (NODE * root, ostream &ss) const{
        // return if the current node is empty
        if(root == nullptr){
            return;
        }

        // Traverse the left subtree
        inorder(root->left, ss);

        // check if there are duplicates
        if(root->dup){
            NODE * temp = root;
            // get the duplicates in order
            while(temp != nullptr){
                ss <<temp->priority <<" value: "<< temp->value << endl;
                temp = temp->link;
            }
        }
        else{
            // no duplicates
            ss <<root->priority <<" value: "<< root->value << endl;
        }

        // Traverse the right subtree
        inorder(root->right,ss);
    }

    // helper function for the destructor
    void postorder(NODE * root){
        // return if the current node is empty
        if(root == nullptr){
            return;
        }

        // Traverse the left subtree
        postorder(root->left);

        // Traverse the right subtree
        postorder(root->right);

        // check if there are duplicates
        postorder(root->link);

        // delete the current node
        delete root;
    }

    // helper function for the copy constructor
    void preorder(NODE* node){

        // return if the current node is empty
        if(node == NULL){
            return;
        }else{
            NODE * temp = node;

            // add to the new tree
            enqueue(temp->value,temp->priority);

            // check if there are duplicates
            if(temp->link != NULL){
                while(temp->link != NULL){
                    temp = temp->link;

                    // add to the new tree
                    enqueue(temp->value,temp->priority);
                }
            }

            // Traverse the left subtree
            preorder(node->left);

            // Traverse the right subtree
            preorder(node->right);
        }


    }


    // helper function to make a new node
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

        // clear the current tree
        this->clear();

        // copy the other tree
        preorder(other.root);

        // set the size
        this->size = other.size;

        // return the new tree
        return *this;

    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {

        // call the helper function
        postorder(root);

        // set the size to 0
        size = 0;

        // set the root to null
        root = NULL;

    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {

        // call the helper function
        this->clear();

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

        // find the correct location
        while(current != nullptr){

            // check if the priority is less than the current node
            if(current->priority>priority){
                prev = current;
                current = current->left;
            }

            // check if the priority is greater than the current node
            else if(current->priority<priority){
                prev = current;
                current = current->right;
            }

            // check if the priority is equal to the current node
            else{
                dup = true;
                current->dup = true;
                break;
            }
        }

        // create the new node
        NODE * newNode = getNewNode(value, priority);

        // keep track of the parent
        newNode->parent = prev;

        // check if there are duplicates
        if(dup){

            // add to the end of the list
            while(current->link != nullptr){
                prev = current;
                current = current->link;
            }

            // update the parent
            newNode->parent = current;
            current->link = newNode;
        }
        else{
            // check if the tree is empty
            if(prev == nullptr){
                root = newNode;
            }

            // check if the priority is less than the parent
            else if(prev->priority>priority){
                prev->left = newNode;
            }

            // check if the priority is greater than the parent
            else{
                prev->right = newNode;
            }
        }
        size++; // increment the size
    }



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

        // check if the tree is empty
        if (temp == nullptr) {
            return T();
        }

        // check if there is a left child
        while (temp->left != nullptr) {
            prev = temp;
            temp = temp->left; // go left
        }

        // if there are no duplicates
        if (temp->dup == false) {

            // check if the node is the root
            if (temp == root) {

                // move the root to the right child
                root = temp->right;

                // set the parent to null
                temp->parent = nullptr;

                // set the value to return
                valueOut = temp->value;

                // delete the node
                delete temp;

                // decrement the size
                size--;

                // return the value
                return valueOut;
            } else {

                // check if the node has a right child
                if (temp->right != nullptr) {

                    // adjust the parent
                    temp->right->parent = prev;
                }

                // adjust the pointers of the parent and the node
                prev->left = temp->right;

                // set the value to return
                valueOut = temp->value;


                // delete the node
                delete temp;
                size--; // decrement the size
                return valueOut; // return the value
            }

        } else {

            // if duplicates exist and the node is the root
            if (temp == root) {

                // set the value to return
                valueOut = temp->value;

                // check if it is the last duplicate
                if(temp->link->link != nullptr){
                    temp->link->dup = true; // set the duplicate flag to true
                }else{
                    temp->link->dup = false; // set the duplicate flag to false
                }
                // check if the node has a right child
                if(temp->right != nullptr) {
                    // adjust the right child
                    temp->link->right = temp->right;
                    // adjust the parent link
                    temp->right->parent = temp->link;
                }

                // adjust the pointers
                temp->link->parent = nullptr;

                // move the root to the next duplicate
                root = temp->link;

                // delete the node
                delete temp;
                size--; // decrement the size
                return valueOut; // return the value
            } else {
                // set the value to return
                valueOut = temp->value;

                // check if it is the last duplicate
                if(temp->link->link != nullptr){
                    temp->link->dup = true; // set the duplicate flag to true
                }else{
                    temp->link->dup = false; // set the duplicate flag to false
                }

                // check if the node has a right child
                if (temp->right != nullptr) {
                    // adjust the right child
                    temp->link->right = temp->right;
                    // adjust the parent link
                    temp->right->parent = temp->link;
                }

                // adjust the pointers
                prev->left = temp->link;

                // adjust the parent link
                temp->link->parent = prev;

                // delete the node
                delete temp;
                size--; // decrement the size
                return valueOut; // return the value


            }
        }
    }


    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        // return the size
        return size;

    }


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

        // set the current node to the root
        curr = root;

        // check if the tree is empty
        if(curr == nullptr){
            return;
        }

        // traverse to the left most node
        while(curr->left != nullptr){
            curr = curr->left;
        }


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

        // check if the tree is empty
        if (curr == nullptr) {
            return false;
        }

        value = curr->value; // set the value
        priority = curr->priority; // set the priority

        // check if the node has duplicates
        if(curr->link != nullptr) {
            curr = curr->link; // move to the next duplicate
            return true;
        }

        // back track from the duplicates
        while(curr->parent != nullptr && curr->priority == curr->parent->priority ){
            curr = curr->parent;
        }

        // check if the node has a right subtree
        if(curr->right != NULL){

            // traverse to the left most node
            curr = curr->right;
            while(curr->left != NULL){
                curr = curr->left;
            }
            return true;
        }else{

            // traverse to the unvisited parent
            while(curr->parent != nullptr && curr->parent->priority < curr->priority){
                curr = curr->parent;
                // check if root is reached
                if(curr->parent == nullptr){

                    // traversal is complete
                    curr = nullptr;
                    return false;
                }
            }

            // check if the node is not the root
            if(curr->parent!= NULL){
                // traverse to the unvisited parent
                curr = curr->parent;
                return true;
            }

            // traversal is complete
            return false;

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

        // call the inorder function
        inorder(root,ss);

        // return the string
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



        T valueOut = T();
        NODE * temp = root;

        // check if the tree is empty
        if(temp == nullptr){
            return valueOut;
        }

        // traverse to the left most node
        while(temp->left != NULL){
            temp = temp->left;
        }


        valueOut = temp->value;
        return valueOut; // return the value


    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {

        // check if the size is the same
        if(size != other.size){
            return false;
        }

        stringstream ss1;
        stringstream ss2;


        // call the inorder function
        inorder(root,ss1);

        // call the inorder function
        inorder(other.root,ss2);

        // check if the strings are the same
        return ss1.str() == ss2.str();


    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {

        // return the root
        return root;
    }
};