#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map *MapLoader::loadMap(const std::string &filename)
{
    // Create a new Map object
    Map *map = new Map();

    // Call the parsing function to read the map file
    parseMapFile(filename, map);

    return map;
}

// TODO: the following logic is not totally accurate.
// For example, the map txt file has numbers after each territory; the following approach does not consider them.
// I need to ask the professor to explain the syntax of the map txt files the code should read.
void MapLoader::parseMapFile(const std::string &filename, Map *map)
{
    std::ifstream file(filename); // ifstream is a stream class to read from files

    // validates file has opened
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open map file." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        std::istringstream iss(line); // Initializes an input string stream with the current line
        std::string type;

        iss >> type; // extracts first token (word) from stream

        // Parse continents
        if (type == "[Continents]")
        {
            while (getline(file, line) && !line.empty())
            {
                std::string continentName;
                iss.str(line);
                iss >> continentName;
                map->addContinent(new Continent(continentName));
            }
        }

        // Parse territories
        else if (type == "[Territories]")
        {
            while (getline(file, line) && !line.empty())
            {
                std::string territoryName, continentName;
                iss.str(line);
                iss >> territoryName >> continentName;
                Territory *territory = new Territory(territoryName, continentName);
                map->addTerritory(territory);
            }
        }
    }

    file.close();
}
