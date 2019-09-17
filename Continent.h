/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Continent.h
 * Author: t_filler
 *
 * Created on September 4, 2019, 8:38 PM
 */

#ifndef CONTINENT_H
#define CONTINENT_H
#include "Territory.h"
#include <vector> 
using namespace std;


class Continent {
    
public:
    Continent();
    Continent(const Continent& orig);
    virtual ~Continent();
    vector<Territory*> Territories;
    void addTerritory(Territory* a);
    int getValue();
    void setValue(int a);
    string getName();
    void setName(string a);
    void setID(int a);
    int getID();
    
private:
    string* name;
    int* value;
    int* ID;
};

#endif /* CONTINENT_H */

