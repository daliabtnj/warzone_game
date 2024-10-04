#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <string>
#include <iostream>

// Function to test all the player functionnalities
void testPlayers() {

    // creating a few territories to test
    Territory* t1 = new Territory("Lebanon", "Middle East", 8);
    Territory* t2 = new Territory("Syria", "Middle East", 10);
    Territory* t3 = new Territory("Greece", "Europe", 6);
    Territory* t4 = new Territory("United States", "America", 8);
    Territory* t5 = new Territory("England", "Europe", 5);

    // create cards
    Card* bomb = new Card(Card::BOMB);
    Card* reinforcement = new Card(Card::REINFORCEMENT);
    Card* blockade = new Card(Card::BLOCKADE);

    Player player1("didou"); // create a player
    Player player2;
    player1.addTerritory(t1);
    player1.addTerritory(t2);
    player1.addTerritory(t3);
    player2.addTerritory(t4);
    player2.addTerritory(t5);

    std::cout << "\n*******************************************\n";

    // add cards to player's hand
    std::cout << "\nADD CARDS TO PLAYER'S HAND\n" << std::endl;

    player1.addCards(bomb);
    player1.addCards(reinforcement);
    player1.addCards(blockade);

    // Display the player's hand
    player1.displayHand();

    std::cout << "\n*******************************************\n";


    // test to defend
    std::cout << "\nTEST METHOD TO DEFEND\n\n";
    player1.toDefend();

    std::cout << "\n*******************************************\n";


    // test to attack
    std::cout << "\nTEST METHOD TO ATTACK\n\n";
    player2.toAttack();

    std::cout << "\n*******************************************\n";

    // test issue order
    std::cout << "\nTEST METHOD TO ISSUE ORDERS\n\n";
    player1.issueOrder(new DeployOrder());      // Issue a Deploy order
    player1.issueOrder(new AdvanceOrder());     // Issue an Advance order
    player1.issueOrder(new BombOrder());        // Issue a Bomb order
    player1.issueOrder(new BlockadeOrder());
    player1.issueOrder(new AirliftOrder());
    player1.issueOrder(new NegotiateOrder());


    std::cout << "\n*******************************************\n";
  
    // Output player status
    std::cout << "\nOUTPUT PLAYER'S STATUS\n\n";
    std::cout << player1 << std::endl;  // Print player information using overloaded << operator
    std::cout << player2 << std::endl;  
    std::cout << "\n\n Code works, stop making wars - peace out";
    std::cout << "\n******************************************";
    std::cout << "\n<3  <3  <3  <3  <3  <3  <3  <3  <3  <3  <3\n\n";
}

int main() {
    testPlayers(); 
    return 0;
}

/*

Compile code : 
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Player.cpp PlayerDriver.cpp Order.cpp Cards.cpp

Run code: 
./warzone

*/ 