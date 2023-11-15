#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
#include <cmath>
#include "Vector2D.h"
using namespace std;

class Point2D
{ 
	public:                                     // Public members
	double x;
    double y;
	
    Point2D();                                  // Default Constructor
    Point2D(double, double);                    // Constructor
};

// Non-member Function
double GetDistanceBetween(Point2D, Point2D);

// Non-member Overloaded Operators
ostream& operator << (ostream&, Point2D&);      // Stream Output Operator
Point2D operator + (Point2D, Vector2D);         // Addition Operator
Vector2D operator - (Point2D, Point2D);         // Subtraction Operator

#endif