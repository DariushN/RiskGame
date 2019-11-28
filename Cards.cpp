//
// Created by dariush
//

#include "Cards.h"
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Constructor (initialize out of strings)
Deck::Deck(vector<string *> territories) {
    initializeDeck(territories);
}

Deck& Deck::operator=(const Deck &orig) {
    if(&orig!=this){
        for(auto&& x:Cards){
            delete x;
        }
        for(auto && x:orig.Cards){
            Cards.push_back(new Card(*x));
        }
    }
    return *this;
}
// Overloaded constructor (initialize out of territories)
Deck::Deck(vector<Territory *> territories) {
    initializeDeck(territories);
}

Deck::Deck(const Deck& orig){
    for(auto && x:orig.Cards){
        Cards.push_back(new Card(*x));
    }
}

// Initialize the deck to populate it with strings of territories
void Deck::initializeDeck(vector<string *> territories) {
    //Creating a types vectors with the correct amount of each
    vector<string> types;
    int typeSize = territories.size()/3;
    types.insert(types.end(), typeSize, "Infantry");
    types.insert(types.end(), typeSize, "Artillery");
    types.insert(types.end(), typeSize, "Cavalry");
    //Shuffling types vector to get different ones in a row
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(types), std::end(types), rng);
    //Populating the cards in the deck
    for(auto&& x: territories){
        Card* tempCard = new Card();
        tempCard->setType(types.back()); //Take last element of types
        tempCard->setTerritory(*x);
        types.pop_back(); //Remove last element of types
        Cards.push_back(tempCard);
    }
}
// Initialize the deck to populate it with Territory objects
void Deck::initializeDeck(vector<Territory *> territories) {
    //Creating a types vectors with the correct amount of each
    vector<string> types;
    int typeSize = territories.size()/3;
    types.insert(types.end(), typeSize, "Infantry");
    types.insert(types.end(), typeSize, "Artillery");
    types.insert(types.end(), typeSize, "Cavalry");
    //Shuffling types vector to get different ones in a row
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(std::begin(types), std::end(types), rng);
    //Populating the cards in the deck
    for(auto&& x: territories){
        Card* tempCard = new Card();
        tempCard->setType(types.back()); //Take last element of types
        tempCard->setTerritory(x->getName());
        types.pop_back(); //Remove last element of types
        Cards.push_back(tempCard);
    }
    std::shuffle(std::begin(Cards), std::end(Cards), rng);
}
//Draw card from deck and place it on the Cards data member of Hand
void Deck::draw(Hand* playerHand) {
    playerHand->Cards.push_back(Cards.back());
    Cards.pop_back();
}
//Setter for the number of sets traded
void Deck::setNbOfSetsTraded(int x) {
    numberOfSetsTraded=x;
}

//Destructor
Deck::~Deck() {
    for(auto&& x:Cards){
        delete x;
    }
}
//Constructor
Card::Card() {
    type = new string("");
    territory = new string("");
}

Card& Card::operator=(const Card &orig) {
    if(&orig!=this){
        delete type;
        delete territory;
        type = new string(*orig.type);
        territory = new string(*orig.territory);
    }
    return *this;
}
Card::Card(const Card& orig){
    type = new string(*orig.type);
    territory = new string(*orig.territory);
}
//Getter of territory
string Card::getTerritory() {
    return *territory;
}
//Getter of type
string Card::getType() {
    return *type;
}
//Setter of territory
void Card::setTerritory(string newTerritory) {
    *territory = newTerritory;
}
//setter of type
void Card::setType(string newType) {
    *type = newType;
}
//Destructor
Card::~Card() {
    delete type;
    delete territory;
}

Hand::Hand(){}; //Default constructor

Hand& Hand::operator=(const Hand &orig) {
    if(&orig!=this){
        for(auto x:Cards){
            delete x;
        }
        for(auto && x:orig.Cards){
            Cards.push_back(new Card(*x));
        }
    }
    return *this;
}

Hand::Hand(const Hand& orig){
    for(auto && x:orig.Cards){
        Cards.push_back(new Card(*x));
    }
}
//Destructor
Hand::~Hand(){
    for(auto&& x:Cards)
        delete x;
}; // Destructor

//Check if the player is eligible for 2 extra armies (Check Risk Rulebook)
//Will compare the territories owned by players to the cards traded in
bool Hand::isExtraArmyBonus(vector<Territory*> playerTerritories, vector<Card*> matchedCards) {
    for(auto&& x:playerTerritories){
        for(auto&& y:matchedCards){
            if(y->getTerritory()==x->getName()){
                return true;
            }
        }
    }
    return false;
}

//Exchange cards for points
int Hand::exchange(vector<Territory*> playerTerritories){
    std::vector<Card*> matchedCards;
    bool exchanged = false;
    //Check if there is a set of similar type
    for(auto&& y:Cards){
        matchedCards.push_back(y);
        for(auto&& z:Cards){
            if(y->getTerritory()!=z->getTerritory()&& y->getType()==z->getType()){
                matchedCards.push_back(z);
            }
        }
        if(matchedCards.size()>2){
            break;
        }
        matchedCards.clear();
    }
    //Check if there is a set of each type
    if(matchedCards.empty()){
        bool searchDone=false;
        for(auto&& a:Cards){
            for(auto&& b:Cards){
                for(auto&& c:Cards){
                    if(a->getType()!=b->getType()&&b->getType()!=c->getType()&&a->getType()!=c->getType()){
                        matchedCards.push_back(a);
                        matchedCards.push_back(b);
                        matchedCards.push_back(c);
                        searchDone=true;
                        break;
                    }
                }
                if(searchDone)
                    break;
            }
            if(searchDone)
                break;
        }
    }
    //Remove cards from hand that are traded in
    if(!matchedCards.empty()) {
        int deleteCount=0;
        for (auto &&y:matchedCards) {
            for (int i=Cards.size()-1;i>=0;i--) {
                if(Cards.at(i)->getTerritory()==y->getTerritory()){
                    deleteCount++;
                    Cards.erase(Cards.begin() + i);
                }
            }
            if (deleteCount>2){
                break;
            }
        }
        exchanged=true;
        numberOfSetsTraded++;
    }
    //Check if player is bonus eligible
    bool isBonusEligible = isExtraArmyBonus(playerTerritories, matchedCards);
    //Exchange set with points
    if(numberOfSetsTraded<6&&exchanged){
        if(isBonusEligible)
            return numberOfSetsTraded*2+4;
        return numberOfSetsTraded*2+2;
    }
    if(numberOfSetsTraded>=6&&exchanged){
        if(isBonusEligible)
            return (numberOfSetsTraded-1)*3+2;
        return (numberOfSetsTraded-1)*3;
    }
    return 0;
};

