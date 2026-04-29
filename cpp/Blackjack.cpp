/* 
The purpose of this is to create a game of blackjack played in the terminal
TODO:
* Insurance
* Splitting
* Graphical ASCII
*/

#include <iostream>
#include <array>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <tuple>

using namespace std;

const int STARTINGMONEY{100};
int money = STARTINGMONEY;

class Card
{
    public:
        int deckNumber; 
        string Rank;
        string Suit;
        int Value;

        int getValue(int deckNumber)
        {
            int iRank = deckNumber % 13;
            if (iRank == 1){return 11;}
            else if (iRank == 11 || iRank == 12 || iRank == 0){return 10;}
            else if (iRank > 1 && iRank < 11){return iRank;}
            else{cout << "Rank Error: Invalid iRank.\n"; return -1;}
        };
        string getRank(int deckNumber)
        {
            int iRank = deckNumber % 13;
            string Rank;
            if (iRank==1){Rank="Ace";}
            else if (iRank==2){Rank="Two";}
            else if (iRank==3){Rank="Three";}
            else if (iRank==4){Rank="Four";}
            else if (iRank==5){Rank="Five";}
            else if (iRank==6){Rank="Six";}
            else if (iRank==7){Rank="Seven";}
            else if (iRank==8){Rank="Eight";}
            else if (iRank==9){Rank="Nine";}
            else if (iRank==10){Rank="Ten";}
            else if (iRank==11){Rank="Jack";}
            else if (iRank==12){Rank="Queen";}
            else if (iRank==0){Rank="King";}
            else{cout << "Rank Error: Invalid iRank.\n"; Rank="Invalid";}
            return Rank;
        };

        string getSuit(int deckNumber)
        {
            int iSuit = deckNumber / 13;
            string Suit;
            if (iSuit == 0){Suit = "Spades";}
            else if (iSuit == 1){Suit ="Hearts";}
            else if (iSuit == 2){Suit ="Clubs";}
            else if (iSuit == 3){Suit="Diamonds";}
            else{cout << "Suit Error: Invalid iSuit.\n"; Suit="Invalid";}
            return Suit;
        };

        int getiRank(int deckNumber){return deckNumber % 13;}

        int getiSuit(int deckNumber){return deckNumber / 13;}

        string getCard(string Rank, string Suit){return Rank + " of " + Suit;};

};

class Deck
{
    public:
        vector<Card> deck;

        vector<Card> createDeck()
        {
            vector<Card> deck;

            for(int i = 0; i < 52; i++)
            {
                Card currentCard;
                currentCard.deckNumber = i;
                currentCard.Rank = currentCard.getRank(i);
                currentCard.Suit = currentCard.getSuit(i);
                currentCard.Value = currentCard.getValue(i);

                deck.push_back(currentCard);
            };
            
            return deck;
        }
        tuple<Card, vector<Card>> dealFromDeck()
        {
            srand(time(0) + deck.size());
            int randomIndex = rand() % deck.size();
            Card dealtCard = deck[randomIndex];
            deck.erase(deck.begin() + randomIndex);
            tuple<Card, vector<Card>> resultantTuple = make_tuple(dealtCard, deck);
            return resultantTuple;
        }

};

class Hand
{
    public:
        vector<Card> hand;
        int HandValue;
        int AcesAvailable;
        int AcesUsed;
        
        int getHandValue(vector<Card> hand)
        {
           int total = 0;
           for (int i = 0; i < hand.size(); i++)
           {
                total += hand[i].Value;
           }
            return total;
        }

        int getAcesAvailable(vector<Card> hand, int AcesUsed)
        {
            int AceCount = 0;
            for (int i = 0; i < hand.size(); i++)
            {
                if(hand[i].Rank == "Ace")
                {
                    AceCount++;
                }
            }
            int AcesAvailable = AceCount - AcesUsed; 
            return AcesAvailable;
        }


};

