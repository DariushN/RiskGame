/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Territory.cpp
 * Author: t_filler
 * 
 * Created on September 4, 2019, 8:37 PM
 */

#include "Territory.h"
#include "Player.h"
#include "Map.h"
#include "Continent.h"
#include <iostream>


Territory::Territory() {
    //Allocate memory to pointers.
    ID = new int(1);
    name = new string("");
    troops = new int(1);
}

Territory::Territory(const Territory& orig) {//Copy constructor
    neighbors = orig.neighbors;
    ID = orig.ID;
    name = orig.name;
    troops = orig.troops;
    location = orig.location;
    adjacents = orig.adjacents;
    owner = orig.owner;
}

Territory::~Territory() {
    //Free allocated memory
    delete ID;
    delete troops;
    delete name;
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