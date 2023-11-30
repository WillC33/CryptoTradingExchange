#include <iostream>
#include <map>

/**
 * Prints the help option
 */
void printHelp()
{
    std::cout << "Help - Your aim is to make money. Watch the market and make offers and bids! " << std::endl;
}

/**
 * Prints current exchange rates
 */
void printMarketStats()
{
    std::cout << "Market looks good! " << std::endl;
}

/**
 * Handles the entry of an offer
 */
void handleOffer()
{
    std::cout << "Make an offer - enter the amount! " << std::endl;
}

/**
 * Handles the entry of a bid
 */
void handleBid()
{
    std::cout << "Make a bid - enter the amount! " << std::endl;
}

/**
 * Prints the wallet
 */
void printWallet()
{
    std::cout << "Your wallet is empty... " << std::endl;
}

/**
 * Completes trading and moves to the next time frame
 */
void completeTrades()
{
    std::cout << "Completing timeframe" << std::endl;
}

/**
 * Processes a given userOption
 * {param}: const int userOption
 */
void processUserOption(const int userOption)
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