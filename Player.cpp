#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <conio.h>
class Dice;
class Map;

Player::Player() {
	name = new std::string("");
	id = new int(1);
	dice = new Dice();
	armies = new int(0);
}

std::string Player::getName(){
    return *name;
}

void Player::setName(std::string Name) {
	*name = Name;
}

void Player::setId(int iD) {
	*id = iD;
}

int Player::getArmies() {
	return *armies;
}

void Player::setArmies(int Armies){
	*armies = Armies;
}

int Player::getId(){
    return *id;
}

void Player::attack() {
	std::cout << "Attacking" << std::endl;
}

void Player::reinforce(Map* map) {
	std::cout << "Reinforcing" << std::endl;

	//check if user owns a continent and update his continent vector accordingly
	//this->hasContinent(map); //broken right now, needs debugging
	int controlledContinents;
	if(this->continents.size() < 1){
		controlledContinents = 0;
	} else {
		for(int i=0; i<this->continents.size(); i++) {
			controlledContinents += this->continents[i]->getValue();
		}
	}

	std::cout << "Number of armies from controlled continents: " << controlledContinents << std::endl;


	int controlledCountries;
	if(this->lands.size() < 9) {
		controlledCountries = 3;
	} else {
		controlledCountries = floor(this->lands.size() / 3);
	}

	std::cout << "Number of armies from Controlled Countries: "<< controlledCountries << std::endl;

	//this->hand->exchange();

	int totalArmies = controlledCountries + controlledContinents; //add armies from exchange()
	this->setArmies(totalArmies);
	this->placeArmies(totalArmies);

	std::cout << "Done Reinforcing" << std::endl;
}

void Player::hasContinent(Map* map)
{
	int counter = 0;
	std::vector<Continent*> continents = map->Continents;

	for(int i=0; i< continents.size(); i++)
	{
		for( int j=0; j<this->lands.size(); j++)
		{
			cout << continents[i]->getName() << std::endl;
			cout << "land continent" << this->lands[j]->getLocation().getName() << std::endl;
			if(continents[i]->getName().compare(this->lands[j]->getLocation().getName()))
			{
				counter++;
				if(counter == continents[i]->Territories.size())
				{
					this->continents.push_back(continents[i]);
				}
			}
		}
		counter = 0;
	}
}

void Player::placeArmies(int armies) {
	bool decidingCountry = true;
	bool placingArmy = true;
	if(this->lands.size() > 0) {
		while(decidingCountry){
			if (this->getArmies() < 1) {
				break;
			}
			std::cout << "Listing your countries, please select a country to place armies on" << std::endl;
			int count = 0;
			for(int i=0; i<this->lands.size(); i++) {
				count++;
				std::cout << count << ": " <<  this->lands[i]->getName() << "  Armies: " << this->lands[i]->getTroops() << std::endl;
			}

			std::cout << "Enter the number of the country you wish to select" << std::endl;
			int number;

			cin >> number;

			if (number > count) {
				std::cout << "Please choose a valid country number from list" << std::endl;
				number = -1;
				continue;
			}

			while(placingArmy){
				std::cout << "Initial Armies on "+ this->lands[number - 1]->getName() + " are " << this->lands[number - 1]->getTroops() << std::endl;
				std::cout << "Enter amount of armies you would like to place, max amount you can place is " << this->getArmies() << std::endl; //maybe allow user to back out if they change their mind
				int armies;
				std::cin >> armies;

				if (armies > this->getArmies()) {
					std::cout << "You cannot place this many armies" << std::endl;
					continue;
				}
				this->lands[number - 1]->incTroops(armies);
				std::cout << "new total on " << this->lands[number - 1]->getName() << " is " << this->lands[number - 1]->getTroops() << std::endl;
				int totalArmies = this->getArmies();
				this->setArmies(totalArmies - armies);
				break;
			}
		}
	}
}

Player::~Player() {
	delete name;
	delete id;
	delete dice;
	delete armies;
}

