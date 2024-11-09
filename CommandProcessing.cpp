#include "CommandProcessing.h"
#include <iostream>

//define unintialized constructors and 
//make sure the state is start in the beginning
CommandProcessor::CommandProcessor() {
    currentState = new std::string("start"); // Allocate memory for currentState
}
CommandProcessor::~CommandProcessor() {
    //sicne we are dealing with pointers use delete and make suere all commands are deleted !
    delete currentState; 
    for (Command* cmd : commands) { 
        delete cmd;
    }
    commands.clear();
}

//implementation of the read command
void CommandProcessor::readCommand(){
    std::string commandText;
    std::cout <<"Enter the command: ";
    //we put the input in the string we created
    std::getline(std::cin, commandText);
    //now use the savecommand option 
    saveCommand(commandText);
    
}

//pass in a reference to avoid making a copy
void CommandProcessor::saveCommand(const std::string& commandText){
    //Check first if the command is valid in that state:
    bool isValid = validate(commandText);
     //create that command as the object it should be 
    Command* newCommand = new Command(commandText);
    //display message if is valid or not
    std::string effect = isValid ? "Command accepted: State transitioned to " + *currentState
                                 : "Invalid command for the current state: " + *currentState;

    //save the effect as parts of the object 
    newCommand->saveEffect(effect);
    
    //add command to the vector  commands only if command is valid
    //we don't care if it is valid or not because assignments says to save it regardless
    commands.push_back(newCommand);


}


Command::Command(std::string commandText) {
    this->commandText = new std::string(commandText);
    this->effect = new std::string();  
}

Command::~Command() {
    delete commandText;
    delete effect;
}

//getCommand() implementatiuon 

Command* CommandProcessor::getCommand(){
    if(!commands.empty()){
        //retrives last elements from the vector
         return commands.back();
    }else {
        //do not forget to add a catch block iun the main... 
        throw std::runtime_error("No command available");
    }
    
}

void Command::saveEffect(const std::string& effect){
    if (this->effect) {
        *(this->effect) = effect; 
    } else {
        this->effect = new std::string(effect); 
    }
}

bool CommandProcessor::validate(const std::string& commandText) {
    if (*currentState == "start" && commandText == "loadmap") {
        *currentState = "maploaded";
        return true;
    } else if (*currentState == "maploaded" && commandText == "validatemap") {
        *currentState = "mapvalidated";
        return true;
    } else if (*currentState == "mapvalidated" && commandText.substr(0, 9) == "addplayer") {
        *currentState = "playersadded";
        return true;
    } else if (*currentState == "playersadded" && commandText == "gamestart") {
        *currentState = "assignreinforcement";
        return true;
    }
    return false;
}


// CODE FOR FileCommandProcessor:

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string& filename) {
    fileStream.open(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    commandProcessor = new CommandProcessor();
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
    delete commandProcessor; 
}

Command* FileCommandProcessorAdapter::getCommand() {
    std::string commandText;
    if (std::getline(fileStream, commandText)) {
        commandProcessor->saveCommand(commandText);
        return commandProcessor->getCommand();
    } else {
        throw std::runtime_error("No more commands available in file");
    }
}


