#include <iostream>

void printMenu();
int getUserOption();
void processUserOption(int);

/**
 * ENTRY POINT
 */
int main()
{
    std::cout << "Welcome to the MerkelRex Crypto Trading Exchange" << std::endl;

    while (true)
    {
        printMenu();
        const int userOption = getUserOption();
        processUserOption(userOption);
    }
    return 0;
}
