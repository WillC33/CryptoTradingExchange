#pragma once
#ifndef CSVREADER_H
#define CSVREADER_H
#include <vector>

#include "OrderBookEntry.h"

class CSVReader
{
public:
   static std::vector<OrderBookEntry> read(std::string);

private:
   static OrderType parseOrderType(std::string);
   static std::vector<std::string> tokenise(const std::string&, char);
   static OrderBookEntry strings_to_order_book_entry(std::vector<std::string>);
};

#endif //CSVREADER_H
