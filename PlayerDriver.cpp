#include <iostream>
#include "Player.h"
#include "MapLoaderUtility.h"
#include "Territory.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	Map MAP = MapBuilder("Resources/Maps/risk.map");
	std::cout<<"Map name: " << MAP.getName() << endl;

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
	for(int i=0; i<10; i++) {
		MAP.Territories[i]->setOwner(player);
		player->lands.push_back(MAP.Territories[i]);
	}

	for(int i=20; i<30; i++) {
		MAP.Territories[i]->setOwner(player);
		player->lands.push_back(MAP.Territories[i]);
	}

	//Player owns a dice rolling facility
	int x;
	player->dice->activate(&x);
	int y;
	player->dice->activate(&y);
	player->dice->printAverages();

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP.Territories);
	deck->draw(player->hand);
	deck->draw(player->hand);
	deck->draw(player->hand);
	deck->draw(player->hand);
	deck->draw(player->hand);


	//player has access to 3 function reinforce, attack, fortify
	player->reinforce(&MAP);
	player->attack();
	player->fortify();
}
