#include "Order.h"
#include "Player.h"
#include "Map.h"

// ---------------------------------------------------------------------------------------
// ORDER
// Order class methods
Order::Order() {
    this->validity = false;
    this->className = "Order";
}
Order::Order(const Order& order) {
    this->validity = order.validity;
    this->className = order.className;
}

Order::~Order() {}

Order& Order::operator=(const Order& order) 
{
    if (this != &order) {  // Check for self-assignment
        this->validity = order.validity;
        this->className = order.className;
    }
    return *this;
}


std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << order.getDescription();
    if (order.validity) {
        os << " - Order successfully executed with effects: " << order.className << "!";
    } else {
        os << " - Order failed, no impact.";
    }
    return os;
}

bool Order::getValidity()		// Accessor method				
{
	return validity;
}

std::string Order::getClassName()		//accessor method				
{
	return className;
}

/* PART 5 UNCOMMENT THIS
std::string Order::stringToLog() {
	return "Issued Base Order";
}
*/ 

// ---------------------------------------------------------------------------------------
// DEPLOY ORDER

// DeployOrder methods
DeployOrder::DeployOrder(Player* issuingPlayer, int armies, Territory* location) : Order(), issuingPlayer(issuingPlayer), armies(armies), location(location){					
	className = "Deploy";
}

DeployOrder::DeployOrder(const DeployOrder& deploy) : Order(deploy), issuingPlayer(deploy.issuingPlayer), armies(deploy.armies), location(deploy.location){	
	this->className = deploy.className;
}

DeployOrder::~DeployOrder() {}

DeployOrder& DeployOrder::operator=(const DeployOrder& deploy) // Assignment Operator Overload
{
	Order::operator =(deploy);
	this->className = deploy.className;
	this->issuingPlayer = deploy.issuingPlayer;
	this->armies = deploy.armies;
	this->location = deploy.location;
	return *this;
}

void DeployOrder::validate() {
    std::cout << "Deploy order validation: checking territory ownership..." << std::endl;
    std::vector<Territory*> playerTerritories = issuingPlayer->getTerritories();
    if (std::find(playerTerritories.begin(), playerTerritories.end(), this->location) != playerTerritories.end()) {
        validity = true;
        std::cout << "Deploy order validated! Ready to reinforce!" << std::endl;
    } else {
        std::cout << "Oops! This territory doesn't belong to you. Try again!" << std::endl;
    }
}

void DeployOrder::execute() {
    std::cout << "Deploying your mighty forces!" << std::endl;
    this->validate();
    if (getValidity()) {
        int currentArmies = this->location->getArmies();  // Use getter to access
        this->location->setArmies(currentArmies + armies); // Use setter to modify
        std::cout << "Successfully deployed " << armies << " armies to " << location->getName() << "." << std::endl;
    } else {
        std::cout << "Deploy order failed." << std::endl;
    }
    std::cout << "Deploy order execution complete. On to victory!" << std::endl;
    // PART 5 UNCOMMENT THIS
    // Notify(this);

}

std::string DeployOrder::getDescription() const {
    return "Deploy Order - Reinforce your position with additional armies!";
}
Order* DeployOrder::clone() const {
    return new DeployOrder(*this);
}

/* PART 5 UNCOMMENT THIS
std::string Deploy::stringToLog() {
	return "Order has been executed: " + issuingPlayer->name + " deployed " + std::to_string(armies) + " units to " + location->name;
}
 */

// ---------------------------------------------------------------------------------------
// ADVANCE ORDER
// AdvanceOrder methods
AdvanceOrder::AdvanceOrder(Player* issuingPlayer, int armies, Territory* to, Territory* from) : Order(), attacking(false), issuingPlayer(issuingPlayer), armies(armies), to(to), from(from){											
	className = "Advance";
}

// Copy Constructor
AdvanceOrder::AdvanceOrder(const AdvanceOrder &other)
    : Order(other), issuingPlayer(other.issuingPlayer), armies(other.armies), to(other.to), from(other.from), attacking(other.attacking) {}

