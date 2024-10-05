#include "Order.h"
#include "OrdersDriver.h"

void testOrdersLists()
{
    OrdersList ol;

    Order *deploy = new DeployOrder();
    Order *advance = new AdvanceOrder();
    Order *bomb = new BombOrder();
    Order *blockadeOrder = new BlockadeOrder();
    Order *negociateOrder = new NegotiateOrder();
    Order *airliftOrder = new AirliftOrder();

    ol.issueOrder(deploy);
    ol.issueOrder(advance);
    ol.issueOrder(bomb);
    ol.issueOrder(blockadeOrder);
    ol.issueOrder(negociateOrder);
    ol.issueOrder(airliftOrder);

    std::cout << "Orders List after adding orders:" << std::endl;
    std::cout << ol << std::endl;

    ol.moveOrder(2, 0);
    std::cout << "Orders List after moving Bomb order to the front:" << std::endl;
    std::cout << ol << std::endl;

    ol.removeOrder(1); // Removing the Advance order

    advance = nullptr;
    std::cout << "Orders List after removing the second order:" << std::endl;
    std::cout << ol << std::endl;

    // Execute all orders
    // deploy->execute();
    // bomb->execute();

    std::cout << "Orders List after executing all orders:" << std::endl;
    std::cout << ol << std::endl;
}

// int main()
// {
//     testOrdersLists();
//     return 0;
// }