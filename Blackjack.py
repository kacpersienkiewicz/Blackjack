import random as rand
import BlackjackFunctions as bj

money = 100

print("Welcome to the blackjack table. You currently have 100 dollars.\n")

while True:

    if money == 0:
        print("You've busted!")
        break

    print("You have %s dollars. How much would you like to bet?\n" % money)

    try:
        bet = int(input())
    except ValueError:
        print("Please enter a valid integer to bet.")
        continue

    Deck = bj.createDeck()

    PlayerAceCount = 0
    DealerAceCount = 0
    
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
    
    runningSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        
        if val == 11:
            PlayerAceCount += 1

        runningSum += val
        print("You drew a %s of %s.\n" % (val,suit))
        i += 1

    # drawing for the dealer

    dealerSum = 0

    for i in range(2):
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)

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

        if runningSum > 21:
            if PlayerAceCount > 0:
                runningSum -= 10
                PlayerAceCount -= 1
                print("An Ace saves you from going bust.")
                continue
            else:    
                print("You bust!\n")
                break
        
        # There's a few things that need to be checked at the first step
        if step == 0:
            if runningSum == 21:
                bjEarning = int(1.5 * bet)
                money = money + bet + bjEarning
                if runningSum == dealerSum:
                    print("Both the dealer and you got a Natural Blackjack! You get your bet of %s dollars back." % bet)
                    money += bet
                    continue
                else:
                    print("Natural Blackjack! You get 1.5 times your bet in profit! You earn %s dollars. You now have %s dollars." % (bjEarning, money ))
                    continue
            print("You are at %s. Would you like to double down (d), draw (a), or stand (s)?\n" % runningSum)
            action = str(input())
        
        else:
            print("You are at %s. Would you like to draw (a), or stand (s)?\n" % runningSum)
            action = str(input())
        
        if action == 'd' and step == 0:
            money -= bet
            bet *= 2
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            runningSum += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, runningSum))
            break

        elif action == 'a':
            suit, face, val, Deck = bj.chooseDescribeCard(Deck)
            runningSum += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, runningSum))
            step += 1
            continue

        elif action == 's':
            print("You stand at %s.\n" % runningSum)
            break

        else:
            print("Please enter a valid option.\n")
            continue
        
    # loop for dealer
        
    print("The dealer reveals a %s. \n" % hiddenCard)

    while dealerSum < 16:
        suit, face, val, Deck = bj.chooseDescribeCard(Deck)
        dealerSum += val
        if dealerSum > 21 and DealerAceCount > 0:
            dealerSum -= 10
            DealerAceCount -= 1
        print("Dealer draws a %s of %s. The dealer shows %s.\n" % (face, suit, dealerSum))

    print("Dealer shows %s and you show %s" % (dealerSum, runningSum))

    # scoring the game

    if dealerSum > 21:
            dealerSum = 0
    if runningSum > 21:
            runningSum = 0

    if dealerSum < runningSum:
        print("You won this round and %s dollars!" % bet)
        money += 2*bet

    elif dealerSum > runningSum:
        print("You lost this round and %s dollars!" % bet)

    elif dealerSum == runningSum:
        if runningSum == 0:
            print("You went bust! You lose %s dollars." % bet)
            continue
        else:
            print("You drew with the dealer. You get your bet of %s dollars back." % bet)
            money += bet
    
    else:
        print("Strange Boardstate.")
   