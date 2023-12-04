#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

/**
 * Prints the help option
 */
void printHelp();

/**
 * Prints current exchange rates
 */
void printMarketStats();

/**
 * Handles the entry of an offer
 */
void handleOffer();

/**
 * Handles the entry of a bid
 */
void handleBid();

/**
 * Prints the wallet
 */
void printWallet();

/**
 * Completes trading and moves to the next time frame
 */
void completeTrades();

#endif //MENUFUNCTIONS_H
