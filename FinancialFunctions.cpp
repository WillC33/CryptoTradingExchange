#include <vector>
#include "OrderBookEntry.h"

/**
* \brief Calculates the average price in the list
 * \param entries the order book entries
 * \return double - the average
 */
double computeAveragePrice(const std::vector<OrderBookEntry>& entries)
{
    double sum = 0;
    for (const OrderBookEntry entry : entries)
    {
        sum += entry.price;
    }
    return sum/entries.size();
}

/**
 * \brief Calculates the lowest price in the range
 * \param entries the order book entries
 * \return double - the lowest value
 */
double computeLowPrice(const std::vector<OrderBookEntry>& entries)
{
    double lowPrice = entries[0].price;
    for (const OrderBookEntry entry : entries)
    {
        if (entry.price < lowPrice)
            lowPrice = entry.price;
    }
    return lowPrice;
}

/**
 * \brief Calculates the highest price in the range
 * \param entries the order book entries
 * \return double - the highest value
 */
double computeHighPrice(const std::vector<OrderBookEntry>& entries)
{
    double highPrice = entries[0].price;
    for (const OrderBookEntry entry : entries)
    {
        if (entry.price > highPrice)
            highPrice = entry.price;
    }
    return highPrice;
}

/**
 * \brief calculates the range of prices
 * \param entries the order book entries
 * \return double - the spread
 */
double computePriceSpread(const std::vector<OrderBookEntry>& entries)
{
    const double lowPrice = computeLowPrice(entries);
    const double highPrice = computeHighPrice(entries);
    return highPrice - lowPrice;
}