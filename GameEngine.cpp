#include "GameEngine.h"

GameEngine::GameEngine() : currentState(STARTUP) {}

void GameEngine::transition(const std::string& command) {
    if ((currentState == STARTUP && command == "loadmap") || (currentState == MAP_LOADED && command == "loadmap")) {
        loadMap();
        currentState = MAP_LOADED;
    } else if (currentState == MAP_LOADED && command == "validatemap") {
        validateMap();
        currentState = MAP_VALIDATED;
    } else if ((currentState == MAP_VALIDATED && command == "addplayer") || (currentState == PLAYERS_ADDED && command == "addplayer")) {
        addPlayer();
        currentState = PLAYERS_ADDED;
    } else if (currentState == PLAYERS_ADDED && command == "assigncountries") {
        assignCountries();
        currentState = ASSIGN_REINFORCEMENTS;
    } else if ((currentState == ASSIGN_REINFORCEMENTS && command == "issueorder") || (currentState == ISSUE_ORDERS && command == "issueorder")) {
        issueOrder();
        currentState = ISSUE_ORDERS;
    } else if ((currentState == ISSUE_ORDERS && command == "executeorder") || (currentState == EXECUTE_ORDERS && command == "executeorder")) {
        executeOrder();
        currentState = EXECUTE_ORDERS;
    } else if (currentState == EXECUTE_ORDERS && command == "win") {
        winGame();
        currentState = WIN;
    } else {
        std::cout << "Invalid command for current state." << std::endl;
    }
}

void GameEngine::printState() const {
    std::cout << "Current state: ";
    switch (currentState) {
        case STARTUP: std::cout << "STARTUP"; break;
        case MAP_LOADED: std::cout << "MAP LOADED"; break;
        case MAP_VALIDATED: std::cout << "MAP VALIDATED"; break;
        case PLAYERS_ADDED: std::cout << "PLAYERS ADDED"; break;
        case ASSIGN_REINFORCEMENTS: std::cout << "ASSIGN REINFORCEMENTS"; break;
        case ISSUE_ORDERS: std::cout << "ISSUE ORDERS"; break;
        case EXECUTE_ORDERS: std::cout << "EXECUTE ORDERS"; break;
        case WIN: std::cout << "WIN"; break;
    }
    std::cout << std::endl;
}

void GameEngine::loadMap() {
    std::cout << "Loading map..." << std::endl;
}

void GameEngine::validateMap() {
    std::cout << "Validating map..." << std::endl;
}

void GameEngine::addPlayer() {
    std::cout << "Adding players..." << std::endl;
}

void GameEngine::assignCountries() {
    std::cout << "Assigning countries..." << std::endl;
}

void GameEngine::issueOrder() {
    std::cout << "Issuing order..." << std::endl;
}

void GameEngine::executeOrder() {
    std::cout << "Executing order..." << std::endl;
}

void GameEngine::winGame() {
    std::cout << "Winning the game..." << std::endl;
}