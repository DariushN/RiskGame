#include <iostream>
#include "Player.h"
#include "GameEngine.h"
#include "MapLoader.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

int main(){
	//get a map for demonstration purposes
		Map* MAP =MapLoader::MapBuilder("Maps/risk.map");
		std::cout<<"Map name: " << MAP->getName() << endl;



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
		for(int i=0; i<MAP->Territories.size(); i++) {
			MAP->Territories[i]->setOwner(player);
			player->lands.push_back(MAP->Territories[i]);
		}
		std::vector<Player*> players;
		players.push_back(player2);
		players.push_back(player);
		GameEngine gameEngine;
		gameEngine.mainGameLoop(MAP, players);


		Map* MAP2 = MapLoader::MapBuilder("Maps/risk.map");
		std::cout<<"\n\nMap name: " << MAP2->getName() << endl;



		//Initialize some player objects
		std::string name3 = "Player3";
		Player* player12 = new Player();
		Player* player22 = new Player();
		Player* player32 = new Player();
		player12->setName(name1);
		player22->setName(name2);
		player32->setName(name3);
		std::cout << "Player Name: " << player12->getName() << std::endl;
		std::cout << "Player Name: " << player22->getName() << std::endl;
		std::cout << "Player Name: " << player32->getName() << std::endl;

		//give player some initial territories
		for(int i=0; i<15; i++) {
			MAP2->Territories[i]->setOwner(player12);
			player12->lands.push_back(MAP2->Territories[i]);
		}
		//give player some initial territories
		for(int i=15; i<30; i++) {
			MAP2->Territories[i]->setOwner(player22);
			player22->lands.push_back(MAP2->Territories[i]);
		}

		//give player some initial territories
		for(int i=30; i<42; i++) {
			MAP2->Territories[i]->setOwner(player32);
			player32->lands.push_back(MAP2->Territories[i]);
		}

		std::vector<Player*> players2;
		players2.push_back(player12);
		players2.push_back(player22);
		players2.push_back(player32);
		gameEngine.mainGameLoop(MAP2, players2);

	return 0;
}
