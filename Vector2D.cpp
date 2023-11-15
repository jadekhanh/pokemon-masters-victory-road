#include <iostream>
#include "Vector2D.h"
using namespace std;

// Vector2D default constructor 
Vector2D::Vector2D() {
    x = 0.0;
    y = 0.0;
}

// Vector2D Constructor inside class Vector2D
Vector2D::Vector2D(double in_x, double in_y) {
    x = in_x;
    y = in_y;
}

// Non-member Overloaded Operators
Vector2D operator* (Vector2D v1, double d) {
    Vector2D retVector2D;
    retVector2D.x = v1.x * d;
    retVector2D.y = v1.y * d;
    return retVector2D;
}

Vector2D operator/ (Vector2D v1, double d) {
    Vector2D retVector2D;
    if (d==0) {
        return v1;
    }
    else {
        retVector2D.x = v1.x / d;
        retVector2D.y = v1.y / d;
        return retVector2D;
    }
}

ostream& operator<< (ostream& v0, Vector2D& v1) {
    v0 << "<" << v1.x << ", " << v1.y << ">";
    return v0;
}