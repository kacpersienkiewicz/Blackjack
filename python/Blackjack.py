import random as rand
import BlackjackFunctions as bj
import BlackjackGUI as GUI

money = 100

print("\nWelcome to the blackjack table. You currently have 100 dollars.\n")

while True:

    PlayerHand = []
    DealerHand = []
    PlayerAceCount = 0
    DealerAceCount = 0
    InsuranceBet = 0

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

    bet = bj.Bet(money)
   
    if bet == 'continue':
        continue

    money -= bet
    print(f"You bet {bet} dollars. You now have {money} dollars.\n")

    Deck = [i  for i in range(1,53)]
    
    PlayerSum = 0
    
    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        PlayerHand.append([face,val,suit])
        
        if val == 11:
            PlayerAceCount += 1

        PlayerSum += val
        print(f"You drew a {val} of {suit}.\n")
        #split card
    DealerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        DealerHand.append([face, val, suit])

        if val == 11:
            DealerAceCount += 1

        DealerSum += val
        if i == 0:
            print(f"The dealer shows a {face} of {suit}.\n")
        if DealerHand[0][0] == 'Ace' and i == 0:
            print(f"The dealer has shown an ace, would you like to bet insurance? It will cost {int(bet/2)} dollars. \n y (yes), n (no)")
            choice = input()
            if choice == 'y' and money >= int(bet/2):
                InsuranceBet = int(bet/2)
                money -= InsuranceBet
            else:
                InsuranceBet = 0

    if PlayerHand[0][1] == PlayerHand[1][1]:
        print({"Would you like to split your hand?\nyes (y) no (no)"})
        choice = str(input)
        if choice == 'y':
            money = bj.SplitCard(PlayerHand[0], PlayerHand[1], PlayerHand[0][1],PlayerHand[1][1], DealerSum, PlayerSum, )
            continue

    action, PlayerSum, money, bet, Deck = bj.PlayerAction(PlayerHand, PlayerSum, PlayerAceCount, DealerSum, DealerAceCount, money, bet, Deck)
    
    if action != 'f':    
        print(f"The dealer reveals a {DealerHand[1][0]} to show {DealerSum} total. \n")

        if InsuranceBet != 0:
            if DealerHand[1][0] == 10:
                print(f"Congrats! Insurance paid off, and you earned {int(1.5 * InsuranceBet)}. You now have {money} dollars")
                money += int(1.5*InsuranceBet)
                InsuranceBet = 0
            else:
                print("Your insurance bet did not pay off.")
                InsuranceBet = 0
                
        DealerSum = bj.DealerDraw(DealerSum, Deck, DealerAceCount)

        print(f"Dealer shows {DealerSum}.")

        money = bj.Scoring(PlayerSum, DealerSum, money, bet)