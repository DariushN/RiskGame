
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector> 
#include "Dice.h"
#include "Map.h"
#include "Cards.h"
#include "PlayerStrategies.h"
class Territory;
class Continent;
class Map;
class Hand;
class PlayerStrategies;


class Player {
private:
	PlayerStrategies *strategy;
public:
    Player();//constructor
    Player(const Player& orig);
    Player& operator=(const Player &orig);
    virtual ~Player();//destructor
    int getId();//getter for id
    void setId(int a); //setter for id
    std::string getName();//getter for name
    void setName(std::string a);//setter for name
    std::vector <Territory*> lands;//vector of territories that a player occupies
    std::vector <Continent*> continents; //vector of continents that a player occupies
    void hasContinent(Map* map);//method to check if owns a continent
	void reinforce(Map* map){
		this->strategy->reinforce(map, this);
	}
	void attack(Map* map);//attack method
	int maxDiceToRoll(bool isAttacker, Territory* territory);
	void fortify(){
		this->strategy->fortify(this);
	}
	int getArmies();//getter for armies
	void recuperateArmies(Map* map);
	void setArmies(int army);//setter for armies
	void placeArmies(int armies);//method to place armies on territories
	void printAdjacentCountries(std::vector<Territory*> territories); //prints the adjacent territories
	Hand* getHand();
	void setHand(Hand hand);
	Dice* getDice();
	void setDice(Dice dice);
	void setStrategy(PlayerStrategies *newStrategy){
		this->strategy = newStrategy;
	}
private:
    int* id; //id of a player
    std::string* name; //name of a player
    int* armies; //number of armies that a player has during his turn
	Dice* dice; //dice rolling facility object
	Hand* hand; // hand of risk cards
};

#endif /* PLAYER_H */

