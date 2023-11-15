#include <iostream>
#include "PokemonCenter.h"
using namespace std;

PokemonCenter::PokemonCenter():Building() {
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed." << endl;
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc):Building() {
    id_num = in_id;
    location = in_loc;
    pokedollar_cost_per_potion = potion_cost;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_cap;
    display_code = 'C';
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed." << endl;
}

PokemonCenter::~PokemonCenter() {
    cout << "PokemonCenter destructed." << endl;
}

bool PokemonCenter::HasPotions() {
    if (num_potions_remaining >= 1) {
        return true;
    }
    else {
        return false;
    }
}

unsigned int PokemonCenter::GetNumPotionRemaining() {
    return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget) {
    if (budget >= potion * pokedollar_cost_per_potion) {
        return true;
    }
    else {
        return false;
    }
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion) {
    return potion * pokedollar_cost_per_potion;
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed) {
    if (num_potions_remaining >= potion_needed) {
        num_potions_remaining -= potion_needed;
        return potion_needed;
    }
    else {
        unsigned int remain = num_potions_remaining;
        num_potions_remaining = 0;
        return remain;
    }
}

bool PokemonCenter::Update() {
    static int count = 0;
    if (num_potions_remaining == 0) {
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter (" << id_num << ") has ran out of potions." << endl;
        count ++;
    }
    if (count == 1) {
        return true;
    }
    else {
        return false;
    }
}

void PokemonCenter::ShowStatus() {
    cout << "PokemonCenter Status: " << endl;
    Building::ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl
    << "has " << num_potions_remaining << " potion(s) remaining" << endl;
}

bool PokemonCenter::ShouldBeVisible() {
    return true;
}