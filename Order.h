#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "Player.h"

class Player;
class Territory;
class Continent;

// PART5 CHECK COMMENTS IN CAPS

// BASE CLASS ORDER
// PART 5 UNCOMMENT TO CHANGE HOW CLASS NAME IS INSTEAD OF JUST class Order
// class Order : public Subject, public ILoggable
class Order
{
protected:
    bool validity;      // Track if the order has been executed
    std::string effect; // Store the effect after execution
    std::string className;
public:
    Order();
    Order(const Order& other);                                             // Copy constructor
    virtual ~Order();                                                      // Destructor
    std::string getClassName();
    bool getValidity();
    virtual void validate() = 0;                                           // Pure virtual method for validation
    virtual void execute() = 0;                                            // Pure virtual method for execution
    virtual std::string getDescription() const = 0;                        // Pure virtual method for description
    friend std::ostream &operator<<(std::ostream &os, const Order &order); // Stream insertion operator
    virtual Order *clone() const = 0;                                      // Pure virtual method for cloning
    Order& operator=(const Order& order);

    // UNCOMMENT THIS FOR PART 5 !!
    // std::string stringToLog() override;
};

// DEPLOY ORDER
class DeployOrder : public Order {
    Player* issuingPlayer;
	int armies;
	Territory* location;
public:
    DeployOrder(Player*, int, Territory*);
    DeployOrder(const DeployOrder &other);
    DeployOrder& operator=(const DeployOrder& d);

    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override; // Clone method
    virtual ~DeployOrder();
};

// ADVANCE ORDER
class AdvanceOrder : public Order {
	Player* issuingPlayer;
	int armies;
	bool attacking;
	Territory* to;
	Territory* from;

public:
    AdvanceOrder(Player*, int, Territory*, Territory*);
    AdvanceOrder(const AdvanceOrder &other);
    AdvanceOrder& operator=(const AdvanceOrder& a);
    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override;
    virtual ~AdvanceOrder();
    bool isAdjacent(Territory* from, Territory* to);
    bool isFriendly(Player* targetPlayer) const;
};

// BOMB ORDER
class BombOrder : public Order
{
    Player* issuingPlayer;
	Territory* location;
public:
    BombOrder(Player*, Territory*);
    BombOrder(const BombOrder& bomb);
    BombOrder& operator=(const BombOrder bomb);
    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override;
    virtual ~BombOrder();
};

// BLOCKADE ORDER
class BlockadeOrder : public Order
{
    Player* issuingPlayer;
	Territory* location;
public:
    BlockadeOrder(Player*, Territory*);
    virtual ~BlockadeOrder();
    BlockadeOrder(const BlockadeOrder &other);
    BlockadeOrder& operator=(const BlockadeOrder& b);
    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override;
};

// AIRLIFT ORDER
class AirliftOrder : public Order
{
    Player* issuingPlayer;
	int armies;
	Territory* to;
	Territory* from;
public:
    AirliftOrder(Player*, int, Territory*, Territory*);
    virtual ~AirliftOrder();
    AirliftOrder(const AirliftOrder &other);
    AirliftOrder& operator=(const AirliftOrder& a);
    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override;
};

// NEGOCIATE ORDER
class NegotiateOrder : public Order
{
    Player* issuingPlayer;
	Player* targetPlayer;
public:
    NegotiateOrder(Player*, Player*);
    NegotiateOrder(const NegotiateOrder &other);
    virtual ~NegotiateOrder();
    NegotiateOrder& operator=(const NegotiateOrder& n);
    void validate() override;
    void execute() override;
    std::string getDescription() const override;
    Order *clone() const override;
};

// ORDERLIST 
// PART 5 UNCOMMENT THIS INSTEAD OF class ordersList
// class OrdersList : public Subject, public ILoggable
class OrdersList
{
private:
    std::vector<Order *> orders;

public:
    OrdersList();
    OrdersList(const OrdersList& other);                                     // Copy constructor
    ~OrdersList();                                                           // Destructor
    void issueOrder(Order *order);                                           // Add order to the list
    void removeOrder(int index);                                             // Remove order from the list by index
    void moveOrder(int fromIndex, int toIndex);                              // Move order within the list
    friend std::ostream& operator<<(std::ostream& os, OrdersList& ordersList);  // Declare the friend function
	OrdersList& operator=(const OrdersList& o);
    const std::vector<Order*>& getOrders() const {return orders;}
};

#endif