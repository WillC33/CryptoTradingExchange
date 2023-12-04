#include <iostream>
#include "MerkelMain.h"

/**
 * ENTRY POINT
 */
int main()
{
    std::cout << "Welcome to the MerkelRex Crypto Trading Exchange" << std::endl;

    MerkelMain app{};
    app.init();

    return 0;
}
