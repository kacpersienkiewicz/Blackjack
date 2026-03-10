/* 
The purpose of this is to create a game of blackjack played in the terminal
Doubling Down, Splitting, and Insurance are planned for implementation as well as a possible graphical ascii representation
*/
#include "Blackjack.h"

const int STARTINGMONEY = 100;
int money = STARTINGMONEY;


int main()
{
    std::cout << "Welcome to the Blackjack Table.\n";
    
    while (1)
    {
        char choice;
        if (money <= 0){
            
            std::cout << "You've gone bust! Would you like to rebuy? (y)es or (n)o\n";
            std::cin >> choice;

            if (choice == 'y')  {money = STARTINGMONEY;}
            else if (choice == 'n') {break;}
            else 
            {
                std::cout << "Please enter a valid option. The only valid options are: 'y' and 'n'\n";
                continue;
            }
        }
        int bet;
        std::cout << "You have " << money << " dollars. How much would you like to bet?\n";
        std::cin >> bet;
        if (bet > money)
        {
            std::cout << "You cannot bet more than you have.\n";
            continue;
        }
        else if (bet < 0) 
        {   
            std::cout << "You cannot bet a negative amount.\n";
            continue;
        }
        else money -= bet;
        
        Deck deck;
        deck.deck = deck.createDeck();
        Hand PlayerHand;
        Hand DealerHand;

        Card PlayerCard1 = deck.dealFromDeck(deck.deck);
        PlayerHand.hand.push_back(PlayerCard1);

        Card PlayerCard2 = deck.dealFromDeck(deck.deck);
        PlayerHand.hand.push_back(PlayerCard2);

        Card DealerCard1 = deck.dealFromDeck(deck.deck);
        DealerHand.hand.push_back(DealerCard1);

        Card DealerCard2 = deck.dealFromDeck(deck.deck);
        DealerHand.hand.push_back(DealerCard2);

        PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, 0);
        DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, 0);

        int PlayerTotal = PlayerHand.getHandValue(PlayerHand.hand);
        int DealerTotal = DealerHand.getHandValue(DealerHand.hand);
        std::cout << "Your hand is: the " << PlayerCard1.getCard(PlayerCard1.Rank, PlayerCard1.Suit) << " and the " << PlayerCard2.getCard(PlayerCard2.Rank, PlayerCard2.Suit) << ".\n";

        if (PlayerTotal > 21)
        {
            if (PlayerHand.AcesAvailable > 0)
            {
            PlayerTotal -= 10;
            PlayerHand.AcesUsed++;
            PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);

            std::cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerTotal << ".\n";
            }
            else
            {
                std::cout << "You went bust! You lose " << bet << " dollars.\n";
                PlayerTotal = 22;
                continue;
            }
        }
        else if (PlayerTotal == 21)
        {
            std::cout << " Natural Blackjack! You win " << bet*1.5 << " dollars.\n";
            money += bet*2.5;
            continue;
        }

        PlayerTotal = PlayerAction(PlayerHand, deck, DealerCard2, PlayerTotal, bet, money);
        DealerTotal = DealerAction(DealerHand, deck);
        money = Scoring(PlayerTotal, DealerTotal, bet, money);

    }

    std::cout << "Thanks for playing Blackjack!\n";

};