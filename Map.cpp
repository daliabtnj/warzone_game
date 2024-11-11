#include "Map.h"
#include <iostream>
#include <queue>
#include <set>

// Territory class implementation
Territory::Territory(std::string name, std::string continentName, int initialArmies)
{
    this->name = new std::string(name);
    this->continentName = new std::string(continentName);
    this->adjacentTerritories = new std::vector<Territory *>();
    this->owner = nullptr;                 // No player owns the territory initially
    this->armies = new int(initialArmies); // Initial number of armies (default 0)
}

Territory::Territory(const Territory &other)
{
    this->name = new std::string(*other.name);
    this->continentName = new std::string(*other.continentName);
    this->adjacentTerritories = new std::vector<Territory *>(*other.adjacentTerritories);
    this->owner = other.owner;             // Shallow copy of owner (assuming Player is managed elsewhere)
    this->armies = new int(*other.armies); // Copy the number of armies
}

Territory &Territory::operator=(const Territory &other)
{
    if (this != &other)
    {
        *this->name = *other.name;
        *this->continentName = *other.continentName;
        *this->adjacentTerritories = *other.adjacentTerritories;
        this->owner = other.owner;     // Shallow copy of owner
        *this->armies = *other.armies; // Copy the number of armies
    }
    return *this;
}

Territory::~Territory()
{
    delete name;
    delete continentName;
    delete adjacentTerritories;
    delete armies; // Free memory allocated for the number of armies
}

// Getter for territory name
std::string Territory::getName() const
{
    return *this->name;
}

// Getter for territory's continent name
std::string Territory::getContinentName() const
{
    return *this->continentName;
}

// Getter and setter for player ownership
void Territory::setOwner(Player *p)
{
    this->owner = p;
}

Player *Territory::getOwner() const
{
    return this->owner;
}

// Getter and setter for the number of armies in the territory
int Territory::getArmies() const
{
    return *this->armies;
}

void Territory::setArmies(int armies)
{
    *this->armies = armies;
}

void Territory::addAdjacentTerritory(Territory *t)
{
    adjacentTerritories->push_back(t);
}

std::vector<Territory *> Territory::getAdjacents() const
{
    return *adjacentTerritories;
}

std::ostream &operator<<(std::ostream &os, const Territory &t)
{
    os << "Territory: " << *t.name << ", Continent: " << *t.continentName
       << ", Armies: " << *t.armies
       << ", Owner: " << (t.owner ? "Player assigned" : "No owner");
    return os;
}

bool Territory::operator==(const Territory &other) const
{
    return this->getName() == other.getName(); // Compare based on the territory's name (or another unique identifier)
}

// Continent class implementation
Continent::Continent(std::string name, int bonus)
{
    this->name = new std::string(name);
    this->territories = new std::vector<Territory *>();
    this->bonus = bonus;
}

Continent::Continent(const Continent &other)
{
    this->name = new std::string(*other.name);
    this->territories = new std::vector<Territory *>(*other.territories);
    this->bonus = other.bonus;
}

Continent &Continent::operator=(const Continent &other)
{
    if (this != &other)
    {
        *this->name = *other.name;
        *this->territories = *other.territories;
        this->bonus = other.bonus;
    }
    return *this;
}

Continent::~Continent()
{
    delete name;
    delete territories;
}

std::string Continent::getName() const
{
    return *name;
}
// getter for bonuses
int Continent::getBonus() const
{
    return bonus;
}

void Continent::addTerritory(Territory *t)
{
    territories->push_back(t);
}

std::vector<Territory *> Continent::getTerritories() const
{
    return *territories;
}

// Map class implementation
Map::Map()
{
    this->territories = new std::vector<Territory *>();
    this->continents = new std::vector<Continent *>();
}

Map::Map(const Map &other)
{
    this->territories = new std::vector<Territory *>(*other.territories);
    this->continents = new std::vector<Continent *>(*other.continents);
}

Map &Map::operator=(const Map &other)
{
    if (this != &other)
    {
        *this->territories = *other.territories;
        *this->continents = *other.continents;
    }
    return *this;
}

Map::~Map()
{
    delete territories;
    delete continents;
}

void Map::addTerritory(Territory *t)
{
    territories->push_back(t);
}

void Map::addContinent(Continent *c)
{
    continents->push_back(c);
}

bool Map::validate()
{
    return isConnected() && areContinentsConnected();
}

const std::vector<Territory *> &Map::getTerritories() const
{
    return *territories;
}

bool Map::isConnected()
{
    if (territories->empty())
        return false;

    std::queue<Territory *> toVisit;
    std::set<Territory *> visited;

    toVisit.push(territories->at(0));
    visited.insert(territories->at(0));

    while (!toVisit.empty())
    {
        Territory *current = toVisit.front();
        toVisit.pop();

        for (Territory *neighbor : current->getAdjacents())
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                toVisit.push(neighbor);
            }
        }
    }

    return visited.size() == territories->size();
}

bool Map::areContinentsConnected()
{
    for (Continent *continent : *continents)
    {
        std::vector<Territory *> continentTerritories = continent->getTerritories();
        if (continentTerritories.empty())
            continue;

        std::queue<Territory *> toVisit;
        std::set<Territory *> visited;

        toVisit.push(continentTerritories[0]);
        visited.insert(continentTerritories[0]);

        while (!toVisit.empty())
        {
            Territory *current = toVisit.front();
            toVisit.pop();

            for (Territory *neighbor : current->getAdjacents())
            {
                if (current->getContinentName() == neighbor->getContinentName() &&
                    visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    toVisit.push(neighbor);
                }
            }
        }

        if (visited.size() != continentTerritories.size())
        {
            return false;
        }
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const Map &m)
{
    os << "Map with " << m.territories->size() << " territories and "
       << m.continents->size() << " continents." << std::endl;

    os << "Territories and their adjacent territories:" << std::endl;

    for (auto territory : *m.territories)
    {
        // Find the correct continent for this territory
        for (auto continent : *m.continents)
        {
            if (continent->getName() == territory->getContinentName())
            {
                os << "Territory: " << territory->getName()
                   << ", Continent: " << territory->getContinentName()
                   << ", Points: " << continent->getBonus() << std::endl;
                break;
                // once correct continent is foudn, break out of the loop
            }
        }

        // Print adjacent territories
        os << "Adjacent territories: ";
        std::vector<Territory *> adjacents = territory->getAdjacents();
        if (adjacents.empty())
        {
            os << "None ";
        }
        else
        {
            for (auto adjacent : adjacents)
            {
                os << "\n"
                   << adjacent->getName();
            }
        }
        os << "\n"
           << std::endl;
    }

    return os;
}