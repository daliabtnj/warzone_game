#include "Cards.h"
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Order.h"
#include <algorithm>

void testCards()
{
    // Create Card objects of various types for testing
    Card card1 = Card(Card::BOMB);
    Card card2 = Card(Card::REINFORCEMENT);
    Card card3 = Card(Card::AIRLIFT);
    Card card4 = Card(Card::BLOCKADE);
    Card card5 = Card(Card::DIPLOMACY);
    Card card6 = Card(Card::BOMB);
    Card card7 = Card(Card::REINFORCEMENT);
    Card card8 = Card(Card::AIRLIFT);
    Card card9 = Card(Card::DIPLOMACY);
    Card card10 = Card(Card::BLOCKADE);
    Card card11 = Card(Card::BOMB);
    Card card12 = Card(Card::BLOCKADE);
    Card card13 = Card(Card::BOMB);
    Card card14 = Card(Card::REINFORCEMENT);
    Card card15 = Card(Card::AIRLIFT);
    Card card16 = Card(Card::BLOCKADE);
    Card card17 = Card(Card::DIPLOMACY);
    Card card18 = Card(Card::BOMB);
    Card card19 = Card(Card::REINFORCEMENT);
    Card card20 = Card(Card::AIRLIFT);
    Card card21 = Card(Card::BOMB);
    Card card22 = Card(Card::REINFORCEMENT);
    Card card23 = Card(Card::AIRLIFT);
    Card card24 = Card(Card::BLOCKADE);
    Card card25 = Card(Card::DIPLOMACY);
    Card card26 = Card(Card::BOMB);
    Card card27 = Card(Card::REINFORCEMENT);
    Card card28 = Card(Card::AIRLIFT);
    Card card29 = Card(Card::DIPLOMACY);
    Card card30 = Card(Card::BLOCKADE);
    Card card31 = Card(Card::BOMB);
    Card card32 = Card(Card::BLOCKADE);
    Card card33 = Card(Card::BOMB);
    Card card34 = Card(Card::REINFORCEMENT);
    Card card35 = Card(Card::AIRLIFT);
    Card card36 = Card(Card::BLOCKADE);
    Card card37 = Card(Card::DIPLOMACY);
    Card card38 = Card(Card::BOMB);
    Card card39 = Card(Card::REINFORCEMENT);
    Card card40 = Card(Card::AIRLIFT);

    // Initialize an array to hold all the card objects created above, used for the Deck object
    Card allCards[60] = {card1, card2, card3, card4, card5, card6, card7, card8, card9, card10, card11, card12, card13, card14, card15, card16, card17, card18, card19, card20, card21, card22, card23, card24, card25, card26, card27, card28, card29, card30, card31, card32, card33, card34, card35, card36, card37, card38, card39, card40};

    // Create a Deck object using the allCards array
    Deck testDeck(allCards);

    // Output the initial state of the deck
    std::cout << testDeck;

    // Create a Hand object to hold cards drawn from the deck
    Hand testHand;

    // Draw 5 cards from the deck and add them to the hand
    for(int i = 0; i < 5; i++)
    {
        testDeck.draw(testHand);
    }

    // Output the state of the hand and the deck after drawing five cards
    std::cout << testHand;
    std::cout << testDeck;

    Card temp;  // Temporary card object for holding drawn cards

    // Play each of the drawn cards from the hand
    for(int i = 0; i < 5; i ++)
    {
        temp = testHand.getCardAt(i);   // Get the card at index i
        temp.play(testHand, testDeck);  // Play the card, affecting both the hand and the deck
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
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Cards.cpp CardsDriver.cpp 
*/

//code works