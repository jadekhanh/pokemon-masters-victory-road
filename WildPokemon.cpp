#include <iostream>
#include "WildPokemon.h"
using namespace std;

WildPokemon::WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'W') {
    state = IN_ENVIRONMENT;
    location = in_loc;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    current_trainer = NULL;
    in_combat = false;
    old_location.x = 0;
    old_location.y = 0;
}

void WildPokemon::follow(Trainer *t) {  // this follows Trainer t
    // change the Wild Pokemon's current_trainer value
    current_trainer = t;
    // trainer is being followed by one Wild Pokemon
    current_trainer->AddOneWildPokemon();
    // reduce the health of the followed trainer
    current_trainer->ReduceHealth();
}

bool WildPokemon::get_variant() {
    return this->variant;
}

double WildPokemon::get_attack() {
    return this->attack;
}

double WildPokemon::get_health() {
    return this->health;
}

bool WildPokemon::get_in_combat() {
    return in_combat;
}

bool WildPokemon::Update() {
    // when the Wild Pokemon's health is 0 or below
    if (health <= 0 && state != DEAD) {
        current_trainer->RemoveOneWildPokemon();
        state = DEAD;
        return true;
    }
    // default state when creating a Wild Pokemon and it returns false
    else if (state == IN_ENVIRONMENT) {
        return false;
    }
    // if Wild Pokemon follows the trainer
    else if (state == FOLLOWING_TRAINER) {
        old_location = location;
        // the WildPokemon copies the location of the followed Trainer
        trainer_location = current_trainer->GetLocation();
        location.x = trainer_location.x;
        location.y = trainer_location.y;
        // reduce the health of Wild Pokemon and Trainer when they move
        if (GetDistanceBetween(old_location, location) != 0) {
            current_trainer->ReduceHealth();
            this->health -= 1;
        }
        return true;
    }
    // if state = DEAD
    else if (state == DEAD) {
        return false;
    }
}

void WildPokemon::ShowStatus() {
    if (state == IN_ENVIRONMENT) {
        cout << "Wild Pokemon status: ";
        GameObject::ShowStatus();
        cout << "is in the environment" << endl;
        cout << "   Health: " << health << endl;
        cout << "   Attack: " << attack << endl;
        cout << "   Variant: " << variant << endl;
    }
    else if (state == FOLLOWING_TRAINER ) {
        cout << "Wild Pokemon status: ";
        GameObject::ShowStatus();
        cout << "following Trainer " << current_trainer->GetId() << endl;
        cout << "   Health: " << health << endl;
        cout << "   Attack: " << attack << endl;
        cout << "   Variant: " << variant << endl;
        // outputs a message that the Pokemon is following the Trainer
        cout << "   In Combat with Trainer: " << current_trainer->GetName() << endl;
    }
    else if (state == DEAD) {
        cout << "Wild Pokemon status: ";
        GameObject::ShowStatus();
        cout << "is dead" << endl;
        cout << "   Health: " << health << endl;
        cout << "   Attack: " << attack << endl;
        cout << "   Variant: " << variant << endl;
    }
}

bool WildPokemon::IsAlive() {
    // return true if it is alive
    if (health > 0) {
        return true;
    }
    // return false otherwise
    else {
        return false;
    }
}

// checks the distance between the passed trainer and the Wild Pokemon
void WildPokemon::DetectTrainer(Trainer * trainer) {
    // if the distance between the passed trainer and the Wild Pokemon is 2, WP not follow any trainer, WP's health > 0, WP is in the environment, and trainer is not fainted
    if (GetDistanceBetween(location, trainer->GetLocation()) <= 2 && current_trainer == NULL && state == IN_ENVIRONMENT && health > 0 && trainer->HasFainted() == false) {
    // the WildPokemon will follow the trainer
        follow(trainer);
        state = FOLLOWING_TRAINER;
        in_combat = true;
        return;
    } 
    else {
            return;
    }
}

bool WildPokemon::ShouldBeVisible() {
    if (health <= 0) {
        return false;
    }
    else {
        return true;
    }
}

