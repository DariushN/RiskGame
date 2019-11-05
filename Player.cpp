#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <limits>

//default constructor
Player::Player() {
	name = new std::string("");
	id = new int(1);
	dice = new Dice();
	armies = new int(0);
	hand = new Hand();
}

Player::Player(const Player &orig) {
    name = new string(*orig.name);
    id = new int(*orig.id);
    dice = new Dice(*orig.dice);
    armies = new int(*orig.armies);
    hand = new Hand(*orig.hand);
}

Player& Player::operator=(const Player &orig) {
    name = orig.name;
    id = orig.id;
    dice = orig.dice;
    armies = orig.armies;
    hand = orig.hand;
    return *this;
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

Hand* Player::getHand(){
	return hand;
}

Dice* Player::getDice(){
	return dice;
}

// Attack method
void Player::attack(Map* map) {
	std::cout << "Attacking" << std::endl;
	// Loop the operation to enable repeat
	while (true){
	    // Ask if wants to attack, if yes proceed, otherwise break
	    cout<< "Would you like to attack? (y/n)"<<endl;
        char input;
        cin >> input;
        if(input == 'n'){
            return;
        } else if(input != 'y') {
            std::cout << "please enter y or n to proceed" << std::endl;
            continue;
        }
        // Choose which country to attack from, from a list
        cout<<"Choose which country to attack from"<<endl;
        for(int i = 1;i<=lands.size();i++){
            cout<<i<<": "<<lands[i-1]->getName()<< "     Armies: " << this->lands[i-1]->getTroops() << std::endl;
        }
        cout<<"Which country would you like to attack from"<<endl;
        int countryInput;
        cin>>countryInput;
        // If invalid index or not enough army, we repeat the attack operation
        if (countryInput>lands.size()||countryInput<1){
            cout<<"Invalid index"<<endl;
            continue;
        }
        if(lands[countryInput-1]->getTroops()<2){
            cout<<"Not enough army on territory"<<endl;
            continue;
        }
        for(int i = 0;i<lands[countryInput-1]->adjacents.size();i++){
            cout<<i+1<<": "<<lands[countryInput-1]->adjacents[i]->getName()<< std::endl;
        }
        // Choose which adjacent country to attack
        cout<<"Which country would you like to attack"<<endl;
        int countryAttackInput;
        cin>>countryAttackInput;
        if (countryAttackInput>lands[countryInput-1]->adjacents.size()||countryAttackInput<1){
            cout<<"Invalid index"<<endl;
            continue;
        }
        Territory* attackedTerritory;
        // Retrieve attacked territory
        for(auto&& x: map->Territories){
            if (x->getName() == lands[countryInput-1]->adjacents[countryAttackInput-1]->getName()){
                attackedTerritory = x;
                break;
            }
        }
        // If we attack our own country, we restart the opertation
        if(attackedTerritory->getOwner()->getName()==getName()){
            cout<<"Cannot attack your own territory"<<endl;
            continue;
        }
        // Determine how many dices user wants to roll after determining the max amount
        int maxAttackerDice = maxDiceToRoll(true, lands[countryInput-1]);
        int maxDefenseDice = maxDiceToRoll(false, attackedTerritory);
        // If attacked territory is unoccupied, take it
        if (maxDefenseDice==0){
            cout<<"Attacker wins battle and wins territory"<<endl;
            //Remove territory lost fromd defense player's owned lands
            lands.push_back(attackedTerritory);
            remove(attackedTerritory->getOwner()->lands.begin(),attackedTerritory->getOwner()->lands.end(),attackedTerritory);
            attackedTerritory->setOwner(this);
            //Move army from attacked territory to new defeated territory
            while(1) {
                std::cout << "How many troops would you like to move from " << this->lands[countryInput - 1]->getName()
                          << " to " << this->lands.back()->getName() << std::endl;

                int troops;
                cin >> troops;

                if(troops <0) { //must leave at least 1 troop on the territory
                    std::cout << "Please pick a positive number"<<std::endl;
                    continue;
                }

                if(troops > this->lands[countryInput - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
                    std::cout << "Please pick a number less than "<< this->lands[countryInput - 1]->getTroops() << std::endl;
                    continue;
                }else {
                    //increment troops on territory chosen
                    this->lands.back()->incTroops(troops);
                    lands[countryInput-1]->decTroops(troops);
                    std::cout << "Fortified " << this->lands.back()->getName() << ", new total is " << this->lands.back()->getTroops() << std::endl;
                    break;
                }
            }
            continue;
        }
        cout<<"How many dices would the attacker want to roll? (1,"<<maxAttackerDice<<")"<<endl;
        int attackerDiceNumber;
        cin>>attackerDiceNumber;
        if(attackerDiceNumber>maxAttackerDice||attackerDiceNumber<1)
            continue;
        cout<<"How many dices would the defense want to roll? (1,"<<maxDefenseDice<<")"<<endl;
        int defenseDiceNumber;
        cin>>defenseDiceNumber;
        if(defenseDiceNumber>maxDefenseDice||defenseDiceNumber<1)
            continue;
        int attackerDiceResults[3];
        int defenseDiceResults[3];
        //Roll dices and compare the highest result to see who wins
        cout<<"Rolling dices"<<endl;
        while(true){
            // Check if enough army to proceed to additional attack
            if(lands[countryInput-1]->getTroops()<2){
                cout<<"Not enough army on territory"<<endl;
                break;
            }
            dice->roll(attackerDiceNumber, attackerDiceResults);
            cout<<attackedTerritory->getOwner()->getName();
            attackedTerritory->getOwner()->dice->roll(defenseDiceNumber,defenseDiceResults);
            cout<<"Attacker score is "<<attackerDiceResults[0]<<" and defense score is "<<defenseDiceResults[0]<<endl;
            if(attackerDiceResults[0]>defenseDiceResults[0]){
                cout<<"Attacker wins duel"<<endl;
                attackedTerritory->decTroops(1);
            }
            else{
                cout<<"Defense wins duel"<<endl;
                lands[countryInput-1]->decTroops(1);
            }
            cout<<"Attacker country stats: "<<lands[countryInput-1]->getName()<< "     Armies: " << this->lands[countryInput-1]->getTroops() << std::endl;
            cout<<"Defense country stats: "<<attackedTerritory->getName()<< "     Armies: " << attackedTerritory->getTroops() << std::endl;
            if(lands[countryInput-1]->getTroops()<2){
                cout<<"Attacker lost battle and can't attack anymore"<<endl;
                continue;
            }
            // If defense loses all defense, attacker gets territory
            if(attackedTerritory->getTroops()==0){
                cout<<"Attacker wins battle and wins territory"<<endl;
                //Remove territory lost fromd defense player's owned lands
                lands.push_back(attackedTerritory);
                remove(attackedTerritory->getOwner()->lands.begin(),attackedTerritory->getOwner()->lands.end(),attackedTerritory);
                attackedTerritory->setOwner(this);
                //Move army from attacked territory to new defeated territory
                while(1) {
                    std::cout << "How many troops would you like to move from " << this->lands[countryInput - 1]->getName()
                              << " to " << this->lands.back()->getName() << std::endl;

                    int troops;
                    cin >> troops;

                    if(troops <0) { //must leave at least 1 troop on the territory
                        std::cout << "Please pick a positive number"<<std::endl;
                        continue;
                    }

                    if(troops > this->lands[countryInput - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
                        std::cout << "Please pick a number less than "<< this->lands[countryInput - 1]->getTroops() << std::endl;
                        continue;
                    }else {
                        //increment troops on territory chosen
                        this->lands.back()->incTroops(troops);
                        lands[countryInput-1]->decTroops(troops);
                        std::cout << "Fortified " << this->lands.back()->getName() << ", new total is " << this->lands.back()->getTroops() << std::endl;
                        break;
                    }
                }
                break;

            }
            // Ask to repeat
            cout<<"Would you like to attack this country again?(y/n)"<<endl;
            char repeatAttackInput;
            cin >> repeatAttackInput;
            if(repeatAttackInput == 'n'){
                return;
            } else if(repeatAttackInput != 'y') {
                std::cout << "please enter y or n to proceed" << std::endl;
                continue;
            }
        }
	}
}

int Player::maxDiceToRoll(bool isAttacker, Territory *territory) {
    if (isAttacker){
        if(territory->getTroops()>3)
            return 3;
        return territory->getTroops()-1;
    }
    else{
        if(territory->getTroops()>2)
            return 2;
        return territory->getTroops();
    }
}

void Player::fortify() {
	std::cout << "fortifying" << std::endl;
	bool deciding = true;
	bool fortifying = true;

	while(deciding) {
		int count = 1;
		//print out all players territories and number of armies on each
		for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
			std::cout << count << ": " <<  this->lands[i]->getName() << "     Armies: " << this->lands[i]->getTroops() << std::endl;
			count++;
		}

		std::cout << "would you like to fortify a position? y or n" << std::endl;
		char input;
		cin >> input;
		if(input == 'n'){
			break;
		} else if(input != 'y') {
			std::cout << "please enter y or n to proceed" << std::endl;
			continue;
		}
		// player decides to fortify

		//Print out all the territories and and their adjacent territories
		count = 1;
			for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
				std::cout << count << ": " <<  this->lands[i]->getName() << "  Armies: " <<
						this->lands[i]->getTroops() << std::endl;
				this->printAdjacentCountries(this->lands[i]->adjacents);
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
			} else if(this->lands[country1 - 1]->getTroops() <= 1) {
				std::cout << "Starting country must have more than 1 army, please pick another country" << std::endl;
				continue;
			} else if(!this->lands[country1 - 1]->isAdj(this->lands[country2 - 1])) {
				std::cout << "please pick countries that are adjacent" << std::endl;
				continue;
			}

			//loop to get number of troops that user wants to move
			while(1) {
				std::cout << "how many troops would you like to move from " << this->lands[country1 - 1]->getName()
						<< " to " << this->lands[country2 - 1]->getName() << std::endl;

				int troops;
				cin >> troops;
				while(std::cin.fail()) {
				    std::cin.clear();
				    std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				    std::cout << "Please Enter a number: ";
				    std::cin >> troops;
				}

				if(troops > this->lands[country1 - 1]->getTroops() - 1) { //must leave at least 1 troop on the territory
					std::cout << "Please pick a number less than "<< this->lands[country1 - 1]->getTroops() << std::endl;
					continue;
				} else if (troops < 1){
					std::cout << "Please enter a valid number" << std::endl;
				}else {
					//increment troops on territory chosen
					this->lands[country2 - 1]->incTroops(troops);
					//decrement troops on country where armies are traded
					this->lands[country1 - 1]->decTroops(troops);

					std::cout << "Fortified " << this->lands[country2 - 1]->getName() << ", new total is " << this->lands[country2 - 1]->getTroops() << std::endl;
					break;
				}
			}
			break;
		}
		break;
	}

	std::cout << "Fortification done" << std::endl;
}

