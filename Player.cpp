#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <string>
class Dice;

Player::Player() {
	name = new std::string("");
	id = new int(1);
	dice = new Dice();
}

std::string Player::getName(){
    return *name;
}

void Player::setName(std::string Name) {
	*name = Name;
}

void Player::setId(int iD) {
	*id = iD;
}

int Player::getId(){
    return *id;
}

void Player::attack() {
	std::cout << "Attacking" << std::endl;
}

void Player::reinforce() {
	std::cout << "Reinforcing" << std::endl;
}

void Player::fortify() {
	std::cout << "Fortifying" << std::endl;
}

Player::~Player() {
	delete name;
	delete id;
	delete dice;
}

