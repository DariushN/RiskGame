#include "PlayerStrategies.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>

void HumanPlayer::reinforce(Map* map, Player* player){

	player->recuperateArmies(map);

	player->placeArmies(player->getArmies());

	std::cout << "!! Player Done Reinforcing !!" << std::endl;
}

void HumanPlayer::fortify(Player* player){

	bool deciding = true;
	bool fortifying = true;

	while(deciding) {
		int count = 1;
		//print out all players territories and number of armies on each
		for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
			std::cout << count << ": " <<  player->lands[i]->getName() << "     Armies: " << player->lands[i]->getTroops() << std::endl;
			count++;
		}

		std::cout << "Would you like to fortify a position? y or n" << std::endl;
		char input;
		cin >> input;
		if(input == 'n'){
			break;
		} else if(input != 'y') {
			std::cout << "Please enter y or n to proceed" << std::endl;
			continue;
		}

		// Player decides to fortify

		//Print out all the territories and and their adjacent territories
		count = 1;
		cout << "\n\t---Your Available Territories--"<<endl;
		for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
			std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " <<
					player->lands[i]->getTroops() << std::endl;
			player->printAdjacentCountries(player->lands[i]->adjacents);
			count++;
		}

		while(fortifying) {
			std::cout << "Enter the country number you would like to move your armies from or type -1 to end fortification"  << std::endl;
			int country1;
			cin >> country1;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> country1;
			}

			if(country1 == -1) break;

			std::cout << "Enter the country you would like to fortify or type -1 to end fortification" << std::endl;
			int country2;
			std::cin >> country2;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> country2;
			}
			if(country2 == -1) break;

			//validation on countries picked
			if(country1 > count || country2 < 1) {
				std::cout << "Please pick a valid starting country" << std::endl;
				continue;
			} else if(country2 > count || country2 < 1) {
				std::cout << "Please pick a valid country to fortify" << std::endl;
				continue;
			} else if(country1 == country2) {
				std::cout << "Please pick different countries" << std::endl;
				continue;
			} else if(player->lands[country1 - 1]->getTroops() <= 1) {
				std::cout << "Starting country must have more than 1 army, please pick another country" << std::endl;
				continue;
			} else if(!player->lands[country1 - 1]->isAdj(player->lands[country2 - 1])) {
				std::cout << "Please pick countries that are adjacent" << std::endl;
				continue;
			}

			//loop to get number of troops that user wants to move
			while(1) {
				std::cout << "How many troops would you like to move from " << player->lands[country1 - 1]->getName()
										<< " to " << player->lands[country2 - 1]->getName() << std::endl;

				int troops;
				cin >> troops;
				while(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
					std::cout << "Please Enter a number: ";
					std::cin >> troops;
				}

				if(troops > player->lands[country1 - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a number less than "<< player->lands[country1 - 1]->getTroops() << std::endl;
					continue;
				} else if (troops < 1){
					std::cout << "Please enter a valid number" << std::endl;
				}else {
					//increment troops on territory chosen
					player->lands[country2 - 1]->incTroops(troops);
					//decrement troops on country where armies are traded
					player->lands[country1 - 1]->decTroops(troops);

					std::cout << "\t---Added armies to " << player->lands[country2 - 1]->getName() << "---" << endl;
					cout<< "\t---The new total is " << player->lands[country2 - 1]->getTroops() << "---" << endl;
					break;
				}
			}
			break;
		}
		break;
	}

	std::cout << "\n!! Player Done Fortifying !!" << std::endl;
}

