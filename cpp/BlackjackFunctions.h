// Functions used in the main blackjack file

#include <iostream>
#include <string>
#include <numeric>
#include <random>
#include <vector>

class Card
{
    private:
        // deck has a total of 52 in it, deckNumber goes from 0 to 51 where the first 13 are one suit, the next suit are another etc.
        int deckNumber; 
        std::string Rank;
        std::string Suit;
        bool faceUp;
    public:
        std::string getRank(int deckNumber)
        {
            int iRank = deckNumber % 13;
            std::string Rank;
            if (iRank==1){Rank="Ace";}
            else if (iRank==2){Rank=="Two";}
            else if (iRank==3){Rank=="Three";}
            else if (iRank==4){Rank=="Four";}
            else if (iRank==5){Rank=="Five";}
            else if (iRank==6){Rank=="Six";}
            else if (iRank==7){Rank=="Seven";}
            else if (iRank==8){Rank=="Eight";}
            else if (iRank==9){Rank=="Nine";}
            else if (iRank==10){Rank=="Ten";}
            else if (iRank==11){Rank=="Jack";}
            else if (iRank==12){Rank=="Queen";}
            else if (iRank==0){Rank=="King";}
            else{std::cout << "Rank Error: Invalid iRank." << std::endl;}
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
            else{std::cout << "Suit Error: Invalid iSuit." << std::endl;}
            return Suit;
        };

        int getiRank(int deckNumber){return deckNumber % 13;}

        int getiSuit(int deckNumber){return deckNumber / 13;}

        std::string getCard(std::string Rank, std::string Suit){return Rank + " of " + Suit;};

};

class Deck
{
    private:
        Card deckOfCards[52];
    public:
        Card dealCard()
        {
            return dealtCard;
        };
};


//Functions