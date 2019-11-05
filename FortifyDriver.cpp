#include <iostream>
#include "Player.h"
#include "MapLoader.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

int main(int argc, char** argv) {
	//get a map for demonstration purposes
	Map* MAP = MapLoader::MapBuilder("Maps/risk.map");
	std::cout<<"Map name: " << MAP->getName() << endl;



	//Initialize some player objects
	std::string name1 = "Player1";
	Player* player = new Player();
	std::string name2 = "Player2";
	Player* player2 = new Player();
	player->setName(name1);
	player2->setName(name2);
	std::cout << "Player Name: " << player->getName() << std::endl;

	//give player some initial territories
	for(int i=0; i<2; i++) {
		MAP->Territories[i]->setOwner(player);
		player->lands.push_back(MAP->Territories[i]);
		MAP->Territories[i]->setTroops(i);
	}

	for(int i=2; i<15; i++){
		MAP->Territories[i]->setOwner(player2);
		player2->lands.push_back(MAP->Territories[i]);
	}

	for(int i=15; i<18; i++) {
		MAP->Territories[i]->setOwner(player);
		player->lands.push_back(MAP->Territories[i]);
		MAP->Territories[i]->setTroops(i);
	}

	for(int i=18; i<42; i++){
		MAP->Territories[i]->setOwner(player2);
		player2->lands.push_back(MAP->Territories[i]);
	}


	bool deciding = true;
	char yesOrno;
	while(deciding){
		player->fortify();
		std::cout << "Would you like to fortify again (for demo)? y/n" << std::endl;
		std::cin >> yesOrno;
		if(yesOrno == 'y'){
			continue;
		}else{
			break;
		}
	}


}
