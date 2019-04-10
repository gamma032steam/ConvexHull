/* * * * * * *
 * Module for creating and manipulating doulbe-linked lists of integers
 *
 * created for COMP20007 Design of Algorithms 2017
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 *
 * Modified by Matthew Lui 993333
 */

// 'include guards': these lines (and #endif at the bottom) prevent this file
// from being included multiple times. multiple inclusion can cause errors on
// some compilers, especially if the included file contains struct definitions
// how it works: https://en.wikipedia.org/wiki/Include_guard
#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "point.h"

typedef struct list List;

// create a new list and return its pointer
List *new_list();

// destroy a list and free its memory
void free_list(List *list);

// add an element to the front of a list
// this operation is O(1)
void list_add_start(List *list, Point newPoint);

// add an element to the back of a list
// this operation is O(1)
void list_add_end(List *list, Point newPoint);

// remove and return the front data element from a list
// this operation is O(1)
// error if the list is empty (so first ensure list_size() > 0)
Point list_remove_start(List *list);

// remove and return the final data element in a list
// this operation is O(n), where n is the number of elements in the list
// error if the list is empty (so first ensure list_size() > 0)
Point list_remove_end(List *list);

// return the number of elements contained in a list
int list_size(List *list);

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

// Custom functions
// prints all the elements in the list
void print_list(List* list);

// returns the indexth element in list
Point index_list(List* list, int index); 

// indexing from the rear
Point index_list_end(List* list, int index); 

// Copies out the list elements to an array
void extract_list(List* list, Point* array);

#endif