void HumanPlayer::attack(Map *map, Player *player) {


	// Loop the operation to enable repeat
	while (true) {
		// Ask if wants to attack, if yes proceed, otherwise break
		cout << "Would you like to attack? (y/n)" << endl;
		char input;
		cin >> input;
		if (input == 'n') {
			cout << "!! Player Done Attacking !!";
			return;
		} else if (input != 'y') {
			std::cout << "please enter y or n to proceed" << std::endl;
			continue;
		}
		// Choose which country to attack from, from a list
		cout << "\n\t---Listing the countries you can attack from---" << endl;
		for (int i = 1; i <= player->lands.size(); i++) {
			cout << i << ": " << player->lands[i - 1]->getName() << "     Armies: " << player->lands[i - 1]->getTroops()
    	                				 << std::endl;
		}
		cout << "Choose which country you would like to attack from: " << endl;
		int countryInput;
		cin >> countryInput;
		// If invalid index or not enough army, we repeat the attack operation
		if (countryInput > player->lands.size() || countryInput < 1) {
			cout << "Invalid index" << endl;
			continue;
		}
		if (player->lands[countryInput - 1]->getTroops() < 2) {
			cout << "Not enough army on territory" << endl;
			continue;
		}
		cout << "\n\t---Listing the countries you can attack---" << endl;
		for (int i = 0; i < player->lands[countryInput - 1]->adjacents.size(); i++) {
			cout << i + 1 << ": " << player->lands[countryInput - 1]->adjacents[i]->getName() << "\tArmies: "
					<< player->lands[countryInput - 1]->adjacents[i]->getTroops() << std::endl;
		}
		// Choose which adjacent country to attack
		cout << "Which country would you like to attack" << endl;
		int countryAttackInput;
		cin >> countryAttackInput;
		if (countryAttackInput > player->lands[countryInput - 1]->adjacents.size() || countryAttackInput < 1) {
			cout << "Invalid index" << endl;
			continue;
		}
		Territory *attackedTerritory;
		// Retrieve attacked territory
		for (auto &&x: map->Territories) {
			if (x->getName() == player->lands[countryInput - 1]->adjacents[countryAttackInput - 1]->getName()) {
				attackedTerritory = x;
				break;
			}
		}
		// If we attack our own country, we restart the opertation
		if (attackedTerritory->getOwner()->getName() == player->getName()) {
			cout << "Cannot attack your own territory" << endl;
			continue;
		}
		// Determine how many dices user wants to roll after determining the max amount
		int maxAttackerDice = maxDiceToRoll(true, player->lands[countryInput - 1]);
		int maxDefenseDice = maxDiceToRoll(false, attackedTerritory);
		// If attacked territory is unoccupied, take it
		if (maxDefenseDice == 0) {
			cout << "Attacker wins battle and wins territory" << endl;
			//Remove territory lost from defense player's owned lands
			player->lands.push_back(attackedTerritory);
			remove(attackedTerritory->getOwner()->lands.begin(), attackedTerritory->getOwner()->lands.end(),
					attackedTerritory);
			//resize the array
			attackedTerritory->getOwner()->lands.resize(attackedTerritory->getOwner()->lands.size() - 1);
			attackedTerritory->setOwner(player);
			//Move army from attacked territory to new defeated territory
			while (1) {
				std::cout << "How many troops would you like to move from "
						<< player->lands[countryInput - 1]->getName()
						<< " to " << player->lands.back()->getName() << std::endl;

				int troops;
				cin >> troops;

				if (troops < 0) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a positive number" << std::endl;
					continue;
				}

				if (troops >
				player->lands[countryInput - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a number less than " << player->lands[countryInput - 1]->getTroops()
                            				  << std::endl;
					continue;
				} else {
					//increment troops on territory chosen
					player->lands.back()->incTroops(troops);
					player->lands[countryInput - 1]->decTroops(troops);
					std::cout << "Fortified " << player->lands.back()->getName() << ", new total is "
							<< player->lands.back()->getTroops() << std::endl;
					break;
				}
			}
			continue;
		}
		cout << "How many dices would the attacker want to roll? (1," << maxAttackerDice << ")" << endl;
		int attackerDiceNumber;
		cin >> attackerDiceNumber;
		if (attackerDiceNumber > maxAttackerDice || attackerDiceNumber < 1)
			continue;
		cout << "How many dices would the defense want to roll? (1," << maxDefenseDice << ")" << endl;
		int defenseDiceNumber;
		cin >> defenseDiceNumber;
		if (defenseDiceNumber > maxDefenseDice || defenseDiceNumber < 1)
			continue;
		int attackerDiceResults[3];
		int defenseDiceResults[3];
		//Roll dices and compare the highest result to see who wins
		cout << "\t---Rolling dices---" << endl;
		while (true) {

			// Store previous amount of armies for the attacker and defender
			int prevAmountD = attackedTerritory->getTroops();
			int prevAmountA = player->lands[countryInput - 1]->getTroops();

			// Check if enough army to proceed to additional attack
			if (player->lands[countryInput - 1]->getTroops() < 2) {
				cout << "Not enough army on territory" << endl;
				break;
			}
			player->getDice()->roll(attackerDiceNumber, attackerDiceResults);
			cout << attackedTerritory->getOwner()->getName();
			attackedTerritory->getOwner()->getDice()->roll(defenseDiceNumber, defenseDiceResults);
			cout << " Attacker rolls a " << attackerDiceResults[0] << " and defense rolls a " << defenseDiceResults[0]
																													<< endl;
			if (attackerDiceResults[0] > defenseDiceResults[0]) {
				cout << "Attacker wins duel" << endl;
				prevAmountD = attackedTerritory->getTroops();
				attackedTerritory->decTroops(1);
			} else {
				cout << "Defense wins duel" << endl;
				prevAmountA = player->lands[countryInput - 1]->getTroops();
				player->lands[countryInput - 1]->decTroops(1);
			}
			cout << "\n\t---Updated armies---\n" << player->lands[countryInput - 1]->getName() << " (attacker) \n\tArmies: "
					<< prevAmountA << " --> " << player->lands[countryInput - 1]->getTroops() << std::endl;
			cout << attackedTerritory->getName() << " (defender) \n\tArmies: "
					<< prevAmountD << " --> "<< attackedTerritory->getTroops() << std::endl;
			if (player->lands[countryInput - 1]->getTroops() < 2) {
				cout << "Attacker lost battle and can't attack anymore" << endl;
				continue;
			}
			// If defense loses all defense, attacker gets territory
			if (attackedTerritory->getTroops() == 0) {
				cout << "Attacker wins battle and wins territory" << endl;
				//Remove territory lost from defense player's owned lands
				player->lands.push_back(attackedTerritory);
				remove(attackedTerritory->getOwner()->lands.begin(), attackedTerritory->getOwner()->lands.end(),
						attackedTerritory);
				//resize the array
				attackedTerritory->getOwner()->lands.resize(attackedTerritory->getOwner()->lands.size() - 1);
				attackedTerritory->setOwner(player);
				//Move army from attacked territory to new defeated territory
				while (1) {
					std::cout << "How many troops would you like to move from "
							<< player->lands[countryInput - 1]->getName()
							<< " to " << player->lands.back()->getName() << std::endl;

					int troops;
					cin >> troops;

					if (troops < 0) { //must leave at least 1 troop on the territory
						std::cout << "Please pick a positive number" << std::endl;
						continue;
					}

					if (troops > player->lands[countryInput - 1]->getTroops() -
							1) { //must leave at least 1 troop on the territory
						std::cout << "Please pick a number less than " << player->lands[countryInput - 1]->getTroops()
                                				  << std::endl;
						continue;
					} else {
						//increment troops on territory chosen
						player->lands.back()->incTroops(troops);
						player->lands[countryInput - 1]->decTroops(troops);
						std::cout << "Fortified " << player->lands.back()->getName() << ", new total is "
								<< player->lands.back()->getTroops() << std::endl;
						break;
					}
				}
				break;

			}
			// Ask to repeat
			cout << "\nWould you like to attack this country again?(y/n)" << endl;
			char repeatAttackInput;
			cin >> repeatAttackInput;
			if (repeatAttackInput == 'n') {
				cout << "!! Player Done Attacking !!";
				return;
			} else if (repeatAttackInput != 'y') {
				std::cout << "Please enter y or n to proceed" << std::endl;
				continue;
			}

		}
	}

}

