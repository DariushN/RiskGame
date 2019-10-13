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
class Territory {
public:
    int getID();//Returns PIN
    void setID(int a);//Sets PIN
    Territory();//Constructor
    Territory(const Territory& orig);//Copy Constructor
    virtual ~Territory();//Destructor
    std::string getName();//Returns name
    void setName(std::string a);//sets name
    int getTroops();//returns # of troops
    void setTroops(int a);//sets number of troops
    void incTroops(int a = 1);//Increases number of troops
    void decTroops(int a = 1);//Decreases number of troops
    void addNeighbor(int a);//Adds PIN of neighbor
    void addAdj(Territory *a);//Adds pointer to neighbor to adjacency vector
    bool isAdj(Territory *a);//Checks if the territory is adjacent
    std::string toString();//Returns string with the Territory's data
    void setOwner(Player *a);//Sets the pointer to owner
    std::vector <int*> neighbors;//vector of PINs of neighbors (not used)
    void setLocation(Continent* a);//Sets Continent that it is contained in.
    std::vector <Territory*> adjacents;//Vector containing the adjacency list.
    Continent* location;//Continent that territory is part of.
private:
    int* ID;//PIN
    std::string* name;//Name of Territory
    int* troops;//Number of troops
    Player* owner;//Owner of this territory.
};

#endif /* TERRITORY_H */

