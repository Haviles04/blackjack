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

vector<card> deck;
vector<card> player_hand;
vector<card> dealer_hand;
string playerMove();
void initialize();
void update();
void printHands();
string getCardName(int suit, int rank);

int randomNum(int i)
{
    return rand() % i;
}

int main()
{
    srand(time(0));
    initialize();
    update();
    return 0;
}

string playerMove()
{
    string playerChoice;
    cout << "Pick a move, stand, hit, or fold" << endl;
    cin >> playerChoice;
    return playerChoice;
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
    printHands();
    playerMove();
}

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

void printHands() 
{
    cout << "Dealer top card is " << getCardName(dealer_hand[0].suit, dealer_hand[0].rank) << endl;
    cout << "Your hand is " << endl;
    for (int i = 0; i < player_hand.size(); i++){
        string end = i != player_hand.size() - 1 ? "," : "\n";
        cout << getCardName(player_hand[i].suit, player_hand[i].rank) << end;
    }
}