void AggressiveComputer::reinforce(Map* map, Player* player){

	std::cout << "Aggressive Computer Reinforcing" << std::endl;
	player->recuperateArmies(map);

	//find land with most armies on
	int maxIndex = 0;
	for(std::vector<Territory>::size_type i=1; i<player->lands.size(); i++){
		if(player->lands[i]->getTroops() > player->lands[maxIndex]->getTroops()){
			maxIndex = i;
		}
	}
	//list all the countries
	int count = 0;
	for(std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		count++;
		std::cout << count << ": " <<  player->lands[i]->getName() << "  Armies: " << player->lands[i]->getTroops() << std::endl;
	}
	player->lands[maxIndex]->incTroops(player->getArmies());
	std::cout << "Player has " << player->getArmies() << " armies and Aggressive Computer decided to reinforce " << player->lands[maxIndex]->getName() << std::endl;
	std::cout << "New total on " << player->lands[maxIndex]->getName() << " is " << player->lands[maxIndex]->getTroops() << std::endl;
	player->setArmies(0);
}

void AggressiveComputer::attack(Map *map, Player *player) {


	// Territory attacking from set to default first
	Territory *attackingFromTerritory = player->lands[0];
	// Assigning territory to attack from to the strongest territory (most troops)
	for (int i = 0; i < player->lands.size(); i++) {
		if (player->lands[i]->getTroops() > attackingFromTerritory->getTroops())
			attackingFromTerritory = player->lands[i];
	}
	while(true) {
		std::cout << "Attacking aggressively" << std::endl;
		if (player->lands.size() < 1) {
			cout << "Player does not have a territory";
			return;
		}
		// Minimum of 2 armies to attack from is required
		if (attackingFromTerritory->getTroops() < 2) {
			cout << "Not enough army on strongest territory" << endl;
			return;
		}
		cout << "Attacking from " << attackingFromTerritory->getName() << " with troops amount "
				<< attackingFromTerritory->getTroops() << endl;
		// Set default attacked territory
		Territory *attackedTerritory = attackingFromTerritory->adjacents[0];
		// Taking an adjacent country to attack which isn't the players'
		bool foundAttackedTerritory = false;
		for (int i = 0; i < attackingFromTerritory->adjacents.size(); i++) {
			if (attackingFromTerritory->adjacents[i]->getOwner()->getName() != player->getName()) {
				foundAttackedTerritory = true;
				attackedTerritory = attackingFromTerritory->adjacents[i];
				break;
			}
		}
		if (!foundAttackedTerritory) {
			cout << "No adjacent country to attack" << endl;
			return;
		}
		cout << "Attacking " << attackedTerritory->getName() << " with troops amount " << attackedTerritory->getTroops()
            				 << endl;

		// Determine how many dices user wants to roll after determining the max amount
		int maxAttackerDice = maxDiceToRoll(true, attackingFromTerritory);
		int maxDefenseDice = maxDiceToRoll(false, attackedTerritory);
		// If attacked territory is unoccupied, take it
		if (maxDefenseDice == 0) {
			cout << "Attacker wins battle and wins territory" << endl;
			//Remove territory lost from defense player's owned lands
			player->lands.push_back(attackedTerritory);
			remove(attackedTerritory->getOwner()->lands.begin(), attackedTerritory->getOwner()->lands.end(),
					attackedTerritory);
			//resize the array
			attackedTerritory->getOwner()->lands.resize(attackedTerritory->getOwner()->lands.size() - 1);
			attackedTerritory->setOwner(player);
			//Move 1 army from attacked territory to new defeated territory
			attackedTerritory->setTroops(1);
			attackingFromTerritory->decTroops(1);
			std::cout << "Fortified " << player->lands.back()->getName() << ", new total is "
					<< player->lands.back()->getTroops() << std::endl;
		}
		int attackerDiceResults[3];
		int defenseDiceResults[3];
		//Roll dices and compare the highest result to see who wins
		cout << "Rolling dices" << endl;
		while (true) {
			// Check if enough army to proceed to additional attack
			if (attackingFromTerritory->getTroops() < 2) {
				cout << "Not enough army on territory" << endl;
				break;
			}
			player->getDice()->roll(maxAttackerDice, attackerDiceResults);
			attackedTerritory->getOwner()->getDice()->roll(maxDefenseDice, defenseDiceResults);
			cout << "Attacker score is " << attackerDiceResults[0] << " and defense score is " << defenseDiceResults[0]
																													 << endl;
			if (attackerDiceResults[0] > defenseDiceResults[0]) {
				cout << "Attacker wins duel" << endl;
				attackedTerritory->decTroops(1);
			} else {
				cout << "Defense wins duel" << endl;
				attackingFromTerritory->decTroops(1);
			}
			cout << "Attacker country stats: " << attackingFromTerritory->getName() << "     Armies: "
					<< attackingFromTerritory->getTroops() << std::endl;
			cout << "Defense country stats: " << attackedTerritory->getName() << "     Armies: "
					<< attackedTerritory->getTroops() << std::endl;
			if (attackingFromTerritory->getTroops() < 2) {
				cout << "Attacker lost battle and can't attack anymore" << endl;
				return;
			}
			// If defense loses all defense, attacker gets territory
			if (attackedTerritory->getTroops() == 0) {
				cout << "Attacker wins battle and wins territory" << endl;
				//Remove territory lost from defense player's owned lands
				player->lands.push_back(attackedTerritory);
				remove(attackedTerritory->getOwner()->lands.begin(), attackedTerritory->getOwner()->lands.end(),
						attackedTerritory);
				//resize the array
				attackedTerritory->getOwner()->lands.resize(attackedTerritory->getOwner()->lands.size() - 1);
				attackedTerritory->setOwner(player);
				//Move 1 army from attacked territory to new defeated territory
				attackedTerritory->setTroops(1);
				attackingFromTerritory->decTroops(1);
				std::cout << "Fortified " << player->lands.back()->getName() << ", new total is "
						<< player->lands.back()->getTroops() << std::endl;
				break;

			}
		}
	}
}