bool isSavedByAce(Hand& hand)
{
    if(hand.AcesAvailable > 0)
    {
        hand.HandValue -= 10;
        hand.AcesUsed++;
        hand.AcesAvailable = hand.getAcesAvailable(hand.hand, hand.AcesUsed);
        cout << "An Ace saved you from going bust! Your hand now totals to " << hand.HandValue << ".\n";
        return true;
    }
    else
    {
        hand.HandValue = 22;
        return false;
    }
}

tuple<int, Hand, Deck> DealerAction(Hand DealerHand, Deck deck)
{
    DealerHand.HandValue = DealerHand.getHandValue(DealerHand.hand);

    if (DealerHand.HandValue >= 17){cout << "The dealer shows a total of " << DealerHand.HandValue << ".\nThe dealer stands.\n";}
    else{cout << "The dealer shows a total of " << DealerHand.HandValue << ".\n";}
    
    while (DealerHand.HandValue < 17)
    {
        Card newCard;
        tie(newCard, deck.deck) = deck.dealFromDeck();
        DealerHand.hand.push_back(newCard);
        DealerHand.HandValue += newCard.Value;
        if (newCard.Rank == "Ace"){DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, DealerHand.AcesUsed);}
        cout << "The dealer draws a " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings the dealer's total to " << DealerHand.HandValue << ".\n";
        if (DealerHand.HandValue > 21)
        {
            if (DealerHand.AcesAvailable > 0)
            {
                DealerHand.HandValue -= 10;
                DealerHand.AcesUsed++;
                DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, DealerHand.AcesUsed);
                cout << "An Ace saved the dealer from going bust! The dealer's total now totals to " << DealerHand.HandValue << ".\n";
                continue;
            }
            else{DealerHand.HandValue = 22; break;}
        }
    }
    if (DealerHand.HandValue == 22){cout << "The dealer has gone bust!\n";}
    else{cout << "The dealer's final total is " << DealerHand.HandValue << ".\n";}
    tuple<int, Hand, Deck> resultantTuple = make_tuple(DealerHand.HandValue, DealerHand, deck);
    return resultantTuple;
}

int Scoring(int PlayerTotal, int DealerTotal, int bet, int money)
{
    if (PlayerTotal > 21) {cout << "You lose! You lost " << bet << " dollars.\n";}
    else if (PlayerTotal == DealerTotal){cout << "It's a push! Your bet is returned.\n"; money += bet;}
    else if (PlayerTotal > DealerTotal){cout << "You win! You gain " << bet << " dollars.\n"; money += 2*bet;}
    else if (PlayerTotal < DealerTotal && DealerTotal > 21){cout << "You win! You gain " << bet << " dollars.\n"; money += 2*bet;}
    else if (PlayerTotal < DealerTotal && DealerTotal < 22){cout << "You lose! You lost " << bet << " dollars.\n";}
    else {cout << "Scoring Error: Invalid PlayerTotal and/or DealerTotal values.\nPlayer's Total: " << PlayerTotal << "\nDealer's Total: " << DealerTotal << '\n';}
    return money;
}

