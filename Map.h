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
    Map();//Default Constructor
    Map(const Map& orig);//Copy Constructor
    virtual ~Map();//Destructor
    std::vector <Territory*> Territories;//Territories in map
    std::vector <Continent*> Continents;//Continents in map
    std::string getName();//Returns name of map
    void setName(std::string a);//Sets name of map
    Territory* getTerritoryById(int a);//Returns territory from Territories with id==a
    bool isValid();//Returns if map is valid or not
    bool isConnected();//Checks if map is connected or not, sets valid flag to false if not
    void Invalidate();//Sets valid flag to false
private:
    std::string* name;//name of map
    bool* valid;//flag for if map is a valid map
};

#endif /* MAP_H */