// Assignment Operator
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& a) {
    if (this != &a) {
        Order::operator=(a);
        issuingPlayer = a.issuingPlayer;
        armies = a.armies;
        to = a.to;
        from = a.from;
        attacking = a.attacking;
    }
    return *this;
}

// Destructor
AdvanceOrder::~AdvanceOrder() {}

void AdvanceOrder::validate() {
    std::cout << "Advancing... Validating the road ahead..." << std::endl;
    if (issuingPlayer == from->getOwner() && isAdjacent(from, to) && armies > 0) {
        Player* targetPlayer = to->getOwner();
        if (issuingPlayer != targetPlayer) {
            std::cout << "Ready to conquer! Advance Order is valid, " << issuingPlayer->getName() << " is attacking " << targetPlayer->getName() << "." << std::endl;
            attacking = true;
            validity = true;  // Mark valid only after confirming it's not owned by the player
        } else {
            std::cout << "This territory is already yours! Can't attack your own land." << std::endl;
            validity = false;
        }
    } else {
        std::cout << "Hold up! Something's wrong with your advance. Make sure the path is clear!" << std::endl;
        validity = false;
    }
}



void AdvanceOrder::execute() {
    validate();
    if (getValidity()) {
        std::cout << "Time to advance! Let's move those armies!" << std::endl;

        if (attacking) {
            std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed for randomness
            std::cout << "Engaging in battle... Wishing you luck!" << std::endl;
            int remainingAttackers = armies;
            from->setArmies(from->getArmies() - armies);

            // Battle simulation loop
            while (to->getArmies() > 0 && remainingAttackers > 0) {
                float randAttack = static_cast<float>(std::rand()) / RAND_MAX;
                float randDefend = static_cast<float>(std::rand()) / RAND_MAX;

                if (randAttack >= 0.4) {
                    to->setArmies(to->getArmies() - 1);
                    std::cout << "Boom! An enemy unit falls!" << std::endl;
                }
                if (randDefend >= 0.3) {
                    remainingAttackers -= 1;
                    std::cout << "Ouch! Your attackers take a hit!" << std::endl;
                }
            }

            if (to->getArmies() == 0) {
                std::cout << "Victory! " << to->getName() << " is now under the control of " << issuingPlayer->getName() << std::endl;
                to->setOwner(issuingPlayer);
                to->setArmies(remainingAttackers);
                std::cout << "The conquering player now holds " << to->getArmies() << " soldiers in the territory." << std::endl;
            } else {
                std::cout << "Attack army was destroyed, " << to->getName() << " was defended." << std::endl;
                std::cout << to->getName() << " has " << to->getArmies() << " remaining on the territory." << std::endl;
            }
        } else {
            from->setArmies(from->getArmies() - armies);
            to->setArmies(to->getArmies() + armies);
            std::cout << "Advancement complete. " << armies << " armies moved from " << from->getName() << " to " << to->getName() << "." << std::endl;
        }
    } else {
        std::cout << "Advance order invalid. No progress can be made." << std::endl;
    }
    attacking = false;
    // UNCOMMENT PART5
    // Notify(this);
}


bool AdvanceOrder::isAdjacent(Territory* from, Territory* to) {
    for (Territory* adjacent : from->getAdjacents()) {
        if (adjacent == to) {
            return true;
        }
    }
    return false;
}

std::string AdvanceOrder::getDescription() const {
    return "Advance Order - Move your armies forward and conquer new lands!";
}
Order* AdvanceOrder::clone() const {
    return new AdvanceOrder(*this);
}

// UNCOMMENT PART 5
/*
std::string Advance::stringToLog() {
	return "Order Executed: " + issuingPlayer->name + " advanced " + std::to_string(numOfArmies) + " from " + from->name + " to " + to->name;
}
 */

// ---------------------------------------------------------------------------------------
// BOMB ORDER
// BombOrder methods
BombOrder::BombOrder(Player* issuingPlayer, Territory* location) 
    : Order(), issuingPlayer(issuingPlayer), location(location) {										
	className = "Bomb";
}

