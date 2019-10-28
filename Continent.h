/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Continent.h
 * Author: t_filler
 * Created on September 4, 2019, 8:38 PM
 */

#ifndef CONTINENT_H
#define CONTINENT_H
#include "Territory.h"
#include <vector> 
using namespace std;
class Territory;

class Continent {
    
public:
    Continent();//Constructor
    Continent(const Continent& orig);//Copy Constructor
    virtual ~Continent();//Destructor
    vector<Territory*> Territories;//Territories in this continent
    void addTerritory(Territory* a);//Add to Territories in this continent
    int getValue();//# of troops for holding this entire continent
    void setValue(int a);//Sets # of troops for holding this entire continent
    string getName();//Returns name
    void setName(string a);//Sets name
    void setID(int a);//sets PIN
    int getID();//returns PIN
    bool isContained(Territory* a);//Checks if the territory is in this continent
private:
    string* name;//Name
    int* value;//# of troops for holding this entire continent
    int* ID;//PIN
};

#endif /* CONTINENT_H */

