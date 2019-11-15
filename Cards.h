//
// Created by dariush
//

#ifndef RISKGAME_CARDS_H
#define RISKGAME_CARDS_H

#include <string>
#include "Map.h"
#include <vector>
using namespace std;
class Territory;

static int numberOfSetsTraded=0;
class Card {
public:
    Card(); // Default constructor
    Card& operator=(const Card &orig);
    ~Card(); // Destructor
    Card(const Card& orig);
    string getType(); //Getter
    void setType(string type); //Setter
    string getTerritory();//Getter
    void setTerritory(string territory); //setter
private:
    string* type;
    string* territory;
};
class Hand{
public:
    Hand(); //Default constructor
    Hand& operator=(const Hand &orig);
    ~Hand(); // Destructor
    Hand(const Hand& orig);
    int exchange(vector<Territory*> playerTerritories); //Exchange set for points
    bool isExtraArmyBonus(vector<Territory*> playerTerritories, vector<Card*> matchedCards); //Check if eligible for bonus
    vector<Card*> Cards; // Cards in hand
};
class Deck {
public:
    Deck(vector<string*> territories); // Constructor
    Deck& operator=(const Deck &orig);
    Deck(vector<Territory*> territories); // Constructor
    Deck(const Deck& orig);
    ~Deck(); // Destructor
    void initializeDeck(vector<string *> territories); // initialize and populate deck
    void initializeDeck(vector<Territory *> territories); // initialize and populate deck
    void draw(Hand* playerHand); // draw card from deck to the hand
    void setNbOfSetsTraded(int x); // setter
    vector<Card*> Cards; //cards in deck
};

#endif //RISKGAME_CARDS_H
