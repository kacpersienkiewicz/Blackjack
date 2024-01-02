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

def SplitCard(Hand1,Hand2, ):



    return