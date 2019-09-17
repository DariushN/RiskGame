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

Continent::Continent() {
    name = new string("");
    ID = new int(1);
    value = new int(1);
}

Continent::Continent(const Continent& orig) {
    //std::cout<< "Continent copy constructor called"<<endl;
    this->ID = orig.ID;
    this->Territories = orig.Territories;
    this->name = orig.name;
    this->value = orig.value;
}

Continent::~Continent() {
    delete name;
    delete ID;
    delete value;
}

void Continent::setName(string a){
    *name = a;
}

int Continent::getID(){
    return *ID;
}

void Continent::setID(int a){
    *ID = a;
}

void Continent::setValue(int a){
    *value = a;
}

int Continent::getValue(){
    return *value;
}

std::string Continent::getName(){
    return *name;
}