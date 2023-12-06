#include "OrderBook.h"

#include <map>

#include "CSVReader.h"

OrderBook::OrderBook(const std::string& filename)
{
    entries = CSVReader::read(filename);
}

std::string OrderBook::getEarliestTime()
{
    return entries[0].timeStamp;
}

std::string OrderBook::getNextTime(const std::string& timestamp)
{
    std::string next_timestamp = "";
    for(const auto& e : entries)
    {
        if (e.timeStamp > timestamp)
        {
            next_timestamp = e.timeStamp;
            break;
        }
    }
    if(next_timestamp.empty()) next_timestamp = entries[0].timeStamp; //wrap back around in simulation
    return next_timestamp;
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool>prodMap;

    for(OrderBookEntry& e : entries)
    {
        prodMap[e.product] = true;
    }

    //flatten the map into a vector
    for (const auto& [product, snd] : prodMap)
    {
        products.push_back(product);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders()
{
    return entries;
}

std::vector<OrderBookEntry> OrderBook::getOrders(const std::string& product)
{
    std::vector<OrderBookEntry> orders;
    for(const auto& e : entries)
    {
        if(e.product == product)
            orders.push_back(e);
    }
    return orders;
}

/**
* \brief Tracks the percentage change since logon
* \param the product to check
* \param the current timestamp to calculate against
* \return double - the change %
*/
double OrderBook::changeSinceLogon(const std::string& product, const std::string& timestamp)
{
    auto logonAvg = computeAveragePrice(product, entries[0].timeStamp);
    auto currentAvg = computeAveragePrice(product, timestamp);

    return currentAvg - logonAvg;
}

/**
* \brief Calculates the average price in the list
* \param the product to check
* \param the current timestamp to calculate against
* \return double - the average
*/
double OrderBook::computeAveragePrice(const std::string& product, const std::string& timestamp)
{
    auto entries = filterOrders(product, timestamp);
    double sum = 0;
    for (const OrderBookEntry& entry : entries)
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
double OrderBook::computeLowPrice(const std::string& product, const std::string& timestamp)
{
    auto entries = filterOrders(product, timestamp);
    double lowPrice = entries[0].price;
    for (const OrderBookEntry& entry : entries)
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
double OrderBook::computeHighPrice(const std::string& product, const std::string& timestamp)
{
    auto entries = filterOrders(product, timestamp);
    double highPrice = entries[0].price;
    for (const OrderBookEntry& entry : entries)
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
double OrderBook::computePriceSpread(const std::string& product, const std::string& timestamp)
{
    const double lowPrice = computeLowPrice(product, timestamp);
    const double highPrice = computeHighPrice(product, timestamp);
    return highPrice - lowPrice;
}

/**
 * \brief filters the orders by given params
 * \param product the product to filter for
 * \param timestamp the timestamp
 * \param type the order type
 * \return a filtered vector of entries
 */
std::vector<OrderBookEntry> OrderBook::filterOrders(const std::string& product, const std::string& timestamp, const OrderType& type)
{
    std::vector<OrderBookEntry> filtered;
    for(const auto& e : entries)
    {
        if(e.product == product &&
            e.orderType == type &&
            e.timeStamp == timestamp)
        {
            filtered.push_back(e);
        }
    }
    return filtered;
}