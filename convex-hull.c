/* * * * * * *
 * Implementation of the Inside Hull algorithm for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2019
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Matthew Lui 993333
 */

//                   WRITE YOUR IMPLEMENTATION HERE
//
// You should fill in the function definitions for orientation() and
// inside_hull() in this file.
//
// Don't be shy to add any extra functions or types you may need.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "convex-hull.h"
#include "deque.h"

// Returns the orientation of Point p2 in relation to the line segment p0p1.
// If p2 is to the left of p0p1 then it returns LEFT ('l'), if p2 is to the
// right it returns RIGHT ('r').
// If p0, p1 and p2 are collinear then COLLINEAR ('c') is returned.
char orientation(Point p0, Point p1, Point p2) {
    // First consider ax + by = c, the line between p0 and p1.
    // a = p1y - y0y, b = p0x - p1x, c = p0x*p1y - p0y*p1x
    // E.g. for p0 = (0,0) and p1 = (5,5), a = 5, b = -5, c = 0.
    double a, b, c;
    a = p1.y - p0.y;
    b = p0.x - p1.x;
    c = p0.x*p1.y - p0.y*p1.x;

    // Now any point left will have ax + by < c, right > c, collinear = c
    // See p139 of Levitin
    // Compute ax+by
    double lhs = a*p2.x + b*p2.y;
    // Compare to c
    if (lhs < c) {
        return 'l';
    } else if (lhs == c) {
        return 'c';
    } else {
        return 'r';
    }
}

// Takes a polygon (i.e. an array of points) given in counter-clockwise order
// with n points.
//
// Stores the points of the convex hull into the hull array (the last point
// should NOT be the same as the first point), and returns the number of
// points which are in the convex hull.
//
// If three successive points in the polygon are collinear then the algorithm
// should terminate and COLLINEAR_POINTS should be returned.
//
// If an error occurs this function should return INSIDE_HULL_ERROR.

// Helpers

/* Initializers the deque as required by the orientation */
int init_hull(Point* polygon, Deque* myDeque) {
    char firstThree = orientation(polygon[0], polygon[1], polygon[2]);
    if(firstThree == 'l') {
        deque_push(myDeque, polygon[2]);
        deque_push(myDeque, polygon[0]);
        deque_push(myDeque, polygon[1]);
        deque_push(myDeque, polygon[2]);
    } else if (firstThree == 'r') {
        deque_push(myDeque, polygon[2]);
        deque_push(myDeque, polygon[1]);
        deque_push(myDeque, polygon[0]);
        deque_push(myDeque, polygon[2]);
    } else {
        return COLLINEAR_POINTS;
    }
    return 0;
}

/* Shortcuts to get the result of the bottom/top orientation */
char orientation_bottom(Deque* myDeque, Point* polygon, int i) {
    return orientation(index_deque(myDeque, 0), 
                       index_deque(myDeque, 1), polygon[i]);
}

char orientation_top(Deque* myDeque, Point* polygon, int n, int i) {
    return orientation(index_deque(myDeque, n-2), index_deque(myDeque, n-1), 
            polygon[i]);
}

int inside_hull(Point *polygon, int n, Point *hull) {
    // Input validation
    // Assert polygon
    assert(polygon);

    // Assume points >= 3
    if(n < 3) {
        return INSIDE_HULL_ERROR;
    }

    // Initialization
    // Create deque
    Deque *myDeque = new_deque(); 
    
    // Set up first three points
    if (init_hull(polygon, myDeque) == COLLINEAR_POINTS) {
        // Function couldn't because collinear
        return COLLINEAR_POINTS;
    }

    print_deque(myDeque);

    // Pseduocode algorithm
    int i = 3;
    while (i < n) {
        if ((orientation_top(myDeque, polygon, n, i) == 'l') && 
                (orientation_bottom(myDeque, polygon, i) == 'l' )) {
            i++;
            continue;
        }

        while(orientation_top(myDeque, polygon, n, i) == 'r') {
            deque_pop(myDeque);
        }
    }
    // Collinear check
    
    // Get and return deque size (ignore last)
    return 0;
}
