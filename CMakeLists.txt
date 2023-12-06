cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled main.cpp
        MerkelMain::MenuFunctions.cpp
        OrderBookEntry.cpp
        OrderBookEntry.h
        MerkelMain.cpp
        MerkelMain.h
        FinancialFunctions.cpp
        CSVReader.cpp
        CSVReader.h
        FinancialFunctions.h
        OrderBook.cpp
        OrderBook.h
)