void Player::printAdjacentCountries(std::vector<Territory*> territories) {
	//prints adjacent territories for each territory in vector
	std::cout << "Adjacent Countries: ";
	for(std::vector<Territory>::size_type i = 0; i != territories.size(); i++) {
		//only display countries owned by player
		if(territories[i]->getOwner() != NULL){
			if(territories[i]->getOwner()->getName() == *this->name){
				std::cout << territories[i]->getName() << " ";
			}
		}
	}
	std::cout << "\n\n";
}

void Player::reinforce(Map* map) {
	std::cout << "Reinforcing" << std::endl;

	//check if user owns a continent
	this->hasContinent(map);
	int controlledContinents = 0;
	if(this->continents.size() > 0){
		for(std::vector<Continent>::size_type i = 0; i < this->continents.size(); i++) {
			controlledContinents += this->continents[i]->getValue();
		}
	}

	std::cout << "Number of armies from controlled continents: " << controlledContinents << std::endl;

	// get number of armies from countries
	int controlledCountries;
	if(this->lands.size() < 9) {
		controlledCountries = 3;
	} else {
		controlledCountries = floor(this->lands.size() / 3);
	}

	std::cout << "Number of armies from Controlled Countries: "<< controlledCountries << std::endl;

	int exchangeValue = this->hand->exchange(this->lands);
	std::cout << "Number of armies from Exchanged Cards: " << exchangeValue << std::endl;

	int totalArmies = controlledCountries + controlledContinents + exchangeValue; //add armies from exchange()
	this->setArmies(totalArmies);
	this->placeArmies(totalArmies);

	std::cout << "Done Reinforcing" << std::endl;
}

