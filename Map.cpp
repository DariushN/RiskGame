#include "Map.h"
#include <iostream>
#include <list>
#include "Player.h"
using std::endl;
using std::to_string;


Map::Map() {//Default contructor
    //Allocate memory:
    name = new string("");
    valid = new bool[1];
    valid[0] = true;//Default value is true
}

Map::Map(const Map& orig) {
    //Copy constructor
    name = new string(*orig.name);
    valid = new bool(*orig.valid);
    for(auto&& x:orig.Territories){
        Territories.push_back(new Territory(*x));
    }
}

Map& Map::operator=(const Map &orig) {
    name = orig.name;
    valid = orig.valid;
    Territories = orig.Territories;
    return *this;
}

Map::~Map() {//Destructor
    //Free memory:
    for(auto&& x:Territories) delete x;
    for(auto&& x:Continents) delete x;
    delete name;
    delete[] valid; 
}

void Map::setName(std::string a){//Sets name
    *name = a;
}

std::string Map::getName(){//returns name
    return *name;
}

Territory* Map::getTerritoryById(int a){//Returns pointer to territory based on PIN
    for(auto&& x:Territories){
        if((*x).getID() == a){
            return x;
        }
    }
    std::cerr<<"Error, cannot find territory with ID:\t"<<a<<endl;
    std::cerr<<"Waiting for user input, after which system will exit.\t";
    char b;
    std::cin>>b;
    exit(1);
}

bool Map::isValid(){//Returns valid flag
    for(auto&& x:Territories){//Verify that all territoris are in a continent
        bool isInAContinent = false;
        for(auto&& y:Continents){
            if(y->isContained(x)){
                isInAContinent = true;
                break;
            } 
        }
        if(!isInAContinent){
            valid[0]= false;
            return false;
        }
    }
    isConnected();//Check if map is connected.
    return valid[0];
}

bool Map::isConnected(){//Check if map is connected
    Territory* current;
    bool notProcessedYet;
    for(auto&& x:Territories){//for each territory, verify that it can traverse the map
        std::list<Territory*> canReach;
        std::list<Territory*> shouldReach;
        for(auto&& y:Territories){
            shouldReach.push_back(y);
        }
        for(auto&& y:x->adjacents){
            canReach.push_back(y);
        }
        shouldReach.remove(x);//Remove x from list of territories that x must reach.
        while(!(canReach.empty() || shouldReach.empty())){//Begin traversal
            current = canReach.back();
            canReach.pop_back();
            notProcessedYet = false;//Territory poped from reachable territories might have been analyzed before.
            for(auto&& z:shouldReach){//See if it hasn't been processed yet.
                if(z==current){
                    notProcessedYet = true;
                    shouldReach.remove(current);
                    break;
                }
            }
            if(notProcessedYet){//Add neighbors to list of unprocessed territories that can be reached.
                for(auto&& y:current->adjacents){
                    canReach.push_back(y);
                }
            }
        }
        if(!shouldReach.empty()){
            std::cerr<<"Map is not connected!\n";
            std::cerr<<"Territory: " << x->getName()<<"\ncannot be reach:\n";
            for(auto&& y:shouldReach){
                std::cerr<<"\t"<<y->getName()<<std::endl;
            }
            valid[0] = false;
            return false;
        }
    }
    for(auto&& x:Territories){//for each territory, verify that it can traverse the continent
        std::list<Territory*> canReach;
        std::list<Territory*> shouldReach;
        for(auto&& y:Territories){
            if(x->location->isContained(y)) shouldReach.push_back(y);
        }
        for(auto&& y:x->adjacents){
            if(x->location->isContained(y))canReach.push_back(y);
        }
        shouldReach.remove(x);//Remove x from list of territories that x must reach.
        while(!(canReach.empty() || shouldReach.empty())){//Begin traversal
            current = canReach.back();
            canReach.pop_back();
            notProcessedYet = false;//Territory poped from reachable territories might have been analyzed before.
            for(auto&& z:shouldReach){//See if it hasn't been processed yet.
                if(z==current){
                    notProcessedYet = true;
                    shouldReach.remove(current);
                    break;
                }
            }
            if(notProcessedYet){//Add neighbors to list of unprocessed territories that can be reached.
                for(auto&& y:current->adjacents){
                    if(x->location->isContained(y)) canReach.push_back(y);
                }
            }
        }
        if(!shouldReach.empty()){
            std::cerr<<"Continent is not connected!\n";
            std::cerr<<"Territory: " << x->getName()<<"\ncannot be reach:\n";
            for(auto&& y:shouldReach){
                std::cerr<<"\t"<<y->getName()<<std::endl;
            }
            valid[0] = false;
            return false;
        }
    }
    return true;
}

