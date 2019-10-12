
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector> 
#include "Dice.h"
#include "Continent.h"
#include "Territory.h"
#include "Map.h"
class Territory;
class Continent;
class Map;


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
	//Needs a hand of Risk cards 
	Dice* dice;

private:
    int* id;
    std::string* name;
    int* armies;
};

#endif /* PLAYER_H */

