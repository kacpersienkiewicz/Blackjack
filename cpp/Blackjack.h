// Functions and classes used in the main blackjack file

#include <iostream>
#include <array>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <tuple>

using namespace std;

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

int Scoring(int PlayerTotal, int DealerTotal, int bet, int money)
{
    if (PlayerTotal == 22) {money -= bet;}
    else if (PlayerTotal == DealerTotal){cout << "It's a push! Your bet is returned.\n"; money += bet;}
    else if (PlayerTotal > DealerTotal){cout << "You win! You gain " << bet << " dollars.\n"; money += 2*bet;}
    else if (PlayerTotal < DealerTotal && DealerTotal != 22){cout << "You lose! You lost " << bet << " dollars.\n";}
    else {cout << "Scoring Error: Invalid PlayerHand.HandValue and/or DealerTotal values.\n";}
    return money;
}


tuple<int, Hand, Deck> DealerAction(Hand DealerHand, Deck deck)
{
    DealerHand.HandValue = DealerHand.getHandValue(DealerHand.hand);
    cout << "The dealer shows a total of " << DealerHand.HandValue << ".\n";
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

tuple<int, Hand, Deck, int, int> PlayerAction(Hand PlayerHand, Deck deck, Card DealerCard2, int bet, int money)
{
    char choice;
    bool initialTurn  = true;

        while (1)
        {   
            if (PlayerHand.hand.size() == 2)
            {
                if (PlayerHand.hand[0].Rank == PlayerHand.hand[1].Rank)
                {
                    cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Both of your cards are the same rank. Would you like to s(p)lit, (h)it, (s)tand, or (d)ouble down?\n";
                    cin >> choice;
                }
                else
                {
                    cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it, (s)tand, or (d)ouble down?\n";
                    cin >> choice;
                }
            }
            else
            {
                cout << "Your hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                cin >> choice;
            }

            if (choice=='h')
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
            else if (choice=='s'){break;}
            else if (choice =='d' && PlayerHand.hand.size() == 2)
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
            else if (choice == 'p' && PlayerHand.hand.size() == 2 && PlayerHand.hand[0].Rank == PlayerHand.hand[1].Rank)
            {
                money -= bet;
                bet *= 2;
                if (money < 0){cout << "You cannot bet yourself into debt.\n\n"; money += bet; continue;}

                Hand PlayerHand2;
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

                while(1)
                {
                    cout << "Your first hand totals to " << PlayerHand.HandValue << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                    cin >> choice;
                    if (choice=='h')
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
                    else if (choice=='s'){break;}
                    else{cout << "Please enter a valid option. The only valid options are: 'h', and 's'.\n"; continue;}
                }

                while(1)
                {
                    cout << "Your second hand totals to " << PlayerHand2.HandValue << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                    cin >> choice;

                    if (choice=='h')
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
                    else if (choice=='s'){break;}
                    else{cout << "Please enter a valid option. The only valid options are: 'h', and 's'.\n"; continue;}
                }
            }
            else{cout << "Please enter a valid option. The only valid options are: 'h', 's', 'p' and 'd'. Splitting and Doubling down is only valid on the initial turn. Spltting additionall requires having two cards of the same rank.\n"; continue;}
        }

    if (PlayerHand.HandValue == 22){cout << "You have gone bust! You've lost your bet of " << bet << " dollars.\n";}
    else{cout << "Your final total is " << PlayerHand.HandValue << ".\n";}
    tuple<int, Hand, Deck, int, int> resultantTuple = make_tuple(PlayerHand.HandValue, PlayerHand, deck, bet, money);
    return resultantTuple;
}