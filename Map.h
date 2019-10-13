/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: t_filler
 *
 * Created on September 4, 2019, 8:38 PM
 */

#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector> 
#include "Continent.h"
#include "Territory.h"
class Territory;
class Continent;

class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    std::vector <Territory*> Territories;
    std::vector <Continent*> Continents;
    std::string getName();
    void setName(std::string a);
    Territory* getTerritoryById(int a);
private:
    std::string* name;
};

#endif /* MAP_H */

