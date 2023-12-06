#include <iostream>
#include "FinancialFunctions.h"
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
        auto entries = orderbook.getOrders(p);
        auto avg = FinancialFunctions::computeAveragePrice(entries);
        auto high = FinancialFunctions::computeHighPrice(entries);
        auto low = FinancialFunctions::computeLowPrice(entries);
        auto spread = FinancialFunctions::computePriceSpread(entries);

        std::cout << "Product: " << p << std::endl;
        std::cout << "Average: " << avg << std::endl;
        std::cout << "High: " << high << std::endl;
        std::cout << "Low: " << low << std::endl;
        std::cout << "Spread: " << spread << std::endl;
        std::cout << "===============" << std::endl;
    }
}

/**
 * Handles the entry of an offer
 */
void MerkelMain::handleOffer()
{
    std::cout << "Make an offer - enter the amount! " << std::endl;
}

/**
 * Handles the entry of a bid
 */
void MerkelMain::handleBid()
{
    std::cout << "Make a bid - enter the amount! " << std::endl;
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
}