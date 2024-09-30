#include "Cards.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Order.h"
#include <random>
#include <algorithm> // Required for std::find_if

////////////////////////////////////

// Default constructor for the Card class
Card::Card()
{
    type = EMPTY;   // Initialize the card type to EMPTY
}

// Constructor that initializes the card with a specific CardType
Card::Card(CardType t)
{
    type = t;   // Set the card type
}

// Copy constructor for the Card class
Card::Card(const Card& other)
{
    type = other.type;  // Copy the type from another card
}

// Assignment operator overload for the Card class
Card& Card::operator=(const Card& other)
{
    if (this != &other)
    { // Self-assignment check
        type = other.type; // Copy the type
    }
    return *this; // Return the current object
}

// Overloaded output operator for the Card class
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    if(card.getType()==Card::EMPTY)
        return os << "";    // Return an empty string for an EMPTY card
    os << "Card Type: ";    // Print the card type
    switch (card.getType()) {
        case Card::BOMB: os << "BOMB \n"; break;
        case Card::REINFORCEMENT: os << "REINFORCEMENT \n"; break;
        case Card::BLOCKADE: os << "BLOCKADE \n"; break;
        case Card::AIRLIFT: os << "AIRLIFT \n"; break;
        case Card::DIPLOMACY: os << "DIPLOMACY \n"; break;
        case Card::EMPTY: os << "EMPTY \n"; break;  // Handle the EMPTY case
        default: os << "Unknown Type \n"; break;    // Optional: Handle any unknown cases
    }
    return os;  // Return the output stream
}

// Equality operator overload to compare two Card objects
bool Card::operator==(const Card& other) const
{
    return this->type == other.getType(); // Compare the card types
}

// Setter for the card type
void Card::setType(CardType t)
{
    type = t;   // Set the card type
}

// Getter for the card type
Card::CardType Card::getType() const
{
    return type;    // Return the card type
}

// Method to play the card, affecting the player's hand and the deck
void Card::play(Hand& hand, Deck& deck)
{
    // Search for this card in the player's hand
    for (int i = 0; i < 7; ++i)
    {
        // Check if the current card in the hand matches the one being played
        if (hand.getHand()[i] == *this) // Using the overloaded == operator
        {
            // Find an empty slot in the deck to return the card
            for (int j = 0; j < 40; ++j)
            {
                if (deck.getDeck()[j].getType() == Card::EMPTY)
                {
                    deck.deckOfCards[j] = hand.getHand()[i]; // Add the card back to the deck
                    break;
                }
            }

            // Remove the card from the hand by setting it to empty
            hand.setCardAt(i, Card(Card::EMPTY)); // Set the card to empty
            std::cout << "Played " << *this << " and returned it to the deck.\n";
            return;
        }
    }

    // If the card wasn't found in the hand
    std::cout << "Card not found in hand!\n";
}




////////////////////////////////////

// Default constructor for the Deck class
Deck::Deck()
{
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = Card();    // Initialize each card in the deck to EMPTY
    }
}

// Constructor that initializes the deck with an array of cards
Deck::Deck(Card deck[])
{
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = deck[i]; // Copy each card
    }
}

// Copy constructor for the Deck class
Deck::Deck(const Deck& other)
{
    // Copy each card individually
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = other.deckOfCards[i]; // Properly copy each element
    }
}

// Assignment operator overload for the Deck class
Deck& Deck::operator=(const Deck& other)
{
    if (this != &other)
    { // Check for self-assignment
        for (int i = 0; i < 40; ++i)
        {
            deckOfCards[i] = other.deckOfCards[i]; // Copy each card
        }
    }
    return *this; // Return the current object
}

// Overloaded output operator for the Deck class
std::ostream& operator<<(std::ostream& os, const Deck& deck)
{
    os << "Deck contains:\n";
    for (const auto& card : deck.deckOfCards) {
        os << card ; // Use the overloaded operator for Card
    }
    return os;
}

// Setter for the deck of cards
void Deck::setDeck(const Card deck[])
{
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = deck[i]; // Copy each card from the input array
    }
}

// Getter for the deck of cards
const Card* Deck::getDeck() const
{
    return deckOfCards;
}

// Method to draw a card from the deck and add it to the player's hand
void Deck::draw(Hand& hand) // Hand is passed as a reference
{
    const Card* currentHand = hand.getHand();
    int cardCount = 0;

    // Count how many cards are currently in the hand (non-empty)
    while (cardCount < 7 && currentHand[cardCount].getType() != Card::EMPTY) {
        cardCount++;
    }

    // Draw a card if the hand can accept more cards
    if (cardCount < 7)
    {
        std::random_device rd;  // Random number generator
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 39); // Range: 0 to 39 (index)

        // Generate a random index to draw from the deck
        int randomIndex = distr(gen);

        // Add the drawn card to the hand using the setter method
        hand.setCardAt(cardCount, deckOfCards[randomIndex]); // Properly set the card in the hand
        deckOfCards[randomIndex] = Card(Card::EMPTY);
    }
    else {
        std::cout << "Hand is full. Cannot draw more cards.\n"; // Optional message if hand is full
    }
}




////////////////////////////////////

// Default constructor for the Hand class
Hand::Hand()
{
    for (int i = 0; i < 5; ++i) // Player starts with 5 cards, but can have a maximum of 7 cards
    {
        handOfCards[i] = Card();    // Initialize each card in the hand to EMPTY
    }
}

// Constructor that initializes the hand with an array of cards
Hand::Hand(Card hand[])
{
    for (int i = 0; i < 7; ++i)
    {
        handOfCards[i] = hand[i]; // Copy each card
    }
}

// Copy constructor for the Hand class
Hand::Hand(const Hand& other)
{
    // Copy each card individually
    for (int i = 0; i < 7; ++i)
    {
        handOfCards[i] = other.handOfCards[i]; // Properly copy each element
    }
}

// Assignment operator overload for the Hand class
Hand& Hand::operator=(const Hand& other)
{
    if (this != &other)
    { // Check for self-assignment
        for (int i = 0; i < 7; ++i)
        {
            handOfCards[i] = other.handOfCards[i]; // Copy each card
        }
    }
    return *this; // Return the current object
}

// Overloaded output operator for the Hand class
std::ostream& operator<<(std::ostream& os, const Hand& hand)
{
    os << "Hand contains:\n";
    const Card* cards = hand.getHand(); // Get the array of cards
    for (int i = 0; i < 7; ++i) { // A hand can hold up to 7 cards
        os << cards[i] << "\n"; // Use the overloaded operator for Card
    }
    return os;
}

// Setter for the hand of cards
void Hand::setHand(const Card hand[])
{
    for (int i = 0; i < 7; ++i)
    {
        handOfCards[i] = hand[i]; // Copy each card from the input array
    }
}

// Getter for the hand of cards
const Card* Hand::getHand() const
{
    return handOfCards; // Return the array of cards
}

// Method to set a specific card at a given index
void Hand::setCardAt(int index, const Card& card)
{
    if (index >= 0 && index < 7) // Make sure the index is valid
    {
        handOfCards[index] = card;  // Set the card at the specified index
    }
}

// Method to get a card at a specific index
const Card& Hand::getCardAt(int index) const
{
    if (index < 0 || index >= 7)
    {
        throw std::out_of_range("Index out of bounds"); // Make sure the index is valid
    }
    return handOfCards[index];  // Return the card at the specified index
}


