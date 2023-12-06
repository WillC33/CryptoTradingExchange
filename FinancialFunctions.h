#pragma once
#include <vector>
#include "OrderBookEntry.h"

class FinancialFunctions
{
public:
    static double computeAveragePrice(const std::vector<OrderBookEntry>& entries);
    static double computeLowPrice(const std::vector<OrderBookEntry>& entries);
    static double computeHighPrice(const std::vector<OrderBookEntry>& entries);
    static double computePriceSpread(const std::vector<OrderBookEntry>& entries);

};
