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
int inside_hull(Point *polygon, int n, Point *hull) {
  // TODO: Implement the InsideHull algorithm
  fprintf(stderr, "Error: inside_hull() not implemented\n");
  exit(EXIT_FAILURE);
}
