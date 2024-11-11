#include "GameEngineDriver.h"
#include "GameEngine.h"
#include <iostream>
#include <string>

void testGameStates()
{
    GameEngine gameEngine;
    std::string command;

    // Display the list of possible commands
    std::cout << "Available commands to transition between states:\n";
    std::cout << "1. loadmap\n";
    std::cout << "2. validatemap\n";
    std::cout << "3. addplayer\n";
    std::cout << "4. assigncountries\n";
    std::cout << "5. issueorder\n";
    std::cout << "6. executeorder\n";
    std::cout << "7. win\n";
    std::cout << "Type 'exit' to quit.\n\n";

    while (true)
    {
        gameEngine.printState();
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "exit")
            break;
        gameEngine.transition(command);
    }
}

void testStartupPhase()
{
    GameEngine gameEngine;
    std::cout << "Starting game setup phase. Use commands to proceed:\n";
    std::cout << "Commands:\n";
    std::cout << " - loadmap <filename>\n";
    std::cout << " - validatemap\n";
    std::cout << " - addplayer <playername>\n";
    std::cout << " - gamestart\n";
    gameEngine.startupPhase();
}

// g++ -std=c++11 -o warzone GameEngine.cpp GameEngineDriver.cpp Map.cpp Maploader.cpp CommandProcessing.cpp Player.cpp Order.cpp Cards.cpp
int main()
{
    // testGameStates();
    testStartupPhase();
    return 0;
}