#include <iostream>
#include "GameCommand.h"
using namespace std;

void DoMoveCommand(Model & model, int trainer_id, Point2D p1) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    // if the command arguments are valid
    if (model.GetTrainerPtr(trainer_id) != NULL) {
        trainer->StartMoving(p1);
        cout << "Moving " << trainer->GetName() << " to " << p1 << endl;
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    PokemonCenter *this_center = model.GetPokemonCenterPtr(center_id);
    // if the command arguments are valid
    if ((model.GetPokemonCenterPtr(center_id) != NULL) && (model.GetTrainerPtr(trainer_id) != NULL)) {
        trainer->StartMovingToCenter(this_center);
        cout << "Moving " << trainer->GetName() << " to Pokemon Center " << center_id <<  endl;
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    PokemonGym *this_gym = model.GetPokemonGymPtr(gym_id);
    // if the command arguments are valid
    if ((model.GetPokemonGymPtr(gym_id) != NULL) && (model.GetTrainerPtr(trainer_id) != NULL)) {
        trainer->StartMovingToGym(this_gym);
        cout << "Moving " << trainer->GetName() << " to Pokemon Gym " << gym_id <<  endl;
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoStopCommand(Model & model, int trainer_id) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    // if the command arguments are valid
    if (model.GetTrainerPtr(trainer_id) != NULL) {
        trainer->Stop();
        cout << "Stopping " << trainer->GetName() << endl;
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoBattleCommand(Model & model, int trainer_id, unsigned int battles) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    // if the command arguments are valid
    if (model.GetTrainerPtr(trainer_id) != NULL) {
        trainer->StartBattling(battles);
        if (trainer->GetState() == IN_GYM) {
            cout << trainer->GetName() << " is battling " << endl;
        }
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed) {
    Trainer *trainer = model.GetTrainerPtr(trainer_id);
    // if the command arguments are valid
    if (model.GetTrainerPtr(trainer_id) != NULL) {
        trainer->StartRecoveringHealth(potions_needed);
        if (trainer->GetState() == AT_CENTER) {
            cout << "Recovering " << trainer->GetName() << "'s Pokemon's health " << endl;
        }
    }
    // otherwise
    else {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoAdvanceCommand(Model& model, View& view) {
    // update each object once
    cout << "Advancing one tick." << endl;
    // update everything
    model.Update();
    // check to see if each Trainer encounters any Wild Pokemon
    model.Trainer_Encounters_WildPokemon();
    // show everything
    model.ShowStatus();
    model.ShowStatus2();
    view.Clear();
    model.Display(view); 
    view.Draw();
}

void DoRunCommand(Model& model, View& view) {
    // repeat until either the function returns true for at least one of the objects or 5 time steps have been done
    cout << "Advancing to next event." << endl;
    for (int i = 0; i < 5; i++) {
        // update each object once
        // if the update function returns true for at least one of the objects, or 5 time steps have been done
        if (model.Update()) {
            break;
        }
    }
    // check to see if each Trainer encounters any Wild Pokemon
    model.Trainer_Encounters_WildPokemon();
    // show everything
    model.ShowStatus();
    model.ShowStatus2();
    view.Clear();
    model.Display(view); 
    view.Draw();
}
