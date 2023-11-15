#include <iostream>
#include <stdlib.h>
#include "Model.h"
using namespace std;

Model::Model() {

    time = 0;
   
    Point2D c1(1, 20); 
    Point2D c2(10, 20); 
    Point2D t1(5, 1);
    Point2D t2(10, 1);
    Point2D g1(0, 0);
    Point2D g2(5, 5);
    Point2D w1(10, 12);
    Point2D w2(15, 5);

    // Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    Trainer *tr1 = new Trainer("Ash", 1, 'T', 2, t1);
    object_ptrs.push_back(tr1);
    active_ptrs.push_back(tr1);
    trainer_ptrs.push_back(tr1);
    Trainer *tr2 = new Trainer("Misty", 2, 'T', 2, t2);
    object_ptrs.push_back(tr2);
    active_ptrs.push_back(tr2);
    trainer_ptrs.push_back(tr2);

    // PokemonCenter (int in_id, double potion_cost, unsigned int potion _cap, Point2D in_loc);
    PokemonCenter *pc1 = new PokemonCenter(1, 1, 100, c1);
    object_ptrs.push_back(pc1);
    active_ptrs.push_back(pc1);
    center_ptrs.push_back(pc1);
    PokemonCenter *pc2 = new PokemonCenter(2, 2, 200, c2);
    object_ptrs.push_back(pc2);
    active_ptrs.push_back(pc2);
    center_ptrs.push_back(pc2);

    // PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
    PokemonGym *pg1 = new PokemonGym(10, 1, 2, 3, 1, g1);
    object_ptrs.push_back(pg1);
    active_ptrs.push_back(pg1);
    gym_ptrs.push_back(pg1);
    PokemonGym *pg2 = new PokemonGym(20, 5, 7.5, 4, 2, g2);
    object_ptrs.push_back(pg2);
    active_ptrs.push_back(pg2);
    gym_ptrs.push_back(pg2);

    // WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc,)
    WildPokemon *wild1 = new WildPokemon("WildPokemon1", 5, 100, false, 1, w1);
    object_ptrs.push_back(wild1);
    active_ptrs.push_back(wild1);
    wildpokemon_ptrs.push_back(wild1);
    WildPokemon *wild2 = new WildPokemon("WildPokemon2", 5, 100, false, 2, w2);
    object_ptrs.push_back(wild2);
    active_ptrs.push_back(wild2);
    wildpokemon_ptrs.push_back(wild2);

    cout << "Model default constructed" << endl;
}

Model::~Model() {
    // deletes each object
    for (list<GameObject*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++) {
        delete *it;
    }
    cout << "Model destructed" << endl;
}

Trainer* Model::GetTrainerPtr(int id) {
    // search the appropriate array for an object matching the id, and either return the pointer if found, or 0 if not //ASK!!!
    for (list<Trainer*>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++) {
        if ((*iter)->GetId() == id) {
            return *iter;
        }
    }
    cout << "Gettrainerptr" << endl;
    return 0;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id) {
    // search the appropriate array for an object matching the id, and either return the pointer if found, or 0 if not
    for (list<PokemonCenter*>::iterator iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++) {
        if ((*iter)->GetId() == id) {
            return *iter;
        }
    }
    return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id) {
    // search the appropriate array for an object matching the id, and either return the pointer if found, or 0 if not
    for (list<PokemonGym*>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++) {
        if ((*iter)->GetId() == id) {
            return *iter;
        }
    }
    return 0;
}

WildPokemon* Model::GetWildPokemonPtr(int id) {
    for (list<WildPokemon*>::iterator iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); iter++) {
        if ((*iter)->GetId() == id) {
            return *iter;
        }
    }
    return 0;
}

bool Model::Update() {
    time += 1;
    // return true if any one of the GameObject::Update() calls returned true
    // create a var here to count true
    int timetrue = 0;
    for (list<GameObject*>::iterator iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++) {
        if ((*iter)->Update()) {
            timetrue ++;
        }
    }
    // if the player finishes all the PokemonGyms
    int count_gyms = 0;
    for (list<PokemonGym*>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++) {
        if ((*iter)->GetNumBattlesRemaining() == 0) {
            count_gyms ++;
        }
    if (count_gyms == gym_ptrs.size()) {
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(0);
    }
    }
    // if all the trainers are fainted and can't move
    int count_trainers = 0;
    for (list<Trainer*>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++) {
        if ((*iter)->HasFainted() == true) {
            count_trainers ++;
    }
    if (count_trainers == trainer_ptrs.size()) {
        cout << "GAME OVER: You lose! All of your Trainers' pokemon have fainted!" << endl;
        exit(0);
    }
    }
    // if an object is dead, then delete it from the active_ptrs
    for (list<GameObject*>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++) {
        if ((*iter)->ShouldBeVisible() == false) {
            active_ptrs.erase(iter);
        }
    }
    if (timetrue == 1) {
        return true;
    }
    else {
        return false;
    }
    
}

void Model::Display(View &view) {
    cout << "Time: " << time << endl;
    // plot each element in the active_ptrs
    for (list<GameObject*>::iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++) {
        view.Plot(*iter);
    }
}

