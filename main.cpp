#include <iostream>
#include <random>

struct Slots {
    short first;
    short second;
    short third;
};

int randomNumber() {
    static std::random_device randomSeed;
    static std::mt19937 randomInteger(randomSeed());
    std::uniform_int_distribution<> numberField(2, 7);

    return numberField(randomInteger);
}

int howRate(int balance) {
    while(true) {
        std::cout << "So, how much will you bet: ";
        int rate;
        std::cin >> rate;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "You understand that you need to enter the amount in numbers, right?\n";
            continue;
        }

        if (balance < rate) {
            std::cout << "You don't have that much in your account. Enter a different amount.\n";
            continue;
        }

        if (rate <= 0) {
            std::cout << "Are you laughing at me? Make a normal bet.\n";
            continue;
        }

        return rate;
    }

}

void casino() {
    static int balance{1000};
    bool exit = true;

    Slots slot;

    std::cout << "Your balance: " << balance << ". Try to win as much as possible!" << std::endl;

    do {
        int rate = howRate(balance);
        balance -= rate;

        slot.first = randomNumber();
        slot.second = randomNumber();
        slot.third = randomNumber();
        
        std::cout << "Your relust is... " << "( " << slot.first << " | " << slot.second << " | " << slot.third << " )" << std::endl;
        
        if (slot.first == 7 && slot.second == 7 && slot.third == 7) {
            std::cout << "Jackpot! (Your balance is multiplied by 10)\n";
            rate *= 10;
            balance += rate;
        }
        else if (slot.first == slot.second && slot.second == slot.third) {
            std::cout << "Good job! You're lucky. (Your balance is multiplied by 5)\n";
            rate *= 5;
            balance += rate;
        }
        else if (slot.first == slot.second || slot.first == slot.third || slot.second == slot.third) {
            std::cout << "Not bad. (Your balance is multiplied by 2)\n";
            rate *= 2;
            balance += rate;
        }
        else {
            std::cout << "Bad luck, but don't give up!\n";
        }

        if (balance <= 0){
            std::cout << "You lost everything! The casino always wins eventually. Bye!\n";
            break;
        }

        std::cout << "Do you want to continue? (y - Yes. n - No): ";
        char response;
        std::cin >> response;
        
        std::cin.ignore(32767, '\n');
        
        switch (response) {
            case 'Y':
            case 'y':
                std::cout << "Wonderful!" << std::endl;
                break;
            case 'N':
            case 'n':
                std::cout << "Ok, good luck." << std::endl;
                exit = false;
                break;
            default:
                std::cout << "Enter only \"y\" or \"n\".\n";
                break;
        }

        std::cout << "Your balance: " << balance << std::endl;

    } while(exit);
}

void doYouWantPlay() {
    bool isPlay = true;

    std::cout << "Welcome to the \"All or Nothing\" casino!" << std::endl;

    while (isPlay) {
        std::cout << "Do you want play? (y - Yes. n - No): ";
        char response;
        std::cin >> response;
        
        std::cin.ignore(32767, '\n');
        
        switch (response) {
            case 'Y':
            case 'y':
                std::cout << "Wonderful! Good luck!" << std::endl;
                isPlay = false;
                casino();
                break;
            case 'N':
            case 'n':
                std::cout << "Ok, good luck." << std::endl;
                isPlay = false;
                break;
            default:
                std::cout << "Enter only \"y\" or \"n\".\n";
                break;
        }
    }
}

int main() {
    doYouWantPlay();

    return 0;
}
