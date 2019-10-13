
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector> 
#include "Dice.h"
#include "Continent.h"
#include "Territory.h"
#include "Map.h"
#include "Cards.h"
class Territory;
class Continent;
class Map;
class Hand;


class Player {
public:
    Player();
    virtual ~Player();
    int getId();
    void setId(int a);
    std::string getName();
    void setName(std::string a);
    std::vector <Territory*> lands;
    std::vector <Continent*> continents;
    void hasContinent(Map* map);
	void reinforce(Map* map);
	void attack();
	void fortify();
	int getControlValue();
	int getArmies();
	void setArmies(int army);
	void placeArmies(int armies);
	void printAdjacentCountries(std::vector<Territory*> territories);
	Dice* dice;
	Hand* hand;


private:
    int* id;
    std::string* name;
    int* armies;
};

#endif /* PLAYER_H */

