#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject(char in_code) {
    display_code = in_code;
    id_num = 1;
    state = ' ';
    cout << "GameObject constructed." << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code) {
    // Initializes member variables
    location = in_loc;
    id_num = in_id;
    display_code = in_code;
    state = ' ';
    cout << "GameObject constructed." << endl;
}

GameObject::~GameObject() {
    cout << "GameObject destructed." << endl;
}

Point2D GameObject::GetLocation() {
    return location;
}

int GameObject::GetId() {
    return id_num;
}

char GameObject::GetState() {
    return state;
}

void GameObject::ShowStatus() {
    cout << display_code << id_num << " at " << location << endl;
}

bool GameObject::ShouldBeVisible() {
    return true;
}

void GameObject::DrawSelf(char * ptr) {
    // puts the display_code at the character pointed by ptr and 
    // then the ASCII character for the id_num in the next character
    *ptr = display_code;
    *(ptr + 1) = '0' + id_num;
}