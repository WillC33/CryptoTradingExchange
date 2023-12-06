#pragma once
#include <string>
/**
* \brief Whether the transaction is a bid or an ask
 */
enum class OrderType {bid, ask};

/**
 * \brief Represents an entry in the order books
 */
class OrderBookEntry
{
public:
    /**
     * \brief Public ctor for an order book entry
     * \param _price the requested transaction price
     * \param _amount  the amount of the transaction
     * \param _timeStamp when the transaction was created
     * \param _product the requested products
     * \param _orderType whether the transaction is an order or a bid
     */
    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timeStamp,
        std::string _product,
        OrderType _orderType);

    static OrderType parseOrderType(std::string);

    // Members
    double price;
    double amount;
    std::string timeStamp;
    std::string product;
    OrderType orderType;
};