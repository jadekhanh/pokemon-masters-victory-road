#include <iostream>
#include "Point2D.h"
using namespace std;

// Constructors
Point2D::Point2D() {
    x = 0.0;
    y = 0.0;
}

Point2D::Point2D(double in_x, double in_y) {
    x = in_x;
    y = in_y;
}

// Non-member Function
double GetDistanceBetween(Point2D p1, Point2D p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Non-member Overloaded Operators
ostream& operator<< (ostream& p0, Point2D& p1) {
    p0 << "(" << p1.x << ", " << p1.y << ")";
    return p0;
}

Point2D operator+ (Point2D p1, Vector2D v1) {
    Point2D retPoint2D;
    retPoint2D.x = p1.x + v1.x;
    retPoint2D.y = p1.y + v1.y;
    return retPoint2D;
}

Vector2D operator- (Point2D p1, Point2D p2) {
    Vector2D retVector2D;
    retVector2D.x = p1.x - p2.x;
    retVector2D.y = p1.y - p2.y;
    return retVector2D;
}

