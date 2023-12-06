#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "CSVReader.h"
#include "OrderBookEntry.h"

/**
 * \brief tokenises a given string
 * \param csvLine the line to tokenise
 * \param seperator the seperator (defaults to , for CSV files)
 * \return a string vector of the tokenised string
 */
std::vector<std::string> CSVReader::tokenise(const std::string& csvLine, const char seperator = ',')
{
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end; //the start and end of the given token

    start = csvLine.find_first_not_of(seperator, 0); //first non seperator character
    do
    {
        end = csvLine.find_first_of(seperator, start); // first seperator character
        if (start == csvLine.length() || start == end) break; // if this is the entire string or the start and end are the same

        // if the end is non zero, grab the substring at the start position and take that many characters up to the seperator
        if (end >= 0 ) token = csvLine.substr(start, end - start);
        // if the end is zero we simply grab the whole string
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1; // go from the next char after the seperator
    }
    while (end != std::string::npos);
    // if the seperator is no longer included in the string end will return ::npos and the loop will stop running

    return tokens;
}

/**
 * \brief creates an order book entry from a tokenised line
 * \param tokens the token vector of the line
 * \return OrderBookEntry
 */
OrderBookEntry CSVReader::strings_to_order_book_entry(std::vector<std::string> tokens)
{
    try
    {
        if (tokens.size() != 5)
            throw std::invalid_argument("Invalid row syntax");

        const auto& timeStamp = tokens[0];
        const auto& product = tokens[1];
        const OrderType type = OrderBookEntry::parseOrderType(tokens[2]);
        const double price = std::stod(tokens[3]);
        const double amount = std::stod(tokens[4]);

        return OrderBookEntry{
            price,
            amount,
            timeStamp,
            product,
            type};
    }
    catch(std::exception&)
    {
        std::cout << "A CSV Line could not be converted" << std::endl;
        throw;
    }
}

/**
 * \brief converts user input to an entry
 * \param product the product pair
 * \param price the price
 * \param amount the amount
 * \param timestamp the timestamp
 * \param type the OrderType
 * \return an OrderBookEntry
 */
OrderBookEntry CSVReader::input_to_order_book_entry(
      std::string product,
      std::string price,
      std::string amount,
      std::string timestamp,
      OrderType type
      )
{
    try
    {
        const double priceDbl = std::stod(price);
        const double amountDbl = std::stod(amount);

        return OrderBookEntry{
            priceDbl,
            amountDbl,
            timestamp,
            product,
            type,
            "user"
        };
    }
    catch(std::exception&)
    {
        std::cout << "The input line could not be converted" << std::endl;
        throw;
    }
}

/**
 * \brief Parses an order book CSV file into valid order objects
 * \return a vector of OrderBookEntry objects
 */
std::vector<OrderBookEntry> CSVReader::read(std::string file)
{
    std::ifstream csvFile{file};
    std::vector<OrderBookEntry> entries;
    std::string line;

    if (!csvFile.is_open())
        throw std::ios_base::failure("File opening failed");

    while (std::getline(csvFile, line))
    {
        auto tokens = tokenise(line, ',');
        try
        {
            auto obe = strings_to_order_book_entry(tokens);
            entries.push_back(obe);
        }
        catch (std::exception)
        {
            continue;
        }
    }

    csvFile.close();
    return entries;
}