GCC=g++ -std=c++11 -g

OBJS=main.o Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o PokemonCenter.o Model.o Trainer.o PokemonGym.o View.o WildPokemon.o

default: PA4

PA4: $(OBJS)
	$(GCC) -o PA4 $(OBJS) 

Vector2D.o: Vector2D.cpp Vector2D.h
	$(GCC) -c Vector2D.cpp -o Vector2D.o 
	
Point2D.o: Point2D.cpp Point2D.h Vector2D.h
	$(GCC) -c Point2D.cpp -o Point2D.o 

Building.o: Building.cpp Building.h
	$(GCC) -c Building.cpp -o Building.o

GameObject.o: GameObject.cpp GameObject.h Point2D.h Vector2D.h
	$(GCC) -c GameObject.cpp -o GameObject.o 

PokemonCenter.o: PokemonCenter.cpp PokemonCenter.h GameObject.h Point2D.h
	$(GCC) -c PokemonCenter.cpp -o PokemonCenter.o

Model.o: Model.cpp Model.h GameObject.h Trainer.h PokemonGym.h PokemonCenter.h View.h
	$(GCC) -c Model.cpp -o Model.o 

PokemonGym.o: PokemonGym.cpp PokemonGym.h GameObject.h Point2D.h
	$(GCC) -c PokemonGym.cpp -o PokemonGym.o

View.o: View.cpp View.h GameObject.h Point2D.h
	$(GCC) -c View.cpp -o View.o 

Trainer.o: Trainer.cpp Trainer.h GameObject.h Point2D.h Vector2D.h PokemonCenter.h PokemonGym.h
	$(GCC) -c Trainer.cpp -o Trainer.o

GameCommand.o: GameCommand.cpp GameCommand.h Model.h GameObject.h Trainer.h PokemonGym.h PokemonCenter.h
	$(GCC) -c GameCommand.cpp -o GameCommand.o

WildPokemon.o: WildPokemon.cpp WildPokemon.h GameObject.h Point2D.h Vector2D.h
	$(GCC) -c WildPokemon.cpp -o WildPokemon.o
	
main.o: main.cpp Building.h Point2D.h Vector2D.h GameCommand.h PokemonCenter.h Model.h Trainer.h PokemonGym.h GameObject.h View.h WildPokemon.h
	$(GCC) -c main.cpp -o main.o

#NOTE: early checkpoint commands might not compile, due to class changes in later checkpoints

test: test.cpp Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o PokemonCenter.o Model.o Trainer.o PokemonGym.o View.o WildPokemon.o
	$(GCC) -o test test.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o View.o WildPokemon.o

checkpoint1: TestCheckPoint1.cpp Point2D.o Vector2D.o GameObject.o
	$(GCC) -o checkpoint1.exe TestCheckPoint1.cpp Point2D.o Vector2D.o GameObject.o
	
checkpoint2: TestCheckPoint2.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o
	$(GCC) -o checkpoint2.exe TestCheckPoint2.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o

checkpoint3: TestCheckpoint3.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o
	$(GCC) -o checkpoint3.exe TestCheckPoint3.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o

checkpoint4: TestCheckpoint4.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o
	$(GCC) -o checkpoint4.exe TestCheckPoint4.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o

checkpoint5: TestCheckpoint5.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o View.o
	$(GCC) -o checkpoint5.exe TestCheckPoint5.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o GameCommand.o View.o

clean: 
	rm $(OBJS) PA4