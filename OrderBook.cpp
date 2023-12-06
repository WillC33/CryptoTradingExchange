#include "OrderBook.h"

#include <iostream>
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

/**
 * \brief returns the full list of order book entrie
 * \return a vector of entries
 */
std::vector<OrderBookEntry> OrderBook::getOrders()
{
    return entries;
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

/**
 * \brief writes a new entry to the orderbook
 * \param entry the entry to write
 */
void OrderBook::writeOrder(const OrderBookEntry& entry)
{
        entries.push_back(entry);
        std::sort(entries.begin(), entries.end(), OrderBook::compare_by_timestamp);
}

/**
 * \brief Gets the current length of the order book
 * \return the number of orders
 */
unsigned int OrderBook::numberOfOrders()
{
    return this->entries.size();
}

/**
 * \brief compares two orders by their timestamp
 * \param e1 the first entry
 * \param e2 the second entry
 * \return whether the first is higher or lower
 */
bool OrderBook::compare_by_timestamp(const OrderBookEntry& e1, const OrderBookEntry& e2 )
{
    return e1.timeStamp < e2.timeStamp;
}

/**
 * \brief Compares ascending price
 * \param e1 the first entry
 * \param e2 the second entry
 * \return
 */
bool OrderBook::compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
    return e1.price < e2.price;
}

/**
 * \brief Compares descending price
 * \param e1 the first entry
 * \param e2 the second entry
 * \return
 */
bool OrderBook::compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
{
    return e1.price > e2.price;
}

/**
 * \brief The matching algorithm for closing open trades on the orderbook
 * \param product the product to match transactions for
 * \param timestamp the frame to match in
 * \return
 */
std::vector<OrderBookEntry> OrderBook::matchBidsToAsks(const std::string& product, const std::string& timestamp)
{
    //sorts asks by lowest first and bids by highest for the current timeframe
    auto asks = filterOrders(product, timestamp, OrderType::ask);
    auto bids = filterOrders(product, timestamp, OrderType::bid);
    std::sort(asks.begin(), asks.end(), OrderBook::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBook::compareByPriceDesc);

    std::vector<OrderBookEntry> sales;
    for (auto ask : asks)
    {
        for (auto bid : bids) // O(n²)
        {
            if (bid.price >= ask.price) // match
            {
                OrderBookEntry sale{
                    ask.price,
                    0,
                    timestamp,
                    product,
                    OrderType::sale
                };

                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);

                    bid.amount = 0; //the bid is complete
                    break;
                }

                if (bid.amount > ask.amount) // ask is completely gone, slice the bid
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);

                    bid.amount = bid.amount - ask.amount; // an amount of bid remains
                    break;
                }

                if (bid.amount < ask.amount) // bid is completely gone, slice the ask
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);

                    ask.amount = ask.amount - bid.amount; // an amount of ask remains
                    continue;
                }
            }
        }
    }
    return sales;
}


