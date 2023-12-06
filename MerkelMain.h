#ifndef MERKELMAIN_H
#define MERKELMAIN_H

#include "OrderBook.h"


class MerkelMain {

    public:
        MerkelMain();
        void init();

    private:
        void printMenu();
        int getUserOption();
        void processUserOption(int userOption);

        void printHelp();
        void printMarketStats();
        void handleOffer();
        void handleBid();
        void printWallet();
        void completeTrades();

        OrderBook orderbook{"OrderBook.csv"};

};

#endif //MERKELMAIN_H
