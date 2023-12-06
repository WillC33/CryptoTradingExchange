#include <iostream>

#include "CSVReader.h"
#include "MerkelMain.h"

/**
 * Prints the help option
 */
void MerkelMain::printHelp()
{
    std::cout << "Help - Your aim is to make money. Watch the market and make offers and bids! " << std::endl;
}

/**
 * Prints current exchange rates
 */
void MerkelMain::printMarketStats()
{
    auto productList = orderbook.getKnownProducts();

    for(const auto& p : productList)
    {
        auto changeSinceLogon = orderbook.changeSinceLogon(p, currentTime);
        auto avg = orderbook.computeAveragePrice(p, currentTime);
        auto high = orderbook.computeHighPrice(p, currentTime);
        auto low = orderbook.computeLowPrice(p, currentTime);
        auto spread = orderbook.computePriceSpread(p, currentTime);

        std::cout << "Product: " << p << std::endl;
        std::cout << "Change since logon: " << changeSinceLogon << "%" << std::endl;
        std::cout << "Average Ask: " << avg << std::endl;
        std::cout << "High Ask: " << high << std::endl;
        std::cout << "Low Ask: " << low << std::endl;
        std::cout << "Spread: " << spread << std::endl;
        std::cout << "===============" << std::endl;
    }
}

/**
 * Handles the entry of an offer
 */
void MerkelMain::handleOffer()
{
    std::cout << "Make an offer - format: product,price,amount" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::cout << "Entered: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input , ',');
    if (tokens.size() != 3)
        std::cout << "Bad input : " << input << std::endl;
    else
    {
        try
        {
            CSVReader::input_to_order_book_entry(tokens[0],
              tokens[1],
              tokens[2],
              currentTime,
              OrderType::ask);
        }
        catch (const std::exception& e)
        {
            std::cout << "Bad input: Please enter a valid order" << std::endl;
        }
    }
}

/**
 * Handles the entry of a bid
 */
void MerkelMain::handleBid()
{
    std::cout << "Make a bid - format: product,price,amount" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::cout << "Entered: " << input << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(input , ',');
    if (tokens.size() != 3)
        std::cout << "Bad input : " << input << std::endl;
    else
    {
        try
        {
            CSVReader::input_to_order_book_entry(tokens[0],
              tokens[1],
              tokens[2],
              currentTime,
              OrderType::ask);
        }
        catch (const std::exception& e)
        {
            std::cout << "Bad input: Please make a valid bid" << std::endl;
        }
    }

}

/**
 * Prints the wallet
 */
void MerkelMain::printWallet()
{
    std::cout << "Your wallet is empty... " << std::endl;
}

/**
 * Completes trading and moves to the next time frame
 */
void MerkelMain::completeTrades()
{
    std::cout << "Completing timeframe" << std::endl;
    currentTime = orderbook.getNextTime(currentTime);
    std::cout << "Current time is: " << currentTime << std::endl;
}