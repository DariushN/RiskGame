/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Continent.cpp
 * Author: t_filler
 * 
 * Created on September 4, 2019, 8:38 PM
 */

#include "Continent.h"
#include <iostream>

Continent::Continent() {//Default constructor
    name = new string("");
    ID = new int(1);
    value = new int(1);
}

Continent::Continent(const Continent& orig) {//Copy Constructor
    //std::cout<< "Continent copy constructor called"<<endl;
    this->ID = orig.ID;
    this->Territories = orig.Territories;
    this->name = orig.name;
    this->value = orig.value;
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