#include "MapLoader.h"
#include "MapDriver.h"
#include <iostream>

void testLoadMaps()
{
    // Create a MapLoader object
    MapLoader loader;

    // Test loading a valid map
    Map *map = loader.loadMap("./maps/valid_map.txt");
    if (map != nullptr)
    {
        std::cout << *map << std::endl;
        std::cout << "Is the map valid? " << (map->validate() ? "Yes" : "No") << std::endl;
        delete map;
    }

    // // Test loading an invalid map
    // map = loader.loadMap("invalid_map.txt");
    // if (map != nullptr)
    // {
    //     std::cout << *map << std::endl;
    //     std::cout << "Is the map valid? " << (map->validate() ? "Yes" : "No") << std::endl;
    //     delete map;
    // }
}

// int main()
// {
//     testLoadMaps();
//     return 0;
// }
