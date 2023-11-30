#include <iostream>

/**
* Prints the main menu
 */
void printMenu()
{
    // 1 print help
    std::cout << "1: Print help" << std::endl;
    // 2 print stats
    std::cout << "2: Print Exchange prices" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer" << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid" << std::endl;
    // 5 print wallet
    std::cout << "5: Print Wallet" << std::endl;
    // 6 complete trades
    std::cout << "6: Complete Trades" << std::endl;

    std::cout << "================" << std::endl;
    std::cout << "Please select an option..." << std::endl;
}

/**
 * Prompts the user for input
 */
int getUserOption()
{
    //using the extraction operator to recieve input
    int userOption;
    std::cin >> userOption;
    //handles the strange loop that appeared on windows
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}