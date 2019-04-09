/* * * * * * *
 * Module for creating and manipulating doubly-linked lists of integers
 *
 * created for COMP20007 Design of Algorithms 2017
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 *
 * Modified by Matthew Lui 993333
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "point.h"

typedef struct node Node;

// a list node points to the next node in the list, and to some data
struct node {
	Node *next;
    Node *prev;
	Point point;
};

// a list points to its first and last nodes, and stores its size (num. nodes)
struct list {
	Node *head;
	Node *tail;
	int size;
};

// helper function to create a new node and return its address
Node *new_node();

// helper function to clear memory of a node (does not free the node's data)
void free_node(Node *node);


/* * * *
 * FUNCTION DEFINITIONS
 */

// create a new list and return a pointer to it
List *new_list() {
	List *list = malloc(sizeof *list);
	assert(list);
	
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

// destroy a list and free its memory
void free_list(List *list) {
	assert(list != NULL);
	// free each node
	Node *node = list->head;
	Node *next;
	while (node) {
		next = node->next;
		free_node(node);
		node = next;
	}
	// free the list struct itself
	free(list);
}

// helper function to create a new node and return its address
Node *new_node() {
	Node *node = malloc(sizeof *node);
	assert(node);
	
	return node;
}

// helper function to clear memory of a node
void free_node(Node *node) {
	free(node);
}

// MODIFIED BY MATTHEW LUI 993333
// add an element to the front of a list
// this operation is O(1)
void list_add_start(List *list, Point newPoint) {
	assert(list != NULL);

	// create and initialise a new list node
	Node *node = new_node();
	node->point = newPoint;
	node->next = list->head; // next will be the old first node (may be null)
    node->prev = NULL; // Can't be a previous node, this one will be head
	// place it at the start of the list
	list->head = node;

	// if list was empty, this new node is also the last node now
	if(list->size == 0) {
		list->tail = node;
    } else {
        // Let the second node know who is behind
        node->next->prev = node; 
    }

	// and we need to keep size updated!
	list->size++;
}

// MODIFIED BY MATTHEW LUI 993333
// add an element to the back of a list
// this operation is O(1)
void list_add_end(List *list, Point newPoint) {
	assert(list != NULL);
	
	// we'll need a new list node to store this data
	Node *node = new_node();
	node->point = newPoint;
	node->next = NULL; // as the last node, there's no next node
    node->prev = list->tail; // old tail is this one's prev. might be null

	if(list->size == 0) {
		// if the list was empty, new node is now the first node
		list->head = node;
	} else {
		// otherwise, it goes after the current last node
		list->tail->next = node;
	}
	
	// place this new node at the end of the list
	list->tail = node;
	
	// and keep size updated too
	list->size++;
}

// MODIFIED BY MATTHEW LUI 993333
// remove and return the front data element from a list
// this operation is O(1)
// error if the list is empty (so first ensure list_size() > 0)
Point list_remove_start(List *list) {
	assert(list != NULL);
	assert(list->size > 0);
	
	// we'll need to save the data to return it
	Node *start_node = list->head;
	Point oldPoint = start_node->point;
	
    // then replace the head with its next node (may be null)
	list->head = start_node->next;
    
    // If it exists, let the adjacent node know
    if (start_node->next != NULL) {
        start_node->next->prev = NULL;
    }

	// if this was the last node in the list, the tail also needs to be cleared
	if(list->size == 1) {
		list->tail = NULL;
	}

	// the list is now one node smaller
	list->size--;

	// and we're finished with the node holding this data
	free_node(start_node);

	// done!
	return oldPoint;
}

// MODFIED BY MATTHEW LUI 993333
// remove and return the final data element in a list
// this operation is O(1), as the list is doubly-linked
// // error if the list is empty (so first ensure list_size() > 0)
Point list_remove_end(List *list) {
	assert(list != NULL);
	assert(list->size > 0);
	
	// we'll need to save the data to return it
	Node *end_node = list->tail;
	Point oldPoint = end_node->point;
	
	// Replace tail, could be null 
    list->tail = end_node->prev;
	if(list->size == 1) {
		// if we're removing the last node, the head also needs clearing
		list->head = NULL;
	} else {
		// let the previous node know what's up
        assert(end_node->prev);
		end_node->prev->next = NULL;
	}

	// the list just got one element shorter
	list->size--;

	// we're finished with the list node holding this data
	free_node(end_node);

	// done!
	return oldPoint;
}

// return the number of elements contained in a list
int list_size(List *list) {
	assert(list != NULL);
	return list->size;
}

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list) {
	assert(list != NULL);
	return (list->size==0);
}

// ADDED:

// Returns the node at a given index
Point index_list(List* list, int index) {
    assert(list);
    assert(index > 0);
    assert(index < list_size(list));
    
    int i = 0;
    Node* curr = list->head;
    while(i < index) {
        curr = curr->next;
        i++;
    }
    return curr->point;
} 

// Prints all the nodes in the list
void print_list(List* list) {
    Node* curr;
    curr = list->head;

    while(curr) {
        print_point(curr->point);
        curr = curr->next;
    }
}

