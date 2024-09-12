#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Map.h"
#include <string>

class MapLoader
{
public:
    // Loads a map from a file
    Map *loadMap(const std::string &filename);

private:
    // Helper function to parse the map file
    void parseMapFile(const std::string &filename, Map *map);
};

#endif // MAPLOADER_H
