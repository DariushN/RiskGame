/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: t_filler
 * 
 * Created on September 4, 2019, 8:55 PM
 */

#include "Player.h"

Player::Player() {
}

Player::Player(std::string Name, int Id){
    name = Name;
    id = Id;
}

std::string Player::getName(){
    return name;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

