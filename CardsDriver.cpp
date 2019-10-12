
#include <cstdlib>
#include <iostream>
#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Territory.h"
#include "Continent.h"
#include "MapLoaderUtility.h"
#include <sstream>

int main(int argc, char** argv) {
    std::cout<<"Beginning program: Cards"<<endl;
    //Initialize main tested objects
    Map MAP = MapBuilder("../Maps/risk.map");
    Deck deck = Deck(MAP.Territories);
    std::cout <<"Newly generated deck: "<<endl;

    //Setting up general test variables for driver
    int nbOfInfantry=0;
    int nbOfArtillery=0;
    int nbOfCavalry=0;
    vector<Territory*> territoriesOwned;
    Territory* t1 = new Territory();
    Territory* t2 = new Territory();
    Territory* t3 = new Territory();
    Territory* t4 = new Territory();
    Territory* t5 = new Territory();
    t1->setName("Eastern-Australia");
    t2->setName("Brazil");
    t3->setName("Ukraine");
    t4->setName("Iceland");
    t5->setName("Peru");
    territoriesOwned.push_back(t1);
    territoriesOwned.push_back(t2);
    territoriesOwned.push_back(t3);
    territoriesOwned.push_back(t4);
    territoriesOwned.push_back(t5);


    //Display the deck content
    for(auto&& x:deck.Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
        if(x->getType()=="Artillery")
            nbOfArtillery++;
        if(x->getType()=="Cavalry")
            nbOfCavalry++;
        if(x->getType()=="Infantry")
            nbOfInfantry++;
    }
    //Display summary of deck
    cout << "\nSummary of deck:" << endl << "Number of Infantry: "<< nbOfInfantry << endl
    << "Number of Cavalry: "<< nbOfCavalry << endl<<"Number of Artillery: "<< nbOfArtillery << endl;
    //Create hand, and draw from it 5 times
    Hand* hand = new Hand();
    cout << "First draw:"<<endl;
    deck.draw(hand);
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    cout << "Second draw:"<<endl;
    deck.draw(hand);
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    cout << "Third draw:"<<endl;
    deck.draw(hand);
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    cout << "Fourth draw:"<<endl;
    deck.draw(hand);
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    cout << "Fifth draw:"<<endl;
    deck.draw(hand);
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    //Exchanging a set for points
    cout<< "Exchanging, with the resulting points: "<<hand->exchange(territoriesOwned)<<endl;
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
    //Drawing 3 times and incrementing global nb of traded sets to display point upgrade
    cout << "Drawing three more times and incrementing the number of traded sets to 5" << endl;
    deck.draw(hand);
    deck.draw(hand);
    deck.draw(hand);
    deck.setNbOfSetsTraded(5);
    cout<< "Exchanging, with the resulting points: "<<hand->exchange(territoriesOwned)<<endl;
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }

    return 0;
}
