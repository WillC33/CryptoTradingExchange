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

    /**
     * \brief Gets the earliest timestamp in the book
     * \return the earliest timestamp
     */
    std::string getEarliestTime();

    /**
     * \brief Gets the next timestamp in the book
     * \return the next timestamp
     */
    std::string getNextTime(const std::string& timestamp);

    /**
     * \brief gets the list of all known currency pairs in the book
     * \return list of known products
     */
    std::vector<std::string> getKnownProducts();

    /**
     * \brief gets all the orders
     * \return the entries member
     */
    std::vector<OrderBookEntry> getOrders();

    /**
     * \brief Gets all orders for a specified product
     * \param product the product to filter
     * \return an order book entry vector
     */
    std::vector<OrderBookEntry> getOrders(const std::string& product);

    /**
    * \brief get the matching orders
    * \param timestamp the time window
    * \param product the requested product pair
    * \param type the order type
    * \return vector of relevant orders
    */
    std::vector<OrderBookEntry> getOrders(const std::string& timestamp,
                                          const std::string& product,
                                          const OrderType& type);

    double changeSinceLogon(const std::string& product, const std::string& timestamp);
    double computeAveragePrice(const std::string& product, const std::string& timestamp);
    double computeLowPrice(const std::string& product, const std::string& timestamp);
    double computeHighPrice(const std::string& product, const std::string& timestamp);
    double computePriceSpread(const std::string& product, const std::string& timestamp);

private:
    std::vector<OrderBookEntry> entries;
    std::vector<OrderBookEntry> filterOrders(
     const std::string& product,
     const std::string& timestamp,
     const OrderType& type = OrderType::ask);

};



#endif //ORDERBOOK_H
