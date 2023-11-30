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
    switch (userOption) {
        case 1:
            printHelp();
        break;
        case 2:
            printMarketStats();
        break;
        case 3:
            handleOffer();
        break;
        case 4:
            handleBid();
        break;
        case 5:
            printWallet();
        break;
        case 6:
            completeTrades();
        break;
        default:
            std::cout << "Invalid Option. Please select 1-6." << std::endl;
    }
}

/**
 * ENTRY POINT
 */
int main()
{
    std::cout << "Welcome to the MerkelRex Crypto Trading Exchange" << std::endl;

    while (true)
    {
        printMenu();
        const int userOption = getUserOption();
        processUserOption(userOption);
    }
    return 0;
}
