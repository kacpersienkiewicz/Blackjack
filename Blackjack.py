import random as rand
import BlackjackFunctions as bj

money = 100

print("Welcome to the blackjack table. You currently have 100 dollars.\n")

while True:

    PlayerHand = []
    DealerHand = []

    PlayerAceCount = 0
    DealerAceCount = 0

    if money == 0:
        print("You've busted!")
        break

    print("You have %s dollars. How much would you like to bet?\n" % money)

    try:
        bet = int(input())
    except ValueError:
        print("Please enter a valid integer to bet.")
        continue

    Deck = [i + 1 for i in range(0,52)]
    
    if bet > money:
        print("You don't have enough money to bet that much. You have %s dollars.\n" % money)
        continue
    elif bet <= 0:
        print("You cannot bet 0 or a negative value")
        continue
    else:
        money -= bet
        print("You bet %s dollars. You now have %s dollars.\n" % (bet, money))

    # drawing the two cards for your hand
    
    PlayerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        PlayerHand.append([face,val,suit])
        print(PlayerHand)
        
        if val == 11:
            PlayerAceCount += 1

        PlayerSum += val
        print("You drew a %s of %s.\n" % (val,suit))
        i += 1

    # drawing for the dealer

    dealerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        DealerHand.append([face, val, suit])

        if val == 11:
            DealerAceCount += 1

        dealerSum += val
        
        if i == 0:
            print("The dealer shows a %s of %s.\n" % (face, suit))
            ShownDealerValue = val
        if i == 1:
            hiddenCard = f"{face} of {suit}"

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
                bjEarning = int(1.5 * bet)
                if PlayerSum == dealerSum:
                    print("Both the dealer and you got a Natural Blackjack! You get your bet of %s dollars back." % bet)
                    money += bet
                    continue
                else:
                    print("Natural Blackjack! You get 1.5 times your bet in profit! You earn %s dollars. You now have %s dollars." % (bjEarning, money ))
                    money = money + bet + bjEarning
                    continue
            elif PlayerHand[0][0] == PlayerHand[1][0]:
                print("You are at %s. Would you like to split (f), double down (d), draw (a), or stand (s)?\n" % PlayerSum)
                action = str(input())
            else:
                print("You are at %s. Would you like to double down (d), draw (a), or stand (s)?\n" % PlayerSum)
                action = str(input())
        
        else:
            print("You are at %s. Would you like to draw (a), or stand (s)?\n" % PlayerSum)
            action = str(input())

        if action == 'f' and step == 0:
            PlayerHand2 = [PlayerHand[1]]
            PlayerHand.pop(1)
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerHand.append([face, val, suit])
            PlayerSum1 = PlayerHand[0][1] + val
            print()
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerHand2.append([face, val, suit])
            PlayerSum2 = PlayerHand2[0][1] + val

            bj.SplitCard(PlayerHand, PlayerHand2, PlayerSum1, PlayerSum2, dealerSum, DealerAceCount, money, bet )
            break
        
        elif action == 'd' and step == 0:
            money -= bet
            bet *= 2
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            PlayerSum += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, PlayerSum))
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
        print("The dealer reveals a %s. \n" % hiddenCard)

        dealerSum = bj.DealerDraw(dealerSum, Deck, DealerAceCount)

        print("Dealer shows %s." % (dealerSum))

        money = bj.Scoring(PlayerSum, dealerSum, money, bet)

   
