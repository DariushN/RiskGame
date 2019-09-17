/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: t_filler
 * 
 * Created on September 4, 2019, 8:38 PM
 */

#include "Map.h"
#include <iostream>
Map::Map() {
    name = new string("");
}

Map::Map(const Map& orig) {
    std::cout<<"copy constructor called!\n";
    /*Continents = orig.Continents;
    Territories = orig.Territories;*/
}

Map::~Map() {
    for(auto&& x:Territories) delete x;
    for(auto&& x:Continents) delete x;
    delete name;
}

void Map::setName(std::string a){
    *name = a;
}

std::string Map::getName(){
    return *name;
}

Territory* Map::getTerritoryById(int a){
    for(auto&& x:Territories){
        if((*x).getID() == a){
            return x;
        }
    }
    std::cout<<"Error, cannot find territory with ID:\t"<<a<<endl;
    std::cout<<"Waiting for user input, after which system will exit.\t";
    char b;
    std::cin>>b;
    exit(1);
}