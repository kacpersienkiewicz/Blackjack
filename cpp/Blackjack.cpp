/* 
The purpose of this is to create a game of blackjack played in the terminal
Doubling Down, Splitting, and Insurance are planned for implementation as well as a possible graphical ascii representation
*/
#include "Blackjack.h"

const int STARTINGMONEY{100};
int money = STARTINGMONEY;

int main()
{
    cout << "Welcome to the Blackjack Table.\n";

    while (1)
    {
        char choice;
        if (money <= 0){
            
            cout << "You've gone bust! Would you like to rebuy? (y)es or (n)o\n";
            cin >> choice;

            if (choice == 'y')  {money = STARTINGMONEY;}
            else if (choice == 'n') {break;}
            else 
            {
                cout << "Please enter a valid option. The only valid options are: 'y' and 'n'\n";
                continue;
            }
        }
        int bet;
        cout << "You have " << money << " dollars. How much would you like to bet? Non whole number bets will be converted to a whole number.\n";
        cin >> bet;

        if (bet > money)
        {
            cout << "You cannot bet more than you have.\n";
            continue;
        }
        else if (bet < 0) 
        {   
            cout << "You cannot bet a negative amount.\n";
            continue;
        }
        else 
        {
            money -= bet;
            cout << "You bet " << bet << " dollars and now have " << money << " dollars left over.\n";
        }
        Deck deck;
        deck.deck = deck.createDeck();
        Hand PlayerHand;
        Hand DealerHand;

        Card PlayerCard1;
        Card PlayerCard2;
        Card DealerCard1;
        Card DealerCard2;

        tie(PlayerCard1, deck.deck) = deck.dealFromDeck();
        PlayerHand.hand.push_back(PlayerCard1);

        tie(PlayerCard2, deck.deck) = deck.dealFromDeck();
        PlayerHand.hand.push_back(PlayerCard2);

        tie(DealerCard1, deck.deck) = deck.dealFromDeck();
        DealerHand.hand.push_back(DealerCard1);

        tie(DealerCard2, deck.deck) = deck.dealFromDeck();
        DealerHand.hand.push_back(DealerCard2);

        PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, 0);
        DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, 0);

        int PlayerTotal = PlayerHand.getHandValue(PlayerHand.hand);
        int DealerTotal = DealerHand.getHandValue(DealerHand.hand);
        cout << "Your hand is: the " << PlayerCard1.getCard(PlayerCard1.Rank, PlayerCard1.Suit) << " and the " << PlayerCard2.getCard(PlayerCard2.Rank, PlayerCard2.Suit) << ".\n";

        if (PlayerTotal > 21)
        {
            if (PlayerHand.AcesAvailable > 0)
            {
            PlayerTotal -= 10;
            PlayerHand.AcesUsed++;
            PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);

            cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerTotal << ".\n";
            }
            else
            {
                cout << "You went bust! You lose " << bet << " dollars.\n";
                PlayerTotal = 22;
                continue;
            }
        }
        else if (PlayerTotal == 21)
        {
            cout << " Natural Blackjack! You win " << bet*1.5 << " dollars.\n";
            money += bet*2.5;
            continue;
        }

        tie(PlayerTotal, PlayerHand, deck, bet, money) = PlayerAction(PlayerHand, deck, DealerCard2, PlayerTotal, bet, money);
        tie(DealerTotal, DealerHand, deck) = DealerAction(DealerHand, deck);
        money = Scoring(PlayerTotal, DealerTotal, bet, money);

    }

    cout << "Thanks for playing Blackjack!\n";

};