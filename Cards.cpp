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
    type = EMPTY; // Initialize the card type to EMPTY
}

// Constructor that initializes the card with a specific CardType
Card::Card(CardType t)
{
    type = t; // Set the card type
}

// Copy constructor for the Card class
Card::Card(const Card &other)
{
    type = other.type; // Copy the type from another card
}

// Assignment operator overload for the Card class
Card &Card::operator=(const Card &other)
{
    if (this != &other)
    {                      // Self-assignment check
        type = other.type; // Copy the type
    }
    return *this; // Return the current object
}

// Overloaded output operator for the Card class
std::ostream &operator<<(std::ostream &os, const Card &card)
{
    if (card.getType() == Card::EMPTY)
        return os << ""; // Return an empty string for an EMPTY card
    os << "Card Type: "; // Print the card type
    switch (card.getType())
    {
    case Card::BOMB:
        os << "BOMB ";
        break;
    case Card::REINFORCEMENT:
        os << "REINFORCEMENT ";
        break;
    case Card::BLOCKADE:
        os << "BLOCKADE ";
        break;
    case Card::AIRLIFT:
        os << "AIRLIFT ";
        break;
    case Card::DIPLOMACY:
        os << "DIPLOMACY ";
        break;
    }
    return os; // Return the output stream
}

// Equality operator overload to compare two Card objects
bool Card::operator==(const Card &other) const
{
    return this->type == other.getType(); // Compare the card types
}

// Setter for the card type
void Card::setType(CardType t)
{
    type = t; // Set the card type
}

// Getter for the card type
Card::CardType Card::getType() const
{
    return type; // Return the card type
}

// Method to play the card, affecting the player's hand and the deck
void Card::play(Hand &hand, Deck &deck, Player &player)
{
    // Find the card in the player's hand
    for (int i = 0; i < 7; ++i)
    {
        if (hand.getHand()[i] == *this)
        {
            // Create and issue a specific order based on card type
            Order *order = nullptr;
            switch (this->type)
            {
            case BOMB:
                order = new BombOrder();
                break;
            case REINFORCEMENT:
                order = new DeployOrder(); // Assuming DeployOrder for reinforcements
                break;
            case AIRLIFT:
                order = new AirliftOrder();
                break;
            case BLOCKADE:
                order = new BlockadeOrder();
                break;
            case DIPLOMACY:
                order = new NegotiateOrder();
                break;
            default:
                std::cout << "Unknown card type!\n";
                return;
            }

            // Issue the order to the player
            if (order != nullptr)
            {
                player.issueOrder(order);
            }

            // Find the first empty slot in the deck to return the card
            for (int j = 0; j < 40; ++j)
            {
                if (deck.getDeck()[j].getType() == Card::EMPTY)
                {
                    deck.deckOfCards[j] = *this;
                    hand.setCardAt(i, Card(Card::EMPTY)); // Remove the card from the hand
                    std::cout << player.getName() << " played " << *this << ", issued an order, and returned it to the deck.\n\n";
                    return; // Exit early since the card is now played
                }
            }

            // If no empty slot is found in the deck
            std::cout << "No empty slot in the deck!\n";
            return;
        }
    }
    std::cout << "Card not found in hand!\n";
}

////////////////////////////////////

// Default constructor for the Deck class
Deck::Deck()
{
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = Card(); // Initialize each card in the deck to EMPTY
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
Deck::Deck(const Deck &other)
{
    // Copy each card individually
    for (int i = 0; i < 40; ++i)
    {
        deckOfCards[i] = other.deckOfCards[i]; // Properly copy each element
    }
}

// Assignment operator overload for the Deck class
Deck &Deck::operator=(const Deck &other)
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
std::ostream &operator<<(std::ostream &os, const Deck &deck)
{
    os << "--------------\nDeck contains:\n--------------\n";
    int count = 0; // Counter to track the number of cards printed on the current line
    for (const auto &card : deck.deckOfCards)
    {
        // Skip the card if it's EMPTY
        if (card.getType() == Card::EMPTY)
        {
            continue; // Skip to the next card
        }

        os << card; // Use the overloaded operator for Card
        count++;

        // Print a newline after every 5 cards
        if (count % 5 == 0)
        {
            os << '\n';
        }
        else
        {
            os << ", "; // Add a comma and space between cards on the same line
        }
    }

    // If there are no cards printed, mention that
    if (count == 0)
    {
        os << "No cards available.\n"; // Optional: Handle the case when no cards are printed
    }
    else
    {
        os << '\n'; // Add a newline at the end of the printed cards
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
const Card *Deck::getDeck() const
{
    return deckOfCards;
}

// Method to draw a card from the deck and add it to the player's hand
void Deck::draw(Hand &hand)
{
    const Card *currentHand = hand.getHand();
    int cardCount = 0;

    // Count how many cards are in the hand
    while (cardCount < 7 && currentHand[cardCount].getType() != Card::EMPTY)
    {
        cardCount++;
    }

    // Draw a card if the hand is not full
    if (cardCount < 7)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 39);

        // Keep trying to draw a card until we find one that isn't EMPTY
        int randomIndex;
        do
        {
            randomIndex = distr(gen);
        } while (deckOfCards[randomIndex].getType() == Card::EMPTY);

        // Add the drawn card to the hand
        hand.setCardAt(cardCount, deckOfCards[randomIndex]);
        deckOfCards[randomIndex] = Card(Card::EMPTY); // Mark the deck slot as empty
    }
    else
    {
        std::cout << "Hand is full. Cannot draw more cards.\n";
    }
}
////////////////////////////////////

// Default constructor for the Hand class
Hand::Hand()
{
    for (int i = 0; i < 5; ++i) // Player starts with 5 cards, but can have a maximum of 7 cards
    {
        handOfCards[i] = Card(); // Initialize each card in the hand to EMPTY
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
Hand::Hand(const Hand &other)
{
    // Copy each card individually
    for (int i = 0; i < 7; ++i)
    {
        handOfCards[i] = other.handOfCards[i]; // Properly copy each element
    }
}

// Assignment operator overload for the Hand class
Hand &Hand::operator=(const Hand &other)
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
std::ostream &operator<<(std::ostream &os, const Hand &hand)
{
    os << "\nHand contains:\n--------------\n";
    const Card *cards = hand.getHand();
    bool isEmpty = true; // Flag to check if hand is empty

    for (int i = 0; i < 7; ++i)
    {
        if (cards[i].getType() != Card::EMPTY)
        {
            os << cards[i] << "\n"; // Output non-empty cards
            isEmpty = false;        // Found a card, so hand is not empty
        }
    }

    // If no non-empty cards were found, display the empty message
    if (isEmpty)
    {
        os << "Nothing, there are no cards!\n\n";
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
const Card *Hand::getHand() const
{
    return handOfCards; // Return the array of cards
}

// Method to set a specific card at a given index
void Hand::setCardAt(int index, const Card &card)
{
    if (index >= 0 && index < 7) // Make sure the index is valid
    {
        handOfCards[index] = card; // Set the card at the specified index
    }
}

// Method to get a card at a specific index
const Card &Hand::getCardAt(int index) const
{
    if (index < 0 || index >= 7)
    {
        throw std::out_of_range("Index out of bounds"); // Make sure the index is valid
    }
    return handOfCards[index]; // Return the card at the specified index
}
