#include "MapDriver.h"       // For testLoadMaps()
#include "PlayerDriver.h"    // For testPlayers()
#include "OrdersDriver.h"    // For testOrdersLists()
#include "CardsDriver.h"     // For testCards()
#include "GameEngineDriver.h" // For testGameStates()

#include <iostream>

int main() {
    // Part 1: Map loading and validation
    std::cout << "=== Part 1: Map Loader and Validation ===" << std::endl;
    testLoadMaps();
    
    // Part 2: Player functionalities
    std::cout << "\n=== Part 2: Player functionalities ===" << std::endl;
    testPlayers();

    // Part 3: Orders and OrdersList functionalities
    std::cout << "\n=== Part 3: Orders and OrdersList functionalities ===" << std::endl;
    testOrdersLists();

    // Part 4: Cards and Deck functionalities
    std::cout << "\n=== Part 4: Cards and Deck functionalities ===" << std::endl;
    testCards();

    // Part 5: GameEngine state transitions
    std::cout << "\n=== Part 5: Game Engine State Transitions ===" << std::endl;
    testGameStates();

    return 0;
}