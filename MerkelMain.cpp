#include "MerkelMain.h"
#include "MenuFunctions.h"

#include <iostream>
#include <map>

void MerkelMain::init()
{
    while (true)
    {
        printMenu();
        const int userOption = getUserOption();
        processUserOption(userOption);
    }
}
/**
* Prints the main menu
 */
void MerkelMain::printMenu()
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
int MerkelMain::getUserOption()
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

/**
 * Processes a given userOption
 * {param}: const int userOption
 */
void MerkelMain::processUserOption(const int userOption)
{
    //maps int keys to void * functions in the list 'menu'
    std::map<int,void(*)()> menu;
    menu[1] = printHelp;
    menu[2] = printMarketStats;
    menu[3] = handleOffer;
    menu[4] = handleBid;
    menu[5] = printWallet;
    menu[6] = completeTrades;

    if (1 <= userOption && userOption <= 6)
        menu[userOption]();
    else
        std::cout << "Invalid Option. Please select 1-6." << std::endl;
}

MerkelMain::MerkelMain()
= default;

