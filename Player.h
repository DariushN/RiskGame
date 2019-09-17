/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: t_filler
 *
 * Created on September 4, 2019, 8:55 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector> 
class Territory;


class Player {
public:
    Player();
    Player(std::string name, int id);
    Player(const Player& orig);
    virtual ~Player();
    int getId();
    void setId(int a);
    std::string getName();
    void setName(std::string a);
    std::vector <Territory*> lands;
private:
    int id;
    std::string name;
    
};

#endif /* PLAYER_H */

