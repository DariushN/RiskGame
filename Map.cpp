#include "Map.h"
#include <iostream>
#include <list>
#include "Continent.h"
#include "Territory.h"

Map::Map() {//Default contructor
    //Allocate memory:
    name = new string("");
    valid = new bool[1];
    valid[0] = true;//Default value is true
}

Map::Map(const Map& orig) {
    //Copy constructor
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