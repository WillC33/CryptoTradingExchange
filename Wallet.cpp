#include "Wallet.h"

#include <iostream>

#include "CSVReader.h"

/**
 * \brief Adds funds of a specific type to the wallet
 * \param type The type of currency to be funded
 * \param amount The amount of currency to be added
 */
void Wallet::fund(const std::string& type, const double& amount)
{
    if (amount < 0)
    {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    auto currentQuantity = funds.find(type);
    if (currentQuantity == funds.end())
    {
        funds.insert({type, amount});
        return;
    }
    currentQuantity->second = currentQuantity->second + amount;
}

/**
 * \brief Deducts amount from the wallet of a specific currency type
 * \param type The type of currency to be deducted
 * \param amount The amount of currency to be deducted
 */
void Wallet::payFrom(const std::string& type, const double& amount)
{
    if (amount < 0)
    {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    if (!hasSufficientCurrency(type, amount))
    {
        std::cout << "Insufficient Funds" << std::endl;
        return;
    }
    auto currentQuantity = funds.find(type);
    currentQuantity->second = currentQuantity->second - amount;
}

/**
 * \brief Checks if the wallet has sufficient amount of a specific type of currency
 * \param type The type of currency to check
 * \param amount The amount of currency to check for
 * \return Returns true if there is sufficient currency of the specified type, else returns false
 */
bool Wallet::hasSufficientCurrency(const std::string& type, const double& amount)
{
    const auto& currentQuantity = funds.find(type);

    if(currentQuantity == funds.end())
        return false; // None found

    return currentQuantity->second >= amount;
}

/**
* \brief Prints the current state of the wallet, showing all types of currency and their amounts
*/
void Wallet::print()
{
  for(const auto& [name, quantity] : funds)
    std::cout << name << ": " << quantity << std::endl;
}

/**
 * \brief Checks whether the user can fulfill a given order
 * \param order An order
 * \return fulfillable or not
 */
bool Wallet::fulfillable(const OrderBookEntry& order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    if (order.orderType == OrderType::ask)
    {
        std::string currency = currs[0];
        return hasSufficientCurrency(currency, order.amount);
    }

    if (order.orderType == OrderType::bid)
    {
        double total = order.amount * order.price;
        std::string currency = currs[1];
        return hasSufficientCurrency(currency, total);
    }

    return false;
}

/**
 * \brief handles the effect of a sale on the wallet
 * \param sale the sale
 */
void Wallet::processSale(const OrderBookEntry& sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

    if (sale.orderType == OrderType::askSale)
    {
        const double& outgoing = sale.amount;
        const std::string& outgoingCurrency = currs[0];
        payFrom(outgoingCurrency, outgoing);

        const double& incoming = sale.amount * sale.price;
        const std::string& incomingCurrency = currs[1];
        fund(incomingCurrency, incoming);
    }
    else if (sale.orderType == OrderType::bidSale)
    {
        const double& outgoing = sale.amount * sale.price;
        const std::string& outgoingCurrency = currs[1];
        payFrom(outgoingCurrency, outgoing);

        const double& incoming = sale.amount;
        const std::string& incomingCurrency = currs[0];
        fund(incomingCurrency, incoming);
    }
}

Wallet::Wallet() = default;
