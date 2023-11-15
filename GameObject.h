#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include "Point2D.h"

using namespace std;

class GameObject {

    public:     // public members
    GameObject (char);
    GameObject(Point2D, int, char);
    virtual ~GameObject();
    Point2D GetLocation();
    int GetId();
    char GetState();
    virtual void ShowStatus();
    virtual bool Update() = 0;          // pure virtual function; makes GameObject an abstract base class
    virtual bool ShouldBeVisible() = 0; // pure virtual function
    void DrawSelf(char *);
    
    protected:  // protected members
    Point2D location;
    int id_num;
    char display_code;
    char state;
};

#endif