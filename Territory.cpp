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
    ID = new int(1);
    name = new string("");
    troops = new int(1);
}

Territory::Territory(const Territory& orig) {
    neighbors = orig.neighbors;
    ID = orig.ID;
    name = orig.name;
    troops = orig.troops;
    location = orig.location;
    adjacents = orig.adjacents;
    owner = orig.owner;
}

Territory::~Territory() {
    delete ID;
    //std::cout<<"deleting ID of territory";
    delete troops;
    delete name;
    for(auto&& x:neighbors) delete x;
}

std::string Territory::getName(){
    return *name;
}

void Territory::setName(std::string a){
    *name = a;
}

int Territory::getTroops(){
    return *troops;
}

void Territory::setTroops(int a){
    *troops = a;
}

void Territory::incTroops(int a){
    *troops += a;
}

void Territory::decTroops(int a){
    *troops -= a;
}

void Territory::addNeighbor(int a){
    int *temp = new int(1);
    *temp = a;
    neighbors.push_back(temp);
}


void Territory::addAdj(Territory* a){
    adjacents.push_back(a);
}

bool Territory::isAdj(Territory* a){
    for(auto&& x: adjacents) if(x==a) return true;
    return false;
}

std::string Territory::toString(){
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

void Territory::setOwner(Player* a){
    owner = a;
}

int Territory::getID(){
    return *ID;
}

void Territory::setID(int a){
    *ID = a;
}

void Territory::setLocation(Continent* a){
    location = a;
}