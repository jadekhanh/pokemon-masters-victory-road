#include <iostream>
#include "Point2D.h"
#include "Model.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
using namespace std;
#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

void DoMoveCommand(Model &, int, Point2D);
void DoMoveToCenterCommand(Model &, int, int);
void DoMoveToGymCommand(Model &, int, int);
void DoStopCommand(Model &, int);
void DoBattleCommand(Model &, int, unsigned int);
void DoRecoverInCenterCommand(Model&, int, unsigned int);
void DoAdvanceCommand(Model&, View&);
void DoRunCommand(Model&, View& view);

#endif