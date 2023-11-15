#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H
#include <iostream>
#include "GameObject.h"
#include "Trainer.h"
#include "Point2D.h"
#include "Vector2D.h"
#include <cstring>
using namespace std;

enum WildPKStates {
    IN_ENVIRONMENT = 1,
    DEAD = 2,
    FOLLOWING_TRAINER = 3
};

class WildPokemon:public GameObject {

    protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    Point2D trainer_location;
    Point2D old_location;
    string name;
    Trainer* current_trainer;

    public:
    WildPokemon(string, double, double, bool, int, Point2D);
    void follow(Trainer*);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool IsAlive();
    void DetectTrainer(Trainer*);
    bool ShouldBeVisible(); //  virtual function
    void ShowStatus2();

};


#endif
