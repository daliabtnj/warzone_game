#include "Player.h"
#include "Map.h"
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

    Player player1("didou"); // create a player
    Player player2;
    player1.addTerritory(t1);
    player1.addTerritory(t2);
    player1.addTerritory(t3);
    player2.addTerritory(t4);
    player2.addTerritory(t5);

    // test to defend
    std::cout << "\nWe will test the method to defend:\n";
    player1.toDefend();

    // test to attack
    std::cout << "\nWe will test the method to attack:\n";
    player2.toAttack();

    // test issue order
    std::cout << "\nWe will test the method to issue orders\n";
    player1.issueOrder();
    player1.issueOrder();
    std::cout << "\n";

    // Output player status
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
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Player.cpp PlayerDriver.cpp

Run code: 
./warzone

*/ 