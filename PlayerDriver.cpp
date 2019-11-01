#include <iostream>
#include "Player.h"
#include "MapLoaderUtility.h"
#include "Territory.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	Map MAP = MapBuilder("Maps/risk.map");
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
	for(int i=0; i<4; i++) {
		MAP.Territories[i]->setOwner(player);
		player->lands.push_back(MAP.Territories[i]);
	}

	for(int i=4; i<15; i++) {
		MAP.Territories[i]->setOwner(player2);
		player2->lands.push_back(MAP.Territories[i]);
	}

	//Player owns a dice rolling facility
	int x;
	player->getDice()->activate(&x);
	int y;
	player->getDice()->activate(&y);
	player->getDice()->printAverages();

	//player owns a hand of risk cards
	Deck* deck = new Deck(MAP.Territories);
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());
	deck->draw(player->getHand());

	//player has access to 3 function reinforce, attack, fortify
	player->reinforce(&MAP);
	player->attack(&MAP);
	player->fortify();
}