int main()
{
    cout << "Welcome to the Blackjack Table.\n";

    while(true)
    {
        char choice;
        if (money <= 0)
        {
            
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
        cout << "You have " << money << " dollars. How much would you like to bet? Bets are rounded to the nearest whole number.\n";
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
        Hand PlayerHand2; //Unneeded unless splitting
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

        PlayerHand.HandValue = PlayerHand.getHandValue(PlayerHand.hand);
        DealerHand.HandValue = DealerHand.getHandValue(DealerHand.hand);
        cout << "Your hand is: the " << PlayerCard1.getCard(PlayerCard1.Rank, PlayerCard1.Suit) << " and the " << PlayerCard2.getCard(PlayerCard2.Rank, PlayerCard2.Suit) << ".\n";

        if (PlayerHand.HandValue > 21)
        {
            if (PlayerHand.AcesAvailable > 0)
            {
            PlayerHand.HandValue -= 10;
            PlayerHand.AcesUsed++;
            PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);

            cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerHand.HandValue << ".\n";
            }
            else
            {
                cout << "You went bust! You lose " << bet << " dollars.\n";
                PlayerHand.HandValue = 22;
                continue;
            }
        }
        else if (PlayerHand.HandValue == 21)
        {
            cout << " Natural Blackjack! You win " << bet*1.5 << " dollars.\n";
            money += bet*2.5;
            continue;
        }

        //Player Action

        bool initialTurn  = true;
        bool splitCard = false;

        while (true)
        {
            if (PlayerHand.hand.size() == 2)
            {
                if (PlayerHand.hand[0].Rank == PlayerHand.hand[1].Rank)
                {
                    cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerHand.hand[1].getCard(DealerHand.hand[1].Rank, DealerHand.hand[1].Suit) << ".\nBoth of your cards are the same rank. Would you like to s(p)lit, (h)it, (s)tand, or (d)ouble down?\n";
                    cin >> choice;
                }
                else
                {
                    cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerHand.hand[1].getCard(DealerHand.hand[1].Rank, DealerHand.hand[1].Suit) << ".\nWould you like to (h)it, (s)tand, or (d)ouble down?\n";
                    cin >> choice;
                }
            }
            else
            {
                cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerHand.hand[1].getCard(DealerHand.hand[1].Rank, DealerHand.hand[1].Suit) << ".\nWould you like to (h)it, or (s)tand?\n";
                cin >> choice;
            }

            if(choice == 's'){break;}
            else if(choice=='h')
            {
                Card newCard;
                tie(newCard, deck.deck) = deck.dealFromDeck();
                PlayerHand.hand.push_back(newCard);
                PlayerHand.HandValue += newCard.Value;
                if (newCard.Rank == "Ace"){PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);}

                cout << "Your new card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerHand.HandValue << ".\n";

                if (PlayerHand.HandValue > 21)
                {
                    if (PlayerHand.AcesAvailable > 0)
                    {
                        PlayerHand.HandValue -= 10;
                        PlayerHand.AcesUsed++;
                        PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);
                        cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerHand.HandValue << ".\n";
                    }
                    else
                    {
                        PlayerHand.HandValue = 22;
                        break;
                    }
                }

            }
            else if(choice=='d' && PlayerHand.hand.size() == 2)
            {
                money -= bet;
                bet *= 2;
                if (money < 0){cout << "You cannot bet yourself into debt.\n\n"; money += bet; continue;}
                Card newCard;
                tie(newCard, deck.deck) = deck.dealFromDeck();
                PlayerHand.hand.push_back(newCard);
                PlayerHand.HandValue += newCard.Value;
                if (newCard.Rank == "Ace"){PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);}
                cout << "Your final card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerHand.HandValue << ", and brings your total bet to " << bet << ".\n";
                if (PlayerHand.HandValue > 21)
                {
                    if (PlayerHand.AcesAvailable > 0)
                    {
                    PlayerHand.HandValue -= 10;
                    PlayerHand.AcesUsed++;
                    PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);
                    cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerHand.HandValue << ".\n";
                    }
                    else
                    {
                        PlayerHand.HandValue = 22;
                        break;
                    }
                }

                break;
            }
            else if(choice == 'p' && PlayerHand.hand.size() == 2 && PlayerHand.hand[0].Rank == PlayerHand.hand[1].Rank)
            {
                splitCard = true;
                money -= bet;
                bet *= 2;
                if (money < 0){cout << "You cannot bet yourself into debt.\n\n"; money += bet; continue;}

                PlayerHand2.hand[0] = PlayerHand.hand[1];
                PlayerHand.hand.erase(PlayerHand.hand.begin() + 1);
                if (PlayerHand.hand[0].Rank == "Ace")
                {
                    PlayerHand.AcesUsed = 0;
                    PlayerHand.AcesAvailable = 1;
                    PlayerHand2.AcesUsed = 0;
                    PlayerHand2.AcesAvailable = 1;

                }

                Card newCard;
                tie(newCard, deck.deck) = deck.dealFromDeck();
                PlayerHand.hand.push_back(newCard);
                tie(newCard, deck.deck) = deck.dealFromDeck();
                PlayerHand2.hand.push_back(newCard);

                PlayerHand.HandValue = PlayerHand.getHandValue(PlayerHand.hand);
                PlayerHand2.HandValue = PlayerHand2.getHandValue(PlayerHand2.hand);

                while(true)
                {
                    cout << "Your first hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerHand.hand[1].getCard(DealerHand.hand[1].Rank, DealerHand.hand[1].Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                    cin >> choice;

                    if(choice ='h')
                    {
                        Card newCard;
                        tie(newCard, deck.deck) = deck.dealFromDeck();
                        PlayerHand.hand.push_back(newCard);
                        PlayerHand.HandValue += newCard.Value;
                        if (newCard.Rank == "Ace"){PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);}
                        cout << "Your new card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerHand.HandValue << ".\n";
                        
                        if (PlayerHand.HandValue > 21)
                        {
                            if (PlayerHand.AcesAvailable > 0)
                            {
                                PlayerHand.HandValue -= 10;
                                PlayerHand.AcesUsed++;
                                PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);
                                cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerHand.HandValue << ".\n";
                            }
                            else
                            {
                                PlayerHand.HandValue = 22;
                                break;
                            }
                        }                        
                    }              
                    else if(choice = 's'){break;}
                    else{cout << "Please enter a valid option. The only valid options are: 'h', and 's'.\n"; continue;}
                }

                while(true)
                {
                    cout << "Your second hand totals to " << PlayerHand2.HandValue << ". The dealer shows a " << DealerHand.hand[1].getCard(DealerHand.hand[1].Rank, DealerHand.hand[1].Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                    cin >> choice;

                    if(choice ='h')
                    {
                        Card newCard;
                        tie(newCard, deck.deck) = deck.dealFromDeck();
                        PlayerHand2.hand.push_back(newCard);
                        PlayerHand2.HandValue += newCard.Value;
                        if (newCard.Rank == "Ace"){PlayerHand2.AcesAvailable = PlayerHand2.getAcesAvailable(PlayerHand2.hand, PlayerHand2.AcesUsed);}
                        
                        cout << "Your new card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerHand2.HandValue << ".\n";

                        if (PlayerHand2.HandValue > 21)
                        {
                            if (PlayerHand2.AcesAvailable > 0)
                            {
                                PlayerHand2.HandValue -= 10;
                                PlayerHand2.AcesUsed++;
                                PlayerHand2.AcesAvailable = PlayerHand2.getAcesAvailable(PlayerHand2.hand, PlayerHand2.AcesUsed);
                                cout << "An Ace saved you from going bust! Your hand now totals to " << PlayerHand2.HandValue << ".\n";
                            }
                            else
                            {
                                PlayerHand2.HandValue = 22;
                                break;
                            }
                        } 
                    }             
                    else if(choice = 's'){break;}
                    else{cout << "Please enter a valid option. The only valid options are: 'h', and 's'.\n"; continue;}
                }
            }
 
        }
        if (PlayerHand.HandValue > 21){cout << "You have gone bust! You've lost your bet of " << bet << " dollars.\n";}
        else{cout << "Your final total is " << PlayerHand.HandValue << ".\n";}

        //Dealer Action
        tie(DealerHand.HandValue, DealerHand, deck) = DealerAction(DealerHand, deck);

        //Scoring
        if(splitCard == true)
        {
            money = Scoring(PlayerHand.HandValue, DealerHand.HandValue, bet, money) + Scoring(PlayerHand2.HandValue, DealerHand.HandValue, bet, money);
        }
        else
        {
            money = Scoring(PlayerHand.HandValue, DealerHand.HandValue, bet, money);
        }
    }

    cout << "Thanks for playing Blackjack!\n";
};