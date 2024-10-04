#include "Order.h"

// Order class methods
Order::Order() : executed(false), effect("") {}
Order::Order(const Order &other) : executed(other.executed), effect(other.effect) {}
Order::~Order() {}
std::ostream &operator<<(std::ostream &os, const Order &order)
{
    os << order.getDescription();
    if (order.executed)
    {
        os << " [Executed with effect: " << order.effect << "]";
    }
    return os;
}

// DeployOrder methods
DeployOrder::DeployOrder() : Order() {}
DeployOrder::DeployOrder(const DeployOrder &other) : Order(other) {}
bool DeployOrder::validate()
{
    // Validation logic
    return true;
}
void DeployOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Deployed units";
    }
    else
    {
        effect = "Invalid deploy order";
    }
}
std::string DeployOrder::getDescription() const
{
    return "Deploy Order";
}

// AdvanceOrder methods
AdvanceOrder::AdvanceOrder() : Order() {}
AdvanceOrder::AdvanceOrder(const AdvanceOrder &other) : Order(other) {}
bool AdvanceOrder::validate()
{
    // Validation logic
    return true;
}
void AdvanceOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Advanced troops";
    }
    else
    {
        effect = "Invalid advance order";
    }
}
std::string AdvanceOrder::getDescription() const
{
    return "Advance Order";
}

// BombOrder methods
BombOrder::BombOrder() : Order() {}
BombOrder::BombOrder(const BombOrder &other) : Order(other) {}
bool BombOrder::validate()
{
    // Validation logic
    return true;
}
void BombOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Bombed target";
    }
    else
    {
        effect = "Invalid bomb order";
    }
}
std::string BombOrder::getDescription() const
{
    return "Bomb Order";
}

// BlockadeOrder methods
BlockadeOrder::BlockadeOrder() : Order() {}
BlockadeOrder::BlockadeOrder(const BlockadeOrder &other) : Order(other) {}
bool BlockadeOrder::validate()
{
    // Validation logic
    return true;
}
void BlockadeOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Blockaded territory";
    }
    else
    {
        effect = "Invalid blockade order";
    }
}
std::string BlockadeOrder::getDescription() const
{
    return "Blockade Order";
}

// AirliftOrder methods
AirliftOrder::AirliftOrder() : Order() {}
AirliftOrder::AirliftOrder(const AirliftOrder &other) : Order(other) {}
bool AirliftOrder::validate()
{
    // Validation logic
    return true;
}
void AirliftOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Airlifted units";
    }
    else
    {
        effect = "Invalid airlift order";
    }
}
std::string AirliftOrder::getDescription() const
{
    return "Airlift Order";
}

// NegotiateOrder methods
NegotiateOrder::NegotiateOrder() : Order() {}
NegotiateOrder::NegotiateOrder(const NegotiateOrder &other) : Order(other) {}
bool NegotiateOrder::validate()
{
    // Validation logic
    return true;
}
void NegotiateOrder::execute()
{
    if (validate())
    {
        executed = true;
        effect = "Negotiation successful";
    }
    else
    {
        effect = "Invalid negotiate order";
    }
}
std::string NegotiateOrder::getDescription() const
{
    return "Negotiate Order";
}

// OrdersList methods
OrdersList::OrdersList() {}
OrdersList::OrdersList(const OrdersList &other)
{
    for (Order *order : other.orders)
    {
        // Create a deep copy of each order (assuming copy constructor is available)
        orders.push_back(order);
    }
}
OrdersList::~OrdersList()
{
    for (Order *order : orders)
    {
        delete order; // Avoid memory leaks
    }
}
void OrdersList::issueOrder(Order *order)
{
    orders.push_back(order);
}
void OrdersList::removeOrder(int index)
{
    if (index >= 0 && index < orders.size())
    {
        delete orders[index]; // Free memory
        orders.erase(orders.begin() + index);
    }
}
void OrdersList::moveOrder(int fromIndex, int toIndex)
{
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size())
    {
        Order *order = orders[fromIndex];
        orders.erase(orders.begin() + fromIndex);
        orders.insert(orders.begin() + toIndex, order);
    }
}
std::ostream &operator<<(std::ostream &os, const OrdersList &ol)
{
    for (const Order *order : ol.orders)
    {
        os << *order << std::endl;
    }
    return os;
}