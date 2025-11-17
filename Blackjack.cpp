// The purpose of this is to create a game of blackjack played in the terminal
// Perhaps visualize the game using a tbd gfx library

#include "BlackjackFunctions.h"

int StartingMoney = 100;
int money = StartingMoney;
int PlayerAceCount, DealerAceCount;


int main()
{

    std::cout << "Welcome to the blackjack table. You currently have " << money << " dollars.\n";
    
    while (1)
    {
        char choice;
        if (money <= 0)
            
            std::cout << "You've gone bust! Would you like to rebuy? (y) or (n)" << std::endl;
            std::cin >> choice;

            if (choice == 'y')  {money = StartingMoney;}
            else if (choice == 'n') {break;}
            else 
            {
                std::cout << "Please enter a valid option." << std::endl;
                continue;
            }
        int bet;
        std::cout << "You have " << money << " dollars. How much would you like to bet?" << std::endl;
        std::cin >> bet;
        
        if (bet > money)
        {
            std::cout << "You cannot bet more than you have." << std::endl;
            continue;
        }
        else if (bet < 0) 
        {   
            std::cout << "You cannot bet a negative amount." << std::endl;
            continue;
        }
        else money -= bet;

        
    }

    std::cout << "Thanks for playing Blackjack!" << std::endl;

};