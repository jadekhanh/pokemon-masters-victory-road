#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <iomanip>
#include "Trainer.h"
using namespace std;

unsigned int health_gained = 0;

Trainer::Trainer():GameObject('B') {
    speed = 5;
    cout << "Trainer default constructed." << endl;
    state = STOPPED;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    PokemonCenter* current_center = NULL;
    PokemonGym* current_gym = NULL;
    wild_pokemon_count = 0;
}

Trainer::Trainer(char in_code):GameObject(in_code) {
    speed = 5;
    cout << "Trainer constructed." << endl;
    state = STOPPED;
    display_code = in_code;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    PokemonCenter* current_center = NULL;
    PokemonGym* current_gym = NULL;
    wild_pokemon_count = 0;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc):GameObject(in_loc, in_id, in_code) {
    speed = in_speed;
    name = in_name;
    state = STOPPED;
    display_code = in_code;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    PokemonCenter* current_center = NULL;
    PokemonGym* current_gym = NULL;
    cout << "Trainer constructed." << endl;
    wild_pokemon_count = 0;
}

Trainer::~Trainer() {
    cout << "Trainer destructed." << endl;
}

void Trainer :: StartMoving(Point2D dest)
{
    SetupDestination(dest);
    // if the trainer is at a gym
    if(state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation()))
    {
        current_gym->RemoveOneTrainer();
    }
    // if the trainer is at a center
    if(state == AT_CENTER && GetDistanceBetween(destination,current_center->GetLocation()))
    {
        current_center -> RemoveOneTrainer();
    } 
    // if the trainer is already at the destination
    if (GetDistanceBetween(destination,location) == 0)
    {
        cout << display_code << " " << id_num << " : I'm already there. See?" << endl;
    }
    // if the trainer is fainted
    else if (this->HasFainted())
    {
        cout <<  display_code << " " << id_num << " : All my Pokemon have fainted. I may move but you cannot see me." << endl;
    }
    // if none of the above
    else
    {
        cout <<  display_code << " " << id_num << " : On my way" << endl;
        state = MOVING;
    }
}

void Trainer :: StartMovingToGym(PokemonGym* gym)
{
    SetupDestination(gym ->GetLocation());
    // if the trainer is at another gym
    if(state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation()))
    {
        current_gym->RemoveOneTrainer();
    }
    // if the trainer is at a center
    if(state == AT_CENTER && GetDistanceBetween(destination,current_center->GetLocation()))
    {
        current_center -> RemoveOneTrainer();
    }
    // if the trainer is fainted
    if(this->HasFainted())
    {
        cout << display_code << " " << id_num << " : All my Pokemon have fainted so I can't move to gym... " << endl;
    }
    // if the trainer is already at the chosen gym
    else if (GetDistanceBetween(this->location,gym->GetLocation()) == 0)
    {
        cout << display_code << " " << id_num << " : I am already at the PokemonGym!" << endl;
    }
    // if none of the above
    else
    {
        state = MOVING_TO_GYM;
        current_gym = gym;
        cout << display_code << " " << id_num << " : on my way to the gym " << gym->GetId() << endl;
    }

}


