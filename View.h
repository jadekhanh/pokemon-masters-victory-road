#include <iostream>
#include "Point2D.h"
#include "GameObject.h"
#ifndef VIEW_H
#define VIEW_H
using namespace std;

const int view_maxsize = 20;

class View {

    public:
    View();
    void Clear();
    void Plot(GameObject *);
    void Draw();

    private:
    int size;
    double scale;
    Point2D origin;
    char grid[view_maxsize][view_maxsize][2];
    bool GetSubscripts(int &, int &, Point2D);

};

#endif
