#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <string>
#include "Map.h"
#include "Cards.h"

// forward declaration of the classes
class Territory;
class Card;
class Order;

class Player{
private:
    static int playerCount;
    std::string name;

    // pointers to a vector of pointers to objects (Territory, Card, Order)
    std::vector<Territory*>* territories; // collection of territories from pt1
    std::vector<Card*>* handOfCards; // colection of warzone cards
    std::vector<Order*>* orders; // collection of orders

public:
    // constructors and deconstructors
    Player(); // default
    Player(const std::string& playerName); // parameterized constructor
    Player(const Player& other); // copy constructor
    Player& operator=(const Player& other); // assignment operator
    ~Player(); //destructor

    // getters & setters
    std::string getName() const; // get the player's name
    void setName(const std::string& newName);
    std::vector<Territory*> getTerritories() const;  // get the territories owned by the player
    std::vector<Card*> getHandOfCards() const;  // get the player's hand of cards
    std::vector<Order*> getOrders() const;  // get the orders issued by the player

    // methods to add and remove territory from a player
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);

    // methods defend/attack : vectors of pointers to objects
    std::vector<Territory*> toDefend(); // outputs a list of territories to defend
    std::vector<Territory*> toAttack(); // outputs a list of territories to attack
   
   // method to create & adds an order to the list
    void issueOrder(); 

    //stream insertion and operator overload
    //function defines how a Player's data is formatted/displayed when using the << operator with output streams
    //"friend" to access private & protected members of class
    friend std::ostream& operator<<(std::ostream& os, const Player& player);  // Overload operator to print player info

};

#endif