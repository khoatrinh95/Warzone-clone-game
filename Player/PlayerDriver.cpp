//
// Created by sarah on 2021-09-28.
//
#include <iostream>
#include <vector>

using namespace std;

#include "PlayerDriver.h"
#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"

void PlayerDriver(){
    /**
     *creating a continent object
     */
    Continent *continent = new Continent(9,"Africa",10);

    /**
     * creating a list of territories
     */
    vector<Territory*> territories;
    territories.push_back(new Territory(99,"Kenya",3,continent));
    territories.push_back(new Territory(98,"Morocco",1,continent));
    territories.push_back(new Territory(97,"Egypt",4,continent));

    /**
     * creating another list of territories
     */
    vector<Territory*> another_territories;
    another_territories.push_back(new Territory(99,"China",3,continent));
    another_territories.push_back(new Territory(98,"Japan",1,continent));
    another_territories.push_back(new Territory(97,"India",4,continent));

    /**
     * creating a hand of cards
     */
    vector<Card*>cards;
    cards.push_back(new Card("bomb"));
    cards.push_back(new Card("reinforcement"));
    cards.push_back(new Card("blockade"));
    cards.push_back(new Card("airlift"));
    cards.push_back(new Card("diplomacy"));
    Hand * handOfCards = new Hand(cards);


    /**
     * creating an orderslist
     */
    vector<Order*> orders;
    orders.push_back(new AirliftOrder());
    orders.push_back(new NegotiateOrder());
    OrdersList *ordersList = new OrdersList(orders);



    /**
     * testting default constructor
     */
    Player *player1 = new Player();
    cout << "\t\t\t***Testing the default Constructor***"<<endl;
    cout<< "This is the information about player No. 1"<<endl;
    cout<<*player1;
    cout<<endl;

    /**
     *     testing parameterized constructor with player name and list of territories
     */
    cout<< "\t\t\t***Testing the Parameterized Constructor***"<<endl;
    cout<< "This is the information about player No. 2"<<endl;
    Player *player2 = new Player("PlayerNO.2",territories);
    cout<<*player2;


    /**
     * testing copy constructor
     */
    cout<< "\t\t\t***Testing the copy Constructor***"<<endl;
    cout<< "This is the information about player No. 3"<<endl;
    Player *player3 = new Player(*player2);
    cout<<*player3;

        // adding a territory to original player (player 2)
    cout<<"!!!Adding a territory to player No.2!!!"<<endl;
    Territory *newTerritory =new Territory(25,"South Africa",3,continent);
    player2->addTerritory(newTerritory);
        // printing out the content of the 2 player after adding another territory to one of them
    cout<< "This is the information about player No. 2"<<endl;
    cout<<*player2;
    cout<< "This is the information about player No. 3"<<endl;
    cout<<*player3;

    // testing all getters
    /**
     * testing get and set player's name functions
     */
    cout << "\t\t\t***Testing set and get function for player name***"<<endl;
    cout<<"player no.1 name old name is "<< player1->getName()<<endl;
    player1->setName("PlayerNO.1_newName");

    string playerName =  player1->getName();
    cout<<"Player new name is "<<playerName <<endl;
    cout<<endl;

    /**
     * testing get and set player's territories functions
     */
    cout << "\t\t\t***Testing set and get territories for player No.1 who had no territories***"<<endl;
    player1->setTerritories(another_territories);

    cout << "player no.1 territories are: "<<endl<<"\t";
    for (auto & territory : player1->getTerritories()){
        cout<<*territory<<endl<<"\t";
    }
    cout<<endl;
    cout<<endl;

    /**
     * testing get and set for player's hand of cards functions
     */
    cout << "\t\t\t***Testing set and get hand of cards for player No.1 who had no cards***"<<endl;
    player1->setPlayerCards(handOfCards);

    cout << "player no.1 's hand of cards is: "<<endl;
    cout<<*player1->getPlayerCards()<<endl;
    cout << endl;

    /**
     * testing get and set for player's list of order functions
     */
    cout << "\t\t\t***Testing set and get list of order for player No.1 who had no orders in his list***"<<endl;
    player1->setPlayerOrdersList(ordersList);

    cout << "player no.1's orders list is: "<<endl;
    cout<<*player1->getPlayerOrdersList()<<endl;
    cout<<endl;
    cout<<endl;


    /**
     * testing toDefend function
     */
    cout <<"\t\t\t***Testing toDefend Function***"<<endl;
    cout << "The list of to be defended territories is:"<< endl<<"\t";
    vector<Territory*> to_be_defended_territories = player1->toDefend();
    for (auto & territory : to_be_defended_territories){
        cout<<*territory<<endl<<"\t";
    }
    cout<<endl;
    cout<<endl;


    /**
     * testing toAttach function
     */
    cout <<"\t\t\t***Testing toAttack Function***"<<endl;
    cout << "The list of to be attacked territories is:"<< endl<<"\t";
    vector<Territory*> to_be_attacked_territories = player1->toAttack();
    for (auto & territory : to_be_attacked_territories){
        cout<<*territory<<endl<<"\t";
    }
    cout<<endl;
    cout<<endl;


    /**
     * testing issueOrder function
     */
    cout <<"\t\t\t***Testing issueOrder Function***"<<endl;
    cout << "The list of player order is:"<< endl;
    player1->issueOrder();
    cout <<*player1->getPlayerOrdersList()<<endl;

    cout<<endl;


    /**
     * memory deallocation
     */
    delete player1 ;
    player1= nullptr;
    cout<<endl;

    delete player2 ;
    player2= nullptr;
    cout<<endl;

    delete player3;
    player3= nullptr;
    cout<<endl;

    ordersList = nullptr;
    cout<<endl;

    handOfCards = nullptr;
    cout<<endl;

    for (auto &territory :territories){
        delete territory;
        territory= nullptr;
    }
    territories.clear();
    cout<<endl;

    for (auto &territory :another_territories){
        delete territory;
        territory= nullptr;
    }
    another_territories.clear();
    cout<<endl;

    delete newTerritory;
    newTerritory = nullptr;
    cout<<endl;

    delete continent;
    continent = nullptr;

}
