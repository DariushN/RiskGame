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
Deck::~Deck() {}

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
Card::~Card() {}

Hand::Hand(){}; //Default constructor

Hand::~Hand(){}; // Destructor

int Hand::exchange(){
    numberOfSetsTraded++;
    /*
    if(numberOfSetsTraded<6){
        for(auto&& y:Cards){

        }
    } else{

    }*/
};

