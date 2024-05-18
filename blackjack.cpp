#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class card
{
public:
    int rank;
    int suit;
    card(int r, int s)
    {
        rank = r;
        suit = s;
    }
};

// victory data
bool gameOver = false;
string winner;
// deck and hands
vector<card> deck;
vector<card> player_hand;
vector<card> dealer_hand;
// functions
string getCardName(int suit, int rank);
void update();
void initialize();
void printHand(string hand);
void dealCards(vector<card> &hand, int count);
void playerMove();
void dealerMove();
void checkWin();
int sumCards(vector<card> hand);

int randomNum(int i)
{
    return rand() % i;
}

int main()
{
    srand(time(0));
    initialize();
    while (gameOver != true)
    {
        update();
    }
    printHand("dealer");
    printHand("");

    cout << "The Winner is " << winner << endl;

    return 0;
}

void makeDeck()
{
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            deck.push_back(card(j, i));
        }
    }
    random_shuffle(deck.begin(), deck.end(), randomNum);
    return;
}

void dealCards(vector<card> &hand, int count)
{
    for (int i = 0; i < count; i++)
    {
        hand.push_back(move(deck.back()));
        deck.pop_back();
    }
    return;
}

void initialize()
{
    makeDeck();
    dealCards(player_hand, 2);
    dealCards(dealer_hand, 2);
    return;
}

void update()
{
    cout << "Dealer top card is " << getCardName(dealer_hand[0].suit, dealer_hand[0].rank) << endl;
    printHand("");
    playerMove();
    dealerMove();
    checkWin();
}

void playerMove()
{
    string playerChoice;
    cout << "Pick a move, stand, hit, or fold" << endl;
    cin >> playerChoice;
    if (playerChoice == "hit")
    {
        dealCards(player_hand, 1);
        if (sumCards(player_hand) > 21)
        {
            gameOver = true;
            winner = "the dealer";
        }
    }
    else if (playerChoice == "stand")
    {
        gameOver = true;
    }
    else
    {
        gameOver = true;
        winner = "the dealer";
        return;
    }
    return;
}

void dealerMove()
{
    int dealerTotal = sumCards(dealer_hand);

    if (dealerTotal <= 8)
    {
        dealCards(dealer_hand, 1);
        if (gameOver == true)
        {
            dealerMove();
        }
    }
    return;
};

string getCardName(int suit, int rank)
{
    string str_suit;
    string str_rank;

    switch (suit)
    {
    case 1:
        str_suit = "♣️";
        break;
    case 2:
        str_suit = "♦️";
        break;
    case 3:
        str_suit = "♥️";
        break;
    case 4:
        str_suit = "♠️";
        break;
    }

    switch (rank)
    {
    case 11:
        str_rank = "J";
        break;
    case 12:
        str_rank = "Q";
        break;
    case 13:
        str_rank = "K";
        break;
    default:
        str_rank = to_string(rank);
        break;
    }

    return str_rank + str_suit;
}

void printHand(string hand)
{
    if (hand == "dealer")
    {
        cout << "the Dealers hand is " << endl;
        for (int i = 0; i < dealer_hand.size(); i++)
        {
            string end = i != dealer_hand.size() - 1 ? "," : "\n";
            cout << getCardName(dealer_hand[i].suit, dealer_hand[i].rank) << end;
        }
    }
    else
    {
        cout << "Your hand is " << endl;
        for (int i = 0; i < player_hand.size(); i++)
        {
            string end = i != player_hand.size() - 1 ? "," : "\n";
            cout << getCardName(player_hand[i].suit, player_hand[i].rank) << end;
        }
    }
    return;
}

int sumCards(vector<card> hand)
{
    int sum = 0;
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i].rank >= 10)
        {
            sum = sum + 10;
        }
        else
            sum = sum + hand[i].rank;
    }
    return sum;
}

void checkWin()
{
    int player_total = sumCards(player_hand);
    int dealer_total = sumCards(dealer_hand);

    if (player_total == dealer_total)
    {
        winner = "a tie";
        gameOver = true;
    }
    else if (dealer_total == 21 || dealer_total > player_total)
    {
        winner = "the dealer";
        gameOver = true;
    }
    else if (player_total > dealer_total && player_total <= 21)
    {
        winner = "you!";
        gameOver = true;
    }
    return;
}