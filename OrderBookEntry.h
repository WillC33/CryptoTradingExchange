#pragma once
#include <string>
/**
* \brief Whether the transaction is a bid or an ask
 */
enum class OrderType {bid, ask, bidSale, askSale};

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
     * \param _username the username of the entry
     */
    OrderBookEntry(
        const double& _price,
        const double& _amount,
        const std::string& _timeStamp,
        const std::string& _product,
        const OrderType& _orderType,
        const std::string& _username = "dataset"
        );

    static OrderType parseOrderType(std::string);

    // Members
    double price;
    double amount;
    std::string timeStamp;
    std::string product;
    OrderType orderType;
    std::string username;
};