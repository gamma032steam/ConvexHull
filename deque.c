/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Matthew Lui 993333 
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for
//  - new_deque()
//  - free_deque()
//  - deque_push()
//  - deque_insert()
//  - deque_pop()
//  - deque_remove()
//  - deque_size()
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "deque.h"
#include "point.h"
#include "list.h"

struct deque {
    List* myList;  
};

// Create a new empty Deque and return a pointer to it
Deque *new_deque() {
    // Make some space
    Deque* newDeque = malloc(sizeof(*newDeque));
    assert(newDeque);
    // List list do the work
    newDeque->myList = new_list();
    return newDeque;
}


// Free the memory associated with a Deque
void free_deque(Deque *deque) {
    assert(deque);
    // Free the underlying list first
    free_list(deque->myList);
    // All that is left is the deque struct
    free(deque);
}

// Add a Point to the top of a Deque
//
// Runtime: O(1)
void deque_push(Deque *deque, Point data) {
    // The top is the end of the list
    list_add_end(deque->myList, data);
}

// Add a Point to the bottom of a Deque
//
// Runtime: O(1)
void deque_insert(Deque *deque, Point data) {
    // The bottom is the start of the list
    list_add_start(deque->myList, data);
}

// Remove and return the top Point from a Deque
//
// Runtime: O(1)
Point deque_pop(Deque *deque) {
    // Pop from top (end of the list)
    return list_remove_end(deque->myList);
}

// Remove and return the bottom Point from a Deque
//
// Runtime: O(1)
Point deque_remove(Deque *deque) {
    // Remove from bottom (start of the list)
    return list_remove_start(deque->myList);
}

// Return the number of Points in a Deque
//
// Runtime: O(1)
int deque_size(Deque *deque) {
    return list_size(deque->myList);
}

void print_deque(Deque* myDeque) {
    print_list(myDeque->myList);
}

Point index_deque(Deque* myDeque, int index) {
    return index_list(myDeque->myList, index);
}
