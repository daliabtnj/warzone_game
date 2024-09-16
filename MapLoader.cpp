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
        std::istringstream iss(line); 
        std::string type;

        // extracts first  word
        iss >> type; 

        // Parse continents + Update with the BONUS VALUES
        if (type == "[Continents]")
        {
            while (getline(file, line) && !line.empty())
            {
                std::istringstream iss(line); 
                std::string continentInfo, continentName;
                int bonus = 0;

                // Split at equalizty sign
                if (std::getline(iss, continentInfo, '='))
                {
                    continentName = continentInfo; 

                   
                    if (iss >> bonus)
                    {
                        // Add the continent with the name and the bonus value
                        map->addContinent(new Continent(continentName, bonus));
                    }
                    else
                    {
                        std::cerr << "Error: Invalid format for continent bonus." << std::endl;
                    }
                }
            }
        }


        // Parse the territories
else if (type == "[Territories]"){
    while (getline(file, line) && !line.empty()){
        std::istringstream iss(line);
        std::string territoryName, continentName;
        std::string token;

        // read name of the territory
        std::getline(iss, territoryName, ',');

        // Ignore x and y coordinates
        std::getline(iss, token, ','); // x coordinate
        std::getline(iss, token, ','); // y coordinate

        // Get the continent name
        std::getline(iss, continentName, ',');

        // Create the Territory object
        Territory *territory = new Territory(territoryName, continentName);

        // addd the territory to the map and the territoryMap 
        map->addTerritory(territory);

        //store the territory in the map with a pointer (territory) associated with it
        territoryMap[territoryName] = territory; 
        }
       }
    }


        file.clear();  
        file.seekg(0); 

while (getline(file, line))
{
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "[Territories]")
    {
        while (getline(file, line) && !line.empty())
        {
            std::istringstream iss(line);
            std::string territoryName, token;

            // read the territory name
            std::getline(iss, territoryName, ',');

            // ignore  x and y coordinates
            std::getline(iss, token, ','); 
            std::getline(iss, token, ','); 
            std::getline(iss, token, ','); 
            

            Territory *currentTerritory = territoryMap[territoryName]; 

            // now add adjacents territories
            while (std::getline(iss, token, ','))
            {
                auto it = territoryMap.find(token); 
                if (it != territoryMap.end()) {
                    currentTerritory->addAdjacentTerritory(it->second);  // Add the adjacent territory
                } else {
                    std::cerr << "Error: Could not resolve adjacent territory: " << token << std::endl;
                }
            }
        }
    }
}

    file.close();
}
