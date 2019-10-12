//
// Created by dariush
//

#include "Cards.h"
#include <algorithm>
#include <random>


Deck::Deck(vector<string *> territories) {
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
    Card* tempCard = new Card();
    //Populating the cards in the deck
    for(auto&& x: territories){
        tempCard->setType(types.back()); //Take last element of types
        tempCard->setTerritory(*x);
        types.pop_back(); //Remove last element of types
        Cards.push_back(tempCard);
    }
}
Card Deck::draw(Hand playerHand) {
    playerHand.Cards.push_back(Cards.back());
    Cards.pop_back();
}
Deck::~Deck() {
    for(auto&& x:Cards){
        delete x;
    }
}

Card::Card() {
}
string Card::getTerritory() {
    return *territory;
}
string Card::getType() {
    return *type;
}
void Card::setTerritory(string territory) {
    *this->territory = territory;
}
void Card::setType(string type) {
    *this->type = type;
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

bool Hand::isExtraArmyBonus(vector<string*> playerTerritories, vector<Card*> matchedCards) {
    for(auto&& x:playerTerritories){
        for(auto&& y:matchedCards){
            if(y->getTerritory()==*x){
                return true;
            }
        }
    }
    return false;
}

//TODO: Add occupied territory rule
int Hand::exchange(vector<string*> playerTerritories){
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
    if(!matchedCards.empty()) {
        for (int i=Cards.size()-1;i>=0;i--) {
            for (auto &&y:matchedCards) {
                if(Cards.at(i)->getTerritory()==y->getTerritory()){
                    Cards.erase(Cards.begin()+i);
                }
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
            return numberOfSetsTraded*3+4;
        return numberOfSetsTraded*3;
    }

};

