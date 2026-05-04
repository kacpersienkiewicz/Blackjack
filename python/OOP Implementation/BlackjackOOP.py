'''
An object-oriented programming approach to the CLI Blackjack game in Python

TODO: I think the split function may not function properly in the edge case of drawing additional aces.

'''

import random as rand

class Card:
    def get_suit(self, deck_number):
        suit_number = deck_number // 13
        if suit_number == 0: return "Spades"
        elif suit_number == 1: return "Diamonds"
        elif suit_number == 2: return "Clubs"
        elif suit_number == 3: return "Hearts"
        else: return "Null"

    def get_rank(self, deck_number):
        rank_number = deck_number % 13
        if rank_number == 1: return "Ace"
        elif rank_number == 11: return "Jack"
        elif rank_number == 12: return "Queen"
        elif rank_number == 0: return "King"
        else: return str(rank_number)

    def get_value(self, deck_number):
        rank_number = deck_number % 13
        if rank_number == 0 or rank_number > 10:
            return 10
        elif rank_number == 1:
            return 11
        else: return rank_number
    
    def get_card(self,suit, rank):
        return f"{rank} of {suit}"

    def __init__(self, deck_number):
        self.suit = self.get_suit(deck_number)
        self.rank = self.get_rank(deck_number)
        self.value = self.get_value(deck_number)


class Deck:
    def create_deck(self):
        deck_list = [x for x in range(0,52)]
        deck = []
        for i in deck_list:
            current_Card = Card(i)
            deck.append(current_Card)
        return deck

    def deal(self, deck):
        index = rand.randint(0, len(deck.deck) - 1)
        card = deck.deck[index]
        deck.deck.pop(index)
        return card

    def __init__(self):
        self.deck = self.create_deck()


class Hand:
    def get_acecount(self, hand):
        AceCount = 0
        for card in hand:
            if card.rank =="Ace":
                AceCount+=1
            else:
                continue
        return AceCount

    def get_hand_value(self, hand):
        total = 0
        for card in hand:
            total += card.value
        return total

    def calculate_aces_available(self, AceCount, AcesUsed):
        return AceCount - AcesUsed


    def __init__(self, deck: Deck):
        self.hand = [deck.deal(deck), deck.deal(deck)]
        self.value = self.get_hand_value(self.hand)
        self.AceCount = self.get_acecount(self.hand)
        self.AcesAvailable = self.AceCount
        self.AcesUsed = 0


def Scoring(PlayerSum, DealerSum, money, bet):
    if DealerSum > 21:
            DealerSum = 0
    if PlayerSum > 21:
            PlayerSum = 0

    if DealerSum < PlayerSum:
        print(f"You won this hand and {int(bet)} dollars!")
        money += int(2*bet)

    elif DealerSum > PlayerSum:
        print(f"You lost this hand and {int(bet)} dollars!")

    elif DealerSum == PlayerSum:
        if PlayerSum == 0:
            print(f"You went bust! You lose {bet} dollars.")
        else:
            print(f"You drew with the dealer. You get your bet of {bet} dollars back.")
            money += bet
    
    else:
        print("Strange Boardstate.")

    return money

STARTINGMONEY = 100
money = STARTINGMONEY

print(f"\nWelcome to the blackjack table. You currently have {money} dollars.\n")

