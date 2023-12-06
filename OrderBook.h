#pragma once

#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include <string>
#include <vector>

#include "OrderBookEntry.h"


class OrderBook {
public:
    /**
     * \brief Creates an order book
     * \param filename the csv filename
     */
    explicit OrderBook(const std::string& filename);

    std::string getEarliestTime();
    std::string getNextTime(const std::string& timestamp);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders();
    void writeOrder(const OrderBookEntry& entry);

    double changeSinceLogon(const std::string& product, const std::string& timestamp);
    double computeAveragePrice(const std::string& product, const std::string& timestamp);
    double computeLowPrice(const std::string& product, const std::string& timestamp);
    double computeHighPrice(const std::string& product, const std::string& timestamp);
    double computePriceSpread(const std::string& product, const std::string& timestamp);
    unsigned int numberOfOrders();

    std::vector<OrderBookEntry> OrderBook::matchBidsToAsks(const std::string& product, const std::string& timestamp);

private:
     std::vector<OrderBookEntry> entries;
     std::vector<OrderBookEntry> filterOrders(
     const std::string& product,
     const std::string& timestamp,
     const OrderType& type = OrderType::ask);
     static bool compare_by_timestamp(const OrderBookEntry& e1, const OrderBookEntry& e2 );
    static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2);
    static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2);

};



#endif //ORDERBOOK_H
