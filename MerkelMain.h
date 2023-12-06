#ifndef MERKELMAIN_H
#define MERKELMAIN_H

#include "OrderBook.h"
#include "Wallet.h"


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

        std::string currentTime;
        OrderBook orderbook{"./OrderBook.csv"};
        Wallet wallet;

};

#endif //MERKELMAIN_H
