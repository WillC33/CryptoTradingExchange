#pragma once
#ifndef CSVREADER_H
#define CSVREADER_H
#include <vector>

#include "OrderBookEntry.h"

class CSVReader
{
public:
   static std::vector<OrderBookEntry> read(std::string);
   static std::vector<std::string> tokenise(const std::string&, char);
   static OrderBookEntry input_to_order_book_entry(
      std::string product,
      std::string price,
      std::string amount,
      std::string timestamp,
      OrderType type
      );

private:
   static OrderType parseOrderType(std::string);
   static OrderBookEntry strings_to_order_book_entry(std::vector<std::string>);
};

#endif //CSVREADER_H
