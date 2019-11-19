/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapLoader.h
 * Author: t_filler
 *
 * Created on November 3, 2019, 7:06 PM
 */

#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"
class MapLoader {
public:
    MapLoader();
    MapLoader(const MapLoader& orig);
    virtual ~MapLoader();
    virtual Map* MapBuilder(std::string filename);
private:

};

#endif /* MAPLOADER_H */

#ifndef DOMINATIONMAPLOADER_H
#define DOMINATIONMAPLOADER_H
#include "Map.h"
class DominationMapLoader {
public:
    DominationMapLoader();//Default Constructor
    DominationMapLoader(const DominationMapLoader& orig);//Copy COnstructor
    virtual ~DominationMapLoader();//Destructor
    virtual Map* MapBuilder(std::string filename);//Map builder function, doesn't need to be virtual, is anyway
    void operator=(DominationMapLoader& a);//Assignment operator
private:
    //Has no data members
};

#endif /* DOMINATIONMAPLOADER_H */

#ifndef CONQUESTADAPTER_H
#define CONQUESTADAPTER_H
class ConquestAdapter: public MapLoader{
private:
    DominationMapLoader* DML;//Target of adapter
public:
    ConquestAdapter();//General constructor
    ConquestAdapter(const ConquestAdapter& a);//Copy constructor
    void setDML(DominationMapLoader* a);//Changes the DML
    void operator=(const ConquestAdapter& a);//Assignment operator
    virtual ~ConquestAdapter();//Destructor
    virtual Map* MapBuilder(std::string filename);//Wrapper for DML
};
#endif