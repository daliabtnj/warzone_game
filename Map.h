#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>

// Forward declaration of Player class
class Player;

// Territory class represents a territory in the map
class Territory
{
public:
    Territory(std::string name, std::string continentName, int initialArmies = 0); // Constructor
    Territory(const Territory &other);                                             // Copy constructor
    Territory &operator=(const Territory &other);                                  // Assignment operator
    ~Territory();                                                                  // Destructor

    // Getters
    std::string getName() const;
    std::string getContinentName() const;
    Player *getOwner() const;
    int getArmies() const;

    // Setters
    void setOwner(Player *p);
    void setArmies(int armies);

    // Adds an adjacent territory to the current territory
    void addAdjacentTerritory(Territory *t);

    // Returns the list of adjacent territories
    std::vector<Territory *> getAdjacents() const;

    // Overloaded stream insertion operator for printing a Territory
    friend std::ostream &operator<<(std::ostream &os, const Territory &t);

private:
    std::string *name;                             // Name of the territory
    std::string *continentName;                    // Name of the continent the territory belongs to
    std::vector<Territory *> *adjacentTerritories; // Adjacent territories (graph edges)

    Player *owner; // Pointer to the player who owns the territory
    int *armies;   // Number of armies in the territory
};

// Continent class represents a continent as a subgraph of territories
class Continent
{
public:
    Continent(std::string name, int bonus);       // Constructor
    Continent(const Continent &other);            // Copy constructor
    Continent &operator=(const Continent &other); // Assignment operator
    ~Continent();                                 // Destructor

    // Getters
    std::string getName() const;
    int getBonus() const;
    std::vector<Territory *> getTerritories() const;

    void addTerritory(Territory *t); // Adds territory to continent

private:
    std::string *name; // Continent name
    int bonus;
    std::vector<Territory *> *territories; // List of territories in continent
};

// Map class represents the whole map
class Map
{
public:
    Map();                            // Constructor
    Map(const Map &other);            // Copy constructor
    Map &operator=(const Map &other); // Assignment operator
    ~Map();                           // Destructor

    void addTerritory(Territory *t); // Adds territory to map
    void addContinent(Continent *c); // Adds continent to map
    bool validate();                 // Validates map

    friend std::ostream &operator<<(std::ostream &os, const Map &m); // Operator overload to print map

private:
    std::vector<Territory *> *territories; // List of map territories
    std::vector<Continent *> *continents;  // List of map continents

    bool isConnected();            // Checks if all map territories are connected
    bool areContinentsConnected(); // Checks if all map continents are connected
};

#endif // MAP_H
