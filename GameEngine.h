#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <iostream>

class GameEngine {
public:
    enum State {
        STARTUP,
        MAP_LOADED,
        MAP_VALIDATED,
        PLAYERS_ADDED,
        ASSIGN_REINFORCEMENTS,
        ISSUE_ORDERS,
        EXECUTE_ORDERS,
        WIN
    };

    GameEngine();
    void transition(const std::string& command);
    void printState() const;

private:
    State currentState;
    void loadMap();
    void validateMap();
    void addPlayer();
    void assignCountries();
    void issueOrder();
    void executeOrder();
    void winGame();
};

#endif // GAMEENGINE_H