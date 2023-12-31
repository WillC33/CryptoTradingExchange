#include "MerkelMain.h"

#include <iostream>
#include <map>

void MerkelMain::init()
{

    currentTime = orderbook.getEarliestTime();
    wallet.fund("BTC", 54.377);

    std::cout << "The current time is: " << currentTime << std::endl;

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
    std::cout << "There are " << orderbook.numberOfOrders() << " orders in the book" << std::endl;
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
    //handles the strange loop when invalid input entered
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
    std::map<int, std::function<void()>> menu;
    menu[1] = [this]() { this->printHelp(); };
    menu[2] = [this]() { this->printMarketStats(); };
    menu[3] = [this]() { this->handleOffer(); };
    menu[4] = [this]() { this->handleBid(); };
    menu[5] = [this]() { this->printWallet(); };
    menu[6] = [this]() { this->completeTrades(); };

    if (1 <= userOption && userOption <= 6)
        menu[userOption]();
    else
        std::cout << "Invalid Option. Please select 1-6." << std::endl;
}

MerkelMain::MerkelMain()
= default;

