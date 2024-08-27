import pytest
import BlackjackFunctions as bj

# basic variables

money = 100
bet = 10

# check bet logic

# check starting hands

# Check Player Action
def test_PlayerAction_Bust():
    pass

# Check Choose describe Card

# Check Split Card

# Check Dealer Draw

# Check Bet Function

# Check Scoring
# Reasoning for the cases. You get double the bet if you win because the bet was already deducted. If you win you get yout bet back twice.
# Loss: You already lost the money for the bet by this point so nothing changes for money.
# Draw: You need your bet back to be even
# Should also include a case for a natural Blackjack and for insurance payouts.

def test_Scoring_Win():
    assert bj.Scoring(1,0,money,bet) == money + int(bet * 2)

def test_Scoring_Loss():
    assert bj.Scoring(0,1,money,bet) == money

def test_Scoring_Draw():
    assert bj.Scoring(1,1,money,bet) == money + bet

# Going bust sets you at 0, if you bust you do not win even if you draw  with the dealer
def test_Scoring_Draw_Bust():
    assert bj.Scoring(0,0,100,10) == money

