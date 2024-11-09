#include "CommandProcessing.h"
#include <iostream>
//g++ -std=c++11 -o part1 CommandProcessing.cpp CommandProcessingDriver.cpp

int main() {
    CommandProcessor* processor = new CommandProcessor();
    try {
        std::cout << "Choose input method (1 for console input, 2 for file input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); 

        if (choice == 1) {
            std::cout << "Processing commands from console input:" << std::endl;
            std::string commandText;
            do {
                std::cout << "Enter the command (or type 'exit' to finish): ";
                getline(std::cin, commandText);
                if (commandText == "exit") break;
                processor->saveCommand(commandText);
                Command* command = processor->getCommand();
                std::cout << "Processed Command: " << command->getCommandText() << std::endl;
                std::cout << "Command Effect: " << command->getEffect() << std::endl;
            } while (true);
        } else if (choice == 2) {
            std::string filename;
            std::cout << "Enter the filename: ";
            getline(std::cin, filename);

            FileCommandProcessorAdapter *fileProcessor = new FileCommandProcessorAdapter(filename);
            try {
                while (true) {
                    Command* fileCommand = fileProcessor->getCommand();  
                    std::cout << "Processed Command: " << fileCommand->getCommandText() << std::endl;
                    std::cout << "Command Effect: " << fileCommand->getEffect() << std::endl;
                }
            } catch (std::runtime_error& e) {
                std::cerr << "Error processing file: " << e.what() << std::endl;
            }
            delete fileProcessor;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    delete processor;
    return 0;
}