#include "CommandProcessing.h"
#include <iostream>
#include <algorithm> // for std::shuffle
#include <random>    // for random device and mt19937
#include <chrono>    // for seeding random device with time
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"

// define unintialized constructors and
// make sure the state is start in the beginning
CommandProcessor::CommandProcessor()
{
    currentState = new std::string("start");
}
CommandProcessor::~CommandProcessor()
{
    // sicne we are dealing with pointers use delete and make suere all commands are deleted !
    delete currentState;
    for (Command *cmd : commands)
    {
        delete cmd;
    }
    commands.clear();
}

// implementation of the read command
void CommandProcessor::readCommand()
{
    std::string commandText;
    std::cout << "Enter the command: ";
    // we put the input in the string we created
    std::getline(std::cin, commandText);
    // now use the savecommand option
    saveCommand(commandText);
}

// pass in a reference to avoid making a copy
void CommandProcessor::saveCommand(const std::string &commandText)
{
    // extract the commands:

    std::string cmd, arg;
    // find index of the space that acts as a delimiter (so command <argument>)
    size_t space = commandText.find(' ');

    if (space != std::string::npos)
    {
        // store whats before the command in cmd
        cmd = commandText.substr(0, space);
        arg = commandText.substr(space + 1);
    }
    else
    {
        // if no argument is provided then
        cmd = commandText;
    }

    // Check first if the command is valid in that state:
    bool isValid = validate(cmd, arg);
    // create that command as the object it should be
    Command *newCommand = new Command(cmd);

    // check if the cmd is loadmap or addplayer to add the argument
    if ((cmd == "loadmap" || cmd == "addplayer") && !arg.empty())
    {
        newCommand->setArgument(arg);
    }
    // display message if is valid or not
    std::string effect = isValid ? "Command accepted: State transitioned to " + *currentState
                                 : "Invalid command for the current state: " + *currentState;

    // save the effect as parts of the object
    newCommand->saveEffect(effect);

    // add command to the vector  commands only if command is valid
    // we don't care if it is valid or not because assignments says to save it regardless
    commands.push_back(newCommand);
}

Command::Command(std::string commandText)
{
    this->commandText = new std::string(commandText);
    this->effect = new std::string();
    // just make the argument nullptr for now
    this->argument = nullptr;
}

Command::~Command()
{
    delete commandText;
    delete effect;
    // avoid memory leak and delete only if argument exists
    if (argument)
        delete argument;
}

// getCommand() implementatiuon

Command *CommandProcessor::getCommand()
{
    if (!commands.empty())
    {
        // retrives last elements from the vector
        return commands.back();
    }
    else
    {
        // do not forget to add a catch block iun the main...
        throw std::runtime_error("No command available");
    }
}

void Command::saveEffect(const std::string &effect)
{
    if (this->effect)
    {
        *(this->effect) = effect;
    }
    else
    {
        this->effect = new std::string(effect);
    }
}

// setter for setting arguments
void Command::setArgument(const std::string &arg)
{
    if (!argument)
    {
        argument = new std::string(arg);
    }
    else
    {
        *argument = arg;
    }
}

bool CommandProcessor::validate(const std::string &commandText, const std::string &argument)
{
    if (commandText == "loadmap")
    {
        if (*currentState == "start" && !argument.empty())
        {
            MapLoader loader;
            loadedMap.reset(loader.loadMap("./maps/" + argument));
            if (loadedMap)
            {
                std::cout << "Map loaded successfully: " << argument << std::endl;
                *currentState = "maploaded";
                return true;
            }
            else
            {
                std::cerr << "Failed to load map: " << argument << std::endl;
                return false;
            }
        }
    }
    else if (commandText == "validatemap")
    {
        if (*currentState == "maploaded" && argument.empty() && loadedMap)
        {
            if (loadedMap->validate())
            {
                std::cout << "Map is valid." << std::endl;
                *currentState = "mapvalidated";
                return true;
            }
            else
            {
                std::cerr << "Map validation failed." << std::endl;
                return false;
            }
        }
    }
    else if (commandText == "addplayer")
    {
        if ((*currentState == "mapvalidated" || *currentState == "playersadded") && !argument.empty() && players.size() < 6)
        {
            players.emplace_back(argument);
            std::cout << "Player added: " << argument << std::endl;
            if (players.size() >= 2)
            {
                *currentState = "playersadded";
            }
            return true;
        }
        else if (players.size() >= 6)
        {
            std::cerr << "Cannot add more than 6 players." << std::endl;
            return false;
        }
    }
    else if (commandText == "gamestart")
    {
        if (*currentState == "playersadded" && argument.empty() && players.size() >= 2)
        {
            // Shuffle player order
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(players.begin(), players.end(), std::default_random_engine(seed));
            std::cout << "Players' turn order randomized:" << std::endl;
            for (const Player &player : players)
            {
                std::cout << player.getName() << " ";
            }
            std::cout << std::endl;

            // Distribute territories
            const std::vector<Territory *> &territories = loadedMap->getTerritories();
            size_t numPlayers = players.size();
            for (size_t i = 0; i < territories.size(); ++i)
            {
                players[i % numPlayers].addTerritory(territories[i]);
            }
            std::cout << "Territories have been distributed among players." << std::endl;

            // give 50 armies/player
            // each player draws 2 cards

            *currentState = "assignreinforcement";
            return true;
        }
        else
        {
            std::cerr << "Game cannot start without 2-6 players or in incorrect state." << std::endl;
            return false;
        }
    }
    return false;
}

// printing the commands just for validation purposes:
void CommandProcessor::printCommands() const
{
    if (commands.empty())
    {
        std::cout << "No commands have been added yet." << std::endl;
        return;
    }

    std::cout << "\n--- List of Stored Commands ---" << std::endl;
    for (const Command *cmd : commands)
    {
        std::cout << "Command: " << cmd->getCommandText()
                  << ", Argument: " << (cmd->getArgument().empty() ? "None" : cmd->getArgument())
                  << ", Effect: " << cmd->getEffect() << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
}

// CODE FOR FileCommandProcessor:

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string &filename)
{
    fileStream.open(filename);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    commandProcessor = new CommandProcessor();
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }
    delete commandProcessor;
}

Command *FileCommandProcessorAdapter::getCommand()
{
    std::string commandText;
    if (std::getline(fileStream, commandText))
    {
        commandProcessor->saveCommand(commandText);
        return commandProcessor->getCommand();
    }
    else
    {
        throw std::runtime_error("No more commands available in file");
    }
}
