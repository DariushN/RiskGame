#include <iostream>
#include "Player.h"
#include "MapLoader.h"
#include "PlayerStrategies.h"
#include "Map.h"
#include "Cards.h"
class AggressiveComputer;
class BenevolentComputer;
class HumanPlayer;

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	MapLoader* mapLoader = new ConquestAdapter();
	Map* MAP = mapLoader->MapBuilder("../Domination_maps/Earth Alternate.map");
	std::cout<<"Map name: " << MAP->getName() << endl;



	//Initialize some player objects
    std::string name1 = "RandomComputer";
    Player* player = new Player();
    player->setName(name1);
	std::cout << "Player Name: " << player->getName() << std::endl;
    //Initialize some player objects
    std::string name2= "CheaterPlayer";
    Player* player2 = new Player();
    player2->setName(name2);
    std::cout << "Player Name: " << player2->getName() << std::endl;
    //Initialize some player objects

	//give player some initial territories
	for(int i=0; i<42; i+=2) {
		MAP->Territories[i]->setOwner(player);
		MAP->Territories[i]->incTroops(i);
		player->lands.push_back(MAP->Territories[i]);
	}
	for(int i=1; i<42; i+=2) {
		MAP->Territories[i]->setOwner(player2);
		MAP->Territories[i]->setTroops(10);
		player2->lands.push_back(MAP->Territories[i]);
	}

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP->Territories);
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());
    deck->draw(player2->getHand());





    // Setting strategies
	player->setStrategy(new RandomComputer());
	player2->setStrategy(new CheaterComputer());
	player->reinforce(MAP);
    std::cout << "\n\n\n\n";
    player2->reinforce(MAP);
    std::cout << "\n\n\n\n";
    player->fortify();
    std::cout << "\n\n\n\n";
    player2->fortify();
    std::cout << "\n\n\n\n";


    //Changing strategy mid-play (switching strategy of player 1 and 2)
    player2->setStrategy(new RandomComputer());
    player->setStrategy(new CheaterComputer());
    player2->attack(MAP);
    std::cout << "\n\n\n\n";
    player->attack(MAP);
    std::cout << "\n\n\n\n";

}
