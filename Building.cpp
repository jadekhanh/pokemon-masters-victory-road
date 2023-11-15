#include <iostream>
#include "Building.h"
using namespace std;

Building::Building():GameObject('B') { 
    // initializes member variables to their initial values
    //display_code = 'B';
    trainer_count = 0;
    cout << "Building default constructed." << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc):GameObject(in_loc, in_id, in_code) { // constructor chaining
    id_num = in_id;
    location = in_loc;
    display_code = in_code;
    // initializes member variables to their initial values
    display_code = 'B';
    trainer_count = 0;
    cout << "Building constructed." << endl;
}

void Building::AddOneTrainer() {
    trainer_count ++;
}

void Building::RemoveOneTrainer() {
    trainer_count --;
}

void Building::ShowStatus() {
    cout << display_code << id_num << " located at " << location << endl;
    if (trainer_count <= 1) {
        cout << trainer_count << " trainer is inside this building" << endl;
    }
    else {
        cout << trainer_count << " trainers are inside this building" << endl;

    }
}

bool Building::ShouldBeVisible() {
    return true;
}