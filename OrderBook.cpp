#include "OrderBook.h"

#include <map>

#include "CSVReader.h"

OrderBook::OrderBook(const std::string& filename)
{
    entries = CSVReader::read(filename);
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

std::vector<OrderBookEntry> OrderBook::getOrders(const std::string& timestamp,
                                          const std::string& product,
                                          const OrderType& type)
{
    std::vector<OrderBookEntry> orders;
    for(const auto& e : entries)
    {
        if(e.product == product &&
            e.orderType == type &&
            e.timeStamp == timestamp)
        {
            orders.push_back(e);
        }
    }
    return orders;
}