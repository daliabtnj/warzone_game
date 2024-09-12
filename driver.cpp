#include "MapLoader.h"
#include <iostream>

void testLoadMaps()
{
    // Create a MapLoader object
    MapLoader loader;

    // Test loading a valid map
    Map *map = loader.loadMap("valid_map.map"); // TODO: replace this with a valid map file
    if (map != nullptr)
    {
        std::cout << *map << std::endl;
        std::cout << "Is the map valid? " << (map->validate() ? "Yes" : "No") << std::endl;
        delete map;
    }

    // Test loading an invalid map
    map = loader.loadMap("invalid_map.map");
    if (map != nullptr)
    {
        std::cout << *map << std::endl;
        std::cout << "Is the map valid? " << (map->validate() ? "Yes" : "No") << std::endl;
        delete map;
    }
}

int main()
{
    testLoadMaps();
    return 0;
}
