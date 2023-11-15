#include <iostream>
#include <list>
#include <iterator>
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"
#include "Input_Handling.h"
#include <limits>
using namespace std;
#ifndef MODEL_H
#define MODEL_H

class Model {

    public:
    Model();
    virtual ~Model();
    Trainer * GetTrainerPtr(int id);
    PokemonCenter * GetPokemonCenterPtr(int id);
    PokemonGym * GetPokemonGymPtr(int id);
    WildPokemon * GetWildPokemonPtr(int id);
    bool Update();
    void Display(View &view);
    void ShowStatus();
    void Trainer_Encounters_WildPokemon();
    void NewCommand(char, int, int, int);
    void ShowStatus2();

    private:
    int time;
    list<GameObject*> object_ptrs;
    list<GameObject*> active_ptrs;
    list<Trainer*> trainer_ptrs;
    list<PokemonCenter*> center_ptrs;
    list<PokemonGym*> gym_ptrs;
    list<WildPokemon*> wildpokemon_ptrs;

};

#endif