void Player::placeArmies(int armies) {
	bool decidingCountry = true;
	bool placingArmy = true;
	if(this->lands.size() > 0) {
		while(decidingCountry){
			//initial
			if (this->getArmies() < 1) {
				break;
			}
			std::cout << "Listing your countries, please select a country to place troops on, you have " << this->getArmies() << " troops to place." << std::endl;
			int count = 0;
			for(std::vector<Territory>::size_type i = 0; i != this->lands.size(); i++) {
				count++;
				std::cout << count << ": " <<  this->lands[i]->getName() << "  Armies: " << this->lands[i]->getTroops() << std::endl;
			}

			std::cout << "Enter the number of the country you wish to select" << std::endl;
			int number;

			cin >> number;
			while(std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
				std::cout << "Please Enter a number: ";
				std::cin >> number;
			}

			if (number > count || number < 1) {
				std::cout << "Please choose a valid country number from list" << std::endl;
				number = -1;
				continue;
			}

			while(placingArmy){
				std::cout << "Initial Armies on "+ this->lands[number - 1]->getName() + " are " << this->lands[number - 1]->getTroops() << std::endl;
				std::cout << "Enter amount of armies you would like to place, max amount you can place is " << this->getArmies() << std::endl; //maybe allow user to back out if they change their mind
				int armies;
				std::cin >> armies;
				while(std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
					std::cout << "Please Enter a number: ";
					std::cin >> armies;
				}

				if (armies > this->getArmies() || armies < 1) {
					std::cout << "You cannot place this many armies" << std::endl;
					continue;
				}
				//incremment troops and setArmies for player
				this->lands[number - 1]->incTroops(armies);
				std::cout << "new total on " << this->lands[number - 1]->getName() << " is " << this->lands[number - 1]->getTroops() << std::endl;
				int totalArmies = this->getArmies();
				this->setArmies(totalArmies - armies);
				break;
			}
		}
	}
}

void Player::hasContinent(Map* map){
	std::vector<Territory>::size_type counter = 0;
	vector<Continent*> continents;
	continents = map->Continents;

	for(std::vector<Continent>::size_type i = 0; i< continents.size(); i++)
	{
		for(std::vector<Territory>::size_type k=0; k<this->lands.size(); k++)
		{
			if(continents[i]->getName() == this->lands[k]->location->getName())
			{
				counter += 1;
				if(counter == continents[i]->Territories.size())
				{
					//check if continent is already owned by player
					if (std::find(this->continents.begin(), this->continents.end(), continents[i]) != this->continents.end())
					{
						return;
					}
					this->continents.push_back(continents[i]);
				}
			}
		}
		counter = 0;
	}
}

Player::~Player() {
	delete name;
	delete id;
	delete dice;
	delete armies;
	delete hand;
}

