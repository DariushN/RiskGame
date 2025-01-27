#include "Map.h"
#include "Player.h"
#include "GameObserver.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
class Player;


#ifndef PLAYERSTRATEGIES_H_
#define PLAYERSTRATEGIES_H_


class PlayerStrategies {
public:
	virtual ~PlayerStrategies() = 0; // Destructor
	virtual void reinforce(Map* map, Player* player) = 0; // Reinforce method
	virtual void attack(Map* map, Player* player) = 0; // Attack method
	virtual void fortify(Player* player) = 0; // Fortify method
        virtual string getName() = 0;
};

class HumanPlayer : public PlayerStrategies {
public:
	void reinforce(Map* map, Player* player); // Reinforce method
	void attack(Map* map, Player* player); // Attack method
	void fortify(Player* player); // Fortify method
        string getName(){ return "Human";} //inline function for strategy name
	// Inline destructor
	~HumanPlayer(){
		std::cout << "Human player destructor \n";
	}

};

class AggressiveComputer : public PlayerStrategies {
public:
	void reinforce(Map* map, Player* player); // Reinforce method
	void attack(Map* map, Player* player); // Attack method
	void fortify(Player* player); // Fortify method
        string getName(){ return "Aggressive";} //inline function for strategy name
	// Inline destructor
	~AggressiveComputer(){
		std::cout << "Aggressive Computer destructor \n";
	}
};

class BenevolentComputer : public PlayerStrategies {
	void reinforce(Map* map, Player* player); // Reinforce method
	void attack(Map* map, Player* player); // Attack method
	void fortify(Player* player); // Fortify method
        string getName(){ return "Benevolent";} //inline function for strategy name
	// Inline destructor
	~BenevolentComputer(){
		std::cout << "Benevolent Computer destructor \n";
	}
};

class CheaterComputer : public PlayerStrategies {
public:
	void reinforce(Map* map, Player* player); // Reinforce method
	void attack(Map* map, Player* player); // Attack method
	void fortify(Player* player); // Fortify method
        string getName(){ return "Cheater";} //inline function for strategy name
	// Inline destructor
	~CheaterComputer(){
		std::cout << "Cheater Computer destructor \n";
	}

private:
	bool shouldFortify(std::vector<Territory*> adjLands, Player* player);
};

class RandomComputer : public PlayerStrategies {
public:
	RandomComputer(){
		int seed = time(0);
		srand(seed);
	}
	void reinforce(Map* map, Player* player); // Reinforce method
	void attack(Map* map, Player* player); // Attack method
	void fortify(Player* player); // Fortify method
        string getName(){ return "Random";} //inline function for strategy name
	// Inline destructor
	~RandomComputer(){
		std::cout << "Cheater Computer destructor \n";
	}
};

int maxDiceToRoll(bool isAttacker, Territory *territory); // Maximum amount of dice a player can roll

#endif /* PLAYERSTRATEGIES_H_ */

