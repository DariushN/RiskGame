/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Territory.h
 * Author: t_filler
 *
 * Created on September 4, 2019, 8:37 PM
 */

#ifndef TERRITORY_H
#define TERRITORY_H
#include "Player.h"
#include <iterator> 
#include <string>
#include <vector> 

class Continent;
class Player;
class Territory {
public:
    int getID();
    void setID(int a);
    Territory();
    Territory(const Territory& orig);
    virtual ~Territory();
    std::string getName();
    void setName(std::string a);
    int getTroops();
    void setTroops(int a);
    void incTroops(int a = 1);
    void decTroops(int a = 1);
    void addNeighbor(int a);
    //vector<int> getNeighbors();
    void addAdj(Territory *a);
    bool isAdj(Territory *a);
    std::string toString();
    void setOwner(Player *a);
    std::vector <int*> neighbors;
    void setLocation(Continent* a);
    std::vector <Territory*> adjacents;
    Continent getLocation();
private:
    int* ID;
    std::string* name;
    int* troops;
    Continent* location;
    
    Player* owner;
};

#endif /* TERRITORY_H */