void Map::Invalidate(){
    valid[0] = false;
}

//Continent Stuff
Continent::Continent() {//Default constructor
    name = new string("");
    ID = new int(1);
    value = new int(1);
}

Continent::Continent(const Continent& orig) {//Copy Constructor
    //std::cout<< "Continent copy constructor called"<<endl;
    this->ID = new int(*orig.ID);
    this->name = new string(*orig.name);
    this->value = new int(*orig.value);
    for(auto&& x:orig.Territories){
        Territories.push_back(new Territory(*x));
    }
}

Continent& Continent::operator=(const Continent &orig) {
    ID = orig.ID;
    name = orig.name;
    value = orig.value;
    Territories = orig.Territories;
    return *this;
}

Continent::~Continent() {//Destructor
    delete name;
    delete ID;
    delete value;
}

void Continent::setName(string a){//Sets name
    *name = a;
}

int Continent::getID(){//Return name
    return *ID;
}

void Continent::setID(int a){//Sets PIN
    *ID = a;
}

void Continent::setValue(int a){//Sets Value
    *value = a;
}

int Continent::getValue(){//returns value
    return *value;
}

std::string Continent::getName(){//return name
    return *name;
}

bool Continent::isContained(Territory* a){//returns true if a is contained in this continent
    for(auto && x:Territories) if(x==a) return true;
    return false;
}

//Territory Stuff

Territory::Territory() {
    //Allocate memory to pointers.
    ID = new int(1);
    name = new string("");
    troops = new int(0);
    owner = NULL;
}

Territory::Territory(const Territory& orig) {//Copy constructor
    neighbors = orig.neighbors;
    for(auto&& x: orig.neighbors){
        neighbors.push_back(new int(*x));
    }
    ID = new int(*orig.ID);
    name = new string(*orig.name);
    troops = new int(*orig.troops);
    location = new Continent(*orig.location);
    for(auto&& x: orig.adjacents){
        adjacents.push_back(new Territory(*x));
    }
    owner = new Player(*orig.owner);
}

Territory& Territory::operator=(const Territory &orig) {
    ID = orig.ID;
    name = orig.name;
    troops = orig.troops;
    return *this;
}

Territory::~Territory() {
    //Free allocated memory
    delete ID;
    delete troops;
    delete name;
    delete owner;
    for(auto&& x:neighbors) delete x;
}

std::string Territory::getName(){//Return name  
    return *name;
}

void Territory::setName(std::string a){//Set the name
    *name = a;
}

int Territory::getTroops(){//Return # of troops
    return *troops;
}

void Territory::setTroops(int a){//Set # of troops
    *troops = a;
}

void Territory::incTroops(int a){//Increase # of troops, default by 1
    *troops += a;
}

void Territory::decTroops(int a){//Decrease # of , default by 1
    *troops -= a;
}

void Territory::addNeighbor(int a){//Adds neighbor's PIN
    int *temp = new int(1);
    *temp = a;
    neighbors.push_back(temp);
}


void Territory::addAdj(Territory* a){//Adds pointer to neighbor to adjacency list
    adjacents.push_back(a);
}

bool Territory::isAdj(Territory* a){//Checks if a points to a neighbor in the adjacency list
    for(auto&& x: adjacents) if(x==a) return true;
    return false;
}

Player* Territory::getOwner() const {
    return owner;
}

std::string Territory::toString(){//Returns relevant stats
    std::string temp = "";
    temp += "Name: "+*name+"\n";
    temp += "Owner: " + owner->getName()+"\n";
    temp += "Troops: ";
    temp += to_string((int) *troops);
    temp += "\n";
    temp += "Neighbors:\n";
    for(auto&& x:neighbors) temp += "\t" + to_string((int) *x)  +"\n";
    return temp;
}

void Territory::setOwner(Player* a){//Sets owner to player pointed to by a
    owner = a;
}

int Territory::getID(){//Returns PIN
    return *ID;
}

void Territory::setID(int a){//Sets PIN
    *ID = a;
}

void Territory::setLocation(Continent* a){//Sets location
    location = a;
}
