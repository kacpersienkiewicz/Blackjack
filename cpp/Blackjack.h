// Functions and classes used in the main blackjack file

#include <iostream>
#include <array>
#include <string>
#include <numeric>
#include <random>
#include <ctime>
#include <vector>

class Card
{
    public:
        int deckNumber; 
        std::string Rank;
        std::string Suit;
        int Value;

        int getValue(int deckNumber)
        {
            int iRank = deckNumber % 13;
            if (iRank == 1){return 11;}
            else if (iRank == 11 || iRank == 12 || iRank == 0){return 10;}
            else if (iRank > 1 && iRank < 11){return iRank;}
            else{std::cout << "Rank Error: Invalid iRank.\n"; return -1;}
        };
        std::string getRank(int deckNumber)
        {
            int iRank = deckNumber % 13;
            std::string Rank;
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
            else{std::cout << "Rank Error: Invalid iRank.\n"; Rank="Invalid";}
            return Rank;
        };

        std::string getSuit(int deckNumber)
        {
            int iSuit = deckNumber / 13;
            std::string Suit;
            if (iSuit == 0){Suit = "Spades";}
            else if (iSuit == 1){Suit ="Hearts";}
            else if (iSuit == 2){Suit ="Clubs";}
            else if (iSuit == 3){Suit="Diamonds";}
            else{std::cout << "Suit Error: Invalid iSuit.\n"; Suit="Invalid";}
            return Suit;
        };

        int getiRank(int deckNumber){return deckNumber % 13;}

        int getiSuit(int deckNumber){return deckNumber / 13;}

        std::string getCard(std::string Rank, std::string Suit){return Rank + " of " + Suit;};

};

class Deck
{
    public:
        std::vector<Card> deck;

        std::vector<Card> createDeck()
        {
            std::vector<Card> deck;

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
        Card dealFromDeck(std::vector<Card> deck)
        {
            srand(std::time(0));
            int randomIndex = rand() % sizeof(deck);
            Card dealtCard = deck[randomIndex];
            deck.erase(deck.begin() + randomIndex);
            return dealtCard;
        }


};

class Hand
{
    public:
        std::vector<Card> hand;
        int HandValue;
        int AcesAvailable;
        int AcesUsed;
        
        int getHandValue(std::vector<Card> hand)
        {
           int total = 0;
           for (int i = 0; i < hand.size(); i++)
           {
                total += hand[i].Value;
           }
            return total;
        }

        int getAcesAvailable(std::vector<Card> hand, int AcesUsed)
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
    else if (PlayerTotal == DealerTotal){std::cout << "It's a push! Your bet is returned.\n"; money += bet;}
    else if (PlayerTotal > DealerTotal){std::cout << "You win! You gain " << bet << " dollars.\n"; money += 2*bet;}
    else if (PlayerTotal < DealerTotal && DealerTotal != 22){std::cout << "You lose! You lost " << bet << " dollars.\n";}
    else {std::cout << "Scoring Error: Invalid PlayerTotal and/or DealerTotal values.\n";}
    return money;
}


int DealerAction(Hand DealerHand, Deck deck)
{
    int DealerTotal = DealerHand.getHandValue(DealerHand.hand);
    std::cout << "The dealer shows a total of " << DealerTotal << ".\n";
    while (DealerTotal < 17)
    {
        Card newCard = deck.dealFromDeck(deck.deck);
        DealerHand.hand.push_back(newCard);
        DealerTotal += newCard.Value;
        if (newCard.Rank == "Ace"){DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, DealerHand.AcesUsed);}
        std::cout << "The dealer draws a " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings the dealer's total to " << DealerTotal << ".\n";
        if (DealerTotal > 21)
        {
            if (DealerHand.AcesAvailable > 0)
            {
                DealerTotal -= 10;
                DealerHand.AcesUsed++;
                DealerHand.AcesAvailable = DealerHand.getAcesAvailable(DealerHand.hand, DealerHand.AcesUsed);
                std::cout << "An Ace saved the dealer from going bust! The dealer's total now totals to " << DealerTotal << ".\n";
                continue;
            }
            else{DealerTotal = 22; break;}
        }
    }
    if (DealerTotal == 22){std::cout << "The dealer has gone bust!\n";}
    else{std::cout << "The dealer's final total is " << DealerTotal << ".\n";}
    return DealerTotal;
}

int PlayerAction(Hand PlayerHand, Deck deck, Card DealerCard2, int PlayerTotal, int bet, int money)
{
    char choice;
    bool initialTurn  = true;

        while (1)
        {
            if (initialTurn == true)
            {
            std::cout << "Your hand totals to " << PlayerTotal << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it, (s)tand, or (d)ouble down?\n";
            std::cin >> choice;
            }
            else
            {
                std::cout << "Your hand totals to " << PlayerTotal << ". The dealer shows a " << DealerCard2.getCard(DealerCard2.Rank, DealerCard2.Suit) << ".\n" << "Would you like to (h)it or (s)tand?\n";
                std::cin >> choice;
            }

            if (choice=='h')
            {
                
                Card newCard = deck.dealFromDeck(deck.deck);
                PlayerHand.hand.push_back(newCard);
                PlayerTotal += newCard.Value;
                if (newCard.Rank == "Ace"){PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);}
                
                std::cout << "Your new card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerTotal << ".\n";

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
                        PlayerTotal = 22;
                        break;
                    }
                }

                initialTurn = false;
            }   
            else if (choice=='s'){break;}
            else if (choice =='d' && initialTurn == true)
            {
                money -= bet;
                bet *= 2;
                if (money < 0){std::cout << "You cannot bet yourself into debt.\n\n"; continue;}
                Card newCard = deck.dealFromDeck(deck.deck);
                PlayerHand.hand.push_back(newCard);
                PlayerTotal += newCard.Value;
                if (newCard.Rank == "Ace"){PlayerHand.AcesAvailable = PlayerHand.getAcesAvailable(PlayerHand.hand, PlayerHand.AcesUsed);}
                std::cout << "Your final card is the " << newCard.getCard(newCard.Rank, newCard.Suit) << ", which brings your total to " << PlayerTotal << ", and brings your total bet to " << bet << ".\n";
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
                        PlayerTotal = 22;
                        break;
                    }
                }
                
                break;
            }
            else{std::cout << "Please enter a valid option. The only valid options are: 'h', 's', and 'd'. Doubling down is only valid on the initial turn.\n"; continue;}
        }

    if (PlayerTotal == 22){std::cout << "You have gone bust! You've lost your bet of " << bet << " dollars.\n";}
    else{std::cout << "Your final total is " << PlayerTotal << ".\n";}
    return PlayerTotal;
}