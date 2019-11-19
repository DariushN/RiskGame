#include "MapLoader.h"

MapLoader::MapLoader() {//Default Constructor
}

MapLoader::MapLoader(const MapLoader& orig) {//Copy COnstructor
}

MapLoader::~MapLoader() {//Destructor
}

#ifndef MAPLOADERUTILITY_H
#define MAPLOADERUTILITY_H
#include <cstdlib>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <conio.h>
#include <cstdlib>
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::cerr;
using std::vector;
using std::to_string;
using std::istringstream;
using std::ifstream;

Map* MapLoader::MapBuilder(string filename){//Map reader function
    istringstream iss;
    ifstream inputFile(filename);
    std::string temp;
    std::string temp2;
    Map* a = new Map();
    int state = 0;
    int tempInt;
    int Continent_counter = 0;
    for( ; getline( inputFile, temp ); ){//For each line of the file
        if(!temp.substr(0,4).compare("name")){//Read map name
            a->setName(temp.substr(5,temp.size()-5));
        }else if(!temp.compare("[continents]")){//Entering continents section
            state = 2;
            continue;
        }else if(!temp.compare("[countries]")){//entering countries section
            state = 3;
            continue;
        }else if(!temp.compare("[borders]")){//ENtering adjacency list section
            state = 4;
            continue;
        }
        
        if(state == 1){//Reading general data
            
        }else if(state == 2){//Reading continent data
            if(temp.length() > 0){
                Continent* tempContinent = new Continent();
                iss.str(temp);
                iss >> temp2;
                tempContinent->setName(temp2);
                iss >> tempInt;
                tempContinent->setValue(tempInt);
                tempContinent->setID(++Continent_counter);

                a->Continents.push_back(tempContinent);
                
            }
        }else if(state == 3){//Reading Territory data
            if(temp.length() > 0){
                Territory* tempTerritory = new Territory();
                iss.str(temp);
                iss>>tempInt;
                tempTerritory->setID(tempInt);
                iss>>temp2;
                tempTerritory->setName(temp2);
                iss>>tempInt;
                if(tempInt <= 0 || tempInt > Continent_counter){
                    std::cerr<<"Invalid continent index:\t"<<temp<<endl;
                    std::cerr<<"Map file is corrupted.\n";
                    a->Invalidate();
                }else{
                    tempTerritory->setLocation( a->Continents[tempInt-1]);
                    a->Territories.push_back(tempTerritory);
                    a->Continents[tempInt-1]->Territories.push_back(tempTerritory);
                }
            }
        }else if(state == 4){//Reading adjacency data
            if(temp.length() > 0){
                Territory* tempTerritory;
                if(iss.eofbit){
                    iss.str( std::string() );
                    iss.clear();
                }
                iss.str(temp);
                
                iss>>tempInt;
                tempTerritory = a->getTerritoryById(tempInt);
                while(!iss.eof()){
                    iss>>tempInt;
                    tempTerritory->addNeighbor(tempInt);
                    tempTerritory->addAdj(a->getTerritoryById(tempInt));
                }
            }
        }
    }
    if(a->Continents.empty()|| a->Territories.empty()){//If no continents or territories were read in
        a->Invalidate();//Map is corrupted
    }
    a->isConnected();//Check if connected.
    return a;
}

#endif /* MAPLOADERUTILITY_H */

DominationMapLoader::DominationMapLoader() {//Default COnstructor
}

DominationMapLoader::DominationMapLoader(const DominationMapLoader& orig) {//Copy constructor
}

DominationMapLoader::~DominationMapLoader() {//Destructor
}

void DominationMapLoader::operator=(DominationMapLoader& a){//Assignment Operator
}

Territory* getTerritoryByName(Map* a, string b);//Retrieves Territory* from map using name string
Continent* getContinentByName(Map* a, string b);//Retrieves Continent* from map using name string
struct TempDS{//Temporary Data Structure for recording adjacency lists.
    Territory* main;//Pointer to corresponding territory
    vector<string> neighbors;//List of neighbers' names
};

