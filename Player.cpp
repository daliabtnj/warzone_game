#include "Player.h"
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Order.h"
#include <algorithm> // Required for std::find_if

// initialize player count number to 0
// playerCount belongs to Player class
int Player::playerCount = 0;

// default constructor
Player::Player()
{
    playerCount++;

    // assign a default unique name
    name = "user" + std::to_string(playerCount + 1000);

    // allocate memory to new vectors that will hold pointers to objetcs
    territories = new std::vector<Territory *>();
    handOfCards = new std::vector<Card *>();
    orders = new std::vector<Order *>();
}

// parameterized constructor, takes okayer name as param
// player owns territories, a hand of cards, and a list of orders
Player::Player(const std::string &playerName)
{
    playerCount++;     // Increment player count
    name = playerName; // Assign the provided name
    territories = new std::vector<Territory *>();
    handOfCards = new std::vector<Card *>();
    orders = new std::vector<Order *>();
}

// Copy constructor
Player::Player(const Player &other)
{
    name = other.name; // Copy name
    territories = new std::vector<Territory *>(*(other.territories));
    handOfCards = new std::vector<Card *>(*(other.handOfCards));
    orders = new std::vector<Order *>(*(other.orders));
}

// Assignment Operator: allows one object to be assigned the properties (data members) of another object
// when you assign one Player object to another (player1 = player2;), all the player's attributes (name, cards...) are correctly copied over
Player &Player::operator=(const Player &other)
{
    if (this != &other)
    { // Check for self-assignment
        // Free memory of the current object's attributes to avoid memory leaks
        delete territories;
        delete handOfCards;
        delete orders;

        // Copy attributes from the other player
        name = other.name; // Copy name

        // Create new copies of the territories, handOfCards, and orders lists
        territories = new std::vector<Territory *>(*(other.territories));
        handOfCards = new std::vector<Card *>(*(other.handOfCards));
        orders = new std::vector<Order *>(*(other.orders));
    }
    return *this; // Return a reference to the current object to allow chained assignments
}

// Destructor
// free memory when a player is destroyed to prevent memory leaks
Player::~Player()
{
    delete territories;
    delete handOfCards;
    delete orders;
}

// getters & setters
std::string Player::getName() const
{
    return name;
}

void Player::setName(const std::string &newName)
{
    name = newName;
}

std::vector<Territory *> Player::getTerritories() const
{
    return *territories;
}

std::vector<Card *> Player::getHandOfCards() const
{
    return *handOfCards;
}

std::vector<Order *> Player::getOrders() const
{
    return *orders;
}

// function to add a territory to a player
// makes sure that no one has the territory so that it is only owned by one person
void Player::addTerritory(Territory *territory)
{
    if (territory->getOwner() != nullptr)
    { // check if it is owned by someone
        std::cout << "Territory " << territory->getName() << " is already owned by another player." << std::endl;
    }
    else
    { // not owned
        territory->setOwner(this);
        territories->push_back(territory);
    }
}

// function to remove a territory from the player
// for when we conquer territories; we must first remove the territory of previous owner before adding to a new player
void Player::removeTerritory(Territory *territory)
{
    auto it = std::find_if(territories->begin(), territories->end(),
                           [&territory](Territory *t)
                           { return t->getName() == territory->getName(); });
    if (it != territories->end())
    {
        territories->erase(it);
        territory->setOwner(nullptr); // Territory no longer has an owner
    }
}

// Method toDefend, for this assignment the list of territories outputted is arbitrary
std::vector<Territory *> Player::toDefend()
{
    std::cout << "Territories to defend:\n";
    for (auto territory : *territories)
    {
        std::cout << territory->getName() << std::endl; // Print the territory names
    }
    return *territories;
}

// Method to attack; returns arbitrary list of territories
std::vector<Territory *> Player::toAttack()
{
    std::cout << "Territories to attack:\n";
    for (auto territory : *territories)
    {
        std::cout << territory->getName() << std::endl; // Print the territory names (all the territories that are owoned by the player)
    }
    return *territories;
}

// Method to issue an order
void Player::issueOrder()
{
    orders->push_back(new Order());            // adds an Order object to the list of orders
    std::cout << "Order issued." << std::endl; // Print statement for order issued
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &os, const Player &player)
{ // Overload for << operator
    // output number of territories, cards and orders
    os << player.name << " has " << player.territories->size() << " territories, "
       << player.handOfCards->size() << " cards, and "
       << player.orders->size() << " orders.";
    return os; // return output stream
}