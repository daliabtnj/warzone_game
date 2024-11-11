#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"

/*Class command must be implemented due to the fact that command is an object
that contains two strings (what is the command ? and what is its effect)*/

class Command
{
public:
    // initilaize the object with the command Text
    //  we dont know the effecft of the command before, do doesnt make sense to include it now
    Command(std::string commandText);
    ~Command();
    // getter for the text
    void saveEffect(const std::string &effect);

    std::string getCommandText() const { return *commandText; }
    std::string getEffect() const { return *effect; }

    // function to return arguments
    std::string getArgument() const { return argument ? *argument : ""; }
    // setter for arguemnts
    void setArgument(const std::string &arg);

private:
    // pointer data members
    std::string *commandText;
    std::string *effect;

    // so we are adding a string of arguments for loadmap and addplayer
    std::string *argument;
};

class CommandProcessor
{
public:
    // constructors and destructors
    CommandProcessor();
    CommandProcessor(std::string *currentState)
        : currentState(currentState), loadedMap(nullptr) {}
    ~CommandProcessor();

    Command *getCommand();

    // to make it accessible to FileCommandProcessorAdapter
    void saveCommand(const std::string &commandText);
    // to make it accessible to driver
    void readCommand();
    void printCommands() const;
    bool validate(const std::string &commandText, const std::string &argument);

private:
    std::vector<Command *> commands; // list of commands
    std::string *currentState;
    std::unique_ptr<Map> loadedMap; // Pointer to the currently loaded map
    std::vector<Player> players;    // List of players in the game
};

// Class fileCommandProcessorAdapter:

class FileCommandProcessorAdapter
{
public:
    // constructor and destructor
    FileCommandProcessorAdapter(const std::string &filename);
    ~FileCommandProcessorAdapter();

    Command *getCommand();

private:
    std::ifstream fileStream;
    CommandProcessor *commandProcessor;
};

#endif