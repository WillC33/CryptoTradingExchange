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
