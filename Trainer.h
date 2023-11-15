#ifndef TRAINER_H
#define TRAINER_H
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Vector2D.h"
#include "Building.h"

using namespace std;

enum TrainerStates {
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};

class Trainer:public GameObject {

    public:
    Trainer();
    Trainer(char);
    Trainer(string, int, char, unsigned int, Point2D);
    virtual ~Trainer();
    void StartMoving(Point2D);
    void StartMovingToGym(PokemonGym*);
    void StartMovingToCenter(PokemonCenter*);
    void StartBattling(unsigned int);
    void StartRecoveringHealth(unsigned int);
    void Stop();
    bool HasFainted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();
    string GetName();
    int Wild_Pokemon_Count();
    int GetHealth();
    int ReduceHealth();
    void AddOneWildPokemon();
    void RemoveOneWildPokemon();
    int wild_pokemon_count;

    //protected:
    bool UpdateLocation();
    void SetupDestination(Point2D);

    private:
    double speed;
    bool is_at_center;                  // true if the trainer is in a PokemonCenter
    bool is_IN_GYM;                     // true if the trainer is in a PokemonGym
    unsigned int health;
    unsigned int experience;
    double PokeDollars;                 // the trainer's PokeDollars
    unsigned int battles_to_buy;
    unsigned int potions_to_buy;
    string name;                        // the name of this trainer
    PokemonCenter* current_center;      // a pointer to the current PokemonCenter
    PokemonGym* current_gym;            // a pointer to the current PokemonGym
    Point2D destination;                // the object's current destination
    Vector2D delta;                     // contains the x and y amounts that the object will move on each time unit
};

static double GetRandomAmountOfPokeDollars();

#endif