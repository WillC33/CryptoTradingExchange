#ifndef MERKELMAIN_H
#define MERKELMAIN_H

class MerkelMain {

    public:
        MerkelMain();
        void init();

    private:
        void printMenu();
        int getUserOption();
        void processUserOption(int userOption);
};

#endif //MERKELMAIN_H
