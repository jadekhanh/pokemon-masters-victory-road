#include <iostream>
#ifndef VECTOR2D_H
#define VECTOR2D_H
using namespace std;

class Vector2D {

    public:     // public members
    double x;
    double y;

    Vector2D(); // default constructor
    Vector2D(double, double);
};

// Non-member Overloaded Operators
Vector2D operator * (Vector2D, double);     // Multiplication Operator
Vector2D operator / (Vector2D, double);     // Division Operator
ostream& operator << (ostream&, Vector2D&); // Stream Output Operator

#endif