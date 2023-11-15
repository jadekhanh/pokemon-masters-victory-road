#include <iostream>
#include "View.h"
using namespace std;

View::View() {
    size = 11;
    scale = 2;
    origin.x = 0;
    origin.y = 0;
}

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location) {
    out_x = (int) (location.x - origin.x) / scale;
    out_y = (int) (location.y - origin.y) / scale;
    // return true if the subscripts are within the size of the grid displayed
    if ((out_x <= size) && (out_y <= size) && (out_x >= 0) && (out_y >= 0)) {
        return true;
    }
    // return false otherwise
    else {
        cout << "An object is outside the display" << endl;
        return false;
    }
}

void View::Clear() {
    for (int j = 0; j < size; j++) 
    {
        for (int i = 0; i < size; i++) 
        {
            // draw objects
                grid[i][j][0] = '.';
                grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject * ptr) {
    int outx;
    int outy;
    // if the object is visible
    if (ptr->ShouldBeVisible() == true) {
        // call GetSubscripts and if the subscripts are valid
        if (GetSubscripts(outx, outy, ptr->GetLocation())) {
            // if the cell is empty
            if (grid[outx][outy][0] == '.') {
                // the characters are replaced with '*' and ' ' to indicate there is more than 1 object in that cell
                ptr->DrawSelf(grid[outx][outy]);
            }
            // if the cell is occupied
            else {
                grid[outx][outy][0] = '*';
                grid[outx][outy][1] = ' ';
            }
        }
    }
    // otherwise if the object is not visible
    else {
        return;
    }
}

void View::Draw() 
// i = y
// j = x
{
    for (int j = size - 1; j >= -1; j--) 
    {
        for (int i = -1; i <= size - 1; i++) 
        {
            // grid axis
            if (i == -1 && j % 2 == 0) 
            {
                cout << j*2;
                if (j/5 == 0) 
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0) 
            {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0) 
            {
                cout << i*2;
                if (i/5 == 0) 
                {
                    cout << " ";
                }
                cout << "  ";
            }
            // draw objects
            if (i >= 0 && j >= 0) 
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;    
    }
}