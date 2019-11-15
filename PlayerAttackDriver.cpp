#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "MapLoader.h"

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	Map* MAP = MapLoader::MapBuilder("Maps/risk.map");
	std::cout << "Map name: " << MAP->getName() << endl;

	//Initialize some player objects
	std::string name1 = "Player1";
	std::string name2 = "Player2";
	Player* player = new Player();
	Player* player2 = new Player();
	player->setName(name1);
	player2->setName(name2);
	std::cout << "Player Name: " << player->getName() << std::endl;
	std::cout << "Player Name: " << player2->getName() << std::endl;

	//give player some initial territories
	for (int i = 0; i<10; i++) {
		MAP->Territories[i]->setOwner(player);
		player->lands.push_back(MAP->Territories[i]);
	}

	for (int i = 10; i<MAP->Territories.size(); i++) {
		MAP->Territories[i]->setOwner(player2);
		player2->lands.push_back(MAP->Territories[i]);
	}


	//player1 and player2 reinforces then player1 attacks
	player->reinforce(MAP);
    player2->reinforce(MAP);
	player->attack(MAP);
}