Map* DominationMapLoader::MapBuilder(std::string filename){//Map Reader function for Domination files
    istringstream iss;
    ifstream inputFile(filename);//Open Files
    if(!inputFile.is_open()){//Check if actually opened
        cerr<<"file could not be opened.";
        Map* a = new Map();//Create something to return.
        a->Invalidate();//Flag as invalid.
        return a;
    }    
    std::string temp;//Create storage for each line of .map file
    std::string temp2;//Create temporary storage for substrings within temp
    Map* a = new Map();//Create a map
    int state = 1;//Initialize the state/read mode for the appropriate section of the .map
    int tempInt;//Temporary int value, for when reading from a stream is necessary
    int Continent_counter = 0;//Stores number of continents
    int territory_counter = 0;//Stores number of territories
    vector<TempDS> DataList;//Stores names of adjacent territories for each territory until they can be resolved to pointers
    for( ; getline( inputFile, temp ); ){//For each line of the .map file
        if(!temp.substr(0,5).compare("image")){//Read name of map
            a->setName(temp.substr(6,temp.size()-10));//No name parameter exists, use image name as map name
        }else if(!temp.compare("[Continents]")){//Entering Continents portion of file
            state = 2;
            continue;
        }else if(!temp.compare("[Territories]")){//Entering Territories poriton of file
            state = 3;
            continue;
        }
        
        if(state == 1){//Reading General Data
            
        }else if(state == 2){//Reading Continents
            if(temp.length() > 0){
                Continent* tempContinent = new Continent();
                iss.str(temp);
                getline(iss,temp2,'=');
                tempContinent->setName(temp2);
                iss >> tempInt;
                iss.clear();
                tempContinent->setValue(tempInt);
                tempContinent->setID(++Continent_counter);
                a->Continents.push_back(tempContinent);
            }
        }else if(state == 3){//Reading Territories.
            if(temp.length() > 0){
                Territory* tempTerritory = new Territory();
                iss.clear();
                iss.str(temp);
                TempDS CurrentList;//For storing current territories list of neighbors.
                CurrentList.main = tempTerritory;
                for(int i = 0;getline(iss,temp2,','); ++i){
                    if(i == 0){
                        tempTerritory->setName(temp2);
                    }else if(i == 1 || i ==2){
                        continue;
                    }else if(i==3){
                        //set continent;
                        Continent* tempContinent = getContinentByName(a, temp2);
                        if(tempContinent == nullptr){
                            cerr<<"Invalid input file!"<<endl;
                            cerr<<temp2<<" does not name a valid continent"<<endl;
                            a->Invalidate();
                            return a;
                        }
                        tempTerritory->setLocation(tempContinent);
                        tempContinent->Territories.push_back(tempTerritory);
                    }else{
                        CurrentList.neighbors.push_back(temp2);//Store names of neighbors to be resolved to pointers later
                    }
                    
                }
                DataList.push_back(CurrentList);
                tempTerritory->setID(++territory_counter);
                a->Territories.push_back(tempTerritory);//Add territory to map
            }
        }
    }

    for(auto&& x:DataList){//Go through list counteries, and resolve names to pointers in adjacency list.
        Territory* t = x.main;
        Territory* t2;
        for(auto&& y:x.neighbors){
            t2 = getTerritoryByName(a,y);
            if(t2 == nullptr){//If no territory of appropriate name exists.
                cerr<<"Invalid adjacent territory: \""<<y<<"\""<<endl;
                cerr<<"For territory: "<<t->getName()<<"\t("<<t->getID()<<")"<<endl;
                a->Invalidate();
                return a;
            }
            t->adjacents.push_back(t2);
            t->addNeighbor(t2->getID());
        }
    }
    if(a->Continents.empty()|| a->Territories.empty()){//If no continents or territories were read:
        cerr<<"Error: target file is either missing continents or territories"<<endl;
        a->Invalidate();//Flag as corrupt
    }
    a->isConnected();//Check if map is valid.
    return a;
}

//Resolve continent name to pointer, if it exists
Continent* getContinentByName(Map* a, string b){
    Continent* c = nullptr;
    for(auto&& x:a->Continents){
        if(x->getName()==b){
            return x;
        }
    }
    return c;
}

//Resolve territory name to pointer, if it exists.
Territory* getTerritoryByName(Map* a, string b){
    for(auto&& x:a->Territories){
        if(x->getName()==b){
            return x;
        }
    }
    Territory* t = nullptr;
    return t;
}

//ConquestAdapter stuff:
ConquestAdapter::ConquestAdapter(){//Default constructor
    DML = new DominationMapLoader();//initialize DML
}

ConquestAdapter::ConquestAdapter(const ConquestAdapter& a){//copy contructor
    DML = new DominationMapLoader(*(a.DML));//Create copy of original's DML
}

ConquestAdapter::~ConquestAdapter(){//Destructor
    delete DML;//Free memory allocated to DML
}

void ConquestAdapter::operator =(const ConquestAdapter& a){//Assignment Operator
    delete DML;//Free memory allocatd to old DML
    DML = new DominationMapLoader(*(a.DML));//Create copy of DML
}

void ConquestAdapter::setDML(DominationMapLoader* a){//Change DML
    delete DML;//Free memory allocated to old DML
    DML = a;//set DML to given DML
}

Map* ConquestAdapter::MapBuilder(std::string filename){//Map builder wrapper
    return DML->MapBuilder(filename);//Call map builder of DML
}