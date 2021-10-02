//
// Created by sarah on 2021-09-19.
//

#include "Player.h"
#include <iostream>

// Player default constructor
Player::Player() {
    name = "anonymous";
    vector<Territory*> Territory;
    territories = Territory;
    playerCards = new Hand();
    playerOrdersList = new OrdersList();
}

// parameter constructor, that takes a name and assign it to the player's name, territories and assign it to player
// territories
Player::Player(string Name, vector<Territory *> &territories) {
    this->name = Name;
    this->territories = territories;
    this->playerCards = new Hand();
    this->playerOrdersList = new OrdersList();


}
// Copy constructor that do a deep copy of a player's members
Player::Player(const Player &anotherPlayer) {
    this->name = anotherPlayer.name +"_copy";
    this->playerCards = new Hand(*anotherPlayer.playerCards);
    this->playerOrdersList = new OrdersList(*anotherPlayer.playerOrdersList);
    vector<Territory*>temp_Territory = anotherPlayer.territories;
    for (vector<Territory*>::iterator iter = temp_Territory.begin(); iter!=temp_Territory.end(); ++iter){
        Territory* newTerritory = new Territory(**iter);
        addTerritory(newTerritory);
    }
}

Player::~Player(){
    cout<<"inside destructor of "<<name<<endl;
    delete playerCards;
    delete playerOrdersList;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() const {
    return this->name;
}

void Player::setPlayerCards(Hand *&PlayerCards) {
    this->playerCards = PlayerCards;
}

Hand *Player::getPlayerCards() const {
    return this->playerCards;
}

void Player::setPlayerOrdersList(OrdersList *&ordersList) {
    this->playerOrdersList = ordersList;
}

OrdersList *Player::getPlayerOrdersList() const {
    return playerOrdersList;
}

void Player::setTerritories(vector<Territory*> territories) {
    this->territories = territories;
}

vector<Territory*> Player::getTerritories() const {
    return territories;
}

vector<Territory*> Player::toDefend() {
    vector<Territory*> territories_to_be_defended;
    territories_to_be_defended.push_back(new Territory(12,"Portugal", 4));
    territories_to_be_defended.push_back(new Territory(21,"Brazil", 2));
    territories_to_be_defended.push_back(new Territory(100,"India", 1));
    return territories_to_be_defended;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> territories_to_be_attacked;
    territories_to_be_attacked.push_back(new Territory(3,"Egypt", 5));
    territories_to_be_attacked.push_back(new Territory(7,"Italy", 3));
    territories_to_be_attacked.push_back(new Territory(10,"Greece", 2));

    return territories_to_be_attacked;
}

void Player::issueOrder() {
    DeployOrder *anOrder = new DeployOrder();
    playerOrdersList->add(anOrder);

}

Player &Player::operator=(const Player &anotherPlayer) {
    if (this!=& anotherPlayer){
        this->~Player();
        territories.clear();

        this->name = anotherPlayer.name +"_copy";
        this->playerCards = new Hand(*anotherPlayer.playerCards);
        this->playerOrdersList = new OrdersList(*anotherPlayer.playerOrdersList);
        vector<Territory*>temp_Territory = anotherPlayer.territories;
        for (vector<Territory*>::iterator iter = temp_Territory.begin(); iter!=temp_Territory.end(); ++iter){
            Territory* newTerritory = new Territory(**iter);
            addTerritory(newTerritory);
        }

    }
    return *this;
}

 ostream &operator<<(ostream &out, const Player &player) {
    if (player.territories.empty()){
        out << "Player name is "<<player.name<<", and he has no territories"<<endl;
    }else{
        out << "Player name is "<< player.name<< ", and he has the following territories:"<<endl<<"\t";
        for (auto &territory : player.territories){
            out << *territory << "\t";
        }
        out<<endl;
    }
    if (player.playerCards->getSize()==0){
        out<<"This player does not have a hand of cards"<<endl;
    } else{
        out<<"player hand of cards is :"<<endl;
        out<<*player.playerCards;
    }
    out<< endl;

    return out;
}

void Player::addTerritory(Territory *newTerritory) {
    this->territories.push_back(newTerritory);
}









