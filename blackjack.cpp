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
string playerMove();
void makeDeck();

int randomNum(int i) {
    return rand() % i;
}

int main()
{
    srand(time(0));
    string move;

    move = playerMove();
    makeDeck();

    for (size_t i = 0; i < deck.size(); i++)
    {
        cout << deck[i].rank << "-"<< deck[i].suit << endl;
    }
    return 0;
}

string playerMove()
{
    string playerChoice;
    cout << "Pick a move, Draw, Hit, or Fold" << endl;
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
}