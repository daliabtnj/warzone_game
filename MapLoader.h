#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Map.h"
#include <string>
#include <map>

class MapLoader
{
public:
    // Loads a map from a file
    Map *loadMap(const std::string &filename);

private:
    // Helper function to parse the map file
    void parseMapFile(const std::string &filename, Map *map);

    void parseMapFile(const std::string &filename, Map *map);
    bool isFileEmpty(const std::string &filename);
    bool hasRequiredSections(const std::string &filename);
    bool isValidFormat(const std::string &filename);
    // map to store the territoyry and its pointers to resolve mapping issue
    std::map<std::string, Territory *> territoryMap;
};

#endif // MAPLOADER_H
