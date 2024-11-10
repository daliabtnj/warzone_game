#include "CommandProcessing.h"
#include <iostream>
#include <limits>

// Compile with: g++ -std=c++11 -o warzone CommandProcessing.cpp CommandProcessingDriver.cpp

int main() {
    CommandProcessor* processor = new CommandProcessor();

    try {
        std::cout << "Choose input method (1 for console input, 2 for file input): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        if (choice == 1) {
            std::cout << "Processing commands from console input:" << std::endl;
            std::string commandText;

            // Loop for console input
            while (true) {
                std::cout << "Enter the command (or type 'exit' to finish): ";
                std::getline(std::cin, commandText);

                if (commandText == "exit") break;

                // Save the command
                processor->saveCommand(commandText);

                // Retrieve and print the last processed command
                try {
                    Command* command = processor->getCommand();
                    if (command) {
                        std::cout << "Processed Command: " << command->getCommandText() << std::endl;
                        std::cout << "Command Effect: " << command->getEffect() << std::endl;
                    }
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                // Print all stored commands in the vector after each command
                processor->printCommands();
            }
        } else if (choice == 2) {
            // File input processing
            std::string filename;
            std::cout << "Enter the filename: ";
            std::getline(std::cin, filename);

            FileCommandProcessorAdapter* fileProcessor = nullptr;
            try {
                fileProcessor = new FileCommandProcessorAdapter(filename);

                // Loop through commands in the file
                while (true) {
                    Command* fileCommand = fileProcessor->getCommand();
                    if (fileCommand) {
                        std::cout << "Processed Command: " << fileCommand->getCommandText() << std::endl;
                        std::cout << "Command Effect: " << fileCommand->getEffect() << std::endl;
                    }

                    // Print all stored commands in the vector after each command
                    processor->printCommands();
                }
            } catch (const std::runtime_error& e) {
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