#include "Map.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>
class Player;

#ifndef SRC_PLAYERSTRATEGIES_H_
#define SRC_PLAYERSTRATEGIES_H_

class PlayerStrategies {
public:
    virtual ~PlayerStrategies() = 0;
    virtual void reinforce(Map* map, Player* player) = 0;
    virtual void attack(Map* map, Player* player) = 0;
    virtual void fortify(Player* player) = 0;
};

class HumanPlayer : public PlayerStrategies {
public:
    void reinforce(Map* map, Player* player);
    void attack(Map* map, Player* player);
    void fortify(Player* player);
    ~HumanPlayer(){
        std::cout << "human player destructor \n";
    }
};

class AggressiveComputer : public PlayerStrategies {
public:
    void reinforce(Map* map, Player* player);
    void attack(Map* map, Player* player);
    void fortify(Player* player);
    ~AggressiveComputer(){
        std::cout << "Aggressive Computer destructor \n";
    }
};

class BenevolentComputer : public PlayerStrategies {
    void reinforce(Map* map, Player* player);
    void attack(Map* map, Player* player);
    void fortify(Player* player);
    ~BenevolentComputer(){
        std::cout << "Benevolent Computer destructor \n";
    }
};

int maxDiceToRoll(bool isAttacker, Territory *territory);

#endif /* SRC_PLAYERSTRATEGIES_H_ */

