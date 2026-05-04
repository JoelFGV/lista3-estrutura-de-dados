#include<iostream>
#include "Player.hpp"

using namespace std;

Player::Player() : id(0), name(""), score(0), timestamp(0) {}

Player::Player(int id, string name, int score, int timestamp) 
    : id(id), name(name), score(score), timestamp(timestamp) {}

Player::~Player() {}

int Player::getId() {
    return id;
}

string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

int Player::getTimestamp() {
    return timestamp;
}