void AggressiveComputer::fortify(Player* player){


	std::cout << "Aggressive Computer fortifying" << std::endl;
	int count = 1;
	for (std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		std::cout << count << ": " << player->lands[i]->getName() << "  Armies: " <<
				player->lands[i]->getTroops() << std::endl;
		player->printAdjacentCountries(player->lands[i]->adjacents);
		count++;
	}

	int mostTroops = 0;
	int country1 = -1;
	int country2 = -1;
	for (std::vector<Territory>::size_type i = 0; i < player->lands.size(); i++) {
		for (std::vector<Territory>::size_type j = 0; j < player->lands[i]->adjacents.size(); j++) {
			//check if bigger than mostTroops
			if (player->lands[i]->getTroops() + (player->lands[i]->adjacents[j]->getTroops() - 1) > mostTroops &&
					player->lands[i]->adjacents[j]->getOwner() != NULL) {
				//check if player owns adjacent country and also if both countries have more than 1 troop
				if (player->lands[i]->adjacents[j]->getOwner()->getName() == player->getName() &&
						player->lands[i]->getTroops() > 1 && player->lands[i]->adjacents[j]->getTroops() > 1) {
					country1 = i;
					country2 = j;
					mostTroops = player->lands[i]->getTroops() + (player->lands[i]->adjacents[j]->getTroops() - 1);
				}
			}
		}
	}

	//check if indexes were set
	if (country1 == -1 || country2 == -1) {
		std::cout << "Aggressive did not fortify" << std::endl;
		return;
	}

	std::cout << "Aggressive computer decided to move " << player->lands[country1]->adjacents[country2]->getTroops() - 1
			<< " armies from " <<
			player->lands[country1]->adjacents[country2]->getName() << " to " << player->lands[country1]->getName()
			<< std::endl;

	//increment troops on territory chosen
	player->lands[country1]->incTroops(player->lands[country1]->adjacents[country2]->getTroops() - 1);
	//set the adjacent countries troops back down to 1
	player->lands[country1]->adjacents[country2]->setTroops(1);

	std::cout << "Aggressive Computer Fortified " << player->lands[country1]->getName() << ", new total is "
			<< player->lands[country1]->getTroops() << std::endl;
}


