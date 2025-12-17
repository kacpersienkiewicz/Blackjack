import random as rand

def PlayerAction(PlayerHand, PlayerSum, PlayerAceCount, DealerSum, DealerAceCount, money, bet, Deck):
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
        
        if step == 0:
            if PlayerSum == 21:
                if PlayerSum == DealerSum:
                    print(f"Both the dealer and you got a Natural Blackjack! You get your bet of {bet} dollars back.")
                    money += bet
                    break
                else:
                    print(f"Natural Blackjack! You get 1.5 times your bet in profit! You earn {(int(bet * 2.5))} dollars. You now have {money} dollars.")
                    money = money + int(2.5 * bet)
                    break
            elif PlayerHand[0][0] == PlayerHand[1][0]:
                if money >= bet:
                    print(f"You are at {PlayerSum}. Would you like to split (f), double down (d), draw (a), or stand (s)?\n")
                    action = str(input())
                else:
                    print(f"You don't have enough money to bet for splitting. You are at {PlayerSum}. Would you like to draw (a), or stand (s)?\n")
                    action = str(input())
            elif money >= bet: 
                print(f"You are at {PlayerSum}. Would you like to double down (d), draw (a), or stand (s)?\n")
                action = str(input())
            else:
                print(f"You are at {PlayerSum}. Would you like to draw (a), or stand (s)?\n")
                action = str(input())
        
        else:
            print(f"You are at {PlayerSum}. Would you like to draw (a), or stand (s)?\n")
            action = str(input())

        if action == 'f' and step == 0:
            money -= bet
            bet *= 2
            PlayerHand2 = [PlayerHand[1]]
            PlayerHand.pop(1)
            suit, face, val, Deck = chooseDescribeCard(Deck)
            PlayerHand.append([face, val, suit])
            PlayerSum1 = PlayerHand[0][1] + val
            suit, face, val, Deck = chooseDescribeCard(Deck)
            PlayerHand2.append([face, val, suit])
            PlayerSum2 = PlayerHand2[0][1] + val

            SplitCard(PlayerHand, PlayerHand2, PlayerSum1, PlayerSum2, DealerSum, DealerAceCount, money, bet, Deck )
            break
        
        elif action == 'd' and step == 0:
            money -= bet
            bet *= 2
            suit, face, val, Deck = chooseDescribeCard(Deck)
            PlayerSum += val
            print(f"You drew a {face} of {suit}. You are currently holding {PlayerSum}.\n")
            
            if PlayerSum > 21:
                if PlayerAceCount > 0:
                    PlayerSum -= 10
                    PlayerAceCount -= 1
                    print("An Ace saves you from going bust.")
                else:    
                    print("You've gone bust!\n")
          
            break

        elif action == 'a':
            suit, face, val, Deck = chooseDescribeCard(Deck)
            PlayerSum += val
            print(f"You drew a {face} of {suit}. You are currently holding {PlayerSum}.\n")
            step += 1
            continue

        elif action == 's':
            print(f"You stand at {PlayerSum}.\n")
            break

        else:
            print("Please enter a valid option.\n")
            continue
        
    return action, PlayerSum, money, bet, Deck

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

    print(f"Your first hand is the {Hand1[0][0]} of {Hand1[0][2]}, and the {Hand1[1][0]} of {Hand1[1][2]}")

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

        print(f"You are at {Sum1}. Would you like to draw (a), or stand (s)?\n")
        action = str(input())
  
        if action == 'a':
            suit, face, val, Deck = chooseDescribeCard(Deck)
            Sum1 += val
            print(f"You drew a {face} of {suit}. You are currently holding {Sum1}.\n")
            continue

        elif action == 's':
            print(f"You stand at {Sum1}.\n")
            break

        else:
            print("Please enter a valid option.\n")
            continue

    PlayerAceCount = 0
    if Hand2[0][1] == 11:
        PlayerAceCount += 1
    if Hand2[1][1] == 11:
        PlayerAceCount += 1

    print(f"Your second hand is the {Hand2[0][0]} of {Hand2[0][2]}, and the {Hand2[1][0]} of {Hand2[1][2]}")

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

        print(f"You are at {Sum2}. Would you like to draw (a), or stand (s)?\n")
        action = str(input())
  
        if action == 'a':
            suit, face, val, Deck = chooseDescribeCard(Deck)
            Sum2 += val
            print(f"You drew a {face} of {suit}. You are currently holding {Sum2}.\n")
            continue

        elif action == 's':
            print(f"You stand at {Sum2}.\n")
            break

        else:
            print("Please enter a valid option.\n")
            continue

    DealerSum = DealerDraw(DealerSum, Deck, DealerAceCount)

    money = Scoring(Sum1, DealerSum, money, bet / 2 )
    money = Scoring(Sum2, DealerSum, money, bet / 2 )
    return money

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

def DealerDraw(DealerSum, Deck, DealerAceCount ):

    while DealerSum < 16:
        suit, face, val, Deck = chooseDescribeCard(Deck)
        DealerSum += val
        if DealerSum > 21 and DealerAceCount > 0:
            DealerSum -= 10
            DealerAceCount -= 1
        print(f"Dealer draws a {face} of {suit}. The dealer shows {DealerSum} total.\n")

    return DealerSum

def Bet(money):
    try:
        bet = int(input())
    except ValueError:
        print("Please enter a valid integer to bet.")
        return 'continue'
    if bet <= 0:
        print("You cannot bet 0 or a negative value")
        return 'continue'
    elif bet > money:
        print(f"You don't have enough money to bet {bet} dollars. You have {money} dollars.\n")
        return 'continue'
    else:
        return bet