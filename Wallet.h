#pragma once
#ifndef WALLET_H
#define WALLET_H
#include <map>
#include <string>

#include "OrderBookEntry.h"


class Wallet {
public:
    Wallet();

    void fund(const std::string& type, const double& amount);
    void payFrom(const std::string& type, const double& amount);
    bool hasSufficientCurrency(const std::string& type, const double& amount);
    bool fulfillable(const OrderBookEntry& order);
    void processSale(const OrderBookEntry& sale);
    void print();

private:
    std::map<std::string, double> funds;
};

#endif //WALLET_H