void BenevolentComputer::reinforce(Map* map, Player* player){

	std::cout << "Benevolent Computer Reinforcing" << std::endl;
	player->recuperateArmies(map);

	//find land with minimum armies
	int minIndex = 0;
	for (std::vector<Territory>::size_type i = 1; i < player->lands.size(); i++) {
		if (player->lands[i]->getTroops() < player->lands[minIndex]->getTroops()) {
			minIndex = i;
		}
	}

	//list all the countries
	int count = 0;
	for (std::vector<Territory>::size_type i = 0; i != player->lands.size(); i++) {
		count++;
		std::cout << count << ": " << player->lands[i]->getName() << "  Armies: " << player->lands[i]->getTroops()
	                				  << std::endl;
	}
	player->lands[minIndex]->incTroops(player->getArmies());
	std::cout << "Player has " << player->getArmies() << " armies and Benevolent Computer decided to reinforce "
			<< player->lands[minIndex]->getName() << std::endl;
	std::cout << "New total on " << player->lands[minIndex]->getName() << " is " << player->lands[minIndex]->getTroops()
	            				  << std::endl;
	player->setArmies(0);
}

void BenevolentComputer::attack(Map *map, Player *player) {

	cout<<"!! Benevolent computer will not attack !!"<<endl;
}

