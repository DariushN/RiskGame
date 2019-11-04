#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector> 

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

#ifndef CONTINENT_H
#define CONTINENT_H
#include <vector> 
using std::string;
using std::vector;
class Territory;
class Map;

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

#ifndef TERRITORY_H
#define TERRITORY_H

#include <iterator> 
#include <string>
#include <vector> 

class Player;
class Continent;
class Map;

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
    Player* getOwner() const;
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
#include "Player.h"
#endif /* TERRITORY_H */