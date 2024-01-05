import random as rand

def chooseDescribeCard(Deck):
    card = rand.choice(Deck)
    suitVal = int(card / 13)
    face = ""
    val = 0
    suit = ""

    if suitVal == 0:
        suit = "Spades"
    elif suitVal == 1:
        suit = "Diamonds"
    elif suitVal == 2:
        suit = "Clubs"
    else:
        suit = "Hearts"

    faceVal = card % 13

    if faceVal == 0 or faceVal > 10:
        val = 10
    elif faceVal == 1:
        val = 11
    else:
        val = faceVal

    if faceVal > 10 or faceVal <= 1:
        if faceVal == 0:
            face = "King"
        if faceVal == 1:
            face = "Ace"
        if faceVal == 11:
            face = "Jack"
        if faceVal == 12:
            face = "Queen"
    else:
        face = str(faceVal)

    return suit, face, val, Deck

def SplitCard(Hand1,Hand2, Sum1, Sum2, DealerSum, DealerAceCount, money, bet, Deck ):
    PlayerAceCount = 0
    if Hand1[0][1] == 11:
        PlayerAceCount += 1
    if Hand1[1][1] == 11:
        PlayerAceCount += 1

    print("Your first hand is the %s of %s, and the %s of %s" % (Hand1[0][0], Hand1[0][2], Hand1[1][0], Hand1[1][2]))

    while True:
        if Sum1 > 21:
            if PlayerAceCount > 0:
                Sum1 -= 10
                PlayerAceCount -= 1
                print("An Ace saves you from going bust.")
                continue
            else:    
                print("You've gone bust!\n")
                break

        print("You are at %s. Would you like to draw (a), or stand (s)?\n" % Sum1)
        action = str(input())
  
        if action == 'a':
            suit, face, val, Deck = chooseDescribeCard(Deck)
            Sum1 += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, Sum1))
            continue

        elif action == 's':
            print("You stand at %s.\n" % Sum1)
            break

        else:
            print("Please enter a valid option.\n")
            continue

    PlayerAceCount = 0
    if Hand2[0][1] == 11:
        PlayerAceCount += 1
    if Hand2[1][1] == 11:
        PlayerAceCount += 1

    print("Your second hand is the %s of %s, and the %s of %s" % (Hand2[0][0], Hand2[0][2], Hand2[1][0], Hand2[1][2]))

    while True:
        if Sum2 > 21:
            if PlayerAceCount > 0:
                Sum2 -= 10
                PlayerAceCount -= 1
                print("An Ace saves you from going bust.")
                continue
            else:    
                print("You've gone bust!\n")
                break

        print("You are at %s. Would you like to draw (a), or stand (s)?\n" % Sum2)
        action = str(input())
  
        if action == 'a':
            suit, face, val, Deck = chooseDescribeCard(Deck)
            Sum2 += val
            print("You drew a %s of %s. You are currently holding %s.\n" % (face, suit, Sum2))
            continue

        elif action == 's':
            print("You stand at %s.\n" % Sum2)
            break

        else:
            print("Please enter a valid option.\n")
            continue

    DealerSum = DealerDraw(DealerSum, Deck, DealerAceCount)

    Scoring(Sum1, DealerSum, money, bet / 2 )
    Scoring(Sum2, DealerSum, money, bet / 2 )
    return money

def Scoring(PlayerSum, DealerSum, money, bet):
    if DealerSum > 21:
            DealerSum = 0
    if PlayerSum > 21:
            PlayerSum = 0

    if DealerSum < PlayerSum:
        print("You won this hand and %s dollars!" % bet)
        money += 2*bet

    elif DealerSum > PlayerSum:
        print("You lost this hand and %s dollars!" % bet)

    elif DealerSum == PlayerSum:
        if PlayerSum == 0:
            print("You went bust! You lose %s dollars." % bet)
        else:
            print("You drew with the dealer. You get your bet of %s dollars back." % bet)
            money += bet
    
    else:
        print("Strange Boardstate.")

    return money

def DealerDraw(DealerSum, Deck, DealerAceCount ):

    while DealerSum < 16:
        suit, face, val, Deck = chooseDescribeCard(Deck)
        DealerSum += val
        if DealerSum > 21 and DealerAceCount > 0:
            DealerSum -= 10
            DealerAceCount -= 1
        print("Dealer draws a %s of %s. The dealer shows %s total.\n" % (face, suit, DealerSum))

    
    return DealerSum