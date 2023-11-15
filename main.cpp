#include <iostream>
#include "Trainer.h"
#include "GameObject.h"
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Vector2D.h"
#include "Building.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include "WildPokemon.h"
#include "Input_Handling.h"
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <limits>
using namespace std;

int main () {
  
    // display the status of each object
    Model model;
    model.ShowStatus();

    // display time and plot all the objects
    View view;

    // display the grid
    view.Clear();
    model.Display(view);
    view.Draw();

    // ask for the command
    char command, type;
    int a, b, c;
    bool loop = true;
    while (loop) {
        cout << "Enter the game command: " << endl;
        cin >> command;
        try {
        switch (command) {
            case 'q': {
                return 0;
            }

            // m ID x y
            case 'm': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for x coordinate");    // throw an exception
                cin >> c;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for y coordinate");    // throw an exception
                DoMoveCommand(model, a, Point2D(b, c));
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // c ID1 ID2
            case 'c': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for center ID");    // throw an exception
                DoMoveToCenterCommand(model, a, b);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // g ID1 ID2
            case 'g': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for gym ID");    // throw an exception
                DoMoveToGymCommand(model, a, b);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // s ID
            case 's': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                DoStopCommand(model, a);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // p ID potion_count
            case 'p': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for potion count");    // throw an exception
                DoRecoverInCenterCommand(model, a, b);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // b ID battle_amount
            case 'b': {
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for battle amount");    // throw an exception
                DoBattleCommand(model, a, b);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            // a
            case 'a': {
                DoAdvanceCommand(model, view);
                break;
            }

            // r
            case 'r': {
                DoRunCommand(model, view);
                break;
            }

            // n TYPE ID X Y
            case 'n': {
                cin >> type;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an character for type");    // throw an exception
                cin >> a;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for trainer ID");    // throw an exception
                cin >> b;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for x coordinate");    // throw an exception
                cin >> c;
                if((cin.fail()))     // do the input
                    throw Invalid_Input("Was expecting an integer for y coordinate");    // throw an exception
                model.NewCommand(type, a, b, c);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            default: {
                throw Invalid_Input("Invalid object type");
                break;
            }
        }
        }
    catch (Invalid_Input& except) {
        cout << "Invalid input - " << except.msg_ptr << "Invalid command code. " << endl;
        // actions to be taken if the input is wrong
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    }
    
    return 0;
}