#include <iostream>
#include "Player.h"
#include "MapLoader.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	MapLoader mapLoader;
	Map* MAP = mapLoader.MapBuilder("Maps/risk.map");
	std::cout<<"Map name: " << MAP->getName() << endl;



	//Initialize some player objects
	std::string name1 = "Player1";
	Player* player = new Player();
	player->setName(name1);
	std::cout << "Player Name: " << player->getName() << std::endl;

	//give player some initial territories
	for(int i=0; i<4; i++) {
		MAP->Territories[i]->setOwner(player);
		player->lands.push_back(MAP->Territories[i]);
	}

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP->Territories);

	std::cout << "\nPlayer only has a few territories (less than 9), no cards and no continents" << std::endl;
	player->reinforce(MAP);

	for(int i=4; i<9; i++) {
		MAP->Territories[i]->setOwner(player);
		player->lands.push_back(MAP->Territories[i]);
	}

	for(int i=20; i<30; i++) {
			MAP->Territories[i]->setOwner(player);
			player->lands.push_back(MAP->Territories[i]);
		}
	std::cout << "\nPlayer now owns 2 continents (north america and africa)" << std::endl;

	player->reinforce(MAP);

	std::cout << "\n Now player has 6 cards in his hand" << std::endl;
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

	player->reinforce(MAP);


}
