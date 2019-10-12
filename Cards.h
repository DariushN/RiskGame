//
// Created by dariush
//

#ifndef RISKGAME_CARDS_H
#define RISKGAME_CARDS_H

#include <string>
#include "Territory.h"
#include <vector>
using namespace std;


static int numberOfSetsTraded=0;
class Card {
public:
    Card(); // Default constructor
    ~Card(); // Destructor
    string getType();
    void setType(string type);
    string getTerritory();
    void setTerritory(string territory);
private:
    string* type;
    string* territory;
};
class Hand{
public:
    Hand(); //Default constructor
    ~Hand(); // Destructor
    int exchange(vector<string*> playerTerritories);
    bool isExtraArmyBonus(vector<string*> playerTerritories, vector<Card*> matchedCards);
    vector<Card*> Cards;
};
class Deck {
public:
    Deck(vector<string*> territories); // Constructor
    Deck(vector<Territory*> territories); // Constructor
    ~Deck(); // Destructor
    void initializeDeck(vector<string *> territories);
    void initializeDeck(vector<Territory *> territories);
    void draw(Hand* playerHand);
    void setNbOfSetsTraded(int x);
    vector<Card*> Cards;
};

#endif //RISKGAME_CARDS_H
