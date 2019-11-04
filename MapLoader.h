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
    Map* MapBuilder(std::string filename);
private:

};

#endif /* MAPLOADER_H */

