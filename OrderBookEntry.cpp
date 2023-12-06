#include "OrderBookEntry.h"
#include <string>

OrderBookEntry::OrderBookEntry(
        double _price,
        double _amount,
        std::string _timeStamp,
        std::string _product,
        OrderType _orderType)
    : price(_price),
    amount(_amount),
    timeStamp(_timeStamp),
    product(_product),
    orderType(_orderType)
    {

    }

/**
 * \brief Parses a string into an OrderType
 * \param value the value of the orderType
 * \return an OrderType enum value
 */
OrderType OrderBookEntry::parseOrderType(std::string value)
{
    //handling for non lowercase string versions of the type
    for(char& c : value)
    {
        c = static_cast<char>(tolower(c));
    }

    if (value == "bid") return OrderType::bid;
    if (value == "ask") return OrderType::ask;

    throw std::invalid_argument("Order must be a bid or ask");
}