void Model::ShowStatus() {
    cout << "Time: " << time << endl;
    // show status of each element in the object_ptrs
    for (list<GameObject*>::iterator iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++) {
        (*iter)->ShowStatus();
    }
}

void Model::Trainer_Encounters_WildPokemon() {
    // check to see if any Trainer encounters any Wild Pokemon
    for (int i = 1; i <= trainer_ptrs.size(); i++) {
        Trainer *trainer = GetTrainerPtr(i);
        for (int j = 1; j <= wildpokemon_ptrs.size(); j++) {
            WildPokemon *wildpokemon = GetWildPokemonPtr(j);
            (wildpokemon)->DetectTrainer(trainer);
        }
    }
}

void Model::NewCommand(char type, int id, int x, int y) {
    Point2D location(x, y);
    try {
    switch (type) {
        case 'c': {
            // check if the id is appropriate
            for (list<PokemonCenter*>::iterator iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++) {
                if ((*iter)->GetId() == id) {
                    throw Invalid_Input("Duplicated ID");
                }
            }

            // check if the id if greater than 9 or less than 0
            if (id < 0 || id > 9) {
                throw Invalid_Input("ID must be less than 9 and larger than 0");
            }

            // check if the location's coordinates are valid
            if (location.x > 20 || location.y > 20 || location.x < 0 || location.y < 0) {
                throw Invalid_Input("Invalid location coordinates");
            }

            // if everything above is good
            // PokemonCenter (int in_id, double potion_cost, unsigned int potion _cap, Point2D in_loc);
            PokemonCenter *c1 = new PokemonCenter(1, 1, 100, location);
            object_ptrs.push_back(c1);
            active_ptrs.push_back(c1);
            center_ptrs.push_back(c1);
            break;
        }

        case 'g': {
            // check if the id is appropriate
            for (list<PokemonGym*>::iterator iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++) {
                if ((*iter)->GetId() == id) {
                    throw Invalid_Input("Duplicated ID");
                }
            }

            // check if the id if greater than 9 or less than 0
            if (id < 0 || id > 9) {
                throw Invalid_Input("ID must be less than 9 and larger than 0");
            }

            // check if the location's coordinates are valid
            if (location.x > 20 || location.y > 20 || location.x < 0 || location.y < 0) {
                throw Invalid_Input("Invalid location coordinates");
            }

            // if everything above is good
            // PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc)
            PokemonGym *g1 = new PokemonGym(5, 1, 1, 5, id, location);
            object_ptrs.push_back(g1);
            active_ptrs.push_back(g1);
            gym_ptrs.push_back(g1);
            break;
        }

        case 't': {
            // check if the id is appropriate
            for (list<Trainer*>::iterator iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++) {
                if ((*iter)->GetId() == id) {
                    throw Invalid_Input("Duplicated ID");
                }
            }

            // check if the id if greater than 9 or less than 0
            if (id < 0 || id > 9) {
                throw Invalid_Input("ID must be less than 9 and larger than 0");
            }

            // check if the location's coordinates are valid
            if (location.x > 20 || location.y > 20 || location.x < 0 || location.y < 0) {
                throw Invalid_Input("Invalid location coordinates");
            }

            // if everything above is good
            // Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
            Trainer *t1 = new Trainer("Trainer", id, 'T', 2, location);
            object_ptrs.push_back(t1);
            active_ptrs.push_back(t1);
            trainer_ptrs.push_back(t1);
            break;
        }

        case 'w': {
            // check if the id is appropriate
            for (list<WildPokemon*>::iterator iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); iter++) {
                if ((*iter)->GetId() == id) {
                    throw Invalid_Input("Duplicated ID");
                }
            }

            // check if the id if greater than 9 or less than 0
            if (id < 0 || id > 9) {
                throw Invalid_Input("ID must be less than 9 and larger than 0");
            }

            // check if the location's coordinates are valid
            if (location.x > 20 || location.y > 20 || location.x < 0 || location.y < 0) {
                throw Invalid_Input("Invalid location coordinates");
            }

            // if everything above is good
            // WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc,)
            WildPokemon *w1 = new WildPokemon("WildPokemon", 100, 2, false, id, location);
            object_ptrs.push_back(w1);
            active_ptrs.push_back(w1);
            wildpokemon_ptrs.push_back(w1);
            break;
        }
        default: {
            throw Invalid_Input("Invalid object type");
            break;
        }
        }
    }
    catch (Invalid_Input& except) {
        cout << "Invalid input - " << except.msg_ptr << "Invalid type" << endl;
        // actions to be taken if the input is wrong
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return;
}

void Model::ShowStatus2() {
    for (list<WildPokemon*>::iterator iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); iter++) {
        int id = (*iter)->GetId();
        bool combat = (*iter)->get_in_combat();
        bool alive = (*iter)->IsAlive();
        cout << "           W" << id << " in combat: " << combat << "      IsAlive: " << alive << endl;
        if ((*iter)->get_in_combat() == true) {
            cout << "Wild Pokemon " << (*iter)->GetId() << " has " << (*iter)->get_health() << " health remaining." << endl;
        }
    }
    return;
}