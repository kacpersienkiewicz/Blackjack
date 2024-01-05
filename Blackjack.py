import random as rand
import BlackjackFunctions as bj

money = 100

print("Welcome to the blackjack table. You currently have 100 dollars.\n")

while True:

    PlayerHand = []
    DealerHand = []
    PlayerAceCount = 0
    DealerAceCount = 0

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

    dealerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        DealerHand.append([face, val, suit])

        if val == 11:
            DealerAceCount += 1

        dealerSum += val
    
        print("The dealer shows a %s of %s.\n" % (face, suit))
        if DealerHand[0][0] == 'Ace':
            print("The dealer has shown an ace, would you like to bet insurance? It will cost %s dollars." % int(bet/2))
            choice = input()
            if choice == 'y':
                InsuranceBet = int(bet/2)
                money -= InsuranceBet
            else:
                InsuranceBet = 0

    # loop for the player
    step = 0

    while True:

        if PlayerSum > 21:
            if PlayerAceCount > 0:
                PlayerSum -= 10
                PlayerAceCount -= 1
                print("An Ace saves you from going bust.")
                continue
            else:    
                print("You've gone bust!\n")
                break
        
        # There's a few things that need to be checked at the first step
        if step == 0:
            if PlayerSum == 21:
                if PlayerSum == dealerSum:
                    print("Both the dealer and you got a Natural Blackjack! You get your bet of %s dollars back." % bet)
                    money += bet
                    break
                else:
                    print("Natural Blackjack! You get 1.5 times your bet in profit! You earn %s dollars. You now have %s dollars." % (int(bet * 2.5), money ))
                    money = money + int(2.5 * bet)
                    break
            elif PlayerHand[0][0] == PlayerHand[1][0]:
                if money >= bet:
                    print("You are at %s. Would you like to split (f), double down (d), draw (a), or stand (s)?\n" % PlayerSum)
                    action = str(input())
                else:
                    print("You don't have enough money to bet for splitting. You are at %s. Would you like to draw (a), or stand (s)?\n" % PlayerSum)
                    action = str(input())
            elif money >= bet: 
                print("You are at %s. Would you like to double down (d), draw (a), or stand (s)?\n" % PlayerSum)
                action = str(input())
            else:
                print("You are at %s. Would you like to draw (a), or stand (s)?\n" % PlayerSum)
                action = str(input())
        
        else:
            print("You are at %s. Would you like to draw (a), or stand (s)?\n" % PlayerSum)
            action = str(input())

        if action == 'f' and step == 0:
            money -= bet
            bet *= 2
            PlayerHand2 = [PlayerHand[1]]
            PlayerHand.pop(1)
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerHand.append([face, val, suit])
            PlayerSum1 = PlayerHand[0][1] + val
            print()
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerHand2.append([face, val, suit])
            PlayerSum2 = PlayerHand2[0][1] + val

            bj.SplitCard(PlayerHand, PlayerHand2, PlayerSum1, PlayerSum2, dealerSum, DealerAceCount, money, bet, Deck )
            break
        
        elif action == 'd' and step == 0:
            money -= bet
            bet *= 2
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerSum += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, PlayerSum))
            
            if PlayerSum > 21:
                if PlayerAceCount > 0:
                    PlayerSum -= 10
                    PlayerAceCount -= 1
                    print("An Ace saves you from going bust.")
                else:    
                    print("You've gone bust!\n")
          
            break

        elif action == 'a':
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerSum += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, PlayerSum))
            step += 1
            continue

        elif action == 's':
            print("You stand at %s.\n" % PlayerSum)
            break

        else:
            print("Please enter a valid option.\n")
            continue
        
    # loop for dealer
    
    if action != 'f':    
        print("The dealer reveals a %s to show %s total. \n" % (DealerHand[1][0], dealerSum))

        if InsuranceBet != 0:
            if DealerHand[1][0] == 10:
                print("Congrats! Insurance paid off, and you earned %s. You now have %s dollars" % int(1.5 * InsuranceBet))
                money += int(1.5*InsuranceBet)
                InsuranceBet = 0
            else:
                print("Your insurance bet did not pay off.")
                InsuranceBet = 0
                
        dealerSum = bj.DealerDraw(dealerSum, Deck, DealerAceCount)

        print("Dealer shows %s." % (dealerSum))

        money = bj.Scoring(PlayerSum, dealerSum, money, bet)

   