BombOrder::BombOrder(const BombOrder& bomb) 
    : Order(bomb), issuingPlayer(bomb.issuingPlayer), location(bomb.location) {										
	this->className = bomb.className;
}

BombOrder& BombOrder::operator=(const BombOrder bomb) {
	Order::operator =(bomb);
	this->className = bomb.className;
	this->issuingPlayer = bomb.issuingPlayer;
	this->location = bomb.location;
	return *this;
}

BombOrder::~BombOrder() {}

void BombOrder::validate() {
    std::cout << "Bomb validation: Make sure the target is within reach..." << std::endl;
    if (location->getOwner() != issuingPlayer) {
        bool isAdjacent = false;
        for (Territory* t : issuingPlayer->getTerritories()) {
            for (Territory* adjacentT : t->getAdjacentTerritories()) {
                if (adjacentT == location) {
                    isAdjacent = true;
                    break;
                }
            }
            if (isAdjacent) break;
        }
        if (isAdjacent) {
            std::cout << "Bomb order validated! Time to cause some chaos!" << std::endl;
            validity = true;
        } else {
            std::cout << "Too far to bomb! Find an adjacent territory." << std::endl;
            validity = false;
        }
    } else {
        std::cout << "You can't bomb your own territory! Think twice before acting!" << std::endl;
        validity = false;
    }
}

void BombOrder::execute() {
	this->validate();
	if (getValidity()) {
        std::cout << "BOOM! The bomb goes off!" << std::endl;
		// Halve the army count on the target location
		location->setArmies(location->getArmies() / 2);
		std::cout << "There are " << location->getArmies() << " armies left in the bombed territory" << std::endl;
		
		// Notify(this); 
	} else {
		std::cout << "Bomb Order failed..." << std::endl;
	}
}
std::string BombOrder::getDescription() const {
    return "Bomb Order - Use this order to destroy enemy forces in adjacent territories.";
}
Order* BombOrder::clone() const {
    return new BombOrder(*this);
}

// UNCOMMENT PT 5
/*
std::string Bomb::stringToLog() {
	return "Order Executed: " + issuingPlayer->name + " bombed " + location->name;
}
 */


// ---------------------------------------------------------------------------------------
// BLOCKADE ORDER
// BlockadeOrder methods
BlockadeOrder::BlockadeOrder(Player* issuingPlayer, Territory* location) : Order(), issuingPlayer(issuingPlayer), location(location)
{											// Constructor
	className = "Blockade";
}

BlockadeOrder::~BlockadeOrder() {}

BlockadeOrder::BlockadeOrder(const BlockadeOrder& b) : Order(b), issuingPlayer(b.issuingPlayer), location(b.location)
{											// Copy Constructor
	this->className = b.className;
}

void BlockadeOrder::validate() {
    std::cout << "Blockade validation: Preparing to block key supply routes!" << std::endl;
    // Check if the territory is owned by the issuing player
    if (location->getOwner() == issuingPlayer) {
        validity = true;
        std::cout << "Blockade order validated! The enemy's territory is now under siege." << std::endl;
    } else {
        validity = false;
        std::cout << "You can't blockade your own territory! Try something more daring!" << std::endl;
    }
}

void BlockadeOrder::execute() {
    this->validate();
    if (getValidity()) {  // Ensuring that execute only proceeds if validated
        std::cout << "Blockade executed! The enemy's reinforcements are delayed!" << std::endl;

        // Double the army count
        location->setArmies(location->getArmies() * 2);

        // Transfer ownership to the Neutral player
        Player* neutralPlayer = Player::getNeutralPlayer();
        issuingPlayer->removeTerritory(location);
        neutralPlayer->addTerritory(location);

        std::cout << "Blockade executed on " << location->getName() << ". "
                  << location->getName() << " is now owned by the Neutral Player." << std::endl;
        std::cout << location->getName() << " now has: " << location->getArmies() << " armies" << std::endl;


        // UNCOMMENT PART 5
        // Notify(this); 
    } else {
        std::cout << "Blockade order failed! No effect on the enemy." << std::endl;
    }
}

BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& other) {
    if (this != &other) {
        Order::operator=(other);
        issuingPlayer = other.issuingPlayer;
        location = other.location;
        className = other.className;
    }
    return *this;
}

std::string BlockadeOrder::getDescription() const {
    return "Blockade Order";
}
Order* BlockadeOrder::clone() const {
    return new BlockadeOrder(*this);
}

// UNCOMMENT FOR PART 5 
/*
std::string BlockadeOrder::stringToLog() {
    return "Order Executed: " + issuingPlayer->getName() + " blockaded " + targetTerritory->getName();
}
 */

// ---------------------------------------------------------------------------------------
// AIRLIFT ORDER
// AirliftOrder methods
AirliftOrder::AirliftOrder(Player* issuingPlayer, int armies, Territory* to, Territory* from)
    : Order(), issuingPlayer(issuingPlayer), armies(armies), to(to), from(from) {
    className = "Airlift";
}

AirliftOrder::AirliftOrder(const AirliftOrder &other)
    : Order(other), issuingPlayer(other.issuingPlayer), armies(other.armies), to(other.to), from(other.from) {}


AirliftOrder& AirliftOrder::operator=(const AirliftOrder& other) {
    if (this != &other) {
        Order::operator=(other);
        issuingPlayer = other.issuingPlayer;
        armies = other.armies;
        to = other.to;
        from = other.from;
        validity = other.validity;
        className = other.className;
    }
    return *this;
}

void AirliftOrder::validate() {
    std::cout << "Airlift validation: Preparing your airborne forces!" << std::endl;

    // Validate if both source and target are owned by the issuing player
    if (from->getOwner() == issuingPlayer && from->getOwner() == issuingPlayer) {
        if (armies > from->getArmies()) {
            validity = false;
            std::cout << "Cannot airlift more soldiers than available in the source territory!" << std::endl;
        } else {
            validity = true;
        std::cout << "Airlift order validated! Your troops are ready for takeoff!" << std::endl;
        }
    } else {
        validity = false;
        std::cout << "Something went wrong. You can't airlift from an enemy territory, or no troops to move!" << std::endl;
    }
}


void AirliftOrder::execute() {
    this->validate();
    if (getValidity()) {
        std::cout << "Airlift in progress... Troops are in the sky!" << std::endl;

        // Transfer armies from source to target
        from->setArmies(from->getArmies() - armies);
        to->setArmies(to->getArmies() + armies);

        std::cout << to->getName() << " received " << armies << " soldiers from " << from->getName() << "." << std::endl;
        std::cout << from->getName() << " now has: " << from->getArmies() << " soldiers." << std::endl;
        std::cout << to->getName() << " now has: " << to->getArmies() << " soldiers." << std::endl;

        // UNCOMMENT PART 5
        // Notify(this);
    } else {
        std::cout << "Airlift order failed! No action taken." << std::endl;
    }
}

std::string AirliftOrder::getDescription() const {
    return "Airlift Order - Move your armies across the map with an airborne strategy!";
}   

Order* AirliftOrder::clone() const {
    return new AirliftOrder(issuingPlayer, armies, to, from);
}

AirliftOrder::~AirliftOrder(){};

/* UNCOMMENT PART 5 
std::string AirliftOrder::stringToLog() {
    return "Order Executed: " + issuingPlayer->getName() + " airlifted " + std::to_string(numOfArmies) + " armies from " + source->getName() + " to " + target->getName();
}
 */

// ---------------------------------------------------------------------------------------
// NEGOTIATE ORDER
// NegotiateOrder methods
NegotiateOrder::NegotiateOrder(Player* issuingPlayer, Player* targetPlayer)
    : Order(), issuingPlayer(issuingPlayer), targetPlayer(targetPlayer) {
    className = "NegotiateOrder";
}

NegotiateOrder::~NegotiateOrder() {}

