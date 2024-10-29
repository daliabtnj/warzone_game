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
    name = new std::string("user" + std::to_string(playerCount + 1000)); // Unique default name

    // allocate memory to new vectors that will hold pointers to objetcs
    territories = new std::vector<Territory *>();
    handOfCards = new Hand();
    orderList = new OrdersList();
    cardsInHand = new int(0);  // Initializing cards in hand to 0
}

// parameterized constructor, takes okayer name as param
// player owns territories, a hand of cards, and a list of orders
Player::Player(const std::string &playerName)
{
    playerCount++;     // Increment player count
    name = new std::string(playerName); // Assign the provided name
    territories = new std::vector<Territory *>();
    handOfCards = new Hand();
	orderList = new OrdersList();
    cardsInHand = new int(0); // Initialize cards to 0
}

// Copy constructor
Player::Player(const Player &other)
{
    name = new std::string(*(other.name));  
    territories = new std::vector<Territory *>(*(other.territories));
    handOfCards = new Hand(*(other.handOfCards));
	orderList = new OrdersList(*(other.orderList));
    cardsInHand = new int(*(other.cardsInHand));  
}

// Assignment Operator: allows one object to be assigned the properties (data members) of another object
// when you assign one Player object to another (player1 = player2;), all the player's attributes (name, cards...) are correctly copied over
Player &Player::operator=(const Player &other)
{
    if (this != &other)
    { // Check for self-assignment
        // Free memory of the current object's attributes to avoid memory leaks
        delete name;
        delete territories;
        delete handOfCards;
        delete orderList;
        delete cardsInHand;

        // Copy attributes from the other player
        name = new std::string(*(other.name));

        // Create new copies of the territories, handOfCards, and orders lists
        territories = new std::vector<Territory *>(*(other.territories));
        handOfCards = new Hand(*(other.handOfCards));
	    orderList = new OrdersList(*(other.orderList));
        cardsInHand = new int(*(other.cardsInHand));

    }
    return *this; // Return a reference to the current object to allow chained assignments
}

// Destructor
// free memory when a player is destroyed to prevent memory leaks
Player::~Player()
{
    delete name;
    delete territories;
    delete handOfCards;
    delete orderList;
    delete cardsInHand;
}

// getters & setters
std::string Player::getName() const
{
    return *name;
}

void Player::setName(const std::string &newName)
{
    *name = newName;
}

Hand* Player::getHandOfCards() const {
    return handOfCards;
}

std::vector<Territory *> Player::getTerritories() const
{
    return *territories;
}

OrdersList* Player::getOrdersList() const {
    return orderList;
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

// method to add a card to the hand
void Player::addCards(Card* card) {
    if (card != nullptr) {
        handOfCards->addCard(*card);  
        (*cardsInHand)++; // Increment the number of cards
    } else {
        std::cout << "Invalid card!" << std::endl;
    }
}

// Method to display the hand of cards
void Player::displayHand() const {
    std::cout << *handOfCards; 
}

// Method toDefend, for this assignment the list of territories outputted is arbitrary
std::vector<Territory *> Player::toDefend()
{
    std::cout << "Territories to defend:\n";
    std::cout << "----------------------\n";
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
    std::cout << "----------------------\n";
    for (auto territory : *territories)
    {
        std::cout << territory->getName() << std::endl; // Print the territory names (all the territories that are owoned by the player)
    }
    return *territories;
}

// method to issue an order
void Player::issueOrder(Order* newOrder) {
    // check if order exists
    if (newOrder != nullptr) {
        orderList->issueOrder(newOrder);  
        std::cout << "Order issued by " << this->getName() << ": " << *newOrder << std::endl; 
    } else {
        std::cout << "Invalid order!" << std::endl;
    }
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << *(player.name) << " has " << player.territories->size() << " territories, "
       << *(player.cardsInHand) << " cards and has issued the following orders:\n"
       << *(player.orderList);
    return os;
}