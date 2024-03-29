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

/* Shortcuts to get the result of the bottom/top orientation 
 * Index functions are O(n) in the worst-case but calls where index = 1 or 0
 * can be considered O(1) */
char orientation_bottom(Deque* myDeque, Point* polygon, Point curr) {
    return orientation(index_deque(myDeque, 0), 
                       index_deque(myDeque, 1), curr);
}

char orientation_top(Deque* myDeque, Point* polygon, Point curr) {
    return orientation(index_deque_end(myDeque, 1),
                       index_deque_end(myDeque, 0), curr);
}

// Returns 1 when a polygon has collinear points, O(n)
int collinear_polygon(Point* polygon, int n) {
    // At least 3 points
    int i = 0;
    for (; i <= n-1; i++) {
        if (orientation(polygon[i], polygon[(i+1)%n], 
            polygon[(i+2)%n]) == 'c') {
            return 1;
        }
    }
    return 0;
}

// Main function (Part F)

int inside_hull(Point *polygon, int n, Point *hull) {
    // Input validation
    // We are making the assumption that the input is a simple polygon

    // Assert polygon
    assert(polygon);

    // Assume points >= 3
    if(n < 3) {
        return INSIDE_HULL_ERROR;
    }

    // Input polygon should not have collinear points
    if (collinear_polygon(polygon, n)) {
        // Nothing to free at this point
        return COLLINEAR_POINTS;
    }

    // Initialization
    // Create deque
    Deque *myDeque = new_deque(); 
    
    // Set up first three points
    if (init_hull(polygon, myDeque) == COLLINEAR_POINTS) {
        // Function couldn't contine because of collinear points
        free_deque(myDeque);
        return COLLINEAR_POINTS;
    }

    // Pseduocode algorithm (Melkmann)
    int i = 3;
    Point curr_point;
    
    while (i < n) {
        curr_point = polygon[i];
        if ((orientation_top(myDeque, polygon, curr_point) == 'l') && 
            (orientation_bottom(myDeque, polygon, curr_point) == 'l' )) {
            i++;
            continue;
        }
        
        // Top
        while (orientation_top(myDeque, polygon, curr_point) == 'r') {
            deque_pop(myDeque);
        }
        // Collinear check; does the point we're about to add form a collinear
        // line with previous two on top?
        if (orientation_top(myDeque, polygon, curr_point) == 'c') {
            free_deque(myDeque);
            return COLLINEAR_POINTS;
        }

        deque_push(myDeque, curr_point);

        // Bottom
        while (orientation_bottom(myDeque, polygon, curr_point) == 'r') {
            deque_remove(myDeque);
        }
        // Second collinear check
        if (orientation_bottom(myDeque, polygon, curr_point) == 'c') {
            free_deque(myDeque);
            return COLLINEAR_POINTS;
        }
        deque_insert(myDeque, curr_point);
        
        i++;
    }
    
    // Get and return deque size (ignore last)
    int size = deque_size(myDeque) - 1;

    // Copy out the deque. This has the last point but is not included by size.
    extract_deque(myDeque, hull);
    free_deque(myDeque);

    return size;
}