NegotiateOrder::NegotiateOrder(const NegotiateOrder& n) : Order(n), issuingPlayer(n.issuingPlayer), targetPlayer(n.targetPlayer){											
	this->className = n.className;
}

void NegotiateOrder::validate() {
    std::cout << "Negotiation validation: Time to talk peace!" << std::endl;
    // Check if the target player is not the same as the issuing player
    if (issuingPlayer != targetPlayer) {
        validity = true;
        std::cout << "Negotiation order validated! Your diplomatic efforts are now in motion." << std::endl;
    } else {
        validity = false;
        std::cout << "You cannot negotiate with yourself! Find a worthy opponent." << std::endl;
    }
}

void NegotiateOrder::execute() {
    this->validate();
    if (getValidity()) {
        std::cout << "Negotiations are underway... Perhaps an alliance is in the works?" << std::endl;

        // Make players unable to attack each other for the remainder of the turn
        issuingPlayer->addDiplomacyPlayer(targetPlayer);
        targetPlayer->addDiplomacyPlayer(issuingPlayer);

        std::cout << "Both players agree to a ceasefire for this round. " 
        << issuingPlayer->getName() << " and " << targetPlayer->getName() 
        << " cannot attack each other until the end of the round." << std::endl;

        // Notify(this);
    } else {
        std::cout << "Negotiation failed! No peace achieved." << std::endl;
    }
}
std::string NegotiateOrder::getDescription() const {
    return "Negotiate Order - Form alliances and ceasefires with other players to avoid conflict.";
}
Order* NegotiateOrder::clone() const {
    return new NegotiateOrder(*this);
}

NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& other) {
    if (this != &other) {
        Order::operator=(other);
        issuingPlayer = other.issuingPlayer;
        targetPlayer = other.targetPlayer;
        className = other.className;
    }
    return *this;
}

/* UNCOMMENT PART 5
std::string NegotiateOrder::stringToLog() {
    return "Order Executed: " + issuingPlayer->getName() + " negotiated with " + targetPlayer->getName();
}
*/


// ---------------------------------------------------------------------------------------
// ORDERLIST
// OrdersList methods
OrdersList::OrdersList() {
}

OrdersList::OrdersList(const OrdersList &other) {
    for (Order *order : other.orders) {
        orders.push_back(order->clone());  // Deep copy using clone method
    }
}

OrdersList& OrdersList::operator=(const OrdersList& o) {
    if (this != &o) {           // Check for self-assignment
        this->orders = o.orders;
    }
    return *this;
}


OrdersList::~OrdersList() {
    for (Order *order : orders) {
        delete order;  // Free memory for each order
    }
}

void OrdersList::issueOrder(Order *order) {
    orders.push_back(order);
}

void OrdersList::removeOrder(int index) {
    if (index >= 0 && index < orders.size()) {
        std::cout << "Removing order at index " << index << std::endl;
        delete orders[index];  // Delete the order at the specified index
        orders.erase(orders.begin() + index);  // Remove the pointer from the list
    } else{
		std::cout << "Invalid Move" << std::endl;
	}
}

void OrdersList::moveOrder(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        if (fromIndex == toIndex) return;  // Avoid moving to the same position
        Order *order = orders[fromIndex];
        orders.erase(orders.begin() + fromIndex);
        orders.insert(orders.begin() + toIndex, order);
    }
}


std::ostream& operator<<(std::ostream& os, OrdersList& ordersList) {
    os << "Orders List: [";
    bool first = true;
    
    // Iterate through the orders in the OrdersList
    for (Order* order : ordersList.getOrders()) {  // Assuming getOrders() returns a collection of Order* objects
        if (!first) {
            os << ", ";  // Add a comma separator between orders
        }
        first = false;
        os << *order;  // Output each order (assuming operator<< is defined for Order)
    }
    
    os << "]" << std::endl;  // Close the list with a bracket and print a newline
    return os;  // Return the ostream to allow chaining
}



/* UNCOMMENT PART 5
std::string OrdersList::stringToLog() {
	return "Order Issued: " + list.back()->getClassName();
}
*/ 

