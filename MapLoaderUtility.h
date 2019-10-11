/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapLoaderUtility.h
 * Author: t_filler
 *
 * Created on September 11, 2019, 9:13 PM
 */

#ifndef MAPLOADERUTILITY_H
#define MAPLOADERUTILITY_H
#include <cstdlib>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Territory.h"
#include "Continent.h"
#include <fstream>
#include <sstream>
#include <conio.h>

Map MapBuilder(string filename){
    istringstream iss;
    ifstream inputFile(filename);
    std::string temp;
    std::string temp2;
    Map a = Map();
    int state = 0;
    int tempInt;
    int Continent_counter = 0;
    for( ; getline( inputFile, temp ); ){
        //std::cout<<temp<<endl;
        if(!temp.substr(0,4).compare("name")){
            a.setName(temp.substr(5,temp.size()-5));
        }else if(!temp.compare("[continents]")){
            state = 2;
            continue;
        }else if(!temp.compare("[countries]")){
            state = 3;
            continue;
        }else if(!temp.compare("[borders]")){
            state = 4;
            continue;
        }
        
        if(state == 1){
            
        }else if(state == 2){
            if(temp.length() > 0){
                //std::cout<<"reached phase 2";
                Continent* tempContinent = new Continent();
                iss.str(temp);
                iss >> temp2;
                //std::cout<<"temp2:"<<temp2<<endl;
                tempContinent->setName(temp2);
                //std::cout<<tempContinent->getName()<<endl;
                iss >> tempInt;
                //cout<<tempInt<<endl;
                tempContinent->setValue(tempInt);
                tempContinent->setID(++Continent_counter);

                a.Continents.push_back(tempContinent);
                
            }
        }else if(state == 3){
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
                    a.Invalidate();
                    /*getch();
                    exit(1);*/
                }else{
                    tempTerritory->setLocation( a.Continents[tempInt-1]);
                    a.Territories.push_back(tempTerritory);
                    /*std::cout<<tempTerritory.toString()<<endl;
                    std::cout<<a.Territories.back().toString();*/
                    a.Continents[tempInt-1]->Territories.push_back(tempTerritory);
                }
            }
        }else if(state == 4){
            if(temp.length() > 0){
                //std::cout<<"in state 4"<<endl;
                //std:cout<<"\ttemp: " << temp << endl;
                
                Territory* tempTerritory;
                if(iss.eofbit){
                    iss.str( std::string() );
                    iss.clear();
                }
                iss.str(temp);
                
                iss>>tempInt;
                tempTerritory = a.getTerritoryById(tempInt);
                while(!iss.eof()){
                    //std::cout<<"\t\t"<<"in iss loop"<<endl;
                    iss>>tempInt;
                    tempTerritory->addNeighbor(tempInt);
                    tempTerritory->addAdj(a.getTerritoryById(tempInt));
                }
            }
        }
    }
    if(a.Continents.empty()|| a.Territories.empty()){
        a.Invalidate();
    }
    a.isConnected();//Check if connected.
    //for(auto&& x:a.Continents) cout<<"\t"<< x.getID() <<endl;
    //std::cout<<"reached here"<<endl;
    return a;
}

#endif /* MAPLOADERUTILITY_H */

