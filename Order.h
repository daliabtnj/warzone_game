#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>

// Base class Order
class Order {
protected:
    bool executed; // Track if the order has been executed
    std::string effect; // Store the effect after execution
public:
    Order();
    Order(const Order& other); // Copy constructor
    virtual ~Order(); // Destructor
    virtual bool validate() = 0; // Pure virtual method for validation
    virtual void execute() = 0; // Pure virtual method for execution
    virtual std::string getDescription() const = 0; // Pure virtual method for description
    friend std::ostream& operator<<(std::ostream& os, const Order& order); // Stream insertion operator
};

// Derived classes for different types of orders
class DeployOrder : public Order {
public:
    DeployOrder();
    DeployOrder(const DeployOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
    AdvanceOrder(const AdvanceOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class BombOrder : public Order {
public:
    BombOrder();
    BombOrder(const BombOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class BlockadeOrder : public Order {
public:
    BlockadeOrder();
    BlockadeOrder(const BlockadeOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class AirliftOrder : public Order {
public:
    AirliftOrder();
    AirliftOrder(const AirliftOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class NegotiateOrder : public Order {
public:
    NegotiateOrder();
    NegotiateOrder(const NegotiateOrder& other);
    bool validate() override;
    void execute() override;
    std::string getDescription() const override;
};

class OrdersList {
private:
    std::vector<Order*> orders;
public:
    OrdersList();
    OrdersList(const OrdersList& other); // Copy constructor
    ~OrdersList(); // Destructor
    void issueOrder(Order* order); // Add order to the list
    void removeOrder(int index); // Remove order from the list by index
    void moveOrder(int fromIndex, int toIndex); // Move order within the list
    friend std::ostream& operator<<(std::ostream& os, const OrdersList& ol); // Stream insertion operator
};

#endif