# pa4-template

## You must pass your code from pa3 to this repository
The behaviors of my Wild Pokemons:

1. If a Wild Pokemon and trainer are on top of each other, the Wild Pokemon starts following the trainer, meaning it will copy the exact location of the trainer.

2. When the trainer moves, the Wild Pokemon moves with it.

3. The Wild Pokemon attacks the trainer everytime the trainer moves, decreasing the trainer's health by 5 (the number of attacks that the Wild Pokemon has). This means that if a trainer is followed by a Wild Pokemon, everytime the trainer moves, the health of the trainer is decreased by 1 (since it moves) and 5 (by the number of Wild Pokemon's attacks). So, trainer's health is decreased by 6 for each move with each following Wild Pokemon.

4. If the trainer is fainted, the Wild Pokemon stops following the trainer.

5. The Wild Pokemon can follow the trainer and come inside any building.

6. The Wild Pokemon's health decreases by 1 for every move it makes.

7. A trainer can be followed by more than 1 Wild Pokemons, but Wild Pokemon can only follow 1 trainer.

8. Each Wild Pokemon initially has health equals 100.