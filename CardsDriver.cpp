
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
    Map MAP = MapBuilder("../Maps/risk.map");//test with proper case
    Deck deck = Deck(MAP.Territories);
    std::cout <<"Newly generated deck: "<<endl;

    //Setting up general test variables for driver
    int nbOfInfantry=0;
    int nbOfArtillery=0;
    int nbOfCavalry=0;
    vector<string*> territoriesOwned;
    territoriesOwned.push_back(new string("Eastern-Australia"));
    territoriesOwned.push_back(new string("Brazil"));
    territoriesOwned.push_back(new string("Ukraine"));
    territoriesOwned.push_back(new string("Iceland"));
    territoriesOwned.push_back(new string("Peru"));



    for(auto&& x:deck.Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
        if(x->getType()=="Artillery")
            nbOfArtillery++;
        if(x->getType()=="Cavalry")
            nbOfCavalry++;
        if(x->getType()=="Infantry")
            nbOfInfantry++;
    }
    cout << "\nSummary of deck:" << endl << "Number of Infantry: "<< nbOfInfantry << endl
    << "Number of Cavalry: "<< nbOfCavalry << endl<<"Number of Artillery: "<< nbOfArtillery << endl;

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
    cout<< "Exchanging, with the resulting points: "<<hand->exchange(territoriesOwned)<<endl;
    cout<< "Hand content: " <<endl;
    for(auto&& x: hand->Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }
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
    /*cout<<"\nDeck Content:"<<endl;
    for(auto&& x:deck.Cards){
        std::cout << "\tTerritory: " << x->getTerritory() << "\tType: " << x->getType() << endl;
    }*/

    return 0;
}
