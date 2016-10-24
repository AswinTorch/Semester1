//Aswin Nair
//Assignment 4: My Ship Sails Game
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> letters = {"(a) ", "(b) ", "(c) ", "(d) ", "(e) ", "(f) ", "(g) "};
class Card {
public:
    char m_suit; //'S', 'C', 'D' 'H'
    int m_num; //Values
    Card(const char suit = 'S', const int number = 0) : m_suit(suit), m_num(number) {}
    friend ostream &operator<<(ostream &, const Card &);
};
ostream &operator<<(ostream &o, const Card &c) {
    o << c.m_suit;
    switch (c.m_num) {
        case 1:
            o << 'A';
            break;
        case 11:
            o << 'J';
            break;
        case 12:
            o << 'Q';
            break;
        case 13:
            o << 'K';
            break;
        default:
            o << c.m_num;
    }
    return o;
}
class Player {
    int m_name;
    vector<Card> m_hand;
public:
    Player(const int &n) : m_name(n) { m_hand.reserve(7); }
    void push_back(const Card &c) { m_hand.push_back(c); }
    Card removeHuman(int element) {
        Card passedCard = m_hand[element];
        swap(m_hand[element], m_hand[m_hand.size() - 1]);
        m_hand.pop_back();
        return passedCard;
    }
    Card removeBot() {
        //Card to be passed is whichever with the least suit occurrence
        Card passedCard;
        vector<int> suitCounter(4);
        for (int a = 0; a < m_hand.size(); ++a) {
            if (m_hand[a].m_suit == 'S') ++suitCounter[0];
            else if (m_hand[a].m_suit == 'C') ++suitCounter[1];
            else if (m_hand[a].m_suit == 'D') ++suitCounter[2];
            else if (m_hand[a].m_suit == 'H') ++suitCounter[3];
        }
        int minimum = 10; char suit = 10;
        for (int a = 0; a < suitCounter.size(); ++a) {
            if (suitCounter[a] != 0 && suitCounter[a] < minimum) {
                minimum = suitCounter[a];
                suit = a;
            }
        }
        switch (suit) {
            case 0:
                suit = 'S'; break;
            case 1:
                suit = 'C'; break;
            case 2:
                suit = 'D'; break;
            case 3:
                suit = 'H'; break;
            default:
                cout << "Error 1" << endl; break;
        }

        for (int a = 0; a < m_hand.size(); ++a) {
            if (m_hand[a].m_suit == suit) {
                passedCard = m_hand[a];
                swap(m_hand[a], m_hand[m_hand.size() - 1]);
                m_hand.pop_back();
                break;
            }
        }
        suitCounter.clear();
        return passedCard;
    }
    bool checkWin() {
        int suitCounter = 0; bool wins = false;
        for (int a = 0; a < m_hand.size(); ++a) {
            if (m_hand[a].m_suit == m_hand[0].m_suit) { ++suitCounter; }
        }
        if (suitCounter == 7) wins = true;
        return wins;
    }
    friend ostream &operator<<(ostream &, const Player &p);
};
ostream &operator<<(ostream &o, const Player &p) {
    for (int a = 0; a < p.m_hand.size(); ++a) { o << letters[a] << p.m_hand[a] << " "; }
    return o;
}
int main() {
    srand(time(0));
    vector<Card> deck; vector<int> winners;
    deck.reserve(52);
    int count = 0;

    //Assigning suits to values
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card('S', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card('D', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card('H', a)); }
    for (int a = 1; a <= 13; ++a) { deck.push_back(Card('C', a)); }
    //Shuffling deck
    random_shuffle(deck.begin(), deck.end());

    //Naming players 0-4
    vector<Player> players;
    for (int a = 0; a < 5; ++a) { players.push_back(Player(a)); }

    //Giving players 7 cards each
    for (int a = 0; a < players.size(); ++a) {
        for (int b = 0; b < 7; ++b) {
            Card c = deck.back();
            players[a].push_back(c);
            deck.pop_back();
        }
    }

    while (true) {
        char input;
        bool wins = false;
        //Checking winners
        for (int a = 0; a < players.size(); ++a) {
            wins = players[a].checkWin();
            if (wins) winners.push_back(a);
        }
        if (winners.size() > 0) break;
        else {
            while (true) {
                //Show player 0 hand
                cout << players[0] << endl;
                cout << "\nWhich one to replace? ";
                //Asks for input
                cin >> input;
                cout << "\n";
                //Cheating to show other player cards
                if (input == '?') {
                    for (int a = 1; a < players.size(); ++a) {
                        cout << "Player " << a << " " << players[a] << endl;
                    } //Error Check
                } else if (input == 'a' || input == 'b' || input == 'c' || input == 'd' || input == 'e' ||
                           input == 'f' || input == 'g')
                    break;
                else cout << "Wrong input! ";
            }
            //Game Process
            //Passes card and removes that card from hand
            Card passedCard = players[0].removeHuman(input - 'a');
            cout << "Hint: Player 0 passed " << passedCard << " to Player 1" << endl;
            for (int a = 1; a < players.size(); ++a) {
                players[a].push_back(passedCard);
                passedCard = players[a].removeBot();
                if (a == 4) cout << "Hint: Player " << a << " passed " << passedCard << " to Player 0" << endl;
                else cout << "Hint: Player " << a << " passed " << passedCard << " to Player " << a + 1 << endl;
            }
            players[0].push_back(passedCard);
            cout << "\n";
        }
    }

    //Shows who won
    for (int a = 0; a < winners.size(); ++a) {
        cout << "My Ship Sails! --- Player " << winners[a] << " won... " << endl;
    }
    cout << "\n[ Final Card Distributions ]" << endl;
    //Prints final cards for all players and ends game.
    for (int a = 0; a < players.size(); ++a) {
        cout << "Player " << a << " " << players[a] << endl;
    }
}
