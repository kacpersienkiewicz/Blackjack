import pytest
import BlackjackFunctions as bj

MONEY = 100
BET = 10

def test_Bet_NonInt():
    bj.input = lambda: "Word"
    output = bj.Bet(MONEY)
    assert output == 'continue'
def test_Bet_Zero():
    bj.input = lambda: 0
    output = bj.Bet(MONEY)
    assert output == 'continue'
def test_Bet_Negative():
    bj.input = lambda: -1
    output = bj.Bet(MONEY)
    assert output == 'continue'
def test_Bet_OverBet():
    bj.input = lambda: 2 * MONEY
    output = bj.Bet(MONEY)
    assert output == 'continue'
def test_Bet_Valid():
    bj.input = lambda: BET
    output = bj.Bet(MONEY)
    assert output == BET

def test_chooseDescribeCard():
    Deck = [1]
    assert bj.chooseDescribeCard(Deck) == ("Spades", "Ace", 11, [1])


def test_Scoring_Win():
    assert bj.Scoring(1,0,MONEY,BET) == MONEY + int(BET * 2)

def test_Scoring_Loss():
    assert bj.Scoring(0,1,MONEY,BET) == MONEY

def test_Scoring_Draw():
    assert bj.Scoring(1,1,MONEY,BET) == MONEY + BET

def test_Scoring_Bust():
    assert bj.Scoring(0,0,MONEY,BET) == MONEY
