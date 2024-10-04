#include "Cards.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Order.h"
#include <algorithm>
#include <vector>

void testCards()
{
    // Create an array of CardTypes for testing
    Card::CardType cardTypes[] = {
        Card::BOMB, Card::REINFORCEMENT, Card::AIRLIFT, Card::BLOCKADE, Card::DIPLOMACY};

    // Initialize an array to hold all the card objects created above, used for the Deck object
    Card allCards[40];

    // Use a loop to fill the allCards array by cycling through the card types
    for (int i = 0; i < 40; ++i)
    {
        allCards[i] = Card(cardTypes[i % 5]); // Cycles through 5 card types
    }

    // Create a Deck object using the allCards array
    Deck testDeck(allCards);

    // Output the initial state of the deck
    std::cout << testDeck;

    // Create a Hand object to hold cards drawn from the deck
    Hand testHand;

    // Create a Player object for the play() method
    Player testPlayer("Bo7");

    // Draw 5 cards from the deck and add them to the hand
    for (int i = 0; i < 5; i++)
    {
        testDeck.draw(testHand);
    }

    // Output the state of the hand and the deck after drawing five cards
    std::cout << testHand;
    std::cout << testDeck;

    Card temp; // Temporary card object for holding drawn cards

    // Play each of the drawn cards from the hand
    for (int i = 0; i < 5; i++)
    {
        temp = testHand.getCardAt(i);              // Get the card at index i
        temp.play(testHand, testDeck, testPlayer); // Play the card, affecting both the hand and the deck
    }

    // Output the final state of the hand and the deck after playing the cards
    std::cout << testHand;
    std::cout << testDeck;
}

int main()
{
    testCards();
    return 0;
}

/*
To compile:
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Cards.cpp CardsDriver.cpp Player.cpp
*/