#include "Order.h"

// Order class methods
Order::Order() : executed(false), effect("") {
    std::cout << "Order created" << std::endl;  // Debug print
}
Order::Order(const Order &other) : executed(other.executed), effect(other.effect) {
    std::cout << "Order copied" << std::endl;  // Debug print
}
Order::~Order() {
    std::cout << "Order destroyed" << std::endl;  // Debug print
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << order.getDescription();
    if (order.executed) {
        os << " [Executed with effect: " << order.effect << "]";
    }
    return os;
}

// DeployOrder methods
DeployOrder::DeployOrder() : Order() {
    std::cout << "DeployOrder created" << std::endl;  // Debug print
}
DeployOrder::DeployOrder(const DeployOrder &other) : Order(other) {
    std::cout << "DeployOrder copied" << std::endl;  // Debug print
}
bool DeployOrder::validate() {
    return true;
}
void DeployOrder::execute() {
    std::cout << "DeployOrder executing..." << std::endl;
    if (validate()) {
        executed = true;
        effect = "Deployed units";
        std::cout << "DeployOrder executed successfully." << std::endl;
    } else {
        effect = "Invalid deploy order";
        std::cout << "DeployOrder execution failed." << std::endl;
    }
    std::cout << "DeployOrder execution finished." << std::endl;
}

std::string DeployOrder::getDescription() const {
    return "Deploy Order";
}
Order* DeployOrder::clone() const {
    std::cout << "DeployOrder cloned" << std::endl;  // Debug print
    return new DeployOrder(*this);
}

// AdvanceOrder methods
AdvanceOrder::AdvanceOrder() : Order() {
    std::cout << "AdvanceOrder created" << std::endl;  // Debug print
}
AdvanceOrder::AdvanceOrder(const AdvanceOrder &other) : Order(other) {
    std::cout << "AdvanceOrder copied" << std::endl;  // Debug print
}
bool AdvanceOrder::validate() {
    return true;
}
void AdvanceOrder::execute() {
    if (validate()) {
        executed = true;
        effect = "Advanced troops";
    } else {
        effect = "Invalid advance order";
    }
}
std::string AdvanceOrder::getDescription() const {
    return "Advance Order";
}
Order* AdvanceOrder::clone() const {
    std::cout << "AdvanceOrder cloned" << std::endl;  // Debug print
    return new AdvanceOrder(*this);
}

// BombOrder methods
BombOrder::BombOrder() : Order() {
    std::cout << "BombOrder created" << std::endl;  // Debug print
}
BombOrder::BombOrder(const BombOrder &other) : Order(other) {
    std::cout << "BombOrder copied" << std::endl;  // Debug print
}
bool BombOrder::validate() {
    return true;
}
void BombOrder::execute() {
    if (validate()) {
        executed = true;
        effect = "Bombed target";
    } else {
        effect = "Invalid bomb order";
    }
}
std::string BombOrder::getDescription() const {
    return "Bomb Order";
}
Order* BombOrder::clone() const {
    std::cout << "BombOrder cloned" << std::endl;  // Debug print
    return new BombOrder(*this);
}

// BlockadeOrder methods
BlockadeOrder::BlockadeOrder() : Order() {
    std::cout << "BlockadeOrder created" << std::endl;  // Debug print
}
BlockadeOrder::BlockadeOrder(const BlockadeOrder &other) : Order(other) {
    std::cout << "BlockadeOrder copied" << std::endl;  // Debug print
}
bool BlockadeOrder::validate() {
    return true;
}
void BlockadeOrder::execute() {
    if (validate()) {
        executed = true;
        effect = "Blockaded territory";
    } else {
        effect = "Invalid blockade order";
    }
}
std::string BlockadeOrder::getDescription() const {
    return "Blockade Order";
}
Order* BlockadeOrder::clone() const {
    std::cout << "BlockadeOrder cloned" << std::endl;  // Debug print
    return new BlockadeOrder(*this);
}

// AirliftOrder methods
AirliftOrder::AirliftOrder() : Order() {
    std::cout << "AirliftOrder created" << std::endl;  // Debug print
}
AirliftOrder::AirliftOrder(const AirliftOrder &other) : Order(other) {
    std::cout << "AirliftOrder copied" << std::endl;  // Debug print
}
bool AirliftOrder::validate() {
    return true;
}
void AirliftOrder::execute() {
    if (validate()) {
        executed = true;
        effect = "Airlifted units";
    } else {
        effect = "Invalid airlift order";
    }
}
std::string AirliftOrder::getDescription() const {
    return "Airlift Order";
}
Order* AirliftOrder::clone() const {
    std::cout << "AirliftOrder cloned" << std::endl;  // Debug print
    return new AirliftOrder(*this);
}

// NegotiateOrder methods
NegotiateOrder::NegotiateOrder() : Order() {
    std::cout << "NegotiateOrder created" << std::endl;  // Debug print
}
NegotiateOrder::NegotiateOrder(const NegotiateOrder &other) : Order(other) {
    std::cout << "NegotiateOrder copied" << std::endl;  // Debug print
}
bool NegotiateOrder::validate() {
    return true;
}
void NegotiateOrder::execute() {
    if (validate()) {
        executed = true;
        effect = "Negotiation successful";
    } else {
        effect = "Invalid negotiate order";
    }
}
std::string NegotiateOrder::getDescription() const {
    return "Negotiate Order";
}
Order* NegotiateOrder::clone() const {
    std::cout << "NegotiateOrder cloned" << std::endl;  // Debug print
    return new NegotiateOrder(*this);
}

// OrdersList methods
OrdersList::OrdersList() {
    std::cout << "OrdersList created" << std::endl;  // Debug print
}

OrdersList::OrdersList(const OrdersList &other) {
    std::cout << "OrdersList copied" << std::endl;  // Debug print
    for (Order *order : other.orders) {
        orders.push_back(order->clone());  // Deep copy using clone method
    }
}

OrdersList::~OrdersList() {
    std::cout << "OrdersList destroyed" << std::endl;  // Debug print
    for (Order *order : orders) {
        delete order;  // Free memory for each order
    }
}

void OrdersList::issueOrder(Order *order) {
    std::cout << "Order issued" << std::endl;  // Debug print
    orders.push_back(order);
}

void OrdersList::removeOrder(int index) {
    if (index >= 0 && index < orders.size()) {
        std::cout << "Removing order at index " << index << std::endl;
        delete orders[index];  // Delete the order at the specified index
        orders.erase(orders.begin() + index);  // Remove the pointer from the list
    }
}

void OrdersList::moveOrder(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        if (fromIndex == toIndex) return;  // Avoid moving to the same position
        std::cout << "Moving order from index " << fromIndex << " to index " << toIndex << std::endl;  // Debug print
        Order *order = orders[fromIndex];
        orders.erase(orders.begin() + fromIndex);
        orders.insert(orders.begin() + toIndex, order);
    }
}

std::ostream &operator<<(std::ostream &os, const OrdersList &ol) {
    for (const Order *order : ol.orders) {
        os << *order << std::endl;
    }
    return os;
}