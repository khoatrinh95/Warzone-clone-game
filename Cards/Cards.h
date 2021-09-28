//
// Created by Ricky Lam on 2021-09-26.
//

#ifndef COMP345_CARDS_H
#define COMP345_CARDS_H

#endif //COMP345_CARDS_H

#include<string>
#include <vector>
using namespace std;

class Card{
public:
    //constructors and destructors
    Card();
    Card(string type);
    ~Card();

    //copy constructor and = operator
    Card(const Card& c);
    Card& operator =(const Card& c);

    Card* play(); //play function as per assignment handout
    void testType(); //guard function for constructor
    string printCard() const; //for debugging, unused

    //accessor and mutator
    string getType() const;
    void setType(string typer);

private:
    string type;
};

class Deck{
public:
    //constructors and destructors
    Deck();
    Deck(vector<Card*> cards);
    ~Deck();

    //copy constructor and = operator
    Deck(const Deck& d);
    Deck& operator =(const Deck& d);

    void addCard(Card* carder); //adds a card from the deck manually
    void addCard(string type); //creates a card of the type passed in parameter then adds to deck
    Card* draw(); //draws a card from the deck as requested from the assignment handout

    int getSize() const; //debugging function to see how big the deck is at the moment
    string printDeck() const; //debugging function to see all cards in deck

private:
    vector<Card *> cards;
};

class Hand{
public:
    //constructors and destructors
    Hand();
    Hand(const vector<Card*> cards);
    ~Hand();

    //copy constructor and = operator
    Hand(const Hand& h);
    Hand& operator =(const Hand& h);

    void drawFromDeck(Deck* deck); //removes a card randomly from the deck and adds it to the player's hand
    void playAllCards(Deck* deck); //plays all cards in the player's hand

    int getSize() const; //debugging function to see the size of the player's hand
    string printHand() const; //prints out all cards on hand

private:
    vector<Card*> hand;
};