void Trainer :: StartMovingToCenter(PokemonCenter* center)
{
    SetupDestination(center->GetLocation());
    // if the trainer is at a gym
    if(state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation())) 
    {
        current_gym->RemoveOneTrainer();
    }
    // if the trainer is at another center
    if(state == AT_CENTER && GetDistanceBetween(destination,current_center->GetLocation()))
    {
        current_center -> RemoveOneTrainer();
    }
    // if the trainer is fainted
    if(this->HasFainted())
    {
        cout << display_code << " " << id_num << " : All my Pokemon have fainted so I should have gone to the center.." << endl;
    }
    // if the trainer is already at the chosen center
    else if(GetDistanceBetween(this->location,center->GetLocation()) == 0)
    {
        cout << display_code << " " << id_num << " : I am already at the Pokemon Center!" << endl;
    }
    // none of the above
    else
    {
        state = MOVING_TO_CENTER;
        current_center = center;
        cout << display_code << " " << id_num << " : On my way to the Pokemon Center " << center->GetId() << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles) {     // tells the trainer to start battling (num_battles) in a PokemonGym
    // If this Trainer’s pokemon are too tired
    if (this->HasFainted() == true) {
        cout << display_code << id_num << ": My Pokemon have fainted so no more battle for me..." << endl;
    }
    // If this Trainer's pokemon is not in a PokemonGym 
    else if (current_gym == NULL || (GetDistanceBetween(this->location, current_gym->GetLocation()) != 0)) {
        cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
    // If this Trainer does not have enough PokeDollars
    else if (current_gym->IsAbleToBattle(num_battles, PokeDollars, health) == false) {
        cout << display_code << id_num << ": Not enough money for battling" << endl;
    }
    // If this current_gym is done
    else if (current_gym->GetNumBattlesRemaining() == 0) {
        cout << "Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    }
    // If this Trainer can start training
    else {
        state = BATTLING_IN_GYM;
        battles_to_buy = (current_gym->TrainPokemon(num_battles));
        battles_to_buy = battles_to_buy/(current_gym->GetExperiencePerBattle());
        cout << display_code << " " << id_num << " : Started to battle at the Gym " << current_gym->GetId() << " with " << num_battles << " battles" << endl;
        health -= (current_gym->GetHealthCost(battles_to_buy));
        PokeDollars -= (current_gym->GetPokeDollarCost((battles_to_buy)));
        experience += (battles_to_buy*(current_gym->GetExperiencePerBattle()));
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions) {     // tells the Trainers to start recovering health at a PokemonCenter
   
    // If this Trainer does not have enough PokeDollars
    if (current_center->CanAffordPotion(num_potions, PokeDollars) == false) {
        cout << display_code << id_num << ": Not enough money to recover health." << endl;
    }
    // If the Pokemon Center does not have at least one potion remaining 
    else if (current_center->GetNumPotionRemaining() < 1) { 
        cout << display_code << id_num << ": Cannot recover! No potion remaining in this PokemonCenter" << endl;
    }
    // If this Trainer is not in a Pokemon Center 
    else if (current_center == NULL || GetDistanceBetween(this->location, current_center->GetLocation()) != 0) {
        cout << display_code << id_num << ": I can only recover health at a Pokemon Center!" << endl;
    }
    // If this Trainer can start recovering health
    else {
        state = RECOVERING_HEALTH;
        potions_to_buy = current_center->DistributePotion(num_potions);
        PokeDollars -=  current_center->GetPokeDollarCost(potions_to_buy);
        unsigned int health_gained = 5*potions_to_buy;
        health += health_gained;
        cout << display_code << " " << id_num << " : Started recovering " << potions_to_buy << " potions at Pokemon Center " << (current_center->GetId()) << endl;
    }
}

void Trainer::Stop() {      // tells this Trainer to stop whatever it is doing
    state = STOPPED;
    cout << display_code << id_num << ": Stopping.." << endl;
}

bool Trainer::HasFainted() {
    if (health == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Trainer::ShouldBeVisible() {
    if (health == 0) {
        return false;
    }
    else {
        return true;
    }
}

void Trainer::ShowStatus() {
    cout << this->name << " status: " << endl;
    GameObject::ShowStatus();
    cout << "Being followed by " << wild_pokemon_count << " Wild Pokemon" << endl;
    if (state == STOPPED) {
        cout << "stopped" << endl;
    }
    else if (state == MOVING) {
        cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl; 
    }
    else if (state == MOVING_TO_GYM) {
        cout << "heading to PokemonGym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
    }
    else if (state == MOVING_TO_CENTER) {
        cout << "heading to PokemonCenter " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
    }
    else if (state == IN_GYM) {
        cout << "inside PokemonGym " << current_gym->GetId() << endl;
    }
    else if (state == AT_CENTER) {
        cout << "inside PokemonCenter " << current_center->GetId() << endl;
    }
    else if (state == BATTLING_IN_GYM) {
        cout << "battling in PokemonGym " << current_gym->GetId() << endl;
    }
    else if (state == RECOVERING_HEALTH) {
        cout << "recovering health in PokemonCenter " << current_center->GetId() << endl;
    }
}

bool Trainer :: Update()
{  
    if (this->HasFainted())
    {
        this->Stop();
        if(state != FAINTED){
            state = FAINTED;
            cout << this->name << " just ran out of health and can't move" << endl;
            return true;
        }
        cout << this->name << " is out of health and can't move" << endl;
        return false;
    }
        
    else if(state == STOPPED)
    {
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        return false;

    }
    else if (state == MOVING)
    {
        health -= 1;
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        
        
        if(UpdateLocation())
        {
            state = STOPPED;
            return true;
        }
        else
        {
            return false;
        }
    }

    else if (state == MOVING_TO_GYM)
    {
        health -= 1;
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        
        if(UpdateLocation())    // if the trainer has arrived OR if this function returns true
        {
            state = IN_GYM;
            current_gym->AddOneTrainer();
            return true;
        }
        else
        {
            return false;
        }
    }

    else if (state == MOVING_TO_CENTER)
    {
        health -= 1;
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        
        if(UpdateLocation())    // if the trainer has arrived OR if this function returns true
        {
            state = AT_CENTER;
            current_center->AddOneTrainer();
            return true;
        }
        else
        {
            return false;
        }
    }

    else if (state == IN_GYM)
    {
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        return false;
    }

    else if (state == AT_CENTER)
    {
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        return false;
    }

    else if (state == BATTLING_IN_GYM)
    {   
        state = IN_GYM;
        cout << name << " completed " << battles_to_buy << " battle(s)!" << endl;
        cout << name << " gained " << (battles_to_buy*(current_gym->GetExperiencePerBattle())) << " experience" << endl;
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        return true;
    }

    else if (state == RECOVERING_HEALTH)
    {
        unsigned int health_gained = 5*potions_to_buy;
        health += health_gained;
        cout << name << " recovered " << health_gained << " health!" << endl;
        cout << name << " bought " << potions_to_buy << " potion(s)!" << endl;
        cout << this->name << " status: " << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars: " << PokeDollars << endl;
        cout << "Experience: " << experience << endl;
        state = AT_CENTER;
        return true;
    }
    return false;
}

bool Trainer::UpdateLocation() {    // this function allows the object to move
    if (fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y)) {
        location = destination;
        cout << display_code << id_num << ": I'm there!" << endl;
        delta.x = 0;
        delta.y = 0;
        return true;    // to indicate that the object has arrived
    }
    else {
        location.x += delta.x;
        location.y += delta.y;
        cout << display_code << id_num << ": step..." << endl;
        return false;   // to indicate that the object has not arrived
    }
}

void Trainer::SetupDestination(Point2D dest) {
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

static double GetRandomAmountOfPokeDollars() { // non-member
    srand(time(NULL));
    double pokedollar_amount = (double)rand()/RAND_MAX;
    return pokedollar_amount*(2.0-0.0);
}

string Trainer::GetName() {
    return name;
}

void Trainer::AddOneWildPokemon() {
    wild_pokemon_count++;
    return;
}

void Trainer::RemoveOneWildPokemon() {
    wild_pokemon_count--;
    return;
}

int Trainer::GetHealth() {
    // return the trainer's health status
    return health;
}

int Trainer::ReduceHealth() {
    // return the trainer's health status after being attacked by a Wild Pokemon
    return health -= 5;
}