struct comparisonClass {
	bool operator()(Territory *&i, Territory *&j) { return (i->getTroops() < j->getTroops()); }
} comparisonFunction;

void BenevolentComputer::fortify(Player* player){

	//Benevolent computer will find the country with min armies and check if it has adjacent countries that can move armies
	//if there are no potential adjacent countries, then it moves to second smallest country
	//it then moves half the armies of the biggest adjacent country to the smallest country
	std::cout << "Benevolent Computer fortifying" << std::endl;
	int count = 1;
	for (std::vector<Territory>::size_type i = 0; i < player->lands.size(); i++) {
		std::cout << count << ": " << player->lands[i]->getName() << "  Armies: " <<
				player->lands[i]->getTroops() << std::endl;
		player->printAdjacentCountries(player->lands[i]->adjacents);
		count++;
	}
	std::vector<Territory*> territories;
	territories = player->lands;
	//sort the players lands from min armies to max in new vector territories
	std::sort(territories.begin(), territories.end(), comparisonFunction);

	int max = 0;
	int maxIndex = -1;
	int minIndex = -1;
	for (std::vector<Territory>::size_type i = 0; i < territories.size(); i++) {
		max = 0;
		for (std::vector<Territory>::size_type j = 0; j < territories[i]->adjacents.size(); j++) {
			if (territories[i]->adjacents[j]->getTroops() > max && territories[i]->adjacents[j]->getOwner() != NULL) {
				if (territories[i]->adjacents[j]->getOwner()->getName() == player->getName() &&
						territories[i]->adjacents[j]->getTroops() > 1) {
					maxIndex = j;
					max = territories[i]->adjacents[j]->getTroops();
				}
			}
		}
		//break out of the loop if the max is found and its bigger than than 1 and set minIndex
		if (max > 1) {
			minIndex = i;
			break;
		}
	}

	if (maxIndex == -1 || minIndex == -1) {
		std::cout << "Benevolent Computer did not fortify" << std::endl;
		return;
	}

	std::cout << "Benevolent computer decided to move half the troops from "
			<< territories[minIndex]->adjacents[maxIndex]->getName() <<
			" to " << territories[minIndex]->getName() << std::endl;

	int transferTroops =
			(territories[minIndex]->getTroops() + territories[minIndex]->adjacents[maxIndex]->getTroops()) / 2;

	//increment troops on territory chosen
	territories[minIndex]->incTroops(transferTroops);
	//decrement troops on max country
	territories[minIndex]->adjacents[maxIndex]->setTroops(
			territories[minIndex]->adjacents[maxIndex]->getTroops() - transferTroops);

	std::cout << "Benevolent Computer Fortified " << territories[minIndex]->getName() << ", new total is "
			<< territories[minIndex]->getTroops() << std::endl;

}

int maxDiceToRoll(bool isAttacker, Territory *territory) {
	if (isAttacker) {
		if (territory->getTroops() > 3)
			return 3;
		return territory->getTroops() - 1;
	} else {
		if (territory->getTroops() > 2)
			return 2;
		return territory->getTroops();
	}
}

PlayerStrategies::~PlayerStrategies(){
}

