import random as rand
import BlackjackFunctions as bj

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

    print("You have %s dollars. How much would you like to bet?\n" % money)

    bet = bj.Bet(money)
   
    if bet == 'continue':
        continue

    money -= bet
    print("You bet %s dollars. You now have %s dollars.\n" % (bet, money))

    Deck = [i  for i in range(1,53)] # list comp is much neater and nicer than a loop

    # drawing the two cards for your hand
    
    PlayerSum = 0
    
    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        PlayerHand.append([face,val,suit])
        
        if val == 11:
            PlayerAceCount += 1

        PlayerSum += val
        print("You drew a %s of %s.\n" % (val,suit))
        
    PlayerHand = [['10',10, 'Hearts'],['10',10,'Spades']]
    PlayerSum = 20

    DealerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        DealerHand.append([face, val, suit])

        if val == 11:
            DealerAceCount += 1

        DealerSum += val
        if i == 0:
            print("The dealer shows a %s of %s.\n" % (face, suit))
        if DealerHand[0][0] == 'Ace' and i == 0:
            print("The dealer has shown an ace, would you like to bet insurance? It will cost %s dollars. \n y (yes), n (no)" % int(bet/2))
            choice = input()
            if choice == 'y' and money >= int(bet/2):
                InsuranceBet = int(bet/2)
                money -= InsuranceBet
            else:
                InsuranceBet = 0

    action, PlayerSum, money, bet, Deck = bj.PlayerAction(PlayerHand, PlayerSum, PlayerAceCount, DealerSum, DealerAceCount, money, bet, Deck)
    
    if action != 'f':    
        print("The dealer reveals a %s to show %s total. \n" % (DealerHand[1][0], DealerSum))

        if InsuranceBet != 0:
            if DealerHand[1][0] == 10:
                print("Congrats! Insurance paid off, and you earned %s. You now have %s dollars" % int(1.5 * InsuranceBet))
                money += int(1.5*InsuranceBet)
                InsuranceBet = 0
            else:
                print("Your insurance bet did not pay off.")
                InsuranceBet = 0
                
        DealerSum = bj.DealerDraw(DealerSum, Deck, DealerAceCount)

        print("Dealer shows %s." % (DealerSum))

        money = bj.Scoring(PlayerSum, DealerSum, money, bet)