while True:
    split_card = False
    insurance_bet = False

    bj_deck = Deck()
    PlayerHand = Hand(bj_deck)
    DealerHand = Hand(bj_deck)

    if money <= 0:
        print("You've busted! Would you like to start over? \nyes (y) no (no)")
        try:
            choice = str(input())
        except ValueError:
            print("please enter 'y' or 'n'")
            continue
        except choice != 'y' or 'n':
            print("please enter 'y' or 'n'")
            continue
        if choice == 'n':
            break
        else:
            money = 100
            continue

    print(f"You have {money} dollars. How much would you like to bet?\n")

    while True:
        try:
            bet = int(input())
        except ValueError:
            print("Please enter a valid integer to bet.")
            continue
        if bet <= 0:
            print("You cannot bet 0 or a negative value")
            continue
        elif bet > money:
            print(f"You don't have enough money to bet {bet} dollars. You have {money} dollars.\n")
            continue
        else:
            break
    
    money -= bet


    if DealerHand.hand[1].rank == "Ace":
        print(f"Your hand is the {PlayerHand.hand[0].get_card(PlayerHand.hand[0].suit, PlayerHand.hand[0].rank)}, and {PlayerHand.hand[1].get_card(PlayerHand.hand[1].suit, PlayerHand.hand[1].rank)} for a total of {PlayerHand.value}. The dealer shows the {DealerHand.hand[1].get_card(DealerHand.hand[1].suit, DealerHand.hand[1].rank)}.\n")
        print("The Dealer shows an ace. Would you like to place an insurance bet? (y) or (n)?")
        while True:
            choice = str(input())
            if bet // 2 > money:
                print(f"You don't have enough money to bet {bet} dollars. You have {money} dollars.\n")
                insurance_bet = True
                continue
            elif choice == 'y':
                money -= bet // 2
                break
            elif choice == 'n':
                continue
            else:
                print("Plese enter a valid option, either 'y' or 'n'.")
                continue
    else:
        print(f"Your hand is the {PlayerHand.hand[0].get_card(PlayerHand.hand[0].suit, PlayerHand.hand[0].rank)}, and {PlayerHand.hand[1].get_card(PlayerHand.hand[1].suit, PlayerHand.hand[1].rank)} for a total of {PlayerHand.value}. The dealer shows the {DealerHand.hand[1].get_card(DealerHand.hand[1].suit, DealerHand.hand[1].rank)}.\n")

  
    prompt = "What would you like to do? (h)it, (s)tand"
    if len(PlayerHand.hand) == 2:
        prompt += ', (d)ouble down'
        if PlayerHand.hand[0].rank == PlayerHand.hand[1].rank:
            prompt += ', s(p)lit'
    prompt += '.\n'
    print(prompt)
    choice = str(input())

    while True:
        if choice == 'h':
            curr_card = bj_deck.deal()
            PlayerHand.hand.append(curr_card)
            PlayerHand.value += curr_card.value
            print(f"You drew a {curr_card.get_card(curr_card.suit, curr_card.rank)}, bringing your total to {PlayerHand.value}.")
            
            if curr_card.rank == "Ace": 
                PlayerHand.AceCount += 1
                PlayerHand.AcesAvailable += 1

            if PlayerHand.value > 21:
                if PlayerHand.AcesAvailable > 0:
                    PlayerHand.AcesUsed += 1
                    PlayerHand.AcesAvailable = PlayerHand.calculate_aces_available(PlayerHand.AceCount, PlayerHand.AcesUsed)
                else:
                    print("You've gone bust!\n")
                    break
            continue

        elif choice == 's':
            break

        elif choice == 'd' and len(PlayerHand.hand) == 2:
            if bet > money:
                print(f"You cannot bet yourself in debt. You have {money}, which is less than your bet of {bet} dollars.")
                continue
            money -= bet
            bet *= 2

            curr_card = bj_deck.deal(bj_deck)
            PlayerHand.hand.append(curr_card)
            PlayerHand.value += curr_card.value
            print(f"Your final card is a {curr_card.get_card(curr_card.suit, curr_card.rank)}, bringing your total to {PlayerHand.value}.")

            if curr_card.rank == "Ace": 
                PlayerHand.AceCount += 1
                PlayerHand.AcesAvailable += 1

            if PlayerHand.value > 21:
                if PlayerHand.AcesAvailable > 0:
                    PlayerHand.AcesUsed += 1
                    PlayerHand.AcesAvailable = PlayerHand.calculate_aces_available(PlayerHand.AceCount, PlayerHand.AcesUsed)
                else:
                    print("You've gone bust!\n")
                    break
            break

        elif choice == 'p' and len(PlayerHand.hand) == 2 and PlayerHand.hand[0].rank == PlayerHand.hand[1].rank:
            split_card = True

            PlayerHand2 = Hand(bj_deck)
            PlayerHand2.hand[0], PlayerHand.hand[1] = PlayerHand.hand[1], PlayerHand2.hand[0]

            PlayerHand.AceCount = PlayerHand.get_acecount(PlayerHand.hand)
            PlayerHand.AcesUsed = 0
            PlayerHand.AcesAvailable = PlayerHand.calculate_aces_available(PlayerHand.AceCount, PlayerHand.AcesUsed)
            PlayerHand.value = PlayerHand.get_hand_value(PlayerHand.hand)

            PlayerHand2.AceCount = PlayerHand2.get_acecount(PlayerHand2.hand)
            PlayerHand2.AcesUsed = 0
            PlayerHand2.AcesAvailable = PlayerHand2.calculate_aces_available(PlayerHand2.AceCount, PlayerHand2.AcesUsed)
            PlayerHand2.value = PlayerHand2.get_hand_value(PlayerHand2.hand)

            print(f"Your first hand is the {PlayerHand.hand[0].get_card(PlayerHand.hand[0].suit, PlayerHand.hand[0].rank)}, and {PlayerHand.hand[1].get_card(PlayerHand.hand[1].suit, PlayerHand.hand[1].rank)} for a total of {PlayerHand.value}. The dealer shows the {DealerHand.hand[1].get_card(DealerHand.hand[1].suit, DealerHand.hand[1].rank)}.\n")
            while True:
                print(f"You are at a toal of {PlayerHand.value}. What would you like to do? (h)it or (s)tand.\n")
                if choice == 'h':
                    curr_card = bj_deck.deal()
                    PlayerHand.hand.append(curr_card)
                    PlayerHand.value += curr_card.value
                    print(f"You drew a {curr_card.get_card(curr_card.suit, curr_card.rank)}, bringing your total to {PlayerHand.value}.")

                    if curr_card.rank == "Ace": 
                        PlayerHand.AceCount += 1
                        PlayerHand.AcesAvailable += 1

                    if PlayerHand.value > 21:
                        if PlayerHand.AcesAvailable > 0:
                            PlayerHand.AcesUsed += 1
                            PlayerHand.AcesAvailable = PlayerHand.calculate_aces_available(PlayerHand.AceCount, PlayerHand.AcesUsed)
                        else:
                            print("You've gone bust!\n")
                            break
                    continue
                if choice == 's':
                    break

            print(f"Your second hand is the {PlayerHand2.hand[0].get_card(PlayerHand2.hand[0].suit, PlayerHand2.hand[0].rank)}, and {PlayerHand2.hand[1].get_card(PlayerHand2.hand[1].suit, PlayerHand2.hand[1].rank)} for a total of {PlayerHand2.value}. The dealer shows the {DealerHand.hand[1].get_card(DealerHand.hand[1].suit, DealerHand.hand[1].rank)}.\n")
            while True:
                print(f"You are at a toal of {PlayerHand2.value}. What would you like to do? (h)it or (s)tand.\n")
                if choice == 'h':
                    curr_card = bj_deck.deal()
                    PlayerHand2.hand.append(curr_card)
                    PlayerHand2.value += curr_card.value
                    print(f"You drew a {curr_card.get_card(curr_card.suit, curr_card.rank)}, bringing your total to {PlayerHand2.value}.")
                    if curr_card.rank == "Ace": 
                        PlayerHand2.AceCount += 1
                        PlayerHand2.AcesAvailable += 1

                    if PlayerHand2.value > 21:
                        if PlayerHand2.AcesAvailable > 0:
                            PlayerHand2.AcesUsed += 1
                            PlayerHand2.AcesAvailable = PlayerHand2.calculate_aces_available(PlayerHand2.AceCount, PlayerHand2.AcesUsed)
                        else:
                            print("You've gone bust!\n")
                            break
                    continue
                if choice == 's':
                    break
        else:
            print("Please enter a valid option. 'd' is only valid on the initial turn, and 'p' is only valid on the initial turn and if the rank of your cards are the same.\n")
            continue

    if DealerHand.hand[1].rank == "Ace":
        if DealerHand.value == 21:
            print(f"The dealer shows a {DealerHand.hand[0].get_card(DealerHand.hand[0].suit, DealerHand.hand[0].rank)} in addition to an ace, scoring a blackjack. Insurance bets have paid off!\n")
            if insurance_bet:
                money += bet // 2
        else:
            print(f"The dealer shows a {DealerHand.hand[0].get_card(DealerHand.hand[0].suit, DealerHand.hand[0].rank)} in addition to an ace, which does not add to 21. Insurance bets have not paid off.\n")

    while DealerHand.value < 16:
        curr_card = bj_deck.deal(bj_deck)
        DealerHand.hand.append(curr_card)
        DealerHand.value += curr_card.value
        if curr_card.rank == "Ace": 
            DealerHand.AceCount += 1
            DealerHand.AcesAvailable += 1
        if DealerHand.value > 21:
            if DealerHand.AcesAvailable > 0:
                DealerHand.AcesUsed += 1
                DealerHand.AcesAvailable = DealerHand.calculate_aces_available(DealerHand.AceCount, DealerHand.AcesUsed)
            else:
                print("The Dealer has gone bust!\n")
                break
        continue
    
    print(f"The Dealer stands at {DealerHand.value}.\n")

    money = Scoring(PlayerHand.value, DealerHand.value, money, bet)