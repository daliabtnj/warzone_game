#include "Order.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <iostream>
#include <ctime>

/*
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Player.cpp Order.cpp Cards.cpp OrdersDriver.cpp
*/



// Test function to demonstrate the execution of various orders.
void testOrderExecution() {
    // Create territories
    Continent* europe = new Continent("Europe", 0);
    Territory* territory1 = new Territory("France", "Europe", 8);
    Territory* territory2 = new Territory("Belgium", "Europe", 10);
    Territory* territory3 = new Territory("Spain", "Europe", 6);
    Territory* territory4 = new Territory("Portugal", "Europe", 8);
    Territory* territory5 = new Territory("Greece", "Europe", 5);


    std::cout << "France has 8 armies" << std::endl;
    std::cout << "Belgium has 10 armies" << std::endl;
    std::cout << "Greece has 5 armies" << std::endl;
    std::cout << "Spain has 6 armies" << std::endl;
    std::cout << "Portugal has 8 armies\n" << std::endl;

    
    // Create players
    Player* player1 = new Player("Didou1");
    Player* player2 = new Player("Tash");
    Player* neutralPlayer = new Player("Neutral");
    
    // Assign ownership of territories
    player1->addTerritory(territory1);    
    player1->addTerritory(territory2);    
    player2->addTerritory(territory3);    
    player2->addTerritory(territory4); 
    player1->addTerritory(territory5);
    
    // Set adjacent territories using addAdjacentTerritory
    territory1->addAdjacentTerritory(territory2);
    territory2->addAdjacentTerritory(territory1);
    territory2->addAdjacentTerritory(territory3);
    territory3->addAdjacentTerritory(territory2);
    territory3->addAdjacentTerritory(territory4);
    territory4->addAdjacentTerritory(territory3);

    std::cout << "\nFrance is adjacent to Belgium" << std::endl;
    std::cout << "Belgium is adjacent to Spain" << std::endl;
    std::cout << "Spain is adjacent to Portugal" << std::endl;


    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"DEPLOY ORDER"<<std::endl;

     // Deploy Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;
    std::cout << "Deploy Order (Player 1 deploys 3 armies to France):\n";
    DeployOrder deployOrder1(player1, 3, territory1);
    deployOrder1.execute();  // Valid, adds armies to France

    // Edge case - Deploy Order invalid (Player 2 does not own France)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Deploy Order (Player 2 tries to deploy 3 armies to France):\n";
    DeployOrder deployOrderInvalid(player2, 3, territory1);
    deployOrderInvalid.execute();  // Invalid, Player 2 does not own France

    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"ADVANCE ORDER"<<std::endl;
    // Advance Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;

    std::cout << "Advance Order (Player 1 attacks Player 2's Spain from Belgium with 2 armies):\n";
    AdvanceOrder advanceOrder(player1, 2, territory3, territory2);  // Advance from France to Spain (Player 1 attacks Player 2)
    advanceOrder.execute();  // Should trigger battle and conquer if successful

    // Edge case - Advance Order invalid (Player 1 tries to attack Player 2's Spain from Belgium, not adjacent)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Advance Order (Player 1 tries to advance from France to Spain with 3 armies):\n";
    AdvanceOrder advanceOrderInvalid(player1, 3, territory3, territory1);  // Belgium to Spain (not adjacent)
    advanceOrderInvalid.execute();  // Invalid, not adjacent

    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"AIRLIFT ORDER"<<std::endl;
    // Airlift Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;
    std::cout << "Airlift Order (Player 1 airlifts to Greece from France with 2 armies):\n";
    AirliftOrder airliftOrder(player1, 2, territory5, territory1);  // Airlift from France to Portugal
    airliftOrder.execute();  // Valid, moves troops from France to Portugal

    // Edge case - Airlift Order invalid (Player 2 tries to airlift to Belgium)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Airlift Order (Player 2 tries to airlift to France from Portugal with 2 armies):\n";
    AirliftOrder airliftOrderInvalid(player2, 2, territory3, territory1);  // Airlift from Spain to Belgium (Player 2 owns Belgium)
    airliftOrderInvalid.execute();  // Invalid, Player 2 does not own Belgium

    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"BOMB ORDER"<<std::endl;
    // Bomb Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;
    std::cout << "Bomb Order (Player 1 bombs Player 2's Spain):\n";
    BombOrder bombOrder(player1, territory3);
    bombOrder.execute();  // Valid, removes half of army units in Spain

    // Edge case - Bomb Order invalid (Player 1 tries to bomb France, which they own)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Bomb Order (Player 1 tries to bomb their own France):\n";
    BombOrder bombOrderInvalid(player1, territory1);
    bombOrderInvalid.execute();  // Invalid, can't bomb own territory

    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"BLOCKADE ORDER"<<std::endl;
    // Blockade Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;
    std::cout << "Blockade Order (Player 1 blockades their own Belgium):\n";
    BlockadeOrder blockadeOrder(player1, territory2);
    blockadeOrder.execute();  // Valid, doubles army count in Belgium, transfers ownership to neutral

    // Edge case - Blockade Order invalid (Player 2 tries to blockade Belgium, owned by Player 1)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Blockade Order (Player 2 tries to blockade Belgium):\n";
    BlockadeOrder blockadeOrderInvalid(player2, territory2);
    blockadeOrderInvalid.execute();  // Invalid, Player 2 doesn't own Belgium

    std::cout<<"\n==============================================================================================================="<<std::endl;
    std::cout<<"NEGOCIATE ORDER"<<std::endl;
    // Negotiate Order - Valid
    std::cout<<"\n-----"<<std::endl;
    std::cout<<"VALID"<<std::endl; 
    std::cout<<"-----"<<std::endl;
    std::cout << "Negotiate Order (Player 1 negotiates with Player 2):\n";
    NegotiateOrder negotiateOrder(player1, player2);
    negotiateOrder.execute();  // Valid, no attack possible between player1 and player2

    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Bomb Order (Player 1 bombs Player 2's Spain):\n";
    BombOrder bombOrder2(player1, territory3);
    bombOrder2.execute();

    // Edge case - Negotiate Order invalid (Player 1 tries to negotiate with themselves)
    std::cout<<"\n-----------------"<<std::endl;
    std::cout<<"INVALID EDGE CASE"<<std::endl; 
    std::cout<<"-----------------"<<std::endl;
    std::cout << "Negotiate Order (Player 1 tries to negotiate with themselves):\n";
    NegotiateOrder negotiateOrderInvalid(player1, player1);
    negotiateOrderInvalid.execute();  // Invalid, cannot negotiate with self
    
    
    // Clean up dynamically allocated memory
    delete territory1;
    delete territory2;
    delete territory3;
    delete territory4;
    delete player1;
    delete player2;
    delete neutralPlayer;
}
/*
int main() {
    // Call the test function
    testOrderExecution();
    return 0;
}
*/

/*
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
    std::cout << "Orders List after removing the second order:" << std::endl;
    std::cout << ol << std::endl;

    // Execute all orders
    bomb->execute();
    advance->execute();
    blockadeOrder->execute();
    negociateOrder->execute();
    airliftOrder->execute();

    std::cout << "Orders List after executing all orders:" << std::endl;
    std::cout << ol << std::endl;
}
*/
