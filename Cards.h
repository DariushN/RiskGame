//
// Created by dariush
//

#ifndef RISKGAME_CARDS_H
#define RISKGAME_CARDS_H

using namespace std;
#include <string>
#include <vector>


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
    ~Deck(); // Destructor
    void initializeDeck(vector<string *> territories);
    Card draw(Hand playerHand);
    vector<Card*> Cards;
};

#endif //RISKGAME_CARDS_H
