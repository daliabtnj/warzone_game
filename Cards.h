#ifndef CARD_H
#define CARD_H

#include "Cards.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Order.h"

//Forward declarations

class Hand;
class Deck;

class Card // Card class definition

public:
    // Enumeration for different types of cards
    enum CardType { EMPTY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY };

private:
    CardType type;  // Variable to store the type of the card

public:
    // Default constructor that initializes the card to EMPTY
    Card();
    // Constructor that initializes the card with a specific CardType
    Card(CardType t);
    // Copy constructor for creating a card from another card
    Card(const Card& other);
    // Destructor
    ~Card() {}

    // Assignment operator overload
    Card& operator=(const Card&other);

    // Equality operator overload to compare two cards
    bool operator==(const Card& other) const;

    // Friend function to output card information
    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    // Setter for the card type
    void setType(CardType t);

    // Getter for the card type
    CardType getType() const;

    // Method to play the card, affecting the hand and deck
    void play(Hand& hand, Deck& deck, Player& player);

};
// Deck class definition
class Deck
{
public:
    Card deckOfCards[100];  // Array to hold the cards in the deck
public:
    // Default constructor that initializes the deck
    Deck();
    // Constructor that initializes the deck with an array of cards
    Deck(Card deckOfCards[]);
    // Copy constructor for creating a deck from another deck
    Deck(const Deck& other);
    // Destructor
    ~Deck() {}

    // Assignment operator overload
    Deck& operator=(const Deck&other);

    // Friend function to output deck information
    friend std::ostream& operator<<(std::ostream& os, const Deck& deck);

    // Setter for the deck of cards
    void setDeck(const Card deck[]);

    // Getter for the deck of cards
    const Card* getDeck() const;

    // Method to draw a card from the deck and add it to a hand
    void draw(Hand& hand);
};

// Hand class definition
class Hand
{

private:
    Card handOfCards[7];    // Array to hold the cards in the hand
    int cardCount;          // Counter to track the number of cards in hand

public:
    // Default constructor that initializes the hand
    Hand();
    // Constructor that initializes the hand with an array of cards
    Hand(Card handOfCards[]);
    // Copy constructor for creating a hand from another hand
    Hand(const Hand& other);

    // Assignment operator overload
    Hand& operator=(const Hand&other);

    // Assignment operator overload
    friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

    // Destructor
    ~Hand() {}

    // Setter for the hand of cards
    void setHand(const Card hand[]);

    // Getter for the hand of cards
    const Card* getHand() const;

    // Method to set a specific card at a given index
    void setCardAt(int index, const Card& card);

    // Method to get a card at a specific index
    const Card& getCardAt(int index) const;

    // Getter for card count
    int getCardCount() const { return cardCount; }

    // Method to add a card to the hand
    bool addCard(const Card& card);
};

#endif
