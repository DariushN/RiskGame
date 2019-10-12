//
// Created by dariush
//

#include "Cards.h"
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


Deck::Deck(vector<string *> territories) {
    initializeDeck(territories);
}
Deck::Deck(vector<Territory *> territories) {
    initializeDeck(territories);
}

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
void Deck::initializeDeck(vector<Territory *> territories) {
    //Creating a types vectors with the correct amount of each
    vector<string> types;
    int typeSize = territories.size()/3;
    types.insert(types.end(), typeSize, "Infantry");
    //types.insert(types.end(), typeSize, "Infantry");
    //types.insert(types.end(), typeSize, "Infantry");
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
void Deck::draw(Hand* playerHand) {
    playerHand->Cards.push_back(Cards.back());
    Cards.pop_back();
}
void Deck::setNbOfSetsTraded(int x) {
    numberOfSetsTraded=x;
}
Deck::~Deck() {
    for(auto&& x:Cards){
        delete x;
    }
}

Card::Card() {
    type = new string("");
    territory = new string("");
}
string Card::getTerritory() {
    return *territory;
}
string Card::getType() {
    return *type;
}
void Card::setTerritory(string newTerritory) {
    *territory = newTerritory;
}
void Card::setType(string newType) {
    *type = newType;
}
Card::~Card() {
    delete type;
    delete territory;
}

Hand::Hand(){}; //Default constructor

Hand::~Hand(){
    for(auto&& x:Cards)
        delete x;
}; // Destructor

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

int Hand::exchange(vector<Territory*> playerTerritories){
    std::vector<Card*> matchedCards;
    bool exchanged = false;
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
    bool isBonusEligible = isExtraArmyBonus(playerTerritories, matchedCards);
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

