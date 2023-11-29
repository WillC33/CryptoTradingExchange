#include <iostream>

int main()
{
    //writing options to console
    std::cout << "Welcome to the MerkelRex Crypto Trading Exchange" << std::endl;
    while (true)
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
        std::cout << "6: Print Wallet" << std::endl;
        // 6 complete trades
        std::cout << "7: Complete Trades" << std::endl;

        std::cout << "================" << std::endl;
        std::cout << "Please select an option..." << std::endl;

        //using the extraction operator to recieve input
        int userOption;
        std::cin >> userOption;
        std::cout << "You chose: " << userOption << std::endl;

        switch (userOption) {
            case 1:
                std::cout << "Help - Your aim is to make money. Watch the market and make offers and bids! " << std::endl;
            break;
            case 2:
                std::cout << "Market looks good! " << std::endl;
            break;
            case 3:
                std::cout << "Make an offer - enter the amount! " << std::endl;
            break;
            case 4:
                std::cout << "Make a bid - enter the amount! " << std::endl;
            break;
            case 5:
                std::cout << "Your wallet is empty... " << std::endl;
            break;
            case 6:
                std::cout << "Completing timeframe" << std::endl;
            break;
            default:
                std::cout << "Invalid Option. Please select 1-6." << std::endl;
        }
    }
    return 